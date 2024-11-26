# Movement

## Movement requirements

- Let us set up a few requirements on how movement should work for us so that it's easy to integrate FPS and 3PS

| Control  		 | FPS 				        | 3PS							                  |
|-------------|-----------------|-----------------------------|
| W				       | Walk forward		  | Walk forward					           |
| A				       | Walk left			    | Turn left + Walk forward		  |
| S				       | Walk backward		 | Turn back + Walk forward		  |
| D				       | Walk right			   | Turn right + Walk forward		 |
| Shift + W		 | Run forward		   | Run forward					            |
| Shift + A		 | Walk left			    | Turn left + Run forward		   |
| Shift + S		 | Walk right			   | Turn back + Run forward		   |
| Shift + D		 | Walk backward		 | Turn right + Run forward		  |
| Ctrl		      | Crouch toggle		 | Crouch toggle					          |
| Space			    | Jump				        | Jump							                 |

- `*` use `Ctrl` as a toggle for crouch instead of continuous press
- If running and then you press `Ctrl`, slide in direction of running (only one anim required as run is only one direction)
- If running and then you press `Space`, make a running jump in direction of running, else stop and do at-place jump (separate anims for left/right/back jump not required)

---

## Movement integration

- Create two new `Input Actions` for `MoveForward` and `MoveSideways` as `Axis 1D` values
  - Add them to the `Input Mapping Configuration`
  - For `MoveForward`, we give it `W` and `S` keyboard mappings with `S` having a `Negate` modifier
  - For `MoveSideways`, we give it `A` and `D` keyboard mappings with `A` having a `Negate` modifier
  - In `CharacterPlayerController` C++ class, add two new `UPROPERTY` fields for the new actions and add the binding functions for them
	- This time we bind on `Triggered` and `Completed`
	- We could have used `Started` to just track when it starts but when you keep both A and D pressed, it fails to emit an event
	- `Completed` signals end of event
	- `Triggered` fires multilpe time while event occurs and therefore it keeps track of it even if both are pressed
	- We do this because we want to track when the event stops and `Triggered` does not help us do that
	- `Completed` will send a value of zero
  - Both Movement actions are Axis 1D so take a `FInputAction` argument in the binding functions and cast it to `float`
    - it will send 1 for `W/D` and -1 for `A/S` and call the trigger binding functions
  
- For `MoveForward`, we create a method `SetMoveForward` on the pawn C++ class and call that with the value
  - Internally, it sets the `CurrentSpeed` of the pawn to a constant `Walk Speed` multiplied by the absolute directional value argument
  - We cannot depend on `CurrentSpeed` specifying direction as there are two axes involved
  - If `Completed`, its set to zero, otherwise it is `10` (current constant in class)
  - We also set a float `MovingForward` to specify if its moving forward (1 for W and -1 for S)
  - In Tick, we check if `CurrentSpeed > 0` and `MovingForward` is not zero
    - we get the Camera forward vector and reset its `Z` value to the skeletal mesh's overridden forward vector Z value
    - we do this so that any rotations to Camera while looking up/down doesn't make the movement in that vector and remains on the floor
    - then we do `SetActorLocation` by adding `CameraVector * CurrentSpeed * MovingForward` to current location
  - This is same for both FPS and 3PS
  
- For `MoveSideways`, we create a new method in the pawn C++ class too
	- For FPS, it doesn't change the forward vector and makes character go sideways
	  -	We set a float `MoveSideways` to specify if its moving sideways (1 for D and -1 for A), and other parts remain the same as for forward
	  - We use Camera right vector but reset its Z with the skeletal mesh's overridden forward vector Z value for same reason as for forward
	  -	We use `SetActorLocation` with New Location as `CurrentLocation + (RightVector * CurrentSpeed * MovingSideways)`
	- For 3PS, it makes the character turn sideways and then move forward
	  -	We get a reference of the `SkeletalMeshComponent` as we did for `CameraComponent`
      - We want to replace all occurrences of `GetActorForwardVector` and `GetActorRightVector` with `SkeletalMeshComponent->GetForwardVector` and `SkeletalMeshComponent->GetRightVector` respectively for now
	  - But because UE treats `X` as forward vector whereas we exported the mesh with `Y` as forward vector, the directions don't align for the pawn and the mesh
	  - So we create blueprint-overrideable functions for returning the forward and right vector of the skeletal mesh as aligned with the pawn
	  - In the C++ class, we return the exact vectors but in BP, we override them from `My Blueprint > Add > Override function`
	  - For forward, we sent the right vector and for right, we send the opposite of the forward vector (multiply by -1)
	  - Similarly, we will add it for RelativeRotation as well which needs `Yaw + 90`
	  - We calculate a turn angle which is the difference of rotations between camera and skeletal mesh (aligned with pawn)
		- Here, we first figure out the target rotation based on the key pressed and the current camera rotation
		- Then, calculate the turn angle and we normalize it in the range (-180, 180) to get rid of infinite rotations and stuttering artifacts
	  - We make the mesh slowly take deltaRotations towards the turn angle
	- The public method however works the same way and the difference is in how movement is processed per tick based on `isFPS`
	
---

## Controlling Anim BP on pawn

- We create a new protected method for setting speed as `SetAnimBlueprintSpeed`
- We add `UFUNCTION(BlueprintNativeEvent)` above it (this doesn't get autocomplete)
- `BlueprintNativeEvent` makes it overridable in the BP
  - Idea is every pawn may have its own Animation BP
  - So we allow overriding the method to control BP and call them from the movement control C++ methods
  - If the method returns a value, you can override it, otherwise you have to listen to the event in the main event graph and do the needful 
- Now, to provide an implementation for this method in C++, we need to implement `{methodName}_Implementation` instead of the actual method name
  - Here we set the `CurrentSpeed` to `WalkSpeed` if either of `MovingForward` or `MovingSideways` is non-zero
  - This basically gets called if the pawn doesn't override the method on its end
- Build this on live code and then in the pawn BP event graph
  - Override this method
  - Right click it and choose `Add Call to Parent Function` which internally sets the current speed
  - We can get the Animation BP Instance from the `Get Anim Instance` method with target as skeletal mesh component of the pawn
  - We check if its valid and if not, we set the instance to use our pawn's Animation BP `BP_MyCharacterAnim`
  - Then we set the `Speed` variable on the Animation BP with the value of the argument coming from `SetAnimBlueprintSpeed`

---

## Side walk animation integration

- Created walk sideways animation and imported from Blender
- Added it to vertical axis of idle-run blendspace
- Created new public variable on Animation blueprint so now there is `FrontSpeed` and `SideSpeed` instead of `Speed`
- In C++, created protected methods called `IsMovingForward` and `IsMovingSideways`
  - Internally, checks if `MovingForward` and `MovingSideways` is zero or not
  - This setup is only there for FPS
	- For MovingForward, always return true if not FPS
	- For MovingSideways, always return false if not FPS
	- This should not be controllable on the BP so we do it directly in C++ code
- Update `BP_MyCharacterPawn` `SetAnimBlueprintSpeed` method
  - If moving forward, set front-speed to speed
  - If not moving forward, set front-speed to zero
  - If moving sideways, set side-speed to speed
  - If not moving sideways, set side-speed to zero

---

## Run animation integration

- Created walk sideways animation and imported from Blender
- Added it to end of horizontal axis of idle-run blendspace
- Created a new `InputAction` for Run of type `boolean` and added it to the `InputMappingContext` with `Left Shift`
- In C++, added this new action to the `CharacterPlayerController`
  - Create a new method binded to Started and Completed of this new action, which would send true on keydown and false on keyup
  - This calls a method on the pawn to set a new private flag `WantsToRun` 
  - Update the `SetAnimBlueprintSpeed` base implementation
	- update conditions so that we run only if going ahead or going either side in 3PS
	- this automatically updates the speed send to the animation blueprint and thereby, the blendspace, so no updates required on Pawn BP or Anim BP
	- We set another flag to identify whether pawn is actually running called `IsActuallyRunning`
- This works well enough for FPS except for delays which are most probably due to performance issues and not code issues
- For 3PS though, turning from right to left looks super weird
  - So we add a `WalkTurnSpeed = 10` and a `RunTurnSpeed = 30` along with a getter `GetTurnSpeed` instead of just one `TurnSpeed`
  - Then all accesses to `TurnSpeed` are replaced by the getter
  - If `isActuallyRunning`, return `RunTurnSpeed` and else use `WalkTurnSpeed`, and that looks a lot more natural

---

## Jump animation integration

- Create `jump_start`, `jump_mid`, `jump_end` animations and imported from Blender
- Created a new `InputAction` for Jump of type `boolean` and added it to the `InputMappingContext` with `Space`
- In C++, added this new action to the `CharacterPlayerController`
    - Create a new method binded to Completed of this new action, which would send true on keyup
    - This calls a method on the pawn to set a new private flag `WantsToJump`
- In the Animation BP, we add 3 new states in the state machine by dragging from the `Idle/Run` state
  - Create a new Anim BP variable called `isInAir` of boolean type 
  - `Idle/Run` to `Jump_Start` transition happens if `isInAir` is true
  - `Jump_Start` to `Jump_Loop` transition happens when `GetRelevantAnimTimeRemaining(Jump_Start)` function returns a value lesser than 0.1
    - this is a predefined function which can be used to check how much of the current animation is done
  - `Jump_Loop` to `Jump_End` transition happens when `isInAir` is false (we use a not operator here)
  - `Jump_End` to `Idle/Run` transition happens when `GetRelevantAnimTimeRemaining(Jump_End)` function returns a value lesser than 0.1
- Things to do for integration
  - Trying to isolate `GetAnimBlueprintReference` as a method to get the anim BP instance [TODO]
    - Cannot override this for some reason so have to separately create it in each BP
  - Connect `WantsToJump` on `CharacterPawn` to `isInAir` on Anim BP
  - Need to set `isInAir` to false once character is specific height above ground for the end anim to work
    - else may need to reimport anims with no location data and control it all from code
  - Need to set `WantsToJump` as false once its back in `Idle/Run` state

---

## Improvements

- Integrate jump animations into movement
- Integrate crouch animations into movement
- Integrate slide animations into movement
- Integrate vault animations into movement

---

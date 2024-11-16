# Unreal Engine

## Learning Kit Project with C++

### Basic Details

- All C++ related blueprints that I started with are in `/Content/LearningKit_Games/Blueprints/MyClasses/`
- Added Nvidia DLSS 3 plugins to UE and enabled them for this project

### How to add a readme file

- Add the readme file from Windows explorer
- Go to Visual Studio and right click where you want to add it and do `Add Existing Item`
- Fill with content

### How to setup directory structure

- We will try to follow https://github.com/Allar/ue5-style-guide#2-content-directory-structure and take inspiration from it for C++ piece
- We will use the directory structure to specify the inheritance structure of the game
- Top level directories will be `Actor`, `ActorComponent` and `GameModeBase` for now
- All C++ classes that directly inherit from `Actor` will be top-level directories inside Actor with the cpp and h files inside this directory with same name as class
- Now if a class inherits from `Pawn` which in-turn inherits from `Actor`, we create a Pawn directory inside Actor and then create a directory inside Pawn for this class
- If there is a class that inherits from two classes in different directories, we have a few options:
	- Choose one or the other directory based on which context is more appropriate
	- Choose the closest common parent directory and create it there

Caveats:
- If you update directory structure from File Explorer, you have to right-click `.uproject` file and ask it to `Generate Visual Studio project files`
- Updating directory structure in File Explorer doesn't update Solution View structure in Visual Studio but generating project files from uproject does update it accordingly
- The `#include` statements will also change based on this so can use relative location using `../` or absolute location using `LearningKitProject/` where LearningKitProject is the project name
- `Build Solution` may fail after this but running directly with `Ctrl+F5` still may work so check that (it will open the engine)

---

### How to setup Live Coding

- Live Coding allows Unreal Editor to pick up on changes made in Visual Studio
- We can use it once we enable it in Unreal Editor
- Thereafter, every time we make a change to a C++ class in Visual Studio, we can press `Ctrl + Alt + F11` to rebuild on Live Coding
- This opens up a Live Coding console showing logs
- Sometimes, certain C++ classes do not show up in editor even if they exist, we can press `Ctrl + Alt + F11` and it should become visible

### How to debug in Unreal from Visual Studio

- Close UE5 editor go to Solution Explorer in Visual Studio
- Set the game project as default project (it will be bold if it already is)
- Set Visual Studio configuration to `DebugGame Editor` and `Win64`
- Rebuild the solution for the first time you do this for a project
- Next time onwards, press `F5` to start Debug (this starts the UE5 editor again with debug enabled, `Ctrl + F5` will start editor without debug enabled)
- Starting the game using `Alt + P` would trigger the breakpoint if this actor is in the world and if debug is enabled
- You cannot change the breakpoints during run again (we have to stop debugging and update the breakpoints)
- Press `Shift + F5` to stop debugging which will also close the editor
 
Alternatively, we can just log the variable values using UE_LOG and keep the editor open on the side (as the above is manual / complex)

---

### Create Blueprints out of C++ classes

- Right click on C++ class and choose "Create Blueprint from C++ class" and choose a name & location
- Open this blueprint and save it
- Now we can also drag meshes into the blueprint viewport to give it a visual represenation along with our C++ class features
- Compile and save, and then drag the blueprint into the level to see it work

Caveats:
- If you create a Blueprint from a class and then update the class like adding a new class variable etc, then the blueprint breaks
- It says that the blueprint has an invalid parent
- We can open the blueprint in editor and then go to file and choose Reparent Blueprint to the class
- You may have to go to the gear icon to specify `show internal classes` to see the C++ classes you created

---

### Create a manual timer using C++

- First we create a Timer class inherited from ActorComponent
- We give it properties and methods to set durations, start timer, check status etc
- Then we can create a TimerTest class inherited from Actor and give it a pointer to Timer
- In BeginPlay of TimerTest, we create a new instance of Timer and register it with UE
- In Tick, we check if timer is finished and log how long it took to finish, for 10 times

Caveats:
- Building from C++ often crashes the engine even if there are no errors
- Just restart and rebuild live coding from Visual Studio with `Ctrl + Alt = F11` and then play to check changes


### Create a C++ Game mode

- Inherit from GameModeBase like is done for `MyDestroyerGameMode`
- To use ThirdPersonCharacter pawn class, create a BP from this class and set the default pawn class to `BP_ThirdPersonCharacter`
- Remember to go to Project settings -> maps and modes -> default game mode and set it to use the BP game mode that you created
- We will later create a custom `GameModeBase` with a custom pawn class to go with it and have this game mode inherit from it
	- For this reason, we will delete the BP for this game mode with `BP_ThirdPersonCharacter`

### Create C++ pawns and player controllers

- We can create C++ classes inherited from Pawn and PlayerController
  - We will also create blueprints classes from these new C++ classes
  - These will be the `BP_MyCharacterPawn` and `BP_MyCharacterPlayerController`
  - In the pawn BP, we can drag in our custom character mesh and camera to give it visual representation
  - Camera and mesh should be siblings so that camera can move independently of mesh if required 
- For this demo, we also create the MouseInputGameModeBase class from the GameModeBase class which sets the default pawn and controller to our custom ones
- To set the defaults, we use `FOjbectFinder` like for `FloatingActor` and we can get the reference of the corresponding BP assets by:
	- finding them in UE5 content browser
	- Right click and choose `Copy Reference`
	- Paste in VSCode and append `_C` to the end inside the single quotes
	- Update `/Script/Engine.Blueprint` to `Class`

#### Processing mouse movement

- We can rotate our default pawn using `GetInputMouseDelta` and getting the deltaX and deltaY updates added to our current pawn rotation and setting it back
- At this point, we can see the pawn rotating but it also needs a camera to work as expected, which we can try to add to the Pawn BP
	- So we add a camera component to our BP and in C++, we attempt to get a reference of it using `UCameraComponent` & `FindComponentByClass<T>()`
	- Once we do, we can use the camera component's relative rotation getter and setter to rotate it accordingly
- We can update the base class of `MyDestroyerGameMode` to `AMouseInputGameModeBase` to get both functionalities
	- Also update default mode from Project settings back to `MyDestroyerGameMode` (we can delete the ThirdPersonGameMode we created based on this)
	- We delete it becase that BP declares `BP_ThirdPersonCharacter` as default pawn and overrides the default pawn settings we set in `AMouseInputGameModeBase`
- Camera rotation should have limits so that you cant go in circles
	- We set base rotation at begin play and compare it with dynamic rotation to decide if to apply more rotation
	- We use `RotationLimit` to decide the limits and keep it in the header file for easy configuration
	- We set up 2 methods, one for 3PS (third-person) and one for FPS (first-person)
	- For FPS, we apply deltaX to `PawnRotation.Yaw`
	- For 3PS, we apply deltaX to CameraRotation.Yaw and calculate its new relative location using `x = r*cos(rad)` & `y = r*sin(rad)`
	- We make r i.e `CameraRadius` and `RotationLimit` as blueprint editable properties
	- We also make an `IsFPS` property on the `CharacterPlayerController` to choose which rotation method to use
	- We can use `FMath::Clamp(value, min, max)` to apply the limits
- We can bind inputs to either the pawn by overriding `APawn::SetupPlayerInputComponent` or to player controller by overriding `APlayerController::SetupInputComponent`

#### Processing mouse input

- We can spawn a ball on left click and shoot it towards the front and change the type of ball on right click
	- To get muzzle location:
		- we get pawn's `GetActorLocation`
		- add `MuzzleOffsetHeight` to its Z component
		- use `GetClampedToMaxSize` which basically returns a vector in same direction but with specific magnitude
		- use `GetForwardVector` with the MuzzleOffsetForward as arg in the above method to get the muzzle location
		- `GetForwardVector` uses the pawn's `GetActorForwardVector` and it's camera component's `GetForwardVector().Z`
	- Then we spawn the bullet using `AddImpulse` on the forward vector along with a force magnitude
		- `AddForce` requires to be used every frame so `AddImpulse` seemed like the easier/better option
- Problem with the pawn spawning way above ground was solved
	- PlayerStart transform is at center of capsule at Z = 126
	- CharacterController and Pawn instantiate at Z = 126
	- The actual pawn asset however has transform at the base making it instantiate its base at Z = 126 instead of center
	- So we offset the actual pawn asset in the pawn BP and update the `MuzzleOffsetHeight` property in BP to match
- Migrate to Enhanced Input Actions from Action/Axis mappings for new characters as the latter is deprecated
	- Create a new folder called `EnhancedInputs` under `MyClasses`
	- Add new Input Actions and give the mousemove a `Vector 2D` type and shoot/change as `bool` type
	- Create a Input Context Mapping and add all the Input Actions to it with corresponding bindings
	- Go to UE5 Project Settings > Input > Default Classes and make sure it uses the enhanced versions
	- Open the uproject file in code and add `EnhancedInput` plugin enabled
	- Open the `<GameProject>.Build.cs` file and add `EnhancedInput` to PublicDependencyModuleNames
	- At this point, IDE may still not be able to pull the corresponding header files and show error
	- Regenerate build files from uproject file and then it should not throw that error on IDE
	- Follow https://nightails.com/2022/10/16/unreal-engine-enhanced-input-system-in-c/ to understand what is being done
	- In this project, we have used `CharacterController` and `Pawn` instead of `Character`
	- Don't forget to assign the Enhanced Input class references to `BP_MyCharacterPlayerController`
- To fix the root component warning in the log for placeables
	- we need to call `SetRootComponent` with the mesh as argument
- To jump out of game mode during game, we can press `F8`

---

### Art notes

- UE5 needs to `Enable Virtual Textures` from Settings to work with UDIMs
- Go to `Engine` > `Rendering` > `Virtual Textures`
- otherwise it loads all UDIMs as single file and only shows first one in preview
- Once enabled, engine restarts by compiling all shaders again which takes some time
- After restart, the preview will show all tiles
- We have to make sure that the imported files are now Virtual Textures
  	- Now all UDIMs are still single files but it will work correctly
- Look at the material created to see how to connect all the maps
  	- Load each map into a `Texture Sample` node in the material editor
  	- `Albedo` goes to the `Diffuse Albedo` pin of `Substrate Slab BSDF` node
  	- `Metalness` goes to the `F0` pin of `Substrate Slab BSDF` node
  	- `Roughness` goes to `Roughness` pin of `Substrate Slab BSDF` node
  	- `Normal` goes to `Normal` pin of `Substrate Slab BSDF` node
  	- `Displacement` goes to `World Position Offset` pin of the final material node
  	- `AO` goes into the `Ambient Occlusion` pin of the final material node
  	- The `Substrate Slab BSDF` node is pre-connected to the `Front Material` pin of the final material node
- All assets in `Content/LearningKit_Games/Assets/Characters/MyFirstCharacter`

---

### Input Integration UE5

- We open our `BP_MyCharacterPawn` blueprint and go to the `Event Graph`
- We can delete all other nodes apart from `Event Begin Play`
- Before anyhing else, we will go to `My Blueprint` panel on the right and click on the gear icon on the top of the panel
  - Check `Show inherited variables` to see all the variables inherited from parent classes
  - We may want to use some of those, especially `Pawn` class
- Now, UE suggests using one animation blueprint per skeleton
  - We may have multiple pawns with different skeletons but using our custom C++ pawn class
  - Each of those pawns will have a custom blueprint class inherited from our custom C++ pawn class as that is where the skeletal mesh of the pawn will go
  - Hence, there is a one-to-one mapping for the pawn blueprint class to the Animation Blueprint
  - Therefore, the C++ class should allow the BP to provide its custom Animation Blueprint
  - The C++ class should also handle updating the speed for the Animation Blueprint as it already handles other interactions
  - The Character Player Controller has the main input interactions so we should start the movement interaction there

---

### Additional docs

- `./move-req.md` for movement requirements and related integration details
- `./shoot-req.md` for shooting requirements and related integration details
- `./level-design.md` for level design related details

---

### Upgrades

- Upgrading to UE 5.4
  - Had to update the `LearningKitProjectEditorTarget.cs` file to `BuildSettingsVersion.V4` and `EngineIncludeOrderVersion.Unreal5_4`
  - Then since some plugins were not available in 5.4, had to go to `LearningKitProject.uproject` to set `Enabled: false`
  - One build failed but then it passed on redoing it
  - It was not identifying UE5 classes but regenerating project files from the `uproject` file fixed that too
- Upgrading to UE 5.5
  - Had to update the `LearningKitProjectEditorTarget.cs` file to `BuildSettingsVersion.V5` and `EngineIncludeOrderVersion.Unreal5_5`
  - Had to update string formatting in UE_LOG from `%s` to `%hs`
  - Run input action `IA_Run` didn't work with `ETriggerEvent::Started`
    - kept sending false all the time
    - changing it to `ETriggerEvent::Triggered` works but fires multiple times which shouldn't be required
    - only works when built through Rider and not if we start the editor directly
    - added question in UEForum so wait for answers if any

---

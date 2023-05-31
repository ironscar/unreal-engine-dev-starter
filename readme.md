# Learning Kit Project with C++

## How to add a readme file

- Add the readme file from Windows explorer
- Go to Visual Studio and right click where you want to add it and do `Add Existing Item`
- Fill with content

---

## How to setup Live Coding

- Live Coding allows Unreal Editor to pick up on changes made in Visual Studio
- We can use it once we enable it in Unreal Editor
- Thereafter, every time we make a change to a C++ class in Visual Studio, we can press `Ctrl + Alt + F11` to rebuild on Live Coding
- This opens up a Live Coding console showing logs
- Sometimes, certain C++ classes do not show up in editor even if they exist, we can press `Ctrl + Alt + F11` and it should become visible

## How to debug in Unreal from Visual Studio

- Close UE5 editor go to Solution Explorer in Visual Studio
- Set the game project as default project (it will be bold if it already is)
- Set Visual Studio configuration to DebugGame Editor and Win64
- Rebuild the solution for the first time you do this for a project
- Next time onwards, press F5 to start Debug (this starts the UE5 editor again with debug enabled, Ctrl + F5 will start editor without debug enabled)
- Starting the game using Alt + P would trigger the breakpoint if this actor is in the world and if debug is enabled
- You cannot change the breakpoints during run again (we have to stop debugging and update the breakpoints)
- Press Shift + F5 to stop debugging which will also close the editor
 
Alternatively, we can just log the variable values using UE_LOG and keep the editor open on the side (as the above is manual / complex)

---

## Create Blueprints out of C++ classes

- Right click on C++ class and choose "Create Blueprint from C++ class" and choose a name & location
- Open this blueprint and save it
- Now we can also drag meshes into the blueprint viewport to give it a visual represenation along with out C++ class features
- Compile and save, and then drag the blueprint into the level to see it work

Caveats:
- If you create a Blueprint from a class and then update the class like adding a new class variable etc, then the blueprint breaks
- It says that the blueprint has an invalid parent
- We can open the blueprint in editor and then go to file and choose Reparent Blueprint to the class (but I couldn't find the C++ class there)
- So I had to delete and recreate it

---

## Create a manual timer using C++

- First we create a Timer class inherited from ActorComponent
- We give it properties and methods to set durations, start timer, check status etc
- Then we can create a TimerTest class inherited from Actor and give it a pointer to Timer
- In BeginPlay of TimerTest, we create a new instance of Timer and register it with UE
- In Tick, we check if timer is finished and log how long it took to finish, for 10 times

Caveats:
- Building from C++ often crashes the engine even if there are no errors
- Just restart and rebuild live coding from Visual Studio with `Ctrl + Alt = F11` and then play to check changes

---

## Create a C++ Game mode

- Inherit from GameModeBase like is done for `MyDestroyerGameMode`
- To use ThirdPersonCharacter pawn class, create a BP from this class and set the default pawn class to `BP_ThirdPersonCharacter`

---

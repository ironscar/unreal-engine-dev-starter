# Animating Fundamentals

## How to begin (Blender)

### Fundamentals

- Tablet navigation controls covered in `rigging.md` for Blender
  - `Zoom` also works on the timeline panel
- Go to Pose mode of Armature by `Ctrl + Tab`
- Rotate the bones around to get the initial pose of the animation
- Select all bones with `A`, press `I` & select `Location Rotation` to insert a location + rotation keyframe
- You can see the associated keyframes in the `Dope Sheet` when bones are selected
  - Important to note that each bone has its own independent keyframe inserted now
  - So whenever you have to move where the keyframe is or delete it, select all bones first and then do the action
- Drag the marker in the `Dope Sheet` to the required time, change the pose and insert another keyframe with all bones selected
- Drag the marker between the two keyframes to see the model move
  - You can drag the keyframe to increase the time gap between two keyframes and it will interpolate accordingly
  - You need to work out the key poses and do this for every animation
- To edit a keyframe
  - take the marker to that keyframe
  - update the pose
  - insert the updated keyframe with all bones selected and it will overwrite the old one
- To add new animations and toggle between them
  - Click on the dropdown on the `Dope Sheet` panel with its name and select `Action Editor`
  - Do the above with all bones selected
  - In the top-middle of the panel, there will be options to add and delete new actions
  - Add a new action and double-click to edit its name
  - Go back to the `Dope Sheet` panel to work on that specific animation
  - We can add the `Action Editor` beside the `Dope Sheet` in the bottom panel to do this without having to switch between the dropdowns over and over again
  - Or you can just do everything in the `Action Editor` too as it also has a timeline & keyframes
- You can play animation with `Spacebar` and navigate the keyframes with `Up/Down arrow`
  - `Shift + Left/Right arrow` jumps to start/end of full animation

---

### Import animations from Blender to Unreal

- Name `Armature` to something else like `skeleton` as otherwise there may be scale issues in UE animation
  - This happens because of a bug in the FBX importer in UE
- Select armature and mesh and do `File > Export > FBX`
- Click `Selected objects` on the right menu of the popup
- Make sure `Forward` and `Up` axes are set correctly under `Transform`
- Under `Geometry`, uncheck `Apply modifiers`
- Under `Armature`, uncheck `Add Leaf Bones`
- Under `Bake Animation`, uncheck `NLA strips` and `Force Start/End Keying`
- Export after this
- In Unreal, click `Import` from Content browser
  - Currently in `MyFirstCharacter/Animations` directory
- Select the exported fbx
- Make sure that `Create Physics Asset` is checked as the animation asset becomes invisible without it
- Set `Material Import Method` to `Do not create material` if you already have material created on engine
- Then click `Import all` which imports the following assets
  - Skeleton 
  - Skeletal asset
  - An Animation Sequence for each Action created in Blender
  - Physics Asset (created by UE as we checked an option for it above)
- Open the `Skeletal mesh` asset and assign material if already created on UE
- From top-right of screen, we can see the `Skeleton`, `Skeletal mesh`, `Animation Sequence`, `Physics Asset` views
  - We can see all of them for our custom character in correct scale
  - In `Animation Sequence` view, we can select each of the sequences and see the animation for that character

---

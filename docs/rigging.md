# Rigging Fundamentals

## How to begin (Blender)

### Fundamentals

- Movement is with Middle mouse click & panning is holding Shift with the same
- Check that character model is positioned at (0,0,0) at foot center
- `Shift + A` will bring up the menu to place objects in scene
- Choose Armature and by default that should place a single bone where the cursor is at
    - Make sure to positionhead of armature object at (0,0,0) as well to align
- Currently the bone maybe hidden by the model because it is inside
    - For that, in the Object Properties on the right, go to `Viewport Display > Show > In Front`
    - You can also change what a bone looks like by going to the `Object Data Properties` on the right
    - Then, going to `Viewport Display > Display As` and select the preffered one (Stick for me)
- Moreover, armatures have three modes: Object, Edit, Pose
- `Tab` toggles between object and edit mode
- `Ctrl + Tab` toggles between object and pose mode
- Placing bones is easier in Orthographic mode so `Numpad 1, Numpad 3, Numpad 7` give you the front, side, top views (adding `Ctrl` to it gives the mirror view)
- To change the name of a bone, go to Bone Properties on the right and update the name
- Pressing `G` puts object/bone in move mode and then pressing `X,Y,Z` constrains the movement to that axis
    - You can do this with the entire bone or the ends of the bone in Edit mode by separately selecting it
    - This will allow you to scale the bone accordingly or move its ends
    - Right Click during move mode cancels the movement
- You can see the armatures of UE5 assets by checking the skeletal assets and try to understand them
- In case you want to add a bone in the middle of an existing armature
    - Go to Edit mode of the armature
    - Press `Shift + A` to add a new bone
    - Position the new bone and affected bones correctly
    - Go to Bone Properties on the right and go to `Relations > Parent`
    - Update the parents of required bones to get the correct hierarchy and check `Connected`
    - Sometimes clicking the connection points in this case won't allow movement
    - In that case, drag-select the connection point and then it will work
    - Update the names if required in convention `boneName_index_l/r`

---

### Creating an Armature

- To start creating a full Armature, we need to go to edit mode of the Armature
- Then we can move the base bone as we need to start as discussed before
- To create the next bone, we select the thin end of the bone and extrude (E)
    - This puts the next bone in move mode so we can constrain the movement by axis and place it correctly
    - Doing the placements in the appropriate orthographic view makes it easier to judge the positions
- We repeat this until we have one side of the bones
    - Then we can Mirror the bones to the other side if its a symmetric model by 
        - drag select one side of the bones only
        - use Shift click to select the bones connected to the central ones in case they didn't get selected before
        - `Right click > Symmetrize`
        - This will also update the names to have `_r` from `_l` 
        - The positions of the entire selection can be off sometimes so fix that while all are still selected
        - Then select the bones connected to the central ones and check `Connected` in `Bone Properties > Relations`
    - If asymmetric, then we will have to create the bones ourselves

---

### Tablet Navigation Fundamentals

- For weight paint mode, it might make sense to do with a tablet
- Like Quixel, we need custom express keys for easier navigation
  - Middle Click
  - Shift + Middle click
  - Zoom
  - Ctrl
- `Middle Click` and hover/move allows moving the camera
- `Shift + Middle click` and hover/move allows panning
- `Zoom` and touch/move pen allows zooming
- `Ctrl + click` helps to select a bone
- `Shift + C` resets view to see the whole model
- Tablet pressure for weights doesn't seem to work by default
  - But you can set `Weight` to 1 and `Strength` to 1
  - Then click the small button beside `Strength` bar which enables painting by pressure
  - But on places where you have already painted red, it doesn't change anything
  - You can try changing blend to `Subtract` at that point to remove from it

---

### Weight Painting

- To start weight painting
    - Select the model in object mode and add an Armature modifier to it
    - Add the Armature object to the modifier
    - Deselect the model, select the armature and `Shift + Left Click` to select the model in object mode
    - Then go to weight paint mode while both are selected (model should be selected second)
    - By default, one bone will be selected and you can paint the weights for that bone
    - You can select other bones using `Ctrl + Left Click` and weight paint for those too
- In left sidebar, in `Active Tools and Workspace settings`, you can turn on symmetry as well
  - The rest of the brush settings like weight, radius and strength are also there
    - These three can also be accessed on right click or on the top toolbar
    - Pressing `F` changes size of brush
- Painting with weight 1 makes it red implying most deformation and weight 0 is blue implying no deformation
  - Green is 0.5 and implies partial deformation
  - You can paint blue on red or green or red, final color is what matters
- Idea is to do this weight paint on the model for each bone so that during animation, its deformation can be controlled
- In `Object Data Properties`, whenever you paint for a new bone, it creates a new vertex group with the bone's name
    - Once created, you can also select the vertex groups from here and do the painting from where you left off
- Once done, you can go to Pose mode of the Armature and rotate the bones to see how they move the model
  - You can actually rotate the bones even in weight paint mode to see how the current distribution works
  - You can also do this to reach and paint the places which you cannot paint due to close surfaces
- If you paint one bone on the left and want to mirror it to the other side
  - Go to `Object Data Properties` on the right side-menu, select the specific vertex group
  - Click on the dark down-chevron on the right of the vertex groups sub-menu
  - Do `Copy Vertex Group` followed by `Mirror Vertex Group`
  - Then update the name of vertex group by replacing `_r` with `_l` or vice versa
  - This will assign it to the corresponding bone on the other side with copied group
  - It mostly works but could need small tweaks (still saves more time than repainting)

---

### Caveats

- Sometime it matters where your bone is positioned and not just what its weights are
  - Based on where its positioned and how you rotate it, the weighted area of the mesh moves around that focal point
  - If that focal point is closer to a large part of the mesh, the mesh attempts to rotate around that point and may get overly curved (Its a matter of radius of rotation orbit)
  - In those cases, we may have to position the bone further away to get it to rotate the right way (greater radius allows lesser mesh curvature)
  - Sometimes these bones are connected to other bones
    - So specifically disconnect them from the `Object Data Properties` right side-menu
    - Deselect the bone and select again at this point as otherwise it may act connected still (weird issue)
    - Then move the bone to an approprate position allowing larger radius

- Sometimes while testing out your bone weight-painting, you won't be able to keep track of getting the bones back in original orientations
  - In that case, Pose mode has a `Clear Pose Rotation` shortcut set to `Alt + R`
  - Due to various reasons (including but not limited to Nvidia GeForce Experience), this shortcut may not work
  - Go to `Edit > Preferences > Keymap` and search by name `Rotation`
  - Update the shortcut for `Clear Pose Rotation` to `Shift + Alt + R`
  - While painting, if you have to get everything back to default
    - like when you have to mirror bone weights and you need the model to be symmetric again
  - Select all bones with `A` and press `Shift + Alt + R` to reset rotations for all
  - For resetting location, `Alt + G` works

---

### Todos

- Figure out why Maya has all those extra shapes and stuff on rigged models
- Figure out when and how to use shape keys / morph targets
- Figure out when and how to use Inverse Kinematics
- Rig a normal human body with perfect range of motion (not face)
- Rig a normal human face with perfect range of motion
- Rig a quadruped
- Rig a flying bird
- Pick a crazy movement monster from ArtStation and rig it

---

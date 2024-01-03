# Rigging Fundamentals

## How to begin (Blender)

### Fundamentals

- Movement is with Middle mouse click & panning is holding Shift with the same
- Check that character model is positioned at (0,0,0) at foot center
- Shift + A will bring up the menu to place objects in scene
- Choose Armature and by default that should place a single bone where the cursor is at
    - Make sure to positionhead of armature object at (0,0,0) as well to align
- Currently the bone maybe hidden by the model because it is inside
    - For that, in the Object Properties on the right, go to Viewport Display > Show > In Front
    - You can also change what a bone looks like by going to the Object Data Properties on the right
    - Then, going to Viewport Display > Display As and select the preffered one (Stick for me)
- Moreover, armatures have three modes: Object, Edit, Pose
- Tab toggles between object and edit mode
- Ctrl + Tab toggles between object and pose mode
- Placing bones is easier in Orthographic mode so Numpad 1, Numpad 3, Numpad 7 give you the front, side, top views
- To change the name of a bone, go to Bone Properties on the right and update the name
- Pressing G puts object/bone in move mode and then pressing X,Y,Z constrains the movement to that axis
    - You can do this with the entire bone or the ends of the bone in Edit mode by separately selecting it
    - This will allow you to scale the bone accordingly or move its ends
    - Right Click during move mode cancels the movement
- You can see the armatures of UE5 assets by checking the skeletal assets and try to understand them
- In case you want to add a bone in the middle of an existing armature
    - Go to Edit mode of the armature
    - Press Shift + A to add a new bone
    - Position the new bone and affected bones correctly
    - Go to Bone Properties on the right and go to Relations > Parent
    - Update the parents of required bones to get the correct hierarchy and check Connected
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
        - right click > Symmetrize
        - This will also update the names to have `_r` from `_l` 
        - The positions of the entire selection can be off sometimes so fix that while all are still selected
        - Then select the bones connected to the central ones and check Connected in Bone Properties > Relations
    - If asymmetric, then we will have to create the bones ourselves

---

### Weight Painting

- 

---

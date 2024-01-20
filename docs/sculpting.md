# Sculpting Fundamentals

## How to Begin (ZBrush)

### Fundamentals

- Pressing `,` to close lightbox and `Tab` to go into zen mode
- Movement is with just touch pen outside the model and panning is holding `Alt` with the same
- Zoom is when you release `Alt` after dragging with mouse a little bit
- Snapping to a particular axis is done by pressing `Shift` for a moment while moving
- `Preferences > CamView > Next` to change the cam view on the top right that shows orientation
- `Preferences > Config > Enable Customize` to start customizing UI
  - We can drag menus to sidebars by hovering on the circular icon on the top left of the menu flyout and dragging it to a sidebar
  - We can create a quick brushes menu by selecting the actual brush and then doing a `Ctrl + Alt + Click drag` the specified brush from the menu to the bar
- Masking is done with `Ctrl`
  - Painting on model with `Ctrl` will mask the model
  - Clicking on model with `Ctrl` will make the boundaries of the mask smoother
  - Painting on model with `Ctrl + Alt` will invert mask where you paint
  - Clicking on model with `Ctrl + Alt` will make the boundaries of the mask starker
  - Clicking outside model with `Ctrl` will invert mask on full model
  - Dragging outside model with `Ctrl` will clear mask
  - Dragging on model with `Ctrl` will mask the parts of the model covered in drag selection
  - Different mask brushes include `Mask Lasso` and `Mask Pen`
- Selecting is done with `Ctrl + Shift`
  - `Ctrl + Shift + Click drag` on model hides the parts which weren't in the drag selection
  - `Ctrl + Shift + Click drag` outside model inverts the visible/hidden parts
  - `Ctrl + Shift + Click` outside model makes the full model visible
  - Different mask brushes include `Select Lasso` and `Select Rect`
- Selecting brushes can be done with `B` followed by a shorthand of the brush
  - The brush menu filters based on the letters types
  - `Clay Buildup` brush is accessed by `BCB` in sequence
  - Holding `Alt` while painting with a sculpting brush will invert its action (additive <-> subtractive)
  - Pressing `S` and adjusting the slider helps in changing size of brush
  - Pressing `U` and adjusting the slider helps in changing intensity of brush
  - Pressing `Shift` while painting selects `Smooth` brush which has a different intensity from the selected brush
- All the above select & mask operations work on the selected `subtool` (model)
- `Shift + F` to toggle pollyframe view and `Sihft + P` to toggle floor
- `Transform > Activate Symmetry > X` to turn on symmetry on X axis
- Pressing `Q (Draw), W (Move), E (Scale), R(Rotate)` to select modes
  - The final 3 use the gizmo
  - Holding `Alt` can unlock the gizmo to reposition it, like when we need to change the pivot for rotation
- Sometimes when two surfaces are two close and both are visible, brushes affect both surfaces
  - In these cases, we can turn on `Brush > Auto Masking > BackfaceMask` to avoid that
  - This setting is done at a brush-level
  - You may want the opposite effect sometimes at which point you should turn this off
- At the very top of the tool menu, it shows a number of tools
  - You can click on them to open them up in a new viewport
  - To jump back to the main viewport, find the entry which has your main viewport
  - If your main viewport has multiple subtools, the entry will show up with a number on the top right

---

### Tool menu

- `Subtools` are a way of adding another part to the model and sculpt on it
  - `Tool > Subtool > Append` or `Tool > Subtool > Insert` can be used to append/insert a new subtool
  - You can select a subtool by `Alt + Click` on it
  - All select & mask operations work on the selected subtool
  - You can toggle visibility of the subtool by clicking the eye icon of the subtool
- `Geometry` menu provides ways of working with geometry
  - `Ctrl + D` or clicking on `Tool > Geometry > Divide` will subdivide the mesh
    - `D` is `Tool > Geometry > Higher Res` and `Shift + D` is `Tool > Geometry > Lower Res`
  - `Dynamesh` is a handy mechanism that allows retopologizing the model based on recent updates
    - You can mark a mesh as Dynamesh and set a resolution for it
    - Then while sculpting, if the topology becomes too stretched, do a `Ctrl + Click drag` outside the model
    - If the model was unmasked before, it will retopologize the model to have uniform topology
  - Generally use `Dynamesh` to get the basic shape and then start `Subdivision`
  - `Polygroups` are a way to group different parts of a single subtool in a group
    - You can create them a bunch of ways visible in `Tool > Geometry > Polygroups`
    - They will be visible in the Polyframe view `Shift + F`
    - Most common is you mask an area and press `Ctrl + W`
    - Handy part is if you `Ctrl + Shift + Click` on a polygroup, it will hide all other polygroups
    - Smart use of polygroups can make sculpting easier in tight areas

---

### Handy brushes

- `Standard (BST)` is the standard brush in ZBrush which gives a soft buildup
- `Move (BMV)` is used to move parts of the mesh under its area of influence
- `HPolish (BHP)` is used to give a polished feel to the mesh and is commonly used in hard-surface modelling
- `Pinch (BPI)` is used to pinch two areas of the mesh together in direction of paint
- `Flatten (BFA)` is used to flatten parts of the mesh
- `Inflate (BIN)` is used to inflate parts of the mesh
- `Clay Buildup (BCB)` is used to buildup the mesh in a more blocky manner and is commonly used in organic sculpting
- `Dam Standard (BDS)` is good for grooves/seams and is subtractive by default

---

### ZSpheres

- `ZSpheres` are used for two main things:
  - Quickly building up shapes with volumes
  - Retopologizing models

- Building shapes
  - We can add a ZSphere by inserting a new ZSphere subtool
  - Here `Move, Scale and Rotate` don't show a gizmo so you have to `Click drag` on the specific ZSphere in that mode
  - `Draw` allows you to extrude another ZSphere out of the current one to build up the shape
  - `Click` to select a specific ZSphere to extrude from it or move/scale/rotate it
  - Going to `Geometry > Adaptive Skin > Preview` can toggle the preview of what it would like as a mesh
  - You can also do `Geometry > Adaptive Skin > Make Adaptive Skin` to generate the skin
  - You can then append the skin as a subtool as it would show up in the menu when you click `Insert` in subtool menu

- Retopolizing models
  - We can add a ZSphere by inserting a new ZSphere subtool
  - Then make sure that it is completely inside the model
  - Go to `Geometry > Topology > Edit Topology` to start creating the new topology
  - You may have to the above every time there is an auto-save as it deselects after save
  - Then go into Draw mode and click on the model to create a new vertex
  - Clicking again at a different place on the model will create another vertex connected to the first one so we made an edge
  - If you want to create a vertex not connected to the currently selected vertex, deselect it by `Ctrl + Shift + Click` on the model or simply clicking outside the model
  - You can remove vertices and its connected edges by `Alt + Click` on it
  - Repeat the `Adaptive Skin` steps but do so with `Dynamesh Resolution` set to zero and `Density` set to one
    - This will make sure its the exact same number of vertices
    - To give `Subdivision` levels to the skin subtool, you can update `Density`
    - To enable `Dynamesh` on the skin subtool, you can update `Dynamesh Resolution`
  - You can then export the tool from the top options of the `Tool` menu to take it to different software as an `OBJ` file
    - The subdivision levels don't get carried through so export it at the correct level

---

### Todos

- Sculpt the human body accurately (blur face and perfect body)
- Sculpt the human body with imperfections (wrinkles and fat)
- Sculpt the human face accurately (perfect face)
- Sculpt the human face with imperfections (wrinkles and fat)
- Sculpt hair and create hair cards for it
- One proper organic sculpt (from ArtStation including retopology look & polycount)
- One proper hard-surface sculpt (from ArtStation including retopology look & polycount)

---

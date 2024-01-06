# UV Unwrapping & UDIM Fundamentals

## How to Begin (Blender)

### Fundamentals

- Movement is with `Middle Mouse Button` and use `Shift` along with it to pan
- Zooming can be done by `scrolling` or `Ctrl + Shift + Middle Click drag`
- Go to `UV Editing` mode from the top menu bar
- Go to Edit mode of model in 3D viewport by clicking `Tab`
- Go to edge mode in 3D viewport and select all edges that should not be connected in UV map
  - `Right click` and select `Mark Seam`
  - You can also `Clear Seam` in the same way as an option right below it
- Select all faces by `A` in 3D viewport, click `U` and select unwrap
- UV viewport has `vertex/edge/face/island` mode selection independent of 3D viewport
- The seams define what kinds of UV islands will be formed
  - Planning the seams is important for the same
  - You can then move/rotate/scale the islands on to the UV map for optimal space
  - The more space they cover on the map, the better its texture resolution will be
- Once done unwrapping, we can export it as an `FBX`

---

### UDIM Workflow

- Go to UV viewport, toggle sidebar with `N`
- Click `+ New` in the top-middle of the UV Editing screen
  - Give it a name and update size of tile if you want
  - Select `Color` and drag `Apha` to zero
  - Set `Generated Type` to `Blank` and check `Tiled`
- Go to sidebar `Image` > `UDIM Tiles` and click `+` and again repeat the settings
- This way, you can keep adding more UDIM tiles
- Then you can drag parts of your unwrap into separate tiles

---

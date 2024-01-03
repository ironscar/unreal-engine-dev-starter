# UV Unwrapping & UDIM Fundamentals

## How to Begin (Blender)

### Fundamentals

- Movement is with `Middle Mouse Button` and use `Shift` along with it to pan
- Zooming can be done by `scrolling`
- Go to `UV Editing` mode from the top menu bar
- Go to Edit mode of model in 3D viewport by clicking `Tab`
- Go to edge mode and select all edges that should not be connected in UV map
  - `Right click` and select `Mark Seam`
  - You can also `Clear Seam` in the same way as an option right below it
- Select all faces by `A`, click `U` and select unwrap
- To create UDIM tiles In Blender 
  - Go to UV mode, toggle sidebar with `N`
  - Click `+ New` in the top-middle of the UV Editing screen
    - Give it a name and update size of tile if you want
    - Select `Color` and drag `Apha` to zero
    - Set `Generated Type` to `Blank` and check `Tiled`
  - Go to sidebar `Image` > `UDIM Tiles` and click `+` and again repeat the settings
  - Then you can drag parts of your unwrap into separate tile

---

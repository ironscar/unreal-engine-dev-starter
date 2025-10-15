# Level design docs

## General flow

- First, we go into `Landscape mode` with `Shift+2` and create a landscape
- Second, plan the layout of the level and set it up with `Starter content` assets:
  - wall panels for walls
  - floor panels for ceilings
  - pillars for pillars
  - keep the main character on scene to have a size comparison at all times
- Third, look into `Megascans/Fab` for wall textures/materials to use and add some variety
- Use corresponding textures/materials for the pillars
- Find decal materials to put on walls as damaging or graffiti etc
- Put a ground material of some sort on the landscape
- Put a ceiling material of some sort on the ceilings adding some variation in it
- Fourth, start adding assets to the scene from larger to smaller
- Fifth, add foliage to the landscape if relevant with the foliage tool 
- Sixth, add foliage in other places if relevant which cannot be done with foliage tool
- Last, try out a few different lighting scenarios to see what looks best and match camera settings to it

---

## Considerations

- Engine scalability settings affect lighting greatly
  - `Global Illumination` and `Shadows` should be at least `High`
  - Other can stay at `Medium` for low-end hardware
- Convert all foliage to `Nanite` for performance reasons
- Think about color balance in a scene
- Avoid repetition to achieve natural randomness
- Think about gameplay practicality when designing spaces like cover and visibility
- Keep in mind that it's a 3D space so often a player can see both front and back of something
  - decals look completely black on the opposite surface if its volume is thicker than surface
  - natural assets are often pushed into walls to achieve variation but need to make sure it works on both sides
- Actively attempt to hide any visible seams on surfaces with assets or decals

---

## Caveats

- Enabling `Hardware Raytracing` can be done from `Project Settings > Engine > Rendering`
- `Megalights` can only work with `Hardware Raytracing` enabled
- Hardware Raytracing makes things much darker
- We can adjust intensity of lights to some degree to address this
- Additionally, we can also change the exposure settings of the camera
  - the default editor camera settings are also in `Project Settings > Engine > Rendering`
  - Exposure can take `Auto-exposure Histogram`, `Auto-exposure Basic` and `Manual`
  - The auto-exposure is what makes scenes darker when you go to a corner and brighter otherwise
  - Manual exposure keeps it more or less consistent (dark corners aren't too dark)
- Having some `ExponentialHeightFog` can help create light shafts
  - we can enable `Bloom` on directional light `Light Shafts` menu
  - we can change `Bloom` intensity from camera settings to look more visually stunning
- Increasing `SourceAngle` of a directional light makes shadows softer
- You can cycle between different directional lights by toggling the `Affects World` setting
  - The outliner visibility doesn't control in-game visibility so the above is more generic

---

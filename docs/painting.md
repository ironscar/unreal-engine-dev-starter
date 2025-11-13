# Painting Fundamentals

## Brush settings (Photoshop)

### Brush tip settings

- By default, the left button `Brush tip shape` is enabled
  - We can choose various brush alphas that are already available
  - We can adjust size (shortcut - `[` and `]`)
  - We can adjust angle of how the alpha is applied (shortcut - `Shift + left/right arrow`)
  - We can adjust roundness of the alpha
    - if the original alpha is set in a circle, it is roundness 100%
    - we can basically squash the alpha to fit it in a thinner ellipse
  - We can adjust hardness which specifies how hard the edges of the alpha are
    - this can only be for certain alphas and not all
  - We can adjust spacing of the alphas
    - when you drag the brush, the alpha is drawn repeatedly with some spacing
    - more the spacing, more distant and clearly the individual alphas are visible

### Advanced brush settings

- There are a bunch of checkboxes on the left below the `Brush tip shape` button
- By default, only `Smoothing` is enabled for hard-round
  - In addition, `Transfer` is enabled for soft-round-pressure-opacity
- From `Shape Dynamics` to `Brush pose` have additional settings
- From `Noise` to `Protect texture` are just the checkbox

### Adding brush presets

- Make something on a canvas in monochrome (in black for 100%)
- Select it with marqee or lasso and choose `Define brush preset` in `Edit` menu at top
- Then we can use this an alpha and apply the above adjustments for a new brush

### Saving custom brushes

- All changes are remembered until the same brush is used
  - If you change the brush, the adjustments are not applied
  - Eraser is not treated as a changed brush so coming back from eraser mode remembers changes
- To save adjustments as a new brush, we need to click the `[+]` button at the bottom-right

---

## Layer types

- `Multiply` is useful when we want everything to get darker by the same amount, such as for shadows
- `Exclusion` is useful for blending things in a specific way, so far only been handy for blending paint into skin

---

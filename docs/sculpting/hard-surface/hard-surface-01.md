# Hard Surface Modeling in ZBrush 1

This doc is the starting point for Hard Surface modeling in ZBrush

## Breastplate Armor cleanup

### References

- https://www.youtube.com/watch?v=Mk909y967EI (completed)

### Steps

- Starting with a more or less organic sculpt of what the Breastplate armor looks like
- First, we mask the different pieces that we want to extract
  - `Alt + Ctrl + Click` on the model to make the masking edges more crisp and less smooth
  - Clean up the edges as much as possible using mask and unmask
  - Then go to `Tool > Subtool > Extract` and make a `Double` extraction of `thickness = 0` (make sure to click accept after the fact)
    - its going to look like it just has one side still (for now we will continue as is while following the reference tutorial)
    - this is done because doing the `Select Lasso` technique below on a thick mesh behaves wierdly and hides the sides of the mesh as well (that will eventually get deleted)

- Second, we want to clean up the edges of the extracted subtool further
  - We use the `Select Lasso` brush which is activated by `Ctrl + Shift`
  - Holding `Alt + Ctrl + Shift`, we can drag the lasso over the edges to hide the unrequired parts
    - this will lead some jagged edges and that is okay, we will clean that up later
  - Once all are successfully hidden, we can go to `Tool > Geometry > Modify Topology` and click `Del Hidden` to delete those hidden parts

- Third, we can clean up the edges further
  - Go to `Tool > Deformation` and drag on `Polish` slider to make the jagged edges from before smoother

- Fourth, we are going to use `Tool > Geometry > ZRemesher` and click on `ZRemesher` with `Target Polygon Count = 5` (default) to get a cleaner topology
  - we can check topology at many point using `Shift + F`
  - we are going to want to go even lower resolution though, so we remesh twice with `Half` selected (this will make the topology even cleaner)
  - then we will use the `Move` brush to move the individual vertices now (as its fairly low resolution now) to fix the edges further
    - remember we have symmetry on so we dont have to do both sides
  - at this stage as well, if we see any weird extra polygons, we can use the `Select Lasso` technique above to hide it and delete it
    - covering some part of a polygon will hide the entire polygon and delete it when we click the delete button

- Fifth, we add thickness now
  - Go to `Tool > Geometry > Dynamic Subdiv`, click on `Dynamic` to enable it
  - Slide `SmoothSubdiv = 0` and add `Thickness` until you get the thickness you want
  - Then, slide `offset` to negative as we picked the mask from the front in the base model so the other side must be on the inside and therefore be pulled in (default is pulled out)
  - Once we are happy with it, click `Apply`
  - Then we enable dynamic subdivision again and this time, we set `Thickness = 0` and move the `SmoothSubdiv = 3` (this makes things look a little rounded at the edges)
  - To fix the smooth edges and make them sharp again, we can use the `ZModeler` brush
  - Hover on an edge and hold `Spacebar` to select `Insert` and then `Single Edge Loop` (default) to insert an edge loop (this inserts an edge loop across that entire space but doesn't change the smoothness as such)
  - Then hover on one edge of the new loop and hold `Spacebar` to select `Slide` and `Edge Loop Complete`, and then move the edge to the side that needs to be sharp (this pushes the edge out and makes it sharp)
    - we can repeat this for the inside and the outside edges if required
  - Finally, we smooth out the plane surfaces so that there are no bumps and then we can hit `Apply` again to get a clean sharp shape (Toggle topology with `Shift + F` to see hot it has changed)

- We can apply these techniques to continuously extrude and get the shapes that we want with clean edges
- This way we can create clean looking panels from a fairly organic shape

### Boolean Operations

- To create holes at the bottom of the armour piece which is currently closed, we decided to use boolean operations
- So first, we append a sphere subtool and select the `subtract` icon (3rd icon from the left on the subtool top line)
- Then enable `Live Boolean` at the top beside `Edit` to see how that looks
  - we can scale/translate the sphere however we want
- Once ready, we hide all other subtools except the one that we want to create a hole in and the one creating the hole (the sphere)
- Then we select `Tool > Subtool > Boolean > Make Boolean Mesh` which will take a little time and create a new tool
- Then click `Append` in the subtool menu to find something called `UMesh_*` which looks something like your final shape and select that
  - after this we can delete the old tool and the sphere, and see the new tool with a hole in it
- Finally, turn off `Live Boolean`
- We can also do other boolean operations such as:
  - `Union`: second icon from left (default)
  - `Intersection`: fourth icon from left
- At higher subdivisions, this can help create rather clean shapes easily than manually sculpting that detail

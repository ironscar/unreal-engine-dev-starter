# Texturing Fundamentals

## How to begin (Quixel Mixer)

### Setup Fundamentals

- Quixel Mixer is not very mature and hence has a lot of weird behaviors
- It does allow direct access to Megascans so its handy in that respect
- To import model into Mixer
  - Go to `Setup` on the right
  - Select `Type` as `Custom Model` and navigate to the FBX file you export
  - Select `Texture Sets` as `From UDIMs` if not already selected
  - Set `Texture Resolutions` as `2048px` as its a good resolution to work at
  - Low resolutions are faster to work with but can look bad
  - High resolutionss are slower but have better visual quality
  - The texture resolution can be changed while working
- For additional performance tweaking, you can go to the `Performance` tab on the right
- Let's set the export settings right away
  - Set `Export Target` as `Custom`
  - Set `Export Location` to where you want your textures to be exported
  - Specify an `Asset Name` which will be used in naming the exported textures
  - Select the required `Texture Maps` which for now will be
    - Albedo, Roughness, Normal, Displacement, AO, Metalness
  - Each UDIM is created as a separate `Texture Set` so select all
- The `Display` tab on the right lets you configure the lighting and environment
  - You can also choose the `HDR map` used from a dropdown on the top-right of the 3D viewport
  - You can choose to view a specific map or the combination `PBR Metalness/PBR Specular` from a dropdown on the left
- Finally, in the `Layers` tab on the right, we can select `Texture Target Sets`
  - These also depend on the UDIMs and we want to select all so that we can paint across them
  - Under this layer set, we can now start creating texture layers

---

### Tablet Navigation Fundamentals

- Wacom tablets provide `Express keys` and my current model has 4
- The four keys are mapped as
  - Pan/Scroll
  - Alt
  - Middle Mouse click
  - Shift + Right click
- Holding `Alt` on the keyboard or tablet and dragging the pen around will move the camera around
- Holding the express key for `Middle Mouse click` and moving the pen on the tablet while hovering will pan
- Rotating the environment is a bit more of a hack
  - You first have to paint on a layer at least once, else the express key won't work
  - Maybe undo that if you did it just to be able to use it
  - Then pressing the express key and hover-moving the pen over the tablet will rotate the environment
  - You can also do this the long way in `Display > Lighting > Lighting Rotation`
- `Window mapping` also doesn't seem to work properly for Mixer

---

### Types of Texture Maps

- `Albedo` is the base color
- `Roughness` specifies how rough the surface is, in grayscale, where zero means shiny and one means matte
- `Displacement` specifies some height information on the surface in grayscale (doesn't work well in Mixer)
- `Normal` specifies some height information on the surface in RGB (generally in a blue-purple tone)
- `Emission` specifies where the surface emits light (doesn't seem to work in Mixer but maybe I used it wrong)
- `Metalness` specifies how metallic a surface is, in grayscale, where metal is black and plastic is white
- `AO` is ambient occlusion and specifies the amount of light that reaches parts of the surface, in grayscale
- `Opacity` specifies how opaque the surface is where zero implies trasparent and one implies opaque
- Mixer seems to allow painting only across Albedo, Metalness, Roughness, Emission and Displacement
- There are many other kinds of texture maps in 3D texturing in general (but haven't tried them all)

---

### Painting Fundamentals

- A `Paint Layer` is the basic layer that let's you paint across Albedo, Metalness, Roughness, Emission & Displacement
- You can choose which all to paint acorss and what values to use in the `Set Colors` menu on the left
  - The checkbox specifies if you are painting on that map
  - The circle specifies the color and you can click it to choose the color
  - For the grayscale maps, you can also use the slider
  - Displacement alone seems to take a number input and you can specify if its additive/subtractive below it
- You can also configure other things about the brush in the left menu when a paint layer is selected
  - `Brush presets` allows choosing an alpha to paint with, but I only used the `Brush Soft` Preset
    - didn't see an option to use new presets either which are custom-made
  - `Brush setting` allows changing size, angle, spacing, opacity and flow
  - `Brush shape` allows chaning the falloff curve by configuring hardness, center curve and base curve numbers
  - `Brush jitter` allows adding size, angle and flow jitter (haven't used this)
- You can also configure the eraser tool in a similar manner
- On the right side, you can configure the following
  - `Texture size` for the layer and its `opacity` (this is layer opacity and nothing to do with opacity maps)
  - Then for each map you can paint across, it allows `inverting/clearing/opacity`
  - It also allows specifying a Layer type `Normal/Add/Subtract/Overlay` etc (I only used Normal)

- A `Surface Layer` is the only other kind I used
- This I used to get the Megascans textures on to the model
- You would choose the Megascan texture and download it, and then `double-click` it in your local library
- This will add a surface layer to your layer set and will cover the entire model in that texture
- To paint on this, we need to use a mask on this layer
  - `Click` the third icon from the left at the bottom of the layer tab
  - This will add a white mask (texture covers all and you can erase from it by painting it black)
  - Don't use an actual eraser here, instead set `value` property in left menu to zero (black)
  - Conversely, you can `Alt + click` to add a black mask (no texture visible and you can paint on it)
  - You can specifically click on this mask on a layer and then paint on it using the `value` property in left menu
  - Other brush configs still behave the same
  - On the right menu, you can only update the texture size
- Clicking on the surface layer outside the mask icon gives more options on the right menu
  - This affects all areas equally
  - You can set `Opacity` for the surface layer (there are other options under `Blend` but I didn't try them)
  - `Placement` specifies how the texture is wrapped on the model and I mostly set it to `Tiling`
    - There are some extra options for tiling as well like `repetitions` and `offsets` which is easy to see
  - Each Megascan texture already has specific values set for each of the texture maps but you can still change them
  - I only changed the `Albedo` as other maps change the material properties which may not look accurate anymore
    - `Albedo` is used to change the color of the surface while all other material properties remain intact
- If you want to have the same material but two different colors
  - the only way I found was to create two separate surface layers, each with its own color and then masked aptly
- When you want to name a layer, name it at the very start
  - changing names after you have painted on it, causes problems due to how Mixer saves its files
  - In `Custom Sources` directory of the particular Mixer project, it stores all the paint and mask layers
  - These layers are named a certain way and saved in realtime
  - updating the name causes them to save with a different name and lose all previous changes

---

### Accessing Megascan textures

- Both UE5 and Mixer allows direct access to the `Megascans Library`
- The library has a large number of photorealistic textures and models to use (I haven't used those models yet)
- When you download them, they get saved in `Quixel Megascans Library/Downloaded` in the installation directory
  - It downloads and saves them in certain categories, like surface layers go into a directory `surface`
  - Most megascan textures go here (as far as I have seen)
  - Opening the particular megascan folder under `surface` shows all the maps that are available under it
  - You can specifically copy and use these maps in other apps if you need to

---

### Final Export

- When the texturing is complete, we want to export all the textures
- We did a bunch of export settings at the top of this document
- Before export, you can select the `Texture size` from the bottom dropdown of the `Export` tab
- Then, you can click `Export to disk` and this will export all the textures
  - the location we had set previously
  - each texture map configured will have its own texture with the aggregated result of all layers
  - maps are separate for each UDIM tile
- You can then use these in the engine

---

## How to begin (InstaMat)

### Tablet Navigation Fundamentals

- Express keys from left to right are as follows:
  - Shift
  - Alt
  - Ctrl
  - Double-click
- For the atom and element graphs:
  - Moving around can be done by putting the pen down and dragging
    - moving nodes is a similar experience
  - Zooming can be done by holding down the top button and then dragging
  - Clicking the top button alone opens the node context menu
  - There were a few issues with double ciicking though so that's why mapped an express key
    - Adding a connection point on a link needs this and doesn't work with just tapping twice
  - There were also a few issues with focusing on the 3D view with `F` but its intermittent
  - Scrolling in menus has to be done via the scrollbar
  - All other things are similar as when doing with a mouse
    - Press double-click express key in 3D view and trying again seems to work
- For the actual 3D space:
  - `Alt + Click` dragging for rotating around object
  - `Ctrl + Alt + Click` dragging for panning
  - `Shift + pen-top-button + Click` dragging for rotating environment
  - `express-double-click + F` to focus scene (though actually just `F` should work)
  - `pen-bottom-button + Click` dragging for zooming in and out
  - `pen-top-button + Click` dragging for looking around from fixed camera position

---

### Procedural textures

- You would generally start by setting up the `Material Make` node
  - Then you can right click and select `Expose output parameters` so that each channel is a texture output
- Press `H` to disable selected nodes
- An atom is like a utility function while an element is generally a fully encapsulated material
  - Atoms can be used inside other custom atoms or elements and there are some atoms which are already available
  - For example, predefined atoms are available for different kinds of noise
- Images generated are either grayscale or color
  - pin links to nodes for color images show up in green while for grayscale, show up in grey
- If height related things look too flat in 3D view during element graph building
  - we can press `3` to go to Settings and scroll down to `Render settings`
  - we can increase the `Displacement factor` and the `Tessellation level` to see what looks good
  - increasing these degrades performance so use only when needed

- Following things are basics of procedural texturing:
  - First, you create a new `Element`
  - You generally start with some predefined atoms with image outputs or you can import images of your own
  - You can transform the base image for scaling, rotating and translating as required using the `Transform` node
  - Next, you generally want to blend this image with something else using the `Blend` node
    - this can either be a basic image (from an atom) or a processed image
  - Then, you usually have to tile the basic component of your texture using the `Tile` node
  - You repeat this process for all the basic components of your texture and blend them together
  - Sometimes you need to play around with how light or dark different parts of the texture is, which can be done with the `Levels` node
  - At this point, you have a node graph that generates your texture
  - Throughout this process, we try to incorporate different kinds of randomness into the texture to make it more natural
    - this can be done using noise atoms or attributes of other atoms
    - we can also play around with those noises with different kinds of effects like `Sharpen`, `Blur` etc
  - This helps in generating a procedural texture

- A material needs multiple textures like Normal, Height, AO, Albedo, Roughness, Metalness etc.
  - we create node graphs for each texture in the same element
  - we can often reuse parts of the node graph for different components of the same texture or even across textures
    - these are things you can consider creating custom atoms for
  - usually we start with the height map as it is often used to generate the Normal and AO maps as well
    - we use the `Height to Normal` and `Height to AO` nodes for this
    - personally `Height to Normal` node didn't work well for me so I created a custom atom for it myself in the same package
    - you can refer to the atom of the node you are trying to customize and replicate it youself (direct copy doesn't always work)
  - what comes next [TODO]

- Once we have all the texture maps generated procedurally
  - we use the `Material Make` node and connect all the generated maps to it
    - currently I'm using the `PBR realtime` shading model
    - it defines predefined material type outputs for each corresponding texture map
  - once we have all of this hooked up, our procedural materal is ready

---

### Mesh Baking

- This is the process of transferring high resolution details on to a low poly mesh
- First, we sculpt a high poly mesh in ZBrush
- Second, we retopologize it at varying levels to create low poly meshes
- We export all these meshes as FBX from ZBrush
- We then import the high poly mesh into blender and fix the scale to 1 for X,Y,Z and re-export it as FBX
- For the low-poly mesh, we fix the scale to 1 for X,Y,Z
- In addition, we also UV unwrap it, and then export it as FBX
- For the FBX export
  - limit to selected objects and object types as Mesh
  - nothing needs to change in the Transform tab
  - In Geometry tab, disable `Apply Modifiers`
  - For non-animated assets, nothing else is required
- Then we open instamat and create a new `Layering` project
- We select the low poly mesh in this window, and turn on `Bake mesh on creation` and create the project thereafter
- This will automatically open the baking options on open
  - target mesh will be auto-selected to the low poly mesh
  - select the high poly mesh as source mesh
  - update baking engine to GPU and set the texture resolution as appropriate
  - enable `Displacement` maps and turn on `Full range`
  - in `Normal Tangent Space`, choose output tangent space as `DirectX`
  - we only really need `Normal Tangent Space` for the projection
  - turn off `Use Cage Mesh Normals`
  - then bake it (this takes some time)
- Once baked, go to the `Layering Project Editor` in the top left second icon in the left panel
  - under mesh, select `Mesh Format` as `DirectX`
- With this you can see the transferred details onto the low poly mesh
  - successful detail transfer from high poly mesh of `737152` faces to low poly mesh of `1197` faces

---

### Megascan imports

- This section defines how to use Quixel megascan materials in InstaMat
- First we create a new `Element Graph` project of `PBR` template
- Delete everything apart from the output nodes of `Normal, Base color, Height, AO, Metalness, Roughness`
- Create 2 parameters of type `ElementImage` called `Albedo` and `Normal`
- Create 4 parameters of type `ElementImageGrey` called `AO, Gloss, Specular, Displacement`
- Each parameter corresponds to a texture map for the megascan material
- We import the megascan texture maps into InstaMat assets and then feed it into these parameters
- Drag the parameters onto the canvas and connect them accordingly
  - Albedo -> Base color
  - Normal -> Normal
  - Displacement -> Height
  - if roughness exists, Roughness -> Roughness, else Gloss -> Invert -> Roughness
  - If metalness exists, Metalness -> Metalness, else Specular -> Metalness
    - this is not completely accuraate so check below link for accurate conversion logic
    - https://marmoset.co/posts/pbr-texture-conversion/
  - AO -> AO
- We can save this and preview the quixel material on the mesh
- Then we can go to a `Layering` project and directly drag the saved `Element Graph` into the layer stack
  -  this will apply the material to the mesh

---

### Extra texture channels

- In `Layer Project Editor` on the left menu, we can add channels
- By extra channels, I mean `Emissive, Opacity and Height`
- We can paint height infomation directly using a multi-channel brush
  - adjust the strength either by adjusting the linear scale of height in brush
  - for additional adjustment, we can adjust the `Height Normal Strength` in channel settings
  - to add or subtract, we can set the layer type from `Default` to `Add/Subtract`
  - this will not mix with the normal details added and instead add/subtract on top of it
- For opacity, we can adjust the linear slider and get various gradations of opacity
  - if you are painting on one side of a box, you can see through the entire box
  - this is because there are no actual polygons to render the inside of the box making it invisible
- For emissive, we need to add the emissive channel
  - this won't work if there is an opacity channel already as opacity uses a different render mode
- We can go to blender and select Material properties on the left side panel
  - select a meterial in the list (there should be one there by default)
  - go to edit mode of object and select the faces for that material
    - click `C` to go into selection mode and paint on mesh with pen to select faces
    - `Shoft + C` helps to deselect faces
    - `Esc` to come out of selection mode
    - while using tablet, you cannot seem to move or do anything else in selection mode
    - make sure to come out of selection mode after done selecting
  - click `Assign` in the material panel
    - doing this while in selection mode has no effect
  - add a new material to list and repeat
- Importing this mesh into Instamat will have two material sections
  - you can assign the baked maps for full mesh to both and they will apply correctly
  - you may have to select the active material to refresh the view though for each material
  - depending on type of layering project, the painting expierence is slightly different
    - `Multi-material` allows you to have multiple materials but you can paint across one at a time
    - `Multi-material (unified)` allows you to paint across multiple materials at once

- ideally, we ought to keep two separate material Ids for opaque (non-opacity) and translucent (with opacity) [CURRENTLY-NOT-SUPPORTED]

---

### Brush properties

- Most properties are easy to figure out
- That being said, pressure sensitivity is not auto-enabled
  - It has to be enabled for each brush layer
  - Same for symmetry
  - Both are found in brush properties
- For pressure sensitivity, we have to go to the ``Dynamics` section
  - adjust the amount of the effect by slider
  - click the small `shuffle` button beside the slider
  - the first dropdown let's you select `Pressure` which will enable this
  - we can do this for all the dynamic properties, but `Flow` is the most common usecase
- Moreover, some of the brush strokes may seem a little jittery
  - That is because default spacing is 20 and we can lower it to 5 to feel less jittery

## Todos

- Figure out how to do procedural textures
- Figure out how to texture hair cards
- Figure out how to control the direction of textures on different parts of custom models during painting

---

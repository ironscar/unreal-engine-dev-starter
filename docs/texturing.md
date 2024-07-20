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

- For the atom and element graphs:
  - [TODO]
- For the actual 3D space:
  - [TODO]

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

- To try:
  - what level of low poly detail is good enough to project the high poly details successfully

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

## Todos

- Figure out how to do procedural textures
- Figure out how to texture hair cards
- Figure out how to control the direction of the texture on custom models

---

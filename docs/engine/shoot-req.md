# Shooting

## Shooting requirements

- Let us set up a few requirements on how shooting should work for us so that it's easy to integrate FPS and 3PS

|Control  			| FPS 							| 3PS							|
|-------------------|-------------------------------|-------------------------------|
| Mouse left		|Shoot      					|Shoot      					|
| 1					|Weapon 1						|Weapon 1						|
| 2					|Weapon 2    					|Weapon 2						|
| Mouse right		|Focus							|Focus							|

- When shooting in 3PS/FPS, compare the following cases:
  - what happens if you start shooting with/without focus while camera direction is not the same as pawn (aligned mesh) direction?
  - what happens if you start shooting with/without focus while sprinting forward
  - what happens if you start sprinting forward while shooting
  - what happens if you start shooting with/without focus while walking left/right
  - what happens if you start walking left/right while shooting
  - what happens if you start shooting with/without focus while sprinting left/right
  - what happens if you start sprinting left/right while shooting

---

## Shooting integration

- Add new `EnhancedInputAction` for weapon selection
  - looks like have to create a new one for each weapon, for now only 2
  - add those to `InputMappingContext` and then to `CharacterPlayerController`
- Update bindings so that we can press `1` or `2` to change to specific weapon
  - we ideally want a single method to set it instead of creating a new method for each weapon binding
  - for this we create a private `DECLARE_DELEGATE_OneParam` with a float parameter
  - we pass that float parameter in the BindAction method as a constand for each action
  - don't know how to use different delegates for different actions though [CHECK]
- need to setup focus [TODO]

---

## Improvements

- All shooting is semi-automatic so instead make light weapon as automatic and heavy weapon as semi-automatic

---

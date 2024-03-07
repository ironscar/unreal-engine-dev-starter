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

## Improvements

- All shooting is semi-automatic so instead make light weapon as automatic and heavy weapon as semi-automatic
- Key bindings today are different so need to update those to the requirements

---

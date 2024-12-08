# Collision

## Issue description

- Collision doesn't seem to be automatically added to Pawns so it seems to be able to walk through walls
- We added a `Capsule Collision Component` as root component by dragging it onto `Default Scene Root`
- This will always get created at origin and you cannot move it, so move the skeletal asset and camera downwards to match
- We also need to update the `MuzzleOffsetHeight` for the same reason and reduce it by same amount
- The `PlayerStart` on the other hand needs to come up by that amount
- Even with this, it doesn't enable collisions
- We played around with the collision settings but that doesn't seem to affect much yet
- When we enabled `Simulate Physics`, only then did it actually collide
  - But it started falling like a capsule and had random movements on collision, so couldn't be used
  - Changing the physics settings didn't seem to affect these random movements
- The default `ThirdPerson` character seems to enable `Generate Overlap Events` and set the `Collision Preset` as `Pawn`

## Caveats

- Turns out that UE has a `Character` class which inherits from `Pawn` and adds a `MovementComponent` to it
- It also seems that this is what does all the collision checking
- It necessitates the use of a capsule collision as a root component and you cannot change it
- If you are not using the `Character` class, may have to write your own collision logic

---

## Overlap event logs

- So first step would be to detect collision events
- We add a reference to the Capsule component to `CharacterPawn` and try to get its reference by `FindComponentByClass`
- Then, on `OnComponentBeginOverlap`, we bind it to a method called `BeginOverlap` (it needs a specific signature to work) using `AddDynamic`
  - This needs `BeginOverlap` to be marked with `UFUNCTION()` in the header file and has to be called once in `BeginPlay` (not constructor)
- Turns out that overlap events only fire when the collision preset `overlaps` the other object type and not if `blocks` it
  - Setting the pawn's capsule component's collision preset to `OverlapAllDynamic` makes it work
  - The assets can deselect `Generate Overlap Events` because the capsule component will generate the events
  - The asset can also set its collision preset to `Default` which will still fire the event
  - Then we see the log in the `BeginOverlap` method

---

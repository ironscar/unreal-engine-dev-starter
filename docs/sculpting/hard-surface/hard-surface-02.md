# ChainGun Hard Surface Sculpt

- We started with a primitive double-sided cylinder
- Then using ZModeler Brush, we added edge loops on the outside from one end and scaled them one by one to get the exponential slope
- Then we select alternating face-pairs using ZModeler brush in the front, and then use Extrude on them to get the extrusions
- We also had to scale down the inner edge at that point but that was skipping a few vertices for some reason so had to manually mask and scale them

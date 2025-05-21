### Documentation of the Logic of the Project(cub3D).

This document is written with the purpose of explaining the all in all logic of the project and also the detailed explanation of each function of every part.


###1. Big-Picture Logic of the Ray-Casting Engine
   At its core, cub3D implements the classic ray-casting algorithm to turn a 2D grid map into a real-time first-person view. For each vertical stripe (column) of the window:
Cast a RayFrom the player’s position, shoot out a ray at a specific angle within the field of view.
Step Through the GridUsing DDA (Digital Differential Analyzer), move cell by cell along the ray until hitting a wall.
Compute DistanceRecord how far along the ray the wall was found—this distance determines how “tall” the wall slice appears.
Project & TextureCalculate the vertical line height on screen (inversely proportional to distance), pick the correct wall texture based on which side was hit, and sample the proper texture column.
Draw Floor/CeilingFill the pixels above the wall slice with the ceiling color and below with the floor color.
The ray-casting loop runs once per frame, updating as the player moves or turns to give a smooth, 3D illusion.

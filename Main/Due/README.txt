Hi,

This folder contains the program that ran on the Arduino DUE on our robot for the Robocup Junior Premier Rescue competition
which we placed 1st in Auckland and 3rd in New Zealand in. For more information about robocup junior please visit: http://robocupjunior.org.nz/
(We also had a LEOSTICK which we used to read the colour sensors)

The file ZA_Main.ino is, as you would expect the main file that was executed by the robot, calling functions from the other files.
FB_Line contains the functions written for line-following.
FD_Move contains the functions written to move set distances, which relied on the Motors library which was written by me.
FE_Endtile contains the functions for finding a coke can, picking it up and placing on a platform. Which was largely written by one of my team-mates, agkphysics.

Thanks,
Daniel Britten

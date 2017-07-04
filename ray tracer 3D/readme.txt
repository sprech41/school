Author: Jacob Sprecher

To compile the program, enter the command "make"
To run the program, enter the command "make run INPUT=filename1 OUTPUT=filename2"
Replace filename1 with your desired input file, and filename2 with your desired output file.
To clean the directory, enter the command "make clean"

Outside help received from cplusplus.com, stackoverflow.com, and math.stackexchange.com

Program works as intended, no errors to report.

NOTE: While I was creating this project, I incorrectly thought that rays were represented by just 3 coordinates.
Because of this, I do not have a seperate ray structure for this project. I now understand that rays must include the point of origin as well.
I will be sure to implement them more accurately in future projects.
However, because the camera is stationary in this project, my current implementation has no ill effects on this project. It still works as intended.
I just thought I should point that out, as some variables I call 'ray' are not true rays.

Pierre-Marc Airoldi 9601643
Eric Karemera 
Angelo Pulcini

A simple checkers game in OpenGL

::Explaination of Program::

The program is split into two parts, the part the does the game logic and the part that draws the graphics.
The gameLogic part is split into two classes, gameLogic and stateSpace. These two classes position the pieces,
calculates the possible moves, switched turns and makes the moves. The second part is the OpenGL part which is comprised
of the classes Board, Camera, Piece and Tile. These classes are the primative of our game. In order to make these primatives
we load .obj files that were created in SketchUp using the GLM class. This class takes care of loading all the vertices and normals
from the .obj file. The color and texture of these objects are specified in the .mtl file that accompanies the .obj file.
This file contains the material data that will be used for the lighting. The two parts are linked using the mouse function in the
comp371_project class. This function interprets mouse clicks in 3d and allows to select a piece and then select a tile to move it
to. The function will call the gameLogic to make the move and then the screen will be redrawn to show the result. The comp371_project 
class takes care of calculating the lighting, drawing the objects and making moves. It also does the controls to move the camera and
a light source. The camera and the movable light source rotates in a sphere pattern around the origin of the board. The classes
Board, Camera, Piece and Tile store the position and information of the primatives that are used to draw ir change the primative.

::Controls::
W = Move Camera Towards -X Direction
A = Move Camera Towards +Z Direction
S = Move Camera Towards +X Direction
D = Move Camera Towards -Z Direction
Q = Zoom Out
E = Zoom In
T = Show WireFrames 
UP = Move Light Source Towards -X Direction
LEFT = Move Light Source Towards +Z Direction
DOWN = Move Light Source Towards +X Direction
RIGHT = Move Light Source Towards -Z Direction
LEFT CLICK = Select Piece/Make Move
/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * Hey this is Sriram Maddirala and this is 
 * the intro page for my iteration1 for 3081W
 * I worked quite a bit on it 
 * so hopefully you enjoy it as much as I did
 * \section overview
 * This project uses main to instantiate the controller which in turn instantiates a graphicsarenaviewer class
the viewer class is in control of the gui and the communication from the viewer to the game
the game is essentially to avoid the obstacles and walls while hitting the bases with the robot
upon collision of the robot with an object, the robot (as well as the object if it is an obstacle)
have their handle collision functions call which respectively reduce a life, start mercy period and stop movement for the robot 
and start an arc reversal to move away for the obstacle
communication that the game is over (i.e. all lives for the robot are lost or the game is won by hitting the bases) occurs through
arena checking game status which is an attribute of the robot and then controller querying every timestep for this status
when controller gets the information it then sends it to gui via acceptcommunication and then gui neccessitates a newgame being called
 */

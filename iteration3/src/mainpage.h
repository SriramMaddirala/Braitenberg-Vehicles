/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * Hey this is Sriram Maddirala and this is 
 * the intro page for my iteration3 for 3081W
 * I worked quite a bit on it 
 * so hopefully you enjoy it as much as I did.
 *
 * This project is a Braitenberg Vehicle simulator in which robot behavior is visualized within a graphics window implemented 
 * through a model-view-controller architecture which means that there is a model responsible for holding the data, a viewer that 
 * gives an interface to interact with and/or view the data and a controller that manipulates the model and updates the viewer. 
 * The game is essentially to avoid the lights and walls while hitting the foods with the robot
 *
 * \section  tech_sec TechnicalOverview
 * The simulation starts in main.cc which instantiates and calls the run function of the Controller which sets the entire project into motion. 
 * The Controller then initializes the arena and the GraphicsArenaViewer which pops up with an interface that presents the arena and a GUI remote control.
 * This Arena environment will have multiple robots, as well as stimuli such as lights and food where the robots exhibit different behavior in reaction to
 * those stimuli. Some robots are attracted to the light while some fear the light and the relationship to food will change over time as the robot gets 
 * hungrier. This behavior is implemented through sensors for each stimuli. The sensors are stored in the robot. The pointers to these robots are stored 
 * in the arena and are accessed by the arena. The arena iterates through all the arena entities for every robot at each time step and then passes the 
 * positional information of that entity to the robot sensors. It also checks for collisions between every entity and every mobile entity and then calls 
 * the handlecollision method of the mobile entity where the following action is taken. If the mobile entity is a robot and it is colliding with a light 
 * or food, it passes through it. If the robot is colliding with a wall or another robot it begins an arc reversal motion. If the mobile entity is a light 
 * then if it collides with a wall or another light it begins an arc reversal. Both arc reversals are conducted through a finite state automata that is 
 * initiated in the handlecollision and is advanced with regards to time in the TimestepUpdate method. This same TimestepUpdate method of the mobile 
 * entities also, depending on the arc traversal status, behavior and for a robot hunger or starvation, sets the velocity of their respective motionhandlers 
 * through the sensor readings. This change in velocity updates the position and heading of the entity with a call to motionBehaviorDifferential and then 
 * resets the sensor readings. If the entity is a Robot and has fear, the reading from the right sensor impacts the velocity of the right wheel and the 
 * left sensor impacts the left wheel with respect to the lights. If the entity is a Robot and has exploratory behavior then the reading from the right 
 * sensor impacts the velocity of the left wheel, and the left sensor impacts the right wheel and the left sensor impacts the right wheel with respect to
 * the lights. If the entity is a robot and senses food it is aggressive meaning the sensors have a positive correlation between the right sensor and left 
 * wheel, and between the left sensor and right wheel. If the entity is a Robot and is really hungry then it ignores and goes through the lights without 
 * care for light sensor readings. If the robot isn’t hungry then it would not go towards the food even when it is close enough to sense it. The Robot 
 * eats food and resets its hunger and starvation status when it is around 5 units away from the food if it is hungry. The GraphicsArenaViewer passes 
 * information to the model through a communication class that it uses to indicate certain signals to the controller which takes appropriate action and 
 * indicates its own situation appropriate signal to the arena. The GUI interface possesses the ability to change the number of robots, number of lights, 
 * sensitivity of robots to light, percentage of robots with Fear-based behavior, the ability to play/pause the simulation and start a new game, the 
 * ability to toggle food on and off as well as the functionality to change the number of Food objects. These changes are all implemented after a new Game 
 * is called. When the new game is called the controller destroys the old arena, creates a new arenaparams, which is designed to hold all the Arena and GUI 
 * relevant data, with the new values that need to be implemented and then creates a new arena with those params and calls the viewer on the arena. Once 
 * the data is inside the arena, the number of robots, number of lights and  the number of food objects are all specified through for loops which call the 
 * appropriate entityFactory method, entityfactory being the creator of entities, the specific number of times necessary for each entity to stay in keeping 
 * with the requested changes. The food toggle is used as a conditional throughout arena to implement the no food/food scenarios accordingly. 
 * In entityFactory, the percentage of robots with fear-based behavior is implemented through setting the robot’s behavior after it is created depending 
 * on how many are to be created in that step as well as how many of those have to be fear-based. After each robot is created the sensors, which are 
 * created in the robots themselves, are then called and the sensitivity to light is set through a setter method that acts on a pre-existing constant 
 * to adjust according to the request.
 *
 * \section non_tech_sec User Guide
 * First to start the program double click on the executable in the that says ArenaViewer. Once you do so a large graphical interface and a 
 * window will pop up. This interface will feature a number of blue circles which are the robots with sensors drawn onto them as well as red circles 
 * for food and white circles for Lights. These objects exist in the confines of a tightly defined box outlined by a white trace. There is also a 
 * graphical control mechanism visible and available that outlines a number of features. The first button on the control is a Play button. It starts 
 * the simulation. When you want to pause it, press that button again. Below it is the Arena Configuration menu. It features a slider for selecting 
 * the number of robots in the simulation, moving the slider will alter that value. A slider for the number of lights and number of Food is also visible.
 * There is a slider that reads percentage of Robots that exhibit Fear which works in intervals of 1 from 0-10. When it is at 0 then all the Robots 
 * would have exploratory behavior with respect to lights i.e. negative crossed connections and if the slider is 10 then the Robots would all have Fear 
 * based behavior with respect to lights i.e. Positive direct connections. This means that if the robot senses light on its left side then the left wheel
 * of the robot is going to speed up in the direction of the light and if the robot senses light on its right side then the right wheel of the robot is 
 * going to speed up in the direction of the light.  If the slider is at 0 then all the robots will have Negative crossed connections with respect to 
 * the lights. This means that if the robot senses light on its left side then the right wheel of the robot is going to speed up in the opposite direction
 * and if the robot senses light on its right side then the left wheel of the robot is going to speed up in the opposite direction. There is also a slider 
 * that controls the sensitivity of robots to light, when this slider value is increased by moving to the right then the readings the robots take in from 
 * the sensors is increased and the effect of the lights on robot behavior is augmented. If the robot comes close to a food object, it eats it. But for 
 * every second that it doesn’t eat food the robots grow closer to being hungry until it hits 30 seconds from its last meal where it then experiences 
 * Positive Crossed connections towards food. This means that if the robot senses Food on its left side then the right wheel of the robot is going to 
 * speed up in the positive direction and if the robot senses light on its right side then the left wheel of the robot is going to speed up in the 
 * positive direction. If the robot hasn’t eaten in 120 seconds it starts to starve and ignores all light and just goes after food and if it isn’t 
 * successful in finding that Food in 30 seconds after that initial starvation, then that Robot starves and the simulation ends. To start a New Game 
 * all you would have to do is click the New Game button right below the Food button. There Food button turns off the Food functionality when clicked so 
 * if you want to play without regards for any unnecessary famine then just click that.  I hope that was clear and you have a good time with my simulation. 
 * Enjoy.

 */

### CSCI3081 Project : Base Code Changes

Github is a repository intended to be used in a team environment in which everyone can collaborate on a single code base. In our academic environment, we are using Github in a way that is antithetical to its purpose. We are asking 100+ people to develop the same code in replicated repositories. For this reason, bug fixes and feature enhancements are difficult to push out to everyone in a convenient manner. Our solution is to modify the code base in the _public-class-repo_ then ask that you make the same changes in your project repository. There are merge tools that might make this process easier, but the changes are relatively minor so it might be easier for you to make the changes by hand, rather than find an automated way.

The following changes have been made to the code base of iteration1 since its release.

- 02/23/18:
  - FIX: Increase Graphics Window Size.
  - FILE: params.h</td>
  - CHANGE:
  ```
  #define X_DIM 1024
  #define Y_DIM 768
  ```

- 02/23/18:
  - FIX: rename lives to be style compliant.
  - NOTE: **__Necessary for unittest compilation__**
  - FILE: robot.h
  - LOCATION: Robot class definition
  - CHANGE:
  ```
  int lives_;
  ```
  AND
  - FILE: robot.cc
  - LOCATION: Robot constructor initializer list
  - CHANGE:
  ```
  lives_(9) {
  ```

- 02/23/18:
  - FIX: lives\_ getter/setter.<br>
  - NOTE: **__Necessary for unittest compilation__**
  - FILE: robot.h
  - LOCATION: Robot class definition
  - FIX:
  ```
  int get_lives() { return lives_; }
  void set_lives(int l) { lives_ = l; }
  ```

- 02/23/18:
  - FIX: MotionHandler getter.
  - NOTE: **__Necessary for unittest compilation.__**
  - FILE: robot.h
  - LOCATION: Robot class Definition
  - FIX:
  ```
  MotionHandlerRobot get_motion_handler() {return motion_handler_;}
  ```

- 02/23/18:
  - FIX: MotionBehavior getter.
  - NOTE: **__Necessary for unittest compilation.__**
  - FILE: robot.h
  - LOCATION: Robot class Definition
  - FIX:
  ```
  MotionBehaviorDifferential get_motion_behavior() {return motion_behavior_;}
  ```

- 02/23/18:
  - FIX: MotionHandler use default copy, assignment (not delete).
  - NOTE: **__Necessary for unittest compilation.__**
  - FILE: motion_handler.h
  - LOCATION: MotionHandler class definition (lines \#46, 47)
  - FIX:
  ```
  MotionHandler(const MotionHandler& other) = default;
  MotionHandler& operator=(const MotionHandler& other) = default;
  ```

- 02/23/18:
  - FIX: MotionHandlerRobot use default copy, assignment (not delete).
  - NOTE: **__Necessary for unittest compilation.__**
  - FILE: motion_handler_robot.h
  - LOCATION: MotionHandlerRobot class definition (lines \#42, 43)
  - FIX:
  ```
  MotionHandlerRobot(const MotionHandlerRobot& other) = default;
  MotionHandlerRobot& operator=(const MotionHandlerRobot& other) = default;
  ```

- 02/23/18:
  - FIX: MotionBehavior use default copy, assignment (not delete).
  - NOTE: **__Necessary for unittest compilation.__**
  - FILE: motion_behavior.h
  - LOCATION: MotionBehavior class definition (lines \#41, 42)
  - FIX:
  ```
  MotionBehavior(const MotionBehavior& other) = default;
  MotionBehavior& operator=(const MotionBehavior& other) = default;
  ```

- 02/23/18:
  - FIX: MotionBehaviorDifferential use default copy, assignment (not delete).
  - NOTE: **__Necessary for unittest compilation.__**
  - FILE: motion_behavior_differential.h
  - LOCATION: MotionBehaviorDifferential class definition (lines \#37, 38)
  - FIX:
  ```
  MotionBehaviorDifferential(const MotionBehaviorDifferential& other) = default;
  MotionBehaviorDifferential& operator=(const MotionBehaviorDifferential& other) = default;
  ```

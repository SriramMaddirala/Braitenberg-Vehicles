#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/arena_params.h"
#include "src/entity_type.h"
#include "src/communication.h"
#include "src/sensor.h"
#include "src/light_sensor.h"
#ifdef MY_SENSOR

class SensorTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize Arena for Collections of TESTS
    csci3081::arena_params aparams;
    arena = new csci3081::Arena(&aparams);
    arena->set_game_status(PLAYING);
    robot = arena->robot(); 
    csci3081::LightSensor * leftlightsensor = robot->left;
    csci3081::LightSensor * rightlightsensor = robot->right;
  }
  csci3081::Arena * arena;
  csci3081::Robot * robot;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(SensorTest, TestDestructorConstructor ) {
  csci3081::Sensor * constr = new csci3081::Sensor();
  delete constr;
  csci3081::LightSensor * lightconstr = new csci3081::LightSensor();
  delete lightconstr;
  };

TEST_F(SensorTest, testCommunicationFear) {
  robot->get_motion_handler().set_velocity(5,5);
  rightlightsensor.AcceptCommunication(Communication kCollidingLight, 10);
  csci3081::WheelVelocity v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(v.left, ROBOT_MAX_SPEED));
  robot->get_motion_handler().set_velocity(5,5);
  
  leftlightsensor.AcceptCommunication(kCollidingLight, 10);
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(ROBOT_MAX_SPEED,v.right));   
  robot->get_motion_handler().set_velocity(5,5);
  
  rightlightsensor.AcceptCommunication(kCollidingLight, 0);
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(v.left, v.right));
  robot->get_motion_handler().set_velocity(5,5);

  leftlightsensor.AcceptCommunication(kCollidingLight, 0);
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(v.left,v.right));
  robot->get_motion_handler().set_velocity(5,5);
 };

TEST_F(SensorTest, testCommunicationExploratory) {
  robot->set_behavior(1);
  robot->get_motion_handler().set_velocity(5,5);
  rightlightsensor.AcceptCommunication(kCollidingLight, 10);
  csci3081::WheelVelocity v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(ROBOT_MAX_SPEED, v.left));
  robot->get_motion_handler().set_velocity(5,5);

  leftlightsensor.AcceptCommunication(kCollidingLight, 10);
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(v.left,ROBOT_MAX_SPEED));         

   rightlightsensor.AcceptCommunication(kCollidingLight, 0);
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(v.left, v.right));
  robot->get_motion_handler().set_velocity(5,5);

  leftlightsensor.AcceptCommunication(kCollidingLight, 0);
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(v.left,v.right));
  robot->get_motion_handler().set_velocity(5,5);
 
};
#endif /* Sensor_TESTS */

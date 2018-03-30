#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/arena_params.h"
#include "src/entity_type.h"

#ifdef MY_SENSOR

class SensorTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize Arena for Collections of TESTS
    csci3081::arena_params aparams;
    arena = new csci3081::Arena(&aparams);
    arena->set_game_status(PLAYING);
    robot = arena->robot();
    light = robot.light_sensor_; { cout << "Light Sensor Constructor is executed\n"; }
    sensor = robot.sensor_; { cout << "Sensor Constructor is executed\n"; }
  }
  csci3081::Arena * arena;
  csci3081::Robot * robot;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(SensorTest, TestDestructorConstructor ) {
  csci3081::Sensor constr = new csci3081::Sensor();
  delete constr { cout << "Sensor Destructor is executed\n"; }
  csci3081::LightSensor lightconstr = new csci3081::LightSensor();
  delete lightconstr { cout << "Light Sensor Destructor is executed\n"; }
  };

TEST_F(SensorTest, testCommunication) {
  EXPECT_EQ(sensor.AcceptCommunication()
};

TEST_F(RobotTest, IncreaseSpeedMax) {
  int nIncrease = 10;
  while(nIncrease--)
    robot->IncreaseSpeed();
  csci3081::WheelVelocity v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(ROBOT_MAX_SPEED, ROBOT_MAX_SPEED));
  robot->IncreaseSpeed();
  v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right),
            std::make_tuple(ROBOT_MAX_SPEED, ROBOT_MAX_SPEED));
};

#endif /* Sensor_TESTS */

#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/arena_params.h"
#include "src/entity_type.h"

#ifdef MY_MOTION_HANDLER

class MotionTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize Arena for Collections of TESTS
    csci3081::arena_params aparams;
    arena = new csci3081::Arena(&aparams);
    arena->set_game_status(PLAYING);
    robot = arena->robot();
    sensor = robot->LightSensor();
  }
  csci3081::Arena * arena;
  csci3081::Robot * robot;
  csci3081::LightSensor * lightsensor;
  csci3081::Sensor * sensor;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RobotTest, RobotStopOnObstacleCollision) {
  robot->IncreaseSpeed();
  robot->set_position(200, 200);
  for(auto& ent : arena->get_entities()) {
    if(ent->get_type() == csci3081::kObstacle) {
      ent->set_position(201, 200);
      break;
    }
  }
  arena->AdvanceTime(1);
  arena->AdvanceTime(1);
  csci3081::WheelVelocity v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right), std::make_tuple(0, 0)) << "Fail: Robot did not stop on collision with an Obstacle";
};

TEST_F(RobotTest, DecreaseSpeedMin) {
  robot->DecreaseSpeed();
  csci3081::WheelVelocity v = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(v.left, v.right), std::make_tuple(0, 0));
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

#endif /* Motion_handler test */

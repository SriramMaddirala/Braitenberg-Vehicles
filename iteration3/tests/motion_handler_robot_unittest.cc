/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "src/light_sensor.h"
#include "src/robot.h"
#include "src/motion_handler_robot.h"
#include "src/arena.h"
#include "src/arena_params.h"
#include "src/entity_type.h"

#ifdef MOTION_HANDLER_ROBOT_TESTS



/******************************************************
* TEST FIXTURE SetUp
*******************************************************/
class MotionHandlerRobotTest : public ::testing::Test {

protected:
 virtual void SetUp() {
  csci3081::arena_params aparams;
  aparams.n_robot =1;
  aparams.n_light =0;
  aparams.food=false;
  arena = new csci3081::Arena(&aparams);
  arena->set_game_status(PLAYING);
  robot = (arena->get_robotentities).front();
  csci3081::Robot robot;
  mh = robot->get_motion_handler();
  sensor_right =robot->get_left();
  sensor_left = robot->get_right();
 }
 csci3081::Arena * arena;
 csci3081::Robot * robot;
 csci3081::MotionHandlerRobot * mh;
 csci3081::LightSensor  sensor_right;
 csci3081::LightSensor  sensor_left;
};
TEST_F(MotionHandlerRobotTest, TestConstructor ) {
  EXPECT_EQ(sensor_right.getReading(), 0) << "FAIL: Constructors did not work";
  EXPECT_EQ(sensor_left.getReading(), 0) << "FAIL: Constructors did not work";
};

TEST_F(SensorTest, testFear) {
  robot->set_behave(0);
  double xpos = static_cast<float>(robot->get_pose().x);
  double ypos = static_cast<float>(robot->get_pose().y);
  sensor_right.CalculateReading(xpos+10,ypos+10);
  double left = sensor_left.getReading()/100;
  double right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  csci3081::WheelVelocity w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Fear Behavior not implemented";

  sensor_left.CalculateReading(xpos+10,ypos+10);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Fear Behavior not implemented";

  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos+10,ypos+10);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Fear Behavior not implemented";

  sensor_left.CalculateReading(xpos+100,ypos-30);
  sensor_right.CalculateReading(xpos+100,ypos-10);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Fear Behavior not implemented";

  sensor_left.CalculateReading(xpos+40,ypos-30);
  sensor_right.CalculateReading(xpos+6,ypos-10);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Fear Behavior not implemented";
}

TEST_F(SensorTest, testExploratory) {
  robot->set_behave(1);
  double xpos = static_cast<float>(robot->get_pose().x);
  double ypos = static_cast<float>(robot->get_pose().y);
  sensor_right.CalculateReading(xpos+10,ypos+10);
  double left = sensor_right.getReading()/100;
  double right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  csci3081::WheelVelocity w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Exploratory Behavior not implemented";

  sensor_left.CalculateReading(xpos+10,ypos+10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Exploratory Behavior not implemented";

  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos+10,ypos+10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Exploratory Behavior not implemented";

  sensor_left.CalculateReading(xpos+100,ypos-30);
  sensor_right.CalculateReading(xpos+100,ypos-10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Exploratory Behavior not implemented";

  sensor_left.CalculateReading(xpos+40,ypos-30);
  sensor_right.CalculateReading(xpos+6,ypos-10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Exploratory Behavior not implemented";
}
TEST_F(SensorTest, testBoundary) {
  robot->set_behave(0);
  double xpos = static_cast<float>(robot->get_pose().x);
  double ypos = static_cast<float>(robot->get_pose().y);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  double left = sensor_left.getReading()/100;
  double right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  csci3081::WheelVelocity w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Boundary Behavior not functional";
  
  robot->set_behave(1);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  sensor_left.CalculateReading(xpos+10,ypos+10);
  sensor_right.CalculateReading(xpos-10,ypos-10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Boundary Behavior not functional";
  
  robot->set_behave(0);
  sensor_left.CalculateReading(xpos-4002,ypos-600);
  sensor_right.CalculateReading(xpos+350,ypos-100);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Boundary Behavior not functional";

  robot->set_behave(1);
  sensor_left.CalculateReading(xpos-1200,ypos-30);
  sensor_right.CalculateReading(xpos+100,ypos-10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Boundary Behavior not functional";

  robot->set_behave(0);
  sensor_left.CalculateReading(xpos,ypos);
  sensor_right.CalculateReading(xpos,ypos);
  sensor_left.CalculateReading(xpos,ypos);
  sensor_right.CalculateReading(xpos,ypos);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Boundary Behavior not functional";

  robot->set_behave(1);
  sensor_left.CalculateReading(xpos,ypos);
  sensor_right.CalculateReading(xpos,ypos);
  sensor_left.CalculateReading(xpos,ypos);
  sensor_right.CalculateReading(xpos,ypos);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Boundary Behavior not functional";
}
TEST_F(SensorTest, testEquivalence) {
  robot->set_behave(0);
  double xpos = static_cast<float>(robot->get_pose().x);
  double ypos = static_cast<float>(robot->get_pose().y);
  sensor_left.CalculateReading(xpos+10,ypos+20);
  sensor_right.CalculateReading(xpos-20,ypos+10);
  double left = sensor_left.getReading()/100;
  double right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  csci3081::WheelVelocity w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Equivalence Behavior not functional";
  
  robot->set_behave(1);
  sensor_left.CalculateReading(xpos+10,ypos+20);
  sensor_right.CalculateReading(xpos-20,ypos+10);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Equivalence Behavior not functional";
  
  robot->set_behave(0);
  sensor_left.CalculateReading(xpos+20,ypos+20);
  sensor_right.CalculateReading(xpos+40,ypos+40);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Equivalence Behavior not functional";

  robot->set_behave(1);
  sensor_left.CalculateReading(xpos+20,ypos+20);
  sensor_right.CalculateReading(xpos+40,ypos+40);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Equivalence Behavior not functional";

  robot->set_behave(0);
  sensor_left.CalculateReading(xpos+50,ypos);
  sensor_right.CalculateReading(xpos,ypos+50);
  sensor_left.CalculateReading(xpos+11,ypos);
  sensor_right.CalculateReading(xpos+11,ypos+3);
  left = sensor_left.getReading()/100;
  right = sensor_right.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Equivalence Behavior not functional";

  robot->set_behave(1);
  sensor_left.CalculateReading(xpos+50,ypos);
  sensor_right.CalculateReading(xpos,ypos+50);
  sensor_left.CalculateReading(xpos+11,ypos);
  sensor_right.CalculateReading(xpos+11,ypos+3);
  left = sensor_right.getReading()/100;
  right = sensor_left.getReading()/100;
  arena->AdvanceTime(1);
  w = robot->get_motion_handler().get_velocity();
  EXPECT_EQ(std::make_tuple(left, right),
            std::make_tuple(w.left, w.right)); << "FAIL: Equivalence Behavior not functional";
}

}



#endif

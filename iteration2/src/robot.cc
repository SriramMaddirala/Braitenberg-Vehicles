/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"
#include "src/pose.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
    motion_handler_(this),
    motion_behavior_(this),
    lives_(9),
    basehit_(0),
    left(motion_handler_, get_pose().x+3, get_pose().y-3),    
    right(motion_handler_, get_pose().x-3, get_pose().y+3)   
  {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);
  left.setDirection(0);
  right.setDirection(1);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.set_velocity(motion_handler_.get_velocity().left -(right.getReading()/1000),motion_handler_.get_velocity().left -(left.getReading()/1000));  
  motion_handler_.UpdateVelocity();
   // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
  if (get_mercy() > 0) {
    set_mercy(get_mercy()-1);
    set_color(ROBOT_MERCY_COLOR);
  }
  if (get_mercy() == 0) {
  set_color(ROBOT_COLOR);
  }
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(Pose(static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))));
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  motion_handler_.UpdateVelocity();
  if (object_type == kBase) {
  Base* base = dynamic_cast<Base*>(object);
  object -> set_color(BASE_HIT_COLOR);
  base -> set_captured(true);
  inc_basehit();
  } else if ((object_type == kLight) || (object_type == kRightWall) || (object_type == kLeftWall) || (object_type == kTopWall) || (object_type == kBottomWall)) {
  if (get_mercy() == 0) {
  set_lives(get_lives()-1);
  }
  set_mercy(2);
  set_color(ROBOT_MERCY_COLOR);
  }
}
void Robot::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
void Robot::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Robot::TurnRight() {
  motion_handler_.TurnRight();
}
void Robot::TurnLeft() {
  motion_handler_.TurnLeft();
}

NAMESPACE_END(csci3081);

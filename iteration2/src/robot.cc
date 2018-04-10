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
    foodhit_(0),
    left(get_motion_handler(), get_pose().x-3, get_pose().y),    
    right(get_motion_handler(), get_pose().x+3, get_pose().y)
   {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  motion_handler_.set_velocity(motion_handler_.get_velocity().left-(right.getReading()/50),motion_handler_.get_velocity().right-(left.getReading()/50));
  if (get_state() == 0) {
  } else if (get_state() == 1) {
    set_heading(get_pose().theta+180);
    set_state(2);
  } else if (get_state() > 4) {
    set_heading(get_pose().theta + 90);
    set_state(get_state() + 1);
  }
 else if (get_state() <= 4) {
    set_state(get_state() + 1);
  }
 if(get_state()==8){
   set_state(0);
  }
 // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  left.ResetReading();
  right.ResetReading();  
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(Pose(static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))));
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  motion_handler_.set_velocity(0,0);
  sensor_touch_->Reset();
  set_lives(9);
  foodhit_=0;
  
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  motion_handler_.UpdateVelocity();
  if (object_type == kFood) {
  Food* food = dynamic_cast<Food*>(object);
  object -> set_color(FOOD_HIT_COLOR);
  food -> set_captured(true);
  inc_foodhit();
  } else if ((object_type == kLight) || (object_type == kRightWall) || (object_type == kLeftWall) || (object_type == kTopWall) || (object_type == kBottomWall)) {
   set_state(1);
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

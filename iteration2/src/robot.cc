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
    left(get_motion_handler(), get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta + 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta + 40))*( M_PI /180)),    
    right(get_motion_handler(), get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta - 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta - 40))*( M_PI /180)),
   leftFood(get_motion_handler(), get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta + 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta + 40))*( M_PI /180)),
    rightFood(get_motion_handler(), get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta - 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta - 40))*( M_PI /180))
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
if(mealtime>=30){
   set_hunger(true);
}
if(mealtime>=120){
 set_starve(true);
 left.ResetReading();
 right.ResetReading();
} 
if(behavior==1){
  motion_handler_.set_velocity(-right.getReading()/10,-left.getReading()/10);
}
 if(behavior==0){
  motion_handler_.set_velocity( left.getReading()/10,right.getReading()/10);
}  
if(hungry){
 motion_handler_.set_velocity(get_motion_handler().get_velocity().left+ rightFood.getReading(),get_motion_handler().get_velocity().right+ leftFood.getReading());
}
if (get_state() == 0) {
  } else if (get_state() == 1) {
    set_heading(get_pose().theta+180);
    set_state(2);
  } 
 else if (get_state() <= 3) {
    set_state(get_state() + 1);
  }
 if(get_state()==4){
   set_heading(get_pose().theta+90);
   set_state(0);
  }
 motion_handler_.UpdateVelocity();
 // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  left.ResetReading();
  right.ResetReading();
  set_mealtime(get_mealtime()+1);  
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(Pose(static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))));
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  motion_handler_.set_velocity(0,0);
  sensor_touch_->Reset();
  set_starve(false);
  set_hunger(false);
  set_mealtime(0);  
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  motion_handler_.UpdateVelocity();
  if (object_type == kFood) {
    set_mealtime(0);
    set_hunger(false);
    set_starve(false);
  } else if ((object_type == kRightWall) || (object_type == kLeftWall) || (object_type == kTopWall) || (object_type == kBottomWall)) {
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

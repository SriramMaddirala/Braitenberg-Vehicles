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
    left(get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta + 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta + 40))*( M_PI /180)),    
    right(get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta - 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta - 40))*( M_PI /180)),
    leftFood(get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta + 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta + 40))*( M_PI /180)),
    rightFood(get_pose().x+(ROBOT_RADIUS* cos(get_pose().theta - 40))*( M_PI /180), get_pose().y +(ROBOT_RADIUS * sin(get_pose().theta - 40))*( M_PI /180))
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
//mealtime is time since last meal
if(mealtime>=30){
   set_hunger(true);
}
if(mealtime>=120){
 //this means that the reading that has already been calculated gets reset to zero leading to 
 // the robot ignoring the reading from light sensor
 set_starve(true);
 left.ResetReading();
 right.ResetReading();
} 
if(behavior==1){
 //behavior is 1 when Exploratory
   motion_handler_.set_velocity(-right.getReading()/100,-left.getReading()/100);
 }
 if(behavior==0){
 //behavior is 0 when fearful
  motion_handler_.set_velocity(left.getReading()/100,right.getReading()/100);
}
if(hungry){
 motion_handler_.set_velocity(get_motion_handler().get_velocity().left+ rightFood.getReading()/100,get_motion_handler().get_velocity().right+ leftFood.getReading()/100);
}
if(starve){
 std::cout<< mealtime<< std::endl;
 motion_handler_.set_velocity(rightFood.getReading()/100,leftFood.getReading()/100);
}
//implements the finite state automata for avoidance behavior
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
  leftFood.ResetReading();
  rightFood.ResetReading();
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

/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"
#include "src/pose.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light():
  motion_handler_(this),
  motion_behavior_(this) {
  set_color(LIGHT_COLOR);
  set_pose(LIGHT_POSITION);
  set_radius(LIGHT_RADIUS);
  set_type(kLight);
}

void Light::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  if (get_state() == 0) {
  } else if (get_state() == 1) {
    set_heading(get_pose().theta+180);
    set_state(2);
  } else if ((get_state() > 4)&&(get_state()%2==0)) {
    set_heading(get_pose().theta + 90);
    set_state(get_state() + 1);
  } 
 else if (get_state() <= 4) {
    set_state(get_state() + 1);
  }
  else if ((get_state() > 4)&&(get_state()%2!=0)) { 
    set_heading(get_pose().theta-90);
    set_state(get_state()+1);
  }
  if(get_state()==16){
   set_state(0);
  }
  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Light::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  motion_handler_.UpdateVelocity();
  set_state(1);
}

void Light::Reset() {
  set_pose(Pose(static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))));
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
  set_state(0);
} /* Reset() */

NAMESPACE_END(csci3081);

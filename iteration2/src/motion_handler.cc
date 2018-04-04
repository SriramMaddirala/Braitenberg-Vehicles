/**
 * @file motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler.h"
#include <iostream>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandler::TurnLeft() {
  set_velocity(
    get_velocity().left  - get_angle_delta(),
    get_velocity().right + get_angle_delta());
}

void MotionHandler::TurnRight() {
  set_velocity(
    get_velocity().left  + get_angle_delta(),
    get_velocity().right - get_angle_delta());
}

void MotionHandler::IncreaseSpeed() {
  if (get_velocity().left + get_speed_delta() >= get_max_speed()) {
    if (get_velocity().right + get_speed_delta() >= get_max_speed()) {
       set_velocity(get_max_speed(), get_max_speed());
    } else {
       set_velocity(get_velocity().right + get_speed_delta(), get_velocity().right + get_speed_delta());
    }
  } else {
    if (get_velocity().right + get_speed_delta() >= get_max_speed()) {
       set_velocity(get_velocity().left + get_speed_delta(), get_velocity().left + get_speed_delta());
    } else {
       set_velocity(get_velocity().right + get_speed_delta(), get_velocity().right + get_speed_delta());
    }
  }
}

void MotionHandler::DecreaseSpeed() {
  if (get_velocity().left - get_speed_delta() <= -get_max_speed()) {
    if (get_velocity().right - get_speed_delta() <= -get_max_speed()) {
      set_velocity(-get_max_speed(), -get_max_speed());
    } else {
       set_velocity(-get_max_speed(), get_velocity().right - get_speed_delta());
    }
  } else {
    if (get_velocity().right - get_speed_delta() <= -get_max_speed()) {
       set_velocity(get_velocity().left - get_speed_delta(), -get_max_speed());
    } else {
       set_velocity(get_velocity().left - get_speed_delta(), get_velocity().right - get_speed_delta());
    }
  }
}
void MotionHandler::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
    set_velocity(-get_velocity().left, -get_velocity().right);
    return;
  } else {
  set_velocity(get_velocity().left, get_velocity().left);
  }
}



NAMESPACE_END(csci3081);


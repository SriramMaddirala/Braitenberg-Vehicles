/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// @TODO add clamped

void MotionHandlerRobot::TurnLeft() {
  set_velocity(
    get_velocity().left  - get_angle_delta(),
    get_velocity().right + get_angle_delta());
}

void MotionHandlerRobot::TurnRight() {
  set_velocity(
    get_velocity().left  + get_angle_delta(),
    get_velocity().right - get_angle_delta());
}

void MotionHandlerRobot::IncreaseSpeed() {
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

void MotionHandlerRobot::DecreaseSpeed() {
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

void MotionHandlerRobot::UpdateVelocity() {
}

double MotionHandlerRobot::clamp_vel(double vel) {
  // @TODO: don't go backwards
  double clamped = 0.0;
  if (vel > 0) {
    clamped = (vel > get_max_speed()) ?
              get_max_speed():
              vel;
  } else {
    clamped = (vel < -get_max_speed()) ?
              -get_max_speed():
              vel;
  }
  return clamped;
} /* clamp_vel() */

NAMESPACE_END(csci3081);

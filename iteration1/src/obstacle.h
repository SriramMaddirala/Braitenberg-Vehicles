/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/motion_handler.h"
#include "src/motion_behavior_differential.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionBehaviorDifferential;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an immobile obstacle within the Arena.
 *
 * Since obstacles are immobile, the Obstacle class is very simple.
 */
class Obstacle : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Obstacle();
  void Reset() override;
  /**
   * @brief Get the name of the Obstacle for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Obstacle" + std::to_string(get_id());
  }
  void TimestepUpdate(unsigned int dt) override;


  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);

  /**
   * @brief Command that comes from the controller, then is passed to handler.
   */
  void IncreaseSpeed();

  /**
  * @brief Command that comes from the controller, then is passed to handler.
  */
  void DecreaseSpeed();

  /**
  * @brief Command that comes from the controller, then is passed to handler.
  */
  void TurnRight();

  /**
  * @brief Command that comes from the controller, then is passed to handler.
  */
  void TurnLeft();

  MotionHandler get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }
  int get_state() {return state_;}
  void set_state(int state) {state_ = state;}

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandler motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  int state_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_OBSTACLE_H_

#ifndef SRC_FOOD_SENSOR_H_
#define SRC_FOOD_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include <vector>
#include <iostream>
#include "src/communication.h"
#include "src/common.h"
#include "src/pose.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"
#include "src/sensor.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/**
 * @brief Class representing a Food sensor.
 *
 * This is a Food sensor class that takes in the the position of the entity being sensed
 * it then calculates the reading based on the position of that entity and
 * its own position which it holds. This class inherits from base sensor and most of 
 * the work is done in that class.
 * Sensors are fed readings and return them when prompted.
 */
class FoodSensor : public Sensor {
 public:
 FoodSensor(int xpos, int ypos):
 Sensor(xpos, ypos){}
 ~FoodSensor(){}
  private:
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H

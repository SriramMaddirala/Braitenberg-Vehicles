#ifndef SRC_LIGHT_SENSOR_H_
#define SRC_LIGHT_SENSOR_H_

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
#include "src/motion_handler.h"
#include "src/sensor.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/**
 * @brief Class representing a Light sensor.
 *
 * This is a Light sensor class that takes in the the position of the entity being sensed
 * it then calculates the reading based on the position of that entity and
 * its own position which it holds. This class inherits from base sensor and most of 
 * the work is done in that class.
 * Sensors are fed readings and return them when prompted.
 */
class LightSensor : public Sensor {
 public:
 LightSensor(MotionHandler handler, int xpos, int ypos):
 Sensor(handler, xpos, ypos){}
 ~LightSensor(){}
 private:
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_SENSOR_H

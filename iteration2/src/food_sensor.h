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
#include "src/motion_handler.h"
#include "src/sensor.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
class FoodSensor : public Sensor {
 public:
 FoodSensor(MotionHandler handler, int xpos, int ypos):
 Sensor(handler, xpos, ypos){}
 ~FoodSensor(){}
 private:
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H

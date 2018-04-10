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
class LightSensor : public Sensor {
 public:
 LightSensor(MotionHandler handler, int xpos, int ypos):
 Sensor(handler, xpos, ypos){}
 ~LightSensor(){}
 private:
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_TOUCH_H_

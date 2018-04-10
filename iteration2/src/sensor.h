#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
#include "src/communication.h"
#include "src/common.h"
#include "src/pose.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"
#include "src/motion_handler.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Sensor {
 public:
 Sensor(MotionHandler handler, int xpos, int ypos):
 motion_handler_(handler),
 xpose(xpos),
 ypose(ypos),
 reading(0){}
 virtual ~Sensor();
 MotionHandler GetMotionHandler(){return motion_handler_;}
 void CalculateReading(int x, int y) { 
        int distance = pow((((xpose-x) * (xpose-x)) + ((ypose-y) * (ypose-y))),.5);        
        int temp = 1200/(pow(1.08,distance));
        reading = temp + reading;
        if (reading > 1000){
            reading = 1000;
	}
}
void ResetReading(){reading=0;}
int getReading(){return reading;}
 private:
  MotionHandler motion_handler_;
  int xpose;
  int ypose;
  int reading;
};
NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_TOUCH_H_

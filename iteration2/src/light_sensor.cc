#include "src/light_sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void LightSensor::HandleReading(){
 if(getDirection()==1){
    GetMotionHandler().set_velocity(GetMotionHandler().get_velocity().left-(getReading()/100),GetMotionHandler().get_velocity().right);
  }
if(getDirection()==0){
    GetMotionHandler().set_velocity(GetMotionHandler().get_velocity().left-(getReading()/100),GetMotionHandler().get_velocity().right);
  }
}

NAMESPACE_END(csci3081);

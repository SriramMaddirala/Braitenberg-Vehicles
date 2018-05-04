#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/arena_params.h"
#include "src/entity_type.h"
#include "src/communication.h"
#include "src/sensor.h"
#include "src/light_sensor.h"
#ifdef MY_SENSOR

class SensorTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Create Sensors
    lightsensor= new csci3081::LightSensor(50,50);
    lightsensor2= new csci3081::LightSensor(50,50);
  }
 csci3081::LightSensor *lightsensor;
 csci3081::LightSensor *lightsensor2;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(SensorTest, TestConstructor ) {
  csci3081::LightSensor *constr = new csci3081::LightSensor(0,0);
  EXPECT_EQ(constr->getReading(), 0) << "FAIL: getReading did not work";
  };
TEST_F(SensorTest, TestFarAwayLightReading ) {
  lightsensor->CalculateReading(0,0);
  lightsensor2->CalculateReading(4,4);
  EXPECT_LT(lightsensor->getReading(),lightsensor->getReading()) << "FAIL: Farther light does not lead to Smaller reading";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(200,200);
  lightsensor2->CalculateReading(190,220);
  EXPECT_GE(lightsensor->getReading(),lightsensor->getReading()) << "FAIL: Farther light does not lead to Smaller reading";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(200,50);
  lightsensor2->CalculateReading(0,0);
  EXPECT_LT(lightsensor->getReading(),lightsensor->getReading()) << "FAIL: Farther light does not lead to Smaller reading";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
}
TEST_F(SensorTest, TestCloseByLightReading ) {
  lightsensor->CalculateReading(51,51);
  lightsensor2->CalculateReading(49,49);
  EXPECT_GT(lightsensor->getReading(),lightsensor->getReading()) << "FAIL: Closer light does not lead to bigger reading";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(40,51);
  lightsensor2->CalculateReading(30,30);
  EXPECT_GT(lightsensor->getReading(),lightsensor->getReading()) << "FAIL: Closer light does not lead to bigger reading";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(100,50);
  lightsensor2->CalculateReading(0,30);
  EXPECT_GT(lightsensor->getReading(),lightsensor->getReading()) << "FAIL: Closer light does not lead to bigger reading";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
}
TEST_F(SensorTest, TestMaxReading ) {
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  lightsensor2->CalculateReading(50,50);
  EXPECT_GT(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated";
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  EXPECT_LT(lightsensor->getReading(),1000) << "FAIL: Max Reading is not 1000";
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  EXPECT_LT(lightsensor->getReading(),1000) << "FAIL: Max Reading is not 1000";
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  EXPECT_LT(lightsensor->getReading(),1000) << "FAIL: Max Reading is not 1000";
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,50);
  EXPECT_LT(lightsensor->getReading(),1000) << "FAIL: Max Reading is not 1000";
  lightsensor->ResetReading();
}
TEST_F(SensorTest, TestMinReading ) {
  lightsensor->CalculateReading(-500,-500);
  EXPECT_GE(lightsensor->getReading(),0) << "FAIL: Min Reading is not 0";
  lightsensor->ResetReading();
  EXPECT_EQ(lightsensor->getReading(),0) << "FAIL: Min Reading is not 0";
}
TEST_F(SensorTest, TestMultipleEquivalenceLightReading ) {
  lightsensor->CalculateReading(80,20);
  lightsensor->CalculateReading(-90,90);
  lightsensor->CalculateReading(5,10);
  lightsensor2->CalculateReading(80,20);
  lightsensor2->CalculateReading(5,10);
  EXPECT_GT(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
   lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(8,20);
  lightsensor->CalculateReading(-9,30);
  lightsensor->CalculateReading(40,40);
  lightsensor->CalculateReading(24,11);
  lightsensor2->CalculateReading(50,50);
  EXPECT_GT(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
   lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(80,20);
  lightsensor->CalculateReading(-90,90);
  lightsensor->CalculateReading(5,10);
  lightsensor2->CalculateReading(80,20);
  lightsensor2->CalculateReading(5,10);
  EXPECT_GE(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
  lightsensor2->CalculateReading(-90,90);
  EXPECT_EQ(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
}
TEST_F(SensorTest, TestMultipleBoundaryLightReading ) {
  lightsensor->CalculateReading(500,500);
  lightsensor->CalculateReading(-500,-500);
  lightsensor->CalculateReading(5,10);
  EXPECT_GT(lightsensor->getReading(),0) << "FAIL: Reading is not being accumulated correctly";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,49);
  lightsensor2->CalculateReading(50,50);
  lightsensor2->CalculateReading(49,49);
  EXPECT_GT(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(-400,400);
  lightsensor->CalculateReading(320,49);
  EXPECT_GE(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
  lightsensor->CalculateReading(50,50);
  lightsensor->CalculateReading(50,49);
  lightsensor2->CalculateReading(50,50);
  lightsensor2->CalculateReading(50,49);
  EXPECT_EQ(lightsensor->getReading(),lightsensor2->getReading()) << "FAIL: Reading is not being accumulated correctly";
  lightsensor->ResetReading();
  lightsensor2->ResetReading();
}
#endif /* Sensor_TESTS */

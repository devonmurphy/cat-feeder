#include <arduino-timer.h>
#include <AFMotor.h>

AF_DCMotor motor(1);
int WAIT_TIME_IN_HOURS = 6;
int LID_OPEN_TIME = 500;
auto timer = timer_create_default();
auto lidTimer = timer_create_default();

void setup() {
  // setup motor
  motor.setSpeed(150);
  motor.run(RELEASE);
  
  //timer.in(WAIT_TIME_IN_HOURS*60*60*1000, open_lid);
  timer.in(5*1000, open_lid);
}
bool open_lid(void *) {
  motor.run(BACKWARD);
  lidTimer.in(LID_OPEN_TIME, stop_motor);
  return false; // keep timer active? false
}

bool stop_motor(void *) {
  motor.run(RELEASE);
  motor.setSpeed(0);
  return false; // keep timer active? false
}

void loop() {
  lidTimer.tick();
  timer.tick();
}

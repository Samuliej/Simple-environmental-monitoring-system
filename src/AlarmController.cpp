#include "AlarmController.h"

// Constructor
AlarmController::AlarmController(int pin)
    : alarmPin(pin), alarmState(LOW), alarmStatus(0) {
  pinMode(alarmPin, OUTPUT);
}


// Set the alarm state to on and turn on the LED
void AlarmController::engageAlarm() {
  alarmState = HIGH;
  alarmStatus = 1;
  digitalWrite(alarmPin, alarmState);
  Serial.println("Alarm!");
}


// Set the alarm state to off and turn off the LED
void AlarmController::disengageAlarm() {
  alarmState = LOW;
  alarmStatus = 0;
  digitalWrite(alarmPin, alarmState);
  Serial.println("Alarm cleared.");
}


// Subroutine to get the alarm status
int AlarmController::getStatus() const {
  return alarmStatus;
}
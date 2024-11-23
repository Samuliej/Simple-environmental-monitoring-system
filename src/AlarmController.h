#ifndef AlarmController_h
#define AlarmController_h

#include <Arduino.h>

// Class for managing the alarm
class AlarmController {
  private:
    int alarmPin;   // Variables affected by the alarm
    byte alarmState;
    int alarmStatus;

  public:
    // Constructor
    AlarmController(int pin);

    // Set the alarm state to on and turn on the LED
    void engageAlarm();

    // Set the alarm state to off and turn off the LED
    void disengageAlarm();

    // Subroutine to get the alarm status
    int getStatus() const;
};

#endif
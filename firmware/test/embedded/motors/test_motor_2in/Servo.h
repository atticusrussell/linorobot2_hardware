#ifndef MockServo_h
#define MockServo_h

#include <inttypes.h>

// Mock version of the Servo library for unit testing purposes.
// This version provides stub implementations for all the methods in the Servo class.

#define Servo_VERSION           2
#define MIN_PULSE_WIDTH       544
#define MAX_PULSE_WIDTH      2400
#define DEFAULT_PULSE_WIDTH  1500
#define REFRESH_INTERVAL    20000
#define SERVOS_PER_TIMER       12
#define INVALID_SERVO         255

typedef struct {
  uint8_t nbr        :6;
  uint8_t isActive   :1;
} ServoPin_t;

typedef struct {
  ServoPin_t Pin;
  unsigned int ticks;
} servo_t;

// Servo class definition
class Servo
{
public:
    // Constructor
    Servo() {}

    // Attach servo to pin. Returns 0 in this mock version.
    uint8_t attach(int pin) { return 0; }

    // Attach servo to pin with min and max values. Returns 0 in this mock version.
    uint8_t attach(int pin, int min, int max) { return 0; }

    // Detach servo. No-op in this mock version.
    void detach() {}

    // Set servo angle. No-op in this mock version.
    void write(int value) {}

    // Set servo pulse width. No-op in this mock version.
    void writeMicroseconds(int value) {}

    // Get servo angle. Returns 0 in this mock version.
    int read() { return 0; }

    // Get servo pulse width. Returns 0 in this mock version.
    int readMicroseconds() { return 0; }

    // Check if servo is attached. Returns false in this mock version.
    bool attached() { return false; }

private:
    int8_t min;
    int8_t max;
    uint8_t servoIndex;
};

#endif

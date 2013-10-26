#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H

#include <inttypes.h>
#include <modbus/modbus.h>
#include <time.h>
#include <iostream>
#include <unistd.h>

#define MOTOR_OFF 0
#define MOTOR_ON 1

#define LEFT 0
#define RIGHT 1

#define BACK 0
#define FORWARD 1

#define AMOUNT_OF_MOTORS 3

#define STEERING_WHEEL 0
#define LEFT_WHEEL 1
#define RIGHT_WHEEL 2

#define FLAG_REGISTER 0
#define MOTOR_REFISTERS_OFFSET 1

#define STEERING_WHEEL_ON_BIT 2
#define LEFT_WHEEL_ON_BIT 8
#define RIGHT_WHEEL_ON_BIT 32

#define STEERING_WHEEL_DIRECTION_BIT 1
#define LEFT_WHEEL_DIRECTION_BIT 4
#define RIGHT_WHEEL_DIRECTION_BIT 16

struct Motor {
    bool on;
    bool direction;
    uint16_t speed;
};

class CarController {
private :
    modbus_t * car;
    Motor motors[AMOUNT_OF_MOTORS];
    uint16_t registers[4];
public:
    CarController();
    ~CarController();
    void setMotor(int motor, bool on, bool direction, int speed);
    int applyMotors();
};

#endif // CARCONTROLLER_H

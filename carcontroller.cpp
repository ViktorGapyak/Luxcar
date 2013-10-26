#include "carcontroller.h"

CarController::CarController() {
    char * devName = "/dev/ttyUSB0"; //путь к устройству
    int baud = 9600; //скорость обмена информацией с устройсвом
    int eventMod = 'N';
    int dataBits = 8;
    int stopBit = 2;
    car = modbus_new_rtu(devName, baud, eventMod, dataBits, stopBit);
    modbus_set_slave(car, 1);
    modbus_connect(car);

    for(int i = 0; i<AMOUNT_OF_MOTORS; i++) {
        motors[i].on = MOTOR_OFF;
        motors[i].direction = LEFT;
        motors[i].speed = 0;
    }

    timeval timeout;
    timeout.tv_sec = 1000000000;
    timeout.tv_usec = 1000000000;
    modbus_set_response_timeout(car, &timeout);
}

CarController::~CarController() {
    modbus_close(car);
    modbus_free(car);
}

void CarController::setMotor(int motor, bool on, bool direction, int speed) {
    motors[motor].on = on;
    motors[motor].direction = direction;
    motors[motor].speed = speed;
}

int CarController::applyMotors() {
    registers[FLAG_REGISTER] = 0;

    registers[FLAG_REGISTER] |= motors[STEERING_WHEEL].on ? STEERING_WHEEL_ON_BIT : 0;
    registers[FLAG_REGISTER] |= motors[STEERING_WHEEL].direction ? STEERING_WHEEL_DIRECTION_BIT : 0;
    registers[FLAG_REGISTER] |= motors[LEFT_WHEEL].on ? LEFT_WHEEL_ON_BIT : 0;
    registers[FLAG_REGISTER] |= motors[LEFT_WHEEL].direction ? LEFT_WHEEL_DIRECTION_BIT : 0;
    registers[FLAG_REGISTER] |= motors[RIGHT_WHEEL].on ? RIGHT_WHEEL_ON_BIT : 0;
    registers[FLAG_REGISTER] |= motors[RIGHT_WHEEL].direction ? RIGHT_WHEEL_DIRECTION_BIT : 0;

    for(int i=1; i < 4; i++) {
        registers[i] = motors[i-1].speed;
    }

    int answer;
    for(int i = 0; i < 10; i++) {
        answer = modbus_write_registers(car, 0, 4, registers);
        if(answer == 4)
            break;
    }
    if(answer != 4)
        std::cout<<"fail";
    return answer;
}



#include "carcontroller.h"

int main() {
    timeval start, end;
    long time;
    CarController car;
    car.setMotor(STEERING_WHEEL, MOTOR_ON, LEFT, 3800);
    car.applyMotors();
    gettimeofday(&start, 0);
    time = start.tv_sec*1000000 + start.tv_usec;
    usleep(1300000);
    int a;
    //std::cin >> a;
    gettimeofday(&end, 0);
    time = end.tv_sec*1000000 + end.tv_usec - time;
    std::cout << time << std::endl;
    car.setMotor(STEERING_WHEEL, MOTOR_OFF, 0, 0);
    car.applyMotors();
    return 0;
}


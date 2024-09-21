#include <iostream>
#include <pigpio.h>
#include <chrono>
#include <thread>

class ServoMotor {
public:
    ServoMotor(int pin) : pin_(pin) {
        if (gpioInitialise() < 0) {
            std::cerr << "Failed to initialize pigpio." << std::endl;
            exit(1);
        }
        gpioSetMode(pin_, PI_OUTPUT);
    }

    ~ServoMotor() {
        gpioTerminate();
    }

    void setAngle(int angle) {
        if (angle < 0 || angle > 180) {
            std::cerr << "Angle must be between 0 and 180." << std::endl;
            return;
        }
        // Convert angle to PWM value
        int pwmValue = static_cast<int>((angle / 18.0) + 2.5) * 1000; // in microseconds
        gpioServo(pin_, pwmValue);
    }

private:
    int pin_;
};

int main() {
    int servoPin = 18; // Change this to your GPIO pin
    ServoMotor servo(servoPin);

    for (int angle = 0; angle <= 180; angle += 30) {
        servo.setAngle(angle);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (int angle = 180; angle >= 0; angle -= 30) {
        servo.setAngle(angle);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

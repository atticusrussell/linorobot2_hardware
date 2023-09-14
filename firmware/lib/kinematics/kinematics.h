// Copyright (c) 2021 Juan Miguel Jimeno
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "Arduino.h"

#define RPM_TO_RPS 1/60

/// \brief Handles kinematic calculations for robot bases.
class Kinematics
{
    public:
        /// \brief Enum representing types of robot bases.
        enum base {DIFFERENTIAL_DRIVE, SKID_STEER, MECANUM};

        base base_platform_; // Type of robot base/platform

        /// \brief Struct representing RPM of four motors.
        struct rpm
        {
            float motor1;
            float motor2;
            float motor3;
            float motor4;
        };
        
        /// \brief Struct representing linear and angular velocities.
        struct velocities
        {
            float linear_x;
            float linear_y;
            float angular_z;
        };

        /// \brief Struct representing PWM values for four motors.
        struct pwm
        {
            int motor1;
            int motor2;
            int motor3;
            int motor4;
        };

        /** 
         * \brief Constructor to initialize kinematics object.
         * \param robot_base Type of robot base.
         * \param motor_max_rpm Maximum RPM of the motor.
         * \param max_rpm_ratio Ratio of max RPM.
         * \param motor_operating_voltage Operating voltage of the motor.
         * \param motor_power_max_voltage Maximum power voltage of the motor.
         * \param wheel_diameter Diameter of the wheel.
         * \param wheels_y_distance Distance between wheels in Y direction.
         */
        Kinematics(base robot_base, int motor_max_rpm, float max_rpm_ratio,
                   float motor_operating_voltage, float motor_power_max_voltage,
                   float wheel_diameter, float wheels_y_distance);

        /** 
         * \brief Calculate and return robot's linear and angular velocities.
         * \param rpm1 RPM of motor 1.
         * \param rpm2 RPM of motor 2.
         * \param rpm3 RPM of motor 3.
         * \param rpm4 RPM of motor 4.
         * \return Velocities in linear x, y and angular z directions.
         */
        velocities getVelocities(float rpm1, float rpm2, float rpm3, float rpm4);

        /** 
         * \brief Calculate and return required RPMs for motors.
         * \param linear_x Desired linear velocity in x direction.
         * \param linear_y Desired linear velocity in y direction.
         * \param angular_z Desired angular velocity around z-axis.
         * \return RPM values for the motors.
         */
        rpm getRPM(float linear_x, float linear_y, float angular_z);

        /** 
         * \brief Return the maximum RPM value.
         * \return Maximum RPM value.
         */
        float getMaxRPM();

    private:
         /** 
         * \brief Calculate RPMs based on desired velocities.
         * 
         * \param linear_x Desired linear velocity in x direction.
         * \param linear_y Desired linear velocity in y direction.
         * \param angular_z Desired angular velocity around z-axis.
         * \return RPM values for the motors.
         */
        rpm calculateRPM(float linear_x, float linear_y, float angular_z);

        /** 
         * \brief Return number of wheels based on robot base type.
         * 
         * \param robot_base Type of robot base.
         * \return Number of wheels for the given robot base.
         */
        int getTotalWheels(base robot_base);

        float max_rpm_;
        float wheels_y_distance_;
        float pwm_res_;
        float wheel_circumference_;
        int total_wheels_;
};

#endif

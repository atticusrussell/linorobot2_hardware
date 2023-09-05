/**
 * @file test_pid.cpp
 * @brief Unit tests for the PID controller class.
 *
 * This file contains unit tests for the PID controller class to ensure its correct functionality.
 */

#include <unity.h>
#include "pid.h"

#ifdef DESKTOP
#include <ArduinoFake.h>
#endif

#define PWM_BITS 10
#define PWM_MAX pow(2, PWM_BITS) - 1
#define PWM_MIN -PWM_MAX
#define K_P 0.6                             // P constant
#define K_I 0.8                             // I constant
#define K_D 0.5                             // D constant

PID dut_pid(PWM_MIN, PWM_MAX, K_P, K_I, K_D);

void setUp(void) {
     // Reset PID internal states by reinitializing
    dut_pid = PID(PWM_MIN, PWM_MAX, K_P, K_I, K_D);
    // dut_pid.updateConstants(K_P, K_I, K_D); // Reset the constants
}

void tearDown(void){
    // no cleanup necessary
}

/**
 * @brief A system in the desired state should not have any correction
 * 
 */
void test_compute_zero_error() {
    double output = dut_pid.compute(100, 100);
    TEST_ASSERT_FLOAT_WITHIN(1e-10, 0, output); // Check if output is within a small tolerance of 0
}

/**
 * @brief Test if the feedback is positive when measured value is less than the setpoint
 * 
 */
void test_positive_feedback(){
    double output = dut_pid.compute(100, 90);
    TEST_ASSERT_GREATER_THAN_DOUBLE(0,output);
}

/**
 * @brief Test if the feedback is negative when measured value is greater than the setpoint
 * 
 */
void test_negative_feedback(){
    double output = dut_pid.compute(90, 100);
    TEST_ASSERT_LESS_THAN_DOUBLE(0,output);
}

// TODO comment
void test_output_constrain() {
    double output = dut_pid.compute(1000, 0); // This will produce a large error
    TEST_ASSERT_TRUE(output <= PWM_MAX && output >= PWM_MIN);
}

// TODO test updating constants by setting KI and KD 0

// TODO write a test for integral windup

// TODO model a real PID system



int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_compute_zero_error);
    RUN_TEST(test_positive_feedback);
    RUN_TEST(test_negative_feedback);
    RUN_TEST(test_output_constrain);
    UNITY_END();
}

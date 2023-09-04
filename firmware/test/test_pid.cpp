#include <unity.h>
#include "pid.h"

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
}

void tearDown(void){
    // no cleanup necessary
}

void test_compute_zero_error() {
    double output = dut_pid.compute(100, 100);
    TEST_ASSERT_EQUAL_DOUBLE(0, output);
}

void test_compute_non_zero_error() {
    double output = dut_pid.compute(100, 90);
    double expected_output = K_P * 10; // Only P term contributes as it's the first compute call
    TEST_ASSERT_EQUAL_DOUBLE(expected_output, output);
}

void test_integral_windup() {
    dut_pid.compute(0, 0);
    TEST_ASSERT_EQUAL_DOUBLE(0, dut_pid.getIntegral());
    TEST_ASSERT_EQUAL_DOUBLE(0, dut_pid.getDerivative());
}

void test_output_constrain() {
    double output = dut_pid.compute(1000, 0); // This will produce a large error
    TEST_ASSERT_TRUE(output <= PWM_MAX && output >= PWM_MIN);
}

void test_update_constants() {
    float new_kp = 0.5, new_ki = 0.7, new_kd = 0.4;
    dut_pid.updateConstants(new_kp, new_ki, new_kd);
    double output = dut_pid.compute(100, 90);
    double expected_output = new_kp * 10; // Only P term contributes as it's the first compute call after updating constants
    TEST_ASSERT_EQUAL_DOUBLE(expected_output, output);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_compute_zero_error);
    RUN_TEST(test_compute_non_zero_error);
    RUN_TEST(test_integral_windup);
    RUN_TEST(test_output_constrain);
    RUN_TEST(test_update_constants);
    UNITY_END();
}

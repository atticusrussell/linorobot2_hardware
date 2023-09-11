#include <unity.h>
#include "odometry.h"



// void setUp(void) {
//     // This is run before EACH test
// }

// void tearDown(void) {
//     // This is run after EACH test
// }

// bool compare_rosidl_string(const rosidl_runtime_c__String& ros_string, const char* c_string) {
//     return strcmp(ros_string.data, c_string) == 0;
// }


void test_initialization(void) {
    Odometry odom;
    nav_msgs__msg__Odometry data = odom.getData();

    TEST_ASSERT_EQUAL_FLOAT(0.0, data.pose.pose.position.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0, data.pose.pose.position.y);
    // TEST_ASSERT_TRUE(compare_rosidl_string(data.header.frame_id, "odom"));
    // TEST_ASSERT_TRUE(compare_rosidl_string(data.child_frame_id, "base_footprint"));

}

void test_update_method(void) {
    Odometry odom;
    odom.update(1.0, 1.0, 0.0, 0.0); // 1 second with 1 m/s in x direction

    nav_msgs__msg__Odometry data = odom.getData();

    TEST_ASSERT_EQUAL_FLOAT(1.0, data.pose.pose.position.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0, data.pose.pose.position.y);
    TEST_ASSERT_EQUAL_FLOAT(0.0, data.twist.twist.angular.z);
}

void test_getData_method(void) {
    Odometry odom;
    nav_msgs__msg__Odometry data = odom.getData();

    TEST_ASSERT_EQUAL_FLOAT(0.0, data.pose.pose.position.x);
    TEST_ASSERT_EQUAL_FLOAT(0.0, data.pose.pose.position.y);
}

void test_euler_to_quat_conversion(void) {
    Odometry odom;
    float q[4];
    odom.euler_to_quat(0, 0, 1.5708, q); // 90 degrees or pi/2 radians in yaw

    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.7071, q[0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0, q[1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0, q[2]);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.7071, q[3]);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_initialization);
    RUN_TEST(test_update_method);
    RUN_TEST(test_getData_method);
    RUN_TEST(test_euler_to_quat_conversion);

    UNITY_END();
}

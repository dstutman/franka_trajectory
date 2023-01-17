#include <iostream>

#include <franka/control_types.h>
#include <franka/robot.h>
#include <franka/robot_state.h>

#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/Geometry>

#include "trajectories.hpp"
#include "executor.hpp"

#include "camera.hpp"

int main() {
    auto camera = Camera::Camera();
    camera.capture_to_file("Test");
}

//int main()
//{
//    // Parameters
//    const auto camera_effector_mass = 1.0;
//    const std::array<double, 3UL> camera_effector_mass_offset = {0., 0., 0.05};
//    const std::array<double, 9UL> camera_effector_inertia = {0., 0., 0., 0., 0., 0., 0., 0., 0.};
//
//    // Configuration
//    const auto realtime_config = franka::RealtimeConfig::kIgnore;
//
//    // Create the robot
//    auto robot = franka::Robot("172.16.0.2", realtime_config);
//
//    // Reset the robot
//    robot.automaticErrorRecovery();
//    robot.setLoad(camera_effector_mass, camera_effector_mass_offset, camera_effector_inertia);
//
//    // Unlock all joints and seek the bounding box
//    robot.setGuidingMode({true, true, true, true, true, true}, true);
//    std::cout << "Line the effector up with the base of the satellite and hit enter\n";
//    std::cin.get();
//
//    // Get the homogenous transformation matrix of the current position and wait
//    auto state = robot.readOnce();
//    std::cout << "Hit enter when clear to continue\n";
//    std::cin.get();
//
//    //auto effector_pose = Eigen::Matrix4<double>(state.O_T_EE.data());
//    //auto effector_orientation = effector_pose.block<3, 3>(0, 0);
//    //auto effector_position = effector_pose.block<3, 1>(3, 0);
////
//    //// Determine Dephi's COM location in the base frame
//    //Eigen::Vector3<double> delfi_com_offset = {0, 0, 0.25}; // FIXME: Offset from base of Delfi to COM
//    //auto delfi_position = effector_position + effector_orientation.inverse() * delfi_com_offset;
//
//    // Execute the trajectory
//    const auto initial_time = std::chrono::system_clock::now();
//    const auto exec_config = Executor::ExecutorConfiguration{
//        trajectory : Trajectories::line_generator(Eigen::Vector3d(0., 0., 0.), Eigen::Vector3d(1., 0., 0.), Eigen::Quaterniond()),
//        trajectory_duration : 60.0,
//    };
//    auto exec_state = Executor::ExecutorState{
//        // NOTE: Narrowing ok if trajectory time sufficiently short
//        t : 0,
//    };
//    auto executor = Executor::executor_generator(exec_config, &exec_state);
//    robot.control(executor);
//
//    robot.stop();
//}
#pragma once

#include <array>
#include <functional>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <franka/control_types.h>

namespace Trajectories
{
    typedef struct Pose
    {
        Eigen::Vector3d position;
        Eigen::Quaterniond orientation;

        operator franka::CartesianPose() const {
            const Eigen::Matrix3d orientation_matrix = this->orientation.toRotationMatrix();
            Eigen::Matrix4d homogenous_transformation = Eigen::Matrix4d();
            homogenous_transformation.topLeftCorner<3, 3>() = orientation_matrix;
            homogenous_transformation.block<3, 1>(3, 0) = this->position;
            homogenous_transformation(3, 3) = 1.;

            // Gruesome conversion for libfranka
            // TODO: Do this better
            auto array = std::array<double, 16>();
            for (uint i = 0; i < 16; i++) {
                array[i] = homogenous_transformation.data()[i];
            }
            return franka::CartesianPose(array);
        }
    } Pose;
    
    /// @brief Trajectory defined as a function of a parameter
    /// @details Accepts a parameter from 0. to 1. inclusive and returns a pose
    typedef std::function<Pose(double)> Trajectory;

    const Trajectory line_generator(const Eigen::Vector3d from, const Eigen::Vector3d to, const Eigen::Quaterniond orientation);
}
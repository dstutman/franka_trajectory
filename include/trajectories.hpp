#pragma once

#include <functional>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace Trajectories
{
    typedef struct
    {
        Eigen::Vector3d position;
        Eigen::Quaterniond orientation;
    } Pose;

    /// @brief Trajectory defined as a function of a parameter
    /// @details Accepts a parameter from 0. to 1. inclusive and returns a pose
    typedef std::function<Pose(double)> Trajectory;

    const Trajectory line_generator(const Eigen::Vector3d from, const Eigen::Vector3d to, const Eigen::Quaterniond orientation)
    {
        return [to, from, orientation](double t) -> Pose
        {
            assert(t > 0.0);
            assert(t < 1.0);
            return Pose{position : t * (to - from) + from, orientation : orientation};
        };
    }
}
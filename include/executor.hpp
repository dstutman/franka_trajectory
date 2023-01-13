#pragma once

#include <franka/robot.h>
#include <franka/robot_state.h>

#include "trajectories.hpp"

namespace Executor {
    typedef struct {
        Trajectories::Trajectory trajectory;
        double trajectory_duration;
    } ExecutorConfiguration;

    typedef struct
    {
        double t;
    } ExecutorState;

    typedef std::function<franka::CartesianPose(const franka::RobotState &, franka::Duration)> Executor;

    Executor executor_generator(const ExecutorConfiguration config, ExecutorState *const state);
}
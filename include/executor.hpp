#pragma once

#include <franka/robot.h>

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
    
    bool loop(const ExecutorConfiguration config, ExecutorState *const state, franka::Robot *const robot);
}
#include "executor.hpp"

namespace Executor
{

     Executor executor_generator(const ExecutorConfiguration exec_config, ExecutorState *const exec_state) {
        return [exec_config, exec_state](const franka::RobotState & robot_state, franka::Duration duration) -> franka::CartesianPose {
            exec_state->t += duration.toSec();
            const auto fraction = exec_state->t / exec_config.trajectory_duration;
            return exec_config.trajectory(fraction);
        };
    }
}
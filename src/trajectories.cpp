#include "trajectories.hpp"

namespace Trajectories
{
    const Trajectory line_generator(const Eigen::Vector3d from, const Eigen::Vector3d to, const Eigen::Quaterniond orientation)
    {
        return [to, from, orientation](double t) -> Pose
        {
            assert(t >= 0.0);
            assert(t <= 1.0);
            return Pose{position : t * (to - from) + from, orientation : orientation};
        };
    }
}
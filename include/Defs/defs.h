/** @file defs.h
*
* Simulator definitions
*
*/

#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <cstdint>
#include <vector>
#include <memory>
#include <cmath>
#include "../../3rdParty/Eigen/Geometry"

/// putslam name space
namespace simulator {

    /// putslam default floating point
    typedef double float_type;

    /// 3 element vector class
    typedef Eigen::Translation<float_type,3> Vec3;

    /// Matrix representation of SO(3) group of rotations
    typedef Eigen::Matrix<float_type,3,3> Mat33;

    /// Quaternion representation of SO(3) group of rotations
    typedef Eigen::Quaternion<float_type> Quaternion;

	/// Homogeneous representation of SE(3) rigid body transformations
    typedef Eigen::Transform<double, 3, Eigen::Affine> Mat34;

    /// configuration of the robot
    typedef std::vector<float_type> RobotConfiguration;

    class TorqueForce {
    public:
        ///force values
        Vec3 force;

        ///torque values
        Vec3 torque;

        ///susceptibility values
        std::vector<float_type> susceptibility;

    };

    class RogidBody {
    public:
        /// mass
        float_type mass;

        /// size
        Vec3 size;

        /// center
        Vec3 center;

        /// orientation
        Quaternion orientation;
    };
    //exception class goes here

}

#endif // DEFS_H_INCLUDED

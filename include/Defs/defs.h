/** @file defs.h
*
* Tutorial definitions
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
namespace tutorial {

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

    /// 3D point representation
    typedef Vec3 Point3D;

    /// 3D point cloud representation
    typedef std::vector<Point3D> PointCloud;

    /// Sensor Frame representation
    class SensorFrame {
        public:
            /// sequence of images
            typedef std::vector<SensorFrame> Seq;

            /// XYZ point cloud
            PointCloud cloud;

            /// timestamp
            float_type timestamp;

            /// Default constructor
            inline SensorFrame() : timestamp(0){
            }
    };

    //exception class goes here

}

#endif // DEFS_H_INCLUDED

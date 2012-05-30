/**
 * @brief Custom point types for pcl point cloud.
 */
#ifndef POINT_TYPES_H
#define POINT_TYPES_H

#include <pcl/point_types.h>

//struct EIGEN_ALIGN16 PointWithIndex
//{
//  PCL_ADD_POINT4D; // This adds the members x,y,z which can also be accessed using the point (which is float[4])
//  int index;
//  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
//};

struct EIGEN_ALIGN16 PointXYZRGBT
{
  PCL_ADD_POINT4D; // This adds the members x,y,z which can also be accessed using the point (which is float[4])
  // color
  union
  {
    union
    {
      struct
      {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t _unused;
      };
      float rgb;
    };
    uint32_t rgba;
  };
  uint8_t traversable;

  //! Set traversability and automaticly change color.
  void setTraversability(bool trav)
  {
      traversable = trav;
      if (trav) {
          r = 0; g = 255; b = 0;
      } else {
          r = 255; g = 0; b = 0;
      }
  }

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
//! overload << for easy debug output
inline std::ostream& operator << (std::ostream& os, const PointXYZRGBT& p)
{
    os << "(" << p.x << "," << p.y << "," << p.z << " - " << (p.traversable ? "traversable" : "untraversable")
            << " - RGB = " << (int)p.r << "," << (int)p.g << "," << (int)p.b << ")";
  return (os);
}

//POINT_CLOUD_REGISTER_POINT_STRUCT (PointWithIndex,
//    (float, x, x)
//    (float, y, y)
//    (float, z, z)
//    (int, index, index)
//)
POINT_CLOUD_REGISTER_POINT_STRUCT (PointXYZRGBT,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (float, rgb, rgb)
    (uint8_t, traversable, traversable)
)

#endif // POINT_TYPES_H

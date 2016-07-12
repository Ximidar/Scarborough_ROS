/* Auto-generated by genmsg_cpp for file /home/ubuntu/workspace/sandbox/scarborough/msg/Desired_Directions.msg */
#ifndef SCARBOROUGH_MESSAGE_DESIRED_DIRECTIONS_H
#define SCARBOROUGH_MESSAGE_DESIRED_DIRECTIONS_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace scarborough
{
template <class ContainerAllocator>
struct Desired_Directions_ {
  typedef Desired_Directions_<ContainerAllocator> Type;

  Desired_Directions_()
  : rotation()
  , throttle(0)
  , depth(0.0)
  {
    rotation.assign(0.0);
  }

  Desired_Directions_(const ContainerAllocator& _alloc)
  : rotation()
  , throttle(0)
  , depth(0.0)
  {
    rotation.assign(0.0);
  }

  typedef boost::array<float, 3>  _rotation_type;
  boost::array<float, 3>  rotation;

  typedef int32_t _throttle_type;
  int32_t throttle;

  typedef float _depth_type;
  float depth;


  typedef boost::shared_ptr< ::scarborough::Desired_Directions_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::scarborough::Desired_Directions_<ContainerAllocator>  const> ConstPtr;
}; // struct Desired_Directions
typedef  ::scarborough::Desired_Directions_<std::allocator<void> > Desired_Directions;

typedef boost::shared_ptr< ::scarborough::Desired_Directions> Desired_DirectionsPtr;
typedef boost::shared_ptr< ::scarborough::Desired_Directions const> Desired_DirectionsConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::scarborough::Desired_Directions_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::scarborough::Desired_Directions_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace scarborough

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::scarborough::Desired_Directions_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::scarborough::Desired_Directions_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::scarborough::Desired_Directions_<ContainerAllocator> > {
  static const char* value() 
  {
    return "b52e1a589c56fcea3b3260406f15fe61";
  }

  static const char* value(const  ::scarborough::Desired_Directions_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xb52e1a589c56fceaULL;
  static const uint64_t static_value2 = 0x3b3260406f15fe61ULL;
};

template<class ContainerAllocator>
struct DataType< ::scarborough::Desired_Directions_<ContainerAllocator> > {
  static const char* value() 
  {
    return "scarborough/Desired_Directions";
  }

  static const char* value(const  ::scarborough::Desired_Directions_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::scarborough::Desired_Directions_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float32[3] rotation\n\
int32 throttle\n\
float32 depth\n\
";
  }

  static const char* value(const  ::scarborough::Desired_Directions_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::scarborough::Desired_Directions_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::scarborough::Desired_Directions_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.rotation);
    stream.next(m.throttle);
    stream.next(m.depth);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Desired_Directions_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::scarborough::Desired_Directions_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::scarborough::Desired_Directions_<ContainerAllocator> & v) 
  {
    s << indent << "rotation[]" << std::endl;
    for (size_t i = 0; i < v.rotation.size(); ++i)
    {
      s << indent << "  rotation[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.rotation[i]);
    }
    s << indent << "throttle: ";
    Printer<int32_t>::stream(s, indent + "  ", v.throttle);
    s << indent << "depth: ";
    Printer<float>::stream(s, indent + "  ", v.depth);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SCARBOROUGH_MESSAGE_DESIRED_DIRECTIONS_H


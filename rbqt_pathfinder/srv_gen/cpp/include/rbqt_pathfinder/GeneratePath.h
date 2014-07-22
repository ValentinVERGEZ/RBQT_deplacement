/* Auto-generated by genmsg_cpp for file /home/thomas/Documents/Robocup2014/RBQT_deplacement/rbqt_pathfinder/srv/GeneratePath.srv */
#ifndef RBQT_PATHFINDER_SERVICE_GENERATEPATH_H
#define RBQT_PATHFINDER_SERVICE_GENERATEPATH_H
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

#include "ros/service_traits.h"

#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Pose.h"



namespace rbqt_pathfinder
{
template <class ContainerAllocator>
struct GeneratePathRequest_ {
  typedef GeneratePathRequest_<ContainerAllocator> Type;

  GeneratePathRequest_()
  : id(0)
  , Arrivee()
  , Depart()
  , utilisePositionOdometry(false)
  {
  }

  GeneratePathRequest_(const ContainerAllocator& _alloc)
  : id(0)
  , Arrivee(_alloc)
  , Depart(_alloc)
  , utilisePositionOdometry(false)
  {
  }

  typedef int16_t _id_type;
  int16_t id;

  typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _Arrivee_type;
   ::geometry_msgs::Pose_<ContainerAllocator>  Arrivee;

  typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _Depart_type;
   ::geometry_msgs::Pose_<ContainerAllocator>  Depart;

  typedef uint8_t _utilisePositionOdometry_type;
  uint8_t utilisePositionOdometry;


  typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct GeneratePathRequest
typedef  ::rbqt_pathfinder::GeneratePathRequest_<std::allocator<void> > GeneratePathRequest;

typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathRequest> GeneratePathRequestPtr;
typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathRequest const> GeneratePathRequestConstPtr;


template <class ContainerAllocator>
struct GeneratePathResponse_ {
  typedef GeneratePathResponse_<ContainerAllocator> Type;

  GeneratePathResponse_()
  : requeteAcceptee(false)
  {
  }

  GeneratePathResponse_(const ContainerAllocator& _alloc)
  : requeteAcceptee(false)
  {
  }

  typedef uint8_t _requeteAcceptee_type;
  uint8_t requeteAcceptee;


  typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct GeneratePathResponse
typedef  ::rbqt_pathfinder::GeneratePathResponse_<std::allocator<void> > GeneratePathResponse;

typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathResponse> GeneratePathResponsePtr;
typedef boost::shared_ptr< ::rbqt_pathfinder::GeneratePathResponse const> GeneratePathResponseConstPtr;

struct GeneratePath
{

typedef GeneratePathRequest Request;
typedef GeneratePathResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct GeneratePath
} // namespace rbqt_pathfinder

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "edb2258c032277b1d3770145a3d8a29f";
  }

  static const char* value(const  ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xedb2258c032277b1ULL;
  static const uint64_t static_value2 = 0xd3770145a3d8a29fULL;
};

template<class ContainerAllocator>
struct DataType< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rbqt_pathfinder/GeneratePathRequest";
  }

  static const char* value(const  ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int16  id\n\
geometry_msgs/Pose  Arrivee\n\
geometry_msgs/Pose  Depart\n\
bool    utilisePositionOdometry\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
";
  }

  static const char* value(const  ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "a34a7c545fdef613738b1142b9a33144";
  }

  static const char* value(const  ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xa34a7c545fdef613ULL;
  static const uint64_t static_value2 = 0x738b1142b9a33144ULL;
};

template<class ContainerAllocator>
struct DataType< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rbqt_pathfinder/GeneratePathResponse";
  }

  static const char* value(const  ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "bool    requeteAcceptee\n\
\n\
";
  }

  static const char* value(const  ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.id);
    stream.next(m.Arrivee);
    stream.next(m.Depart);
    stream.next(m.utilisePositionOdometry);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct GeneratePathRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.requeteAcceptee);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct GeneratePathResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<rbqt_pathfinder::GeneratePath> {
  static const char* value() 
  {
    return "c87f6c6dcb2875066c4354235cdff733";
  }

  static const char* value(const rbqt_pathfinder::GeneratePath&) { return value(); } 
};

template<>
struct DataType<rbqt_pathfinder::GeneratePath> {
  static const char* value() 
  {
    return "rbqt_pathfinder/GeneratePath";
  }

  static const char* value(const rbqt_pathfinder::GeneratePath&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "c87f6c6dcb2875066c4354235cdff733";
  }

  static const char* value(const rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rbqt_pathfinder/GeneratePath";
  }

  static const char* value(const rbqt_pathfinder::GeneratePathRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "c87f6c6dcb2875066c4354235cdff733";
  }

  static const char* value(const rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rbqt_pathfinder/GeneratePath";
  }

  static const char* value(const rbqt_pathfinder::GeneratePathResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // RBQT_PATHFINDER_SERVICE_GENERATEPATH_H


// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msg_format:srv/PlcFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__PLC_FORMAT__STRUCT_HPP_
#define MSG_FORMAT__SRV__DETAIL__PLC_FORMAT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__msg_format__srv__PlcFormat_Request __attribute__((deprecated))
#else
# define DEPRECATED__msg_format__srv__PlcFormat_Request __declspec(deprecated)
#endif

namespace msg_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlcFormat_Request_
{
  using Type = PlcFormat_Request_<ContainerAllocator>;

  explicit PlcFormat_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
    }
  }

  explicit PlcFormat_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : action(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
    }
  }

  // field types and members
  using _action_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _action_type action;

  // setters for named parameter idiom
  Type & set__action(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->action = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msg_format::srv::PlcFormat_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const msg_format::srv::PlcFormat_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::PlcFormat_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::PlcFormat_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msg_format__srv__PlcFormat_Request
    std::shared_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msg_format__srv__PlcFormat_Request
    std::shared_ptr<msg_format::srv::PlcFormat_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlcFormat_Request_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlcFormat_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlcFormat_Request_

// alias to use template instance with default allocator
using PlcFormat_Request =
  msg_format::srv::PlcFormat_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace msg_format


#ifndef _WIN32
# define DEPRECATED__msg_format__srv__PlcFormat_Response __attribute__((deprecated))
#else
# define DEPRECATED__msg_format__srv__PlcFormat_Response __declspec(deprecated)
#endif

namespace msg_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct PlcFormat_Response_
{
  using Type = PlcFormat_Response_<ContainerAllocator>;

  explicit PlcFormat_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = "";
    }
  }

  explicit PlcFormat_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = "";
    }
  }

  // field types and members
  using _result_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msg_format::srv::PlcFormat_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const msg_format::srv::PlcFormat_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::PlcFormat_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::PlcFormat_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msg_format__srv__PlcFormat_Response
    std::shared_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msg_format__srv__PlcFormat_Response
    std::shared_ptr<msg_format::srv::PlcFormat_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PlcFormat_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const PlcFormat_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PlcFormat_Response_

// alias to use template instance with default allocator
using PlcFormat_Response =
  msg_format::srv::PlcFormat_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace msg_format

namespace msg_format
{

namespace srv
{

struct PlcFormat
{
  using Request = msg_format::srv::PlcFormat_Request;
  using Response = msg_format::srv::PlcFormat_Response;
};

}  // namespace srv

}  // namespace msg_format

#endif  // MSG_FORMAT__SRV__DETAIL__PLC_FORMAT__STRUCT_HPP_

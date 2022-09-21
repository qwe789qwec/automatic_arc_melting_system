// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msg_format:srv/WeighingFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__STRUCT_HPP_
#define MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__msg_format__srv__WeighingFormat_Request __attribute__((deprecated))
#else
# define DEPRECATED__msg_format__srv__WeighingFormat_Request __declspec(deprecated)
#endif

namespace msg_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct WeighingFormat_Request_
{
  using Type = WeighingFormat_Request_<ContainerAllocator>;

  explicit WeighingFormat_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
    }
  }

  explicit WeighingFormat_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    msg_format::srv::WeighingFormat_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const msg_format::srv::WeighingFormat_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::WeighingFormat_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::WeighingFormat_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msg_format__srv__WeighingFormat_Request
    std::shared_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msg_format__srv__WeighingFormat_Request
    std::shared_ptr<msg_format::srv::WeighingFormat_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeighingFormat_Request_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeighingFormat_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeighingFormat_Request_

// alias to use template instance with default allocator
using WeighingFormat_Request =
  msg_format::srv::WeighingFormat_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace msg_format


#ifndef _WIN32
# define DEPRECATED__msg_format__srv__WeighingFormat_Response __attribute__((deprecated))
#else
# define DEPRECATED__msg_format__srv__WeighingFormat_Response __declspec(deprecated)
#endif

namespace msg_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct WeighingFormat_Response_
{
  using Type = WeighingFormat_Response_<ContainerAllocator>;

  explicit WeighingFormat_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = "";
    }
  }

  explicit WeighingFormat_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    msg_format::srv::WeighingFormat_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const msg_format::srv::WeighingFormat_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::WeighingFormat_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msg_format::srv::WeighingFormat_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msg_format__srv__WeighingFormat_Response
    std::shared_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msg_format__srv__WeighingFormat_Response
    std::shared_ptr<msg_format::srv::WeighingFormat_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WeighingFormat_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const WeighingFormat_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WeighingFormat_Response_

// alias to use template instance with default allocator
using WeighingFormat_Response =
  msg_format::srv::WeighingFormat_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace msg_format

namespace msg_format
{

namespace srv
{

struct WeighingFormat
{
  using Request = msg_format::srv::WeighingFormat_Request;
  using Response = msg_format::srv::WeighingFormat_Response;
};

}  // namespace srv

}  // namespace msg_format

#endif  // MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__STRUCT_HPP_

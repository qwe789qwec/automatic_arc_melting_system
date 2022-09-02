// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from tcp_format:srv/CobottaBcap.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__STRUCT_HPP_
#define TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__tcp_format__srv__CobottaBcap_Request __attribute__((deprecated))
#else
# define DEPRECATED__tcp_format__srv__CobottaBcap_Request __declspec(deprecated)
#endif

namespace tcp_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CobottaBcap_Request_
{
  using Type = CobottaBcap_Request_<ContainerAllocator>;

  explicit CobottaBcap_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
      this->target = "";
    }
  }

  explicit CobottaBcap_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : action(_alloc),
    target(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->action = "";
      this->target = "";
    }
  }

  // field types and members
  using _action_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _action_type action;
  using _target_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _target_type target;

  // setters for named parameter idiom
  Type & set__action(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->action = _arg;
    return *this;
  }
  Type & set__target(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->target = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    tcp_format::srv::CobottaBcap_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const tcp_format::srv::CobottaBcap_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::CobottaBcap_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::CobottaBcap_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__tcp_format__srv__CobottaBcap_Request
    std::shared_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__tcp_format__srv__CobottaBcap_Request
    std::shared_ptr<tcp_format::srv::CobottaBcap_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CobottaBcap_Request_ & other) const
  {
    if (this->action != other.action) {
      return false;
    }
    if (this->target != other.target) {
      return false;
    }
    return true;
  }
  bool operator!=(const CobottaBcap_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CobottaBcap_Request_

// alias to use template instance with default allocator
using CobottaBcap_Request =
  tcp_format::srv::CobottaBcap_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace tcp_format


#ifndef _WIN32
# define DEPRECATED__tcp_format__srv__CobottaBcap_Response __attribute__((deprecated))
#else
# define DEPRECATED__tcp_format__srv__CobottaBcap_Response __declspec(deprecated)
#endif

namespace tcp_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CobottaBcap_Response_
{
  using Type = CobottaBcap_Response_<ContainerAllocator>;

  explicit CobottaBcap_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = "";
      this->message = "";
    }
  }

  explicit CobottaBcap_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : status(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = "";
      this->message = "";
    }
  }

  // field types and members
  using _status_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _status_type status;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__status(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    tcp_format::srv::CobottaBcap_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const tcp_format::srv::CobottaBcap_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::CobottaBcap_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::CobottaBcap_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__tcp_format__srv__CobottaBcap_Response
    std::shared_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__tcp_format__srv__CobottaBcap_Response
    std::shared_ptr<tcp_format::srv::CobottaBcap_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CobottaBcap_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const CobottaBcap_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CobottaBcap_Response_

// alias to use template instance with default allocator
using CobottaBcap_Response =
  tcp_format::srv::CobottaBcap_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace tcp_format

namespace tcp_format
{

namespace srv
{

struct CobottaBcap
{
  using Request = tcp_format::srv::CobottaBcap_Request;
  using Response = tcp_format::srv::CobottaBcap_Response;
};

}  // namespace srv

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__STRUCT_HPP_

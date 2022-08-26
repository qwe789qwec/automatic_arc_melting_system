// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from tcp_format:srv/SocketCreat.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_CREAT__STRUCT_HPP_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_CREAT__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__tcp_format__srv__SocketCreat_Request __attribute__((deprecated))
#else
# define DEPRECATED__tcp_format__srv__SocketCreat_Request __declspec(deprecated)
#endif

namespace tcp_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SocketCreat_Request_
{
  using Type = SocketCreat_Request_<ContainerAllocator>;

  explicit SocketCreat_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_ip = "";
      this->target_port = "";
    }
  }

  explicit SocketCreat_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target_ip(_alloc),
    target_port(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_ip = "";
      this->target_port = "";
    }
  }

  // field types and members
  using _target_ip_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _target_ip_type target_ip;
  using _target_port_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _target_port_type target_port;

  // setters for named parameter idiom
  Type & set__target_ip(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->target_ip = _arg;
    return *this;
  }
  Type & set__target_port(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->target_port = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    tcp_format::srv::SocketCreat_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const tcp_format::srv::SocketCreat_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::SocketCreat_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::SocketCreat_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__tcp_format__srv__SocketCreat_Request
    std::shared_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__tcp_format__srv__SocketCreat_Request
    std::shared_ptr<tcp_format::srv::SocketCreat_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SocketCreat_Request_ & other) const
  {
    if (this->target_ip != other.target_ip) {
      return false;
    }
    if (this->target_port != other.target_port) {
      return false;
    }
    return true;
  }
  bool operator!=(const SocketCreat_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SocketCreat_Request_

// alias to use template instance with default allocator
using SocketCreat_Request =
  tcp_format::srv::SocketCreat_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace tcp_format


#ifndef _WIN32
# define DEPRECATED__tcp_format__srv__SocketCreat_Response __attribute__((deprecated))
#else
# define DEPRECATED__tcp_format__srv__SocketCreat_Response __declspec(deprecated)
#endif

namespace tcp_format
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SocketCreat_Response_
{
  using Type = SocketCreat_Response_<ContainerAllocator>;

  explicit SocketCreat_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = "";
      this->socket_fd = 0ll;
    }
  }

  explicit SocketCreat_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : status(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = "";
      this->socket_fd = 0ll;
    }
  }

  // field types and members
  using _status_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _status_type status;
  using _socket_fd_type =
    int64_t;
  _socket_fd_type socket_fd;

  // setters for named parameter idiom
  Type & set__status(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__socket_fd(
    const int64_t & _arg)
  {
    this->socket_fd = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    tcp_format::srv::SocketCreat_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const tcp_format::srv::SocketCreat_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::SocketCreat_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      tcp_format::srv::SocketCreat_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__tcp_format__srv__SocketCreat_Response
    std::shared_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__tcp_format__srv__SocketCreat_Response
    std::shared_ptr<tcp_format::srv::SocketCreat_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SocketCreat_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->socket_fd != other.socket_fd) {
      return false;
    }
    return true;
  }
  bool operator!=(const SocketCreat_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SocketCreat_Response_

// alias to use template instance with default allocator
using SocketCreat_Response =
  tcp_format::srv::SocketCreat_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace tcp_format

namespace tcp_format
{

namespace srv
{

struct SocketCreat
{
  using Request = tcp_format::srv::SocketCreat_Request;
  using Response = tcp_format::srv::SocketCreat_Response;
};

}  // namespace srv

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_CREAT__STRUCT_HPP_

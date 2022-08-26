# generated from rosidl_generator_py/resource/_idl.py.em
# with input from tcp_format:srv/SocketMessage.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SocketMessage_Request(type):
    """Metaclass of message 'SocketMessage_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('tcp_format')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'tcp_format.srv.SocketMessage_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_message__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_message__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_message__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_message__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_message__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketMessage_Request(metaclass=Metaclass_SocketMessage_Request):
    """Message class 'SocketMessage_Request'."""

    __slots__ = [
        '_socket_fd',
        '_send_message',
    ]

    _fields_and_field_types = {
        'socket_fd': 'int64',
        'send_message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.socket_fd = kwargs.get('socket_fd', int())
        self.send_message = kwargs.get('send_message', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.socket_fd != other.socket_fd:
            return False
        if self.send_message != other.send_message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def socket_fd(self):
        """Message field 'socket_fd'."""
        return self._socket_fd

    @socket_fd.setter
    def socket_fd(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'socket_fd' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'socket_fd' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._socket_fd = value

    @property
    def send_message(self):
        """Message field 'send_message'."""
        return self._send_message

    @send_message.setter
    def send_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'send_message' field must be of type 'str'"
        self._send_message = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_SocketMessage_Response(type):
    """Metaclass of message 'SocketMessage_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('tcp_format')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'tcp_format.srv.SocketMessage_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_message__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_message__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_message__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_message__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_message__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketMessage_Response(metaclass=Metaclass_SocketMessage_Response):
    """Message class 'SocketMessage_Response'."""

    __slots__ = [
        '_status',
        '_receive_message',
    ]

    _fields_and_field_types = {
        'status': 'string',
        'receive_message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', str())
        self.receive_message = kwargs.get('receive_message', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.status != other.status:
            return False
        if self.receive_message != other.receive_message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'status' field must be of type 'str'"
        self._status = value

    @property
    def receive_message(self):
        """Message field 'receive_message'."""
        return self._receive_message

    @receive_message.setter
    def receive_message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'receive_message' field must be of type 'str'"
        self._receive_message = value


class Metaclass_SocketMessage(type):
    """Metaclass of service 'SocketMessage'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('tcp_format')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'tcp_format.srv.SocketMessage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__socket_message

            from tcp_format.srv import _socket_message
            if _socket_message.Metaclass_SocketMessage_Request._TYPE_SUPPORT is None:
                _socket_message.Metaclass_SocketMessage_Request.__import_type_support__()
            if _socket_message.Metaclass_SocketMessage_Response._TYPE_SUPPORT is None:
                _socket_message.Metaclass_SocketMessage_Response.__import_type_support__()


class SocketMessage(metaclass=Metaclass_SocketMessage):
    from tcp_format.srv._socket_message import SocketMessage_Request as Request
    from tcp_format.srv._socket_message import SocketMessage_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

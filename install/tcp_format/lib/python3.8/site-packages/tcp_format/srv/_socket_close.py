# generated from rosidl_generator_py/resource/_idl.py.em
# with input from tcp_format:srv/SocketClose.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SocketClose_Request(type):
    """Metaclass of message 'SocketClose_Request'."""

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
                'tcp_format.srv.SocketClose_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_close__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_close__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_close__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_close__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_close__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketClose_Request(metaclass=Metaclass_SocketClose_Request):
    """Message class 'SocketClose_Request'."""

    __slots__ = [
        '_socket_fd',
    ]

    _fields_and_field_types = {
        'socket_fd': 'int64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.socket_fd = kwargs.get('socket_fd', int())

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


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_SocketClose_Response(type):
    """Metaclass of message 'SocketClose_Response'."""

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
                'tcp_format.srv.SocketClose_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_close__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_close__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_close__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_close__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_close__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketClose_Response(metaclass=Metaclass_SocketClose_Response):
    """Message class 'SocketClose_Response'."""

    __slots__ = [
        '_status',
    ]

    _fields_and_field_types = {
        'status': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', str())

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


class Metaclass_SocketClose(type):
    """Metaclass of service 'SocketClose'."""

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
                'tcp_format.srv.SocketClose')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__socket_close

            from tcp_format.srv import _socket_close
            if _socket_close.Metaclass_SocketClose_Request._TYPE_SUPPORT is None:
                _socket_close.Metaclass_SocketClose_Request.__import_type_support__()
            if _socket_close.Metaclass_SocketClose_Response._TYPE_SUPPORT is None:
                _socket_close.Metaclass_SocketClose_Response.__import_type_support__()


class SocketClose(metaclass=Metaclass_SocketClose):
    from tcp_format.srv._socket_close import SocketClose_Request as Request
    from tcp_format.srv._socket_close import SocketClose_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

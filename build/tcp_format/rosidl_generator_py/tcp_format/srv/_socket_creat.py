# generated from rosidl_generator_py/resource/_idl.py.em
# with input from tcp_format:srv/SocketCreat.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SocketCreat_Request(type):
    """Metaclass of message 'SocketCreat_Request'."""

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
                'tcp_format.srv.SocketCreat_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_creat__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_creat__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_creat__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_creat__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_creat__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketCreat_Request(metaclass=Metaclass_SocketCreat_Request):
    """Message class 'SocketCreat_Request'."""

    __slots__ = [
        '_target_ip',
        '_target_port',
    ]

    _fields_and_field_types = {
        'target_ip': 'string',
        'target_port': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.target_ip = kwargs.get('target_ip', str())
        self.target_port = kwargs.get('target_port', str())

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
        if self.target_ip != other.target_ip:
            return False
        if self.target_port != other.target_port:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def target_ip(self):
        """Message field 'target_ip'."""
        return self._target_ip

    @target_ip.setter
    def target_ip(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'target_ip' field must be of type 'str'"
        self._target_ip = value

    @property
    def target_port(self):
        """Message field 'target_port'."""
        return self._target_port

    @target_port.setter
    def target_port(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'target_port' field must be of type 'str'"
        self._target_port = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_SocketCreat_Response(type):
    """Metaclass of message 'SocketCreat_Response'."""

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
                'tcp_format.srv.SocketCreat_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_creat__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_creat__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_creat__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_creat__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_creat__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketCreat_Response(metaclass=Metaclass_SocketCreat_Response):
    """Message class 'SocketCreat_Response'."""

    __slots__ = [
        '_status',
        '_socket_fd',
    ]

    _fields_and_field_types = {
        'status': 'string',
        'socket_fd': 'int64',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', str())
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
        if self.status != other.status:
            return False
        if self.socket_fd != other.socket_fd:
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


class Metaclass_SocketCreat(type):
    """Metaclass of service 'SocketCreat'."""

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
                'tcp_format.srv.SocketCreat')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__socket_creat

            from tcp_format.srv import _socket_creat
            if _socket_creat.Metaclass_SocketCreat_Request._TYPE_SUPPORT is None:
                _socket_creat.Metaclass_SocketCreat_Request.__import_type_support__()
            if _socket_creat.Metaclass_SocketCreat_Response._TYPE_SUPPORT is None:
                _socket_creat.Metaclass_SocketCreat_Response.__import_type_support__()


class SocketCreat(metaclass=Metaclass_SocketCreat):
    from tcp_format.srv._socket_creat import SocketCreat_Request as Request
    from tcp_format.srv._socket_creat import SocketCreat_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

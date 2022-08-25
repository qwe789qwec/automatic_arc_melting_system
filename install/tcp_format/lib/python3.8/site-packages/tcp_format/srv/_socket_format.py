# generated from rosidl_generator_py/resource/_idl.py.em
# with input from tcp_format:srv/SocketFormat.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SocketFormat_Request(type):
    """Metaclass of message 'SocketFormat_Request'."""

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
                'tcp_format.srv.SocketFormat_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_format__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_format__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_format__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_format__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_format__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketFormat_Request(metaclass=Metaclass_SocketFormat_Request):
    """Message class 'SocketFormat_Request'."""

    __slots__ = [
        '_target_ip',
        '_target_port',
        '_send_message',
    ]

    _fields_and_field_types = {
        'target_ip': 'string',
        'target_port': 'string',
        'send_message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.target_ip = kwargs.get('target_ip', str())
        self.target_port = kwargs.get('target_port', str())
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
        if self.target_ip != other.target_ip:
            return False
        if self.target_port != other.target_port:
            return False
        if self.send_message != other.send_message:
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


class Metaclass_SocketFormat_Response(type):
    """Metaclass of message 'SocketFormat_Response'."""

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
                'tcp_format.srv.SocketFormat_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__socket_format__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__socket_format__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__socket_format__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__socket_format__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__socket_format__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SocketFormat_Response(metaclass=Metaclass_SocketFormat_Response):
    """Message class 'SocketFormat_Response'."""

    __slots__ = [
        '_error',
        '_receive_message',
    ]

    _fields_and_field_types = {
        'error': 'string',
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
        self.error = kwargs.get('error', str())
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
        if self.error != other.error:
            return False
        if self.receive_message != other.receive_message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def error(self):
        """Message field 'error'."""
        return self._error

    @error.setter
    def error(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'error' field must be of type 'str'"
        self._error = value

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


class Metaclass_SocketFormat(type):
    """Metaclass of service 'SocketFormat'."""

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
                'tcp_format.srv.SocketFormat')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__socket_format

            from tcp_format.srv import _socket_format
            if _socket_format.Metaclass_SocketFormat_Request._TYPE_SUPPORT is None:
                _socket_format.Metaclass_SocketFormat_Request.__import_type_support__()
            if _socket_format.Metaclass_SocketFormat_Response._TYPE_SUPPORT is None:
                _socket_format.Metaclass_SocketFormat_Response.__import_type_support__()


class SocketFormat(metaclass=Metaclass_SocketFormat):
    from tcp_format.srv._socket_format import SocketFormat_Request as Request
    from tcp_format.srv._socket_format import SocketFormat_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

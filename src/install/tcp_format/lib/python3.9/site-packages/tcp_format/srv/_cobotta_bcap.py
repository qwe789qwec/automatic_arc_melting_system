# generated from rosidl_generator_py/resource/_idl.py.em
# with input from tcp_format:srv/CobottaBcap.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CobottaBcap_Request(type):
    """Metaclass of message 'CobottaBcap_Request'."""

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
                'tcp_format.srv.CobottaBcap_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__cobotta_bcap__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__cobotta_bcap__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__cobotta_bcap__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__cobotta_bcap__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__cobotta_bcap__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class CobottaBcap_Request(metaclass=Metaclass_CobottaBcap_Request):
    """Message class 'CobottaBcap_Request'."""

    __slots__ = [
        '_action',
        '_target',
    ]

    _fields_and_field_types = {
        'action': 'string',
        'target': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.action = kwargs.get('action', str())
        self.target = kwargs.get('target', str())

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
        if self.action != other.action:
            return False
        if self.target != other.target:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def action(self):
        """Message field 'action'."""
        return self._action

    @action.setter
    def action(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'action' field must be of type 'str'"
        self._action = value

    @property
    def target(self):
        """Message field 'target'."""
        return self._target

    @target.setter
    def target(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'target' field must be of type 'str'"
        self._target = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_CobottaBcap_Response(type):
    """Metaclass of message 'CobottaBcap_Response'."""

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
                'tcp_format.srv.CobottaBcap_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__cobotta_bcap__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__cobotta_bcap__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__cobotta_bcap__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__cobotta_bcap__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__cobotta_bcap__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class CobottaBcap_Response(metaclass=Metaclass_CobottaBcap_Response):
    """Message class 'CobottaBcap_Response'."""

    __slots__ = [
        '_status',
        '_message',
    ]

    _fields_and_field_types = {
        'status': 'string',
        'message': 'string',
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
        self.message = kwargs.get('message', str())

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
        if self.message != other.message:
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
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_CobottaBcap(type):
    """Metaclass of service 'CobottaBcap'."""

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
                'tcp_format.srv.CobottaBcap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__cobotta_bcap

            from tcp_format.srv import _cobotta_bcap
            if _cobotta_bcap.Metaclass_CobottaBcap_Request._TYPE_SUPPORT is None:
                _cobotta_bcap.Metaclass_CobottaBcap_Request.__import_type_support__()
            if _cobotta_bcap.Metaclass_CobottaBcap_Response._TYPE_SUPPORT is None:
                _cobotta_bcap.Metaclass_CobottaBcap_Response.__import_type_support__()


class CobottaBcap(metaclass=Metaclass_CobottaBcap):
    from tcp_format.srv._cobotta_bcap import CobottaBcap_Request as Request
    from tcp_format.srv._cobotta_bcap import CobottaBcap_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')

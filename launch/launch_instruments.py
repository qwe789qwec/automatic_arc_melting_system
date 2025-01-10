from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='plc_control',
            # namespace='plc',
            executable='PlcControl',
            # name='plc'
        ),
        Node(
            package='slider_control',
            # namespace='slider',
            executable='SliderControl',
            # name='slider'
        ),
        Node(
            package='weighing_control',
            # namespace='weighing',
            executable='WeighingControl',
            # name='weighing'
        ),
        Node(
            package='cobotta_bcap',
            # namespace='cobotta',
            executable='CobottaControl',
            # name='cobotta',
            # arguments=['--test', 'default_topic']
        ),
        Node(
            package='data_handle',
            # namespace='data_handle',
            executable='service',
            # name='data_handle',
            # arguments=['--test', 'default_topic']
        ),
        # Node(
        #     package='camera_control',
        #     # namespace='data_handle',
        #     executable='CameraControl',
        #     # name='data_handle',
        #     # arguments=['--test', 'default_topic']
        # ),
    ])
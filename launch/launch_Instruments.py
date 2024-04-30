from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='plc_control',
            namespace='plc',
            executable='PlcControl',
            name='plc',
            output='screen'
        ),
        Node(
            package='slider_control',
            namespace='slider',
            executable='SliderControl',
            name='slider',
            output='screen'
        ),
        Node(
            package='weighing_control',
            namespace='weighing',
            executable='WeighingControl',
            name='weighing',
            output='screen'
        ),
        Node(
            package='cobotta_bcap',
            namespace='cobotta',
            executable='CobottaControl',
            name='cobotta',
            output='screen'
        ),
    ])
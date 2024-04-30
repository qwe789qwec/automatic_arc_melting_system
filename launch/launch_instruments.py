from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='plc_control',
            # namespace='plc',
            executable='PlcTest',
            # name='plc'
        ),
        Node(
            package='slider_control',
            # namespace='slider',
            executable='SliderTest',
            # name='slider'
        ),
        Node(
            package='weighing_control',
            # namespace='weighing',
            executable='WeighingTest',
            # name='weighing'
        ),
        Node(
            package='cobotta_bcap',
            # namespace='cobotta',
            executable='CobottaTest',
            # name='cobotta',
            # arguments=['--test', 'default_topic']
        ),
    ])
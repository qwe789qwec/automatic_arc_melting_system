from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='plc_control',
            # namespace='plc',
            executable='PlcMain',
            # name='plc'
        ),
        Node(
            package='plc_control',
            # namespace='plcxrd',
            executable='PlcxrdMain',
            # name='plcxrd',
        ),
        Node(
            package='slider_control',
            # namespace='slider',
            executable='SliderMain',
            # name='slider'
        ),
        Node(
            package='weighing_control',
            # namespace='weighing',
            executable='WeighingMain',
            # name='weighing'
        ),
        Node(
            package='cobotta_bcap',
            # namespace='cobotta',
            executable='CobottaMain',
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
    ])
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='plc_control',
            # namespace='plc',
            executable='PlcMain',
            # name='plc',
            emulate_tty=True,
            sigterm_timeout='2'  # <-- 強制終了前の猶予を追加
        ),
        Node(
            package='plc_control',
            # namespace='plcxrd',
            executable='Plcxrd_main',
            # name='plc',
            emulate_tty=True,
            sigterm_timeout='2'  # <-- 強制終了前の猶予を追加
        ),
        Node(
            package='slider_control',
            # namespace='slider',
            executable='SliderMain',
            emulate_tty=True,
            # name='slider'
        ),
        Node(
            package='weighing_control',
            # namespace='weighing',
            executable='WeighingMain',
            emulate_tty=True,
            # name='weighing'
        ),
        Node(
            package='cobotta_bcap',
            # namespace='cobotta',
            executable='CobottaMain',
            emulate_tty=True,
            # name='cobotta',
            # arguments=['--test', 'default_topic']
        ),
        Node(
            package='data_handle',
            # namespace='data_handle',
            executable='service',
            emulate_tty=True,
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
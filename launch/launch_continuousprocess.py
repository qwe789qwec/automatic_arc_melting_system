from launch import LaunchDescription
from launch_ros.actions import Node
import os


def generate_launch_description():
    ws = os.getcwd()
    default_csv = os.path.abspath(os.path.join(ws, 'sequence', 'task.csv'))
    sequence_dir = os.path.abspath(os.path.join(ws, 'sequence'))
    sequence_filename = 'sequence.txt'
    
    return LaunchDescription([
        Node(
            package='csv_workflow_py',
            executable='task_manager_node',
            name='task_manager',
            output='screen',
            parameters=[{
                'csv_path': default_csv
            }],
        ),
        Node(
            package='csv_workflow_py',
            executable='test_sequence_generator_node',
            name='test_sequence_generator',
            output='screen',
            parameters=[{
                'files.sequence.dir': sequence_dir,
                'files.sequence.filename': sequence_filename
            }],
        ),
        Node(
            package='main_process',
            executable='MainProcess',
            name='main_process',
            output='screen',
        ),
    ])
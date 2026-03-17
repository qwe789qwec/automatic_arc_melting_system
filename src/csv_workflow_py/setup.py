from setuptools import setup

package_name = 'csv_workflow_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='song',
    maintainer_email='qwe789qwec@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'task_manager_node = csv_workflow_py.task_manager_node:main',
            # 'test_sequence_generator_node = csv_workflow_py.test_sequence_generator_node:main',
            'sequence_generatorssh_node = csv_workflow_py.sequence_generatorssh_node:main'
        ],
    },
)

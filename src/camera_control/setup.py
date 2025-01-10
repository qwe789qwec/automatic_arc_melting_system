from setuptools import setup

package_name = 'camera_control'
camera = 'camera_control/camera'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name, camera],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='terashima',
    maintainer_email='terashima@gmail.com',
    description='camera record',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'CameraControl = camera_control.camera_control:main',
        ],
    },
)

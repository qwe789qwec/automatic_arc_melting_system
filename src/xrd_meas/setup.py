#!/usr/bin/env python3
from setuptools import setup

package_name = 'xrd_meas'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'ros2_utils_py'],
    zip_safe=True,
    maintainer='song',
    maintainer_email='qwe789qwec@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'XrdMeas = xrd_meas.xrd_main:main'
        ],
    },
)

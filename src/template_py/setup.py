from setuptools import setup

package_name = 'template_py'
instrument = 'template_py/instrument'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name, instrument],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'ros2_utils_py'],
    zip_safe=True,
    maintainer='wilson',
    maintainer_email='qwe789qwec@gmail.com',
    description='template for python ROS2 package',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'InstrumentPMain = template_py.instrument_main:main',
        ],
    },
)

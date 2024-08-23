from setuptools import setup

package_name = 'data_handle'
data_record = 'data_handle/data_record'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name, data_record],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='song',
    maintainer_email='qwe789qwec@gmail.com',
    description='handles output of ros2 and make a record file',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'service = data_handle.data_handle:main',
            'subscribe_data = data_handle.subscribe_data:main',
        ],
    },
)

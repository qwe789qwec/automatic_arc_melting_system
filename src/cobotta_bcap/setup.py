from setuptools import setup

package_name = 'cobotta_bcap'
pybcapclient = 'cobotta_bcap/pybcapclient'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name, pybcapclient],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='wilson',
    maintainer_email='qwe789qwec@gmail.com',
    description='control cobotta by bcap protocol',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'service = cobotta_bcap.io_control_service:main',
            'client = cobotta_bcap.cobotta_client:main',
        ],
    },
)

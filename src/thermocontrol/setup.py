from setuptools import setup

package_name = 'thermocontrol'

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
    maintainer='wang',
    maintainer_email='qwe789qwec@gmail.com',
    description='thermo control',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'service = thermocontrol.furnaceOne:main',
            'client = thermocontrol.furanceTest:main',
        ],
    },
)

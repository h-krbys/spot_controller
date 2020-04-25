# spotmicroai_controllers

## Package List

| Package | Detail |
| --- | --- |
| spot_description | urdf model of spotmicroai |
| spot_driver      | hardware managemant |
| spot_interface   | control interface |
| spot_planner     | motion planner (mainly walk) |

## Dependency

This package depends on following packages.

| Package | Detail |
| --- | --- |
| towr  |Light-weight and extensible C++ library for trajectory optimization for legged robots.|
| ifopt |Eigen-based, light-weight C++ Interface to NLP Solvers (Ipopt, Snopt).|
| xpp   |Visualization of legged robots, forces, support areas, ZMP, CoM etc. in ROS rviz.|

Please install necessary packages.

```
$ sudo apt install ros-melodic-towr-ros
$ sudo apt install ros-melodic-ifopt
$ sudo apt install ros-melodic-xpp
```
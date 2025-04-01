# Gazebo Harmonic Simulation with DummySensor Plugin

## Overview
This project demonstrates the setup and execution of a Gazebo Harmonic simulation with a custom robot and the `DummySensor` plugin. The sensor publishes "Hello World" messages on a ROS 2 topic using `gz-transport`.
Here I am using ROS2 Humble with Gazebo Harmonic.

<table align="center">
  <tr>
    <td><img src="https://github.com/user-attachments/assets/631e4cc2-c9a8-462e-8ef4-65925ccdd19d"alt="Top Left" width="400"></td>
    <td><img src="https://github.com/user-attachments/assets/d9afb55b-dcae-493a-b5af-3b61cb55478f" alt="Top Right" width="400"></td>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/8a60440e-ccea-4c0e-882c-f5da5c9e8e57"  alt="Bottom Left" width="400"></td>
    <td><img src="https://github.com/user-attachments/assets/1a8ede8e-d428-40f4-bea2-7ea221b1a27c" alt="Bottom Right" width="400"></td>
  </tr>
</table>


## Installing Gazebo Harmonic on Ubuntu Jammy (22.04) and Ubuntu Noble (24.04).
Gazebo Harmonic binaries are hosted in the `packages.osrfoundation.org` repository. To install them, follow these steps:

### 1. Install Necessary Tools
```sh
sudo apt-get update
sudo apt-get install curl lsb-release gnupg
```

### 2. Add Gazebo Harmonic Repository and Install
```sh
sudo curl https://packages.osrfoundation.org/gazebo.gpg --output /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] http://packages.osrfoundation.org/gazebo/ubuntu-stable $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/gazebo-stable.list > /dev/null
sudo apt-get update
sudo apt-get install gz-harmonic
```

After installation, all libraries should be ready to use, and the `gz sim` application will be ready for execution.

## Setup Instructions
### 1. Clone the Repository
```sh
cd ~/workspace  # or your preferred workspace
git clone <repo_url>
cd PAL_Project
```

### 2. Build the DummySensor Plugin
```sh
cd custom_sensors/dummy_sensor
mkdir build && cd build
cmake ..
make

cd ../custom_sensor_system
mkdir build && cd build
cmake ..
make
```

### 3. Set Environment Variables
```sh
export GZ_SIM_SYSTEM_PLUGIN_PATH=$(pwd)/build
```

### 4. Run the Simulation with DummySensor
```sh
gz sim -r test_world.sdf
```
To verify that `DummySensor` is working, check the published topic:
```sh
gz topic -e -t /dummy_sensor
```
Expected output:
```
header {
  stamp {
    sec: 75
    nsec: 258000000
  }
}
data: "Hello World"
```

## Running the Demo Robot
### 1. Build the ROS 2 Workspace
```sh
cd my_robot_ws
colcon build
source install/setup.bash
```

### 2. Launch the Robot in Gazebo
```sh
ros2 launch my_robot gz.launch.py
```

### 3. Visualize in RViz
```sh
ros2 launch my_robot rviz.launch.py
```























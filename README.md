# Automatic Arc Melting System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![arXiv](https://img.shields.io/badge/arXiv-2509.12011-b31b1b.svg)](https://arxiv.org/abs/2509.12011)

An automated control system built on **ROS2 (Robot Operating System 2)** designed for the synthesis of bulk intermetallic compounds. This project orchestrates heterogeneous experimental hardware to streamline the arc melting process.

## 📖 Citation and Research

The technical methodology and experimental results of this system are detailed in the following paper:

> **Orchestration of Heterogeneous Experimental Machines via ROS2 for Automated Bulk Intermetallic Synthesis** > *Wei-Sheng Wang, Kensei Terashima, and Yoshihiko Takano* > **Link:** [arXiv:2509.12011](https://arxiv.org/abs/2509.12011)


---

## Overview

This repository contains the control software for an automated arc-melting synthesis system built on **ROS 2**.  
The core idea is to model each device (e.g., motion stages, weighing, PLC interlocks, robotic manipulator, etc.) as a ROS 2 component and orchestrate them into safe, repeatable synthesis workflows.

If you use this software in academic work, please cite the paper linked above.

---

## Key Features

- **ROS 2 orchestration** of heterogeneous machines (multi-device integration via nodes)
- **Modular design**: each device is encapsulated as a component/node for easier extension
- **Sequence-driven workflows**: repeatable synthesis procedures defined as sequences
- **Safety-first control philosophy**: designed to work with external safety interlocks (e.g., PLC)

> ⚠️ **Safety note:** This code controls real experimental hardware.  
> Use it only in a properly interlocked environment and review every motion / power / gas / arc step carefully before operation.

---

## 🚀 Getting Started

### Prerequisites

* Ubuntu 22.04 LTS (Recommended)
* [ROS2 Humble](https://docs.ros.org/en/humble/Installation.html) (or compatible version)
* Python 3.10+
* Colcon build tool

### Installation

1.  **Create a ROS2 Workspace:**
    ```bash
    mkdir -p ~/ros2_ws/src
    cd ~/ros2_ws/src
    ```

2.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/qwe789qwec/automatic_arc_melting_system.git](https://github.com/qwe789qwec/automatic_arc_melting_system.git)
    ```

3.  **Install Dependencies:**
    ```bash
    cd ~/ros2_ws
    rosdep install -i --from-path src --rosdistro humble -y
    ```

4.  **Build the Project:**
    ```bash
    colcon build --symlink-install
    source install/setup.bash
    ```

## 🛠 Usage

To launch the system orchestration:
```bash
ros2 launch [package_name] [launch_file_name].py

# Scrambler
Project Scrambler is a soccer-playing hexapod robot loosely based off of Tazer Technical's hexapod robot.

## Introduction
This repository is currently under development. Anything contained herein is provisional. This notice will be removed when an official revision is released. This is a free and open source project. Currently, it is standard practice in the software industry to use generative AI models. As such, some or all of the text based contents of this repository may derive from generative AI without further indication. However, because of ethical concerns, non-text based generative AI content is prohibited in this repository.

Scrambler is a hexapod robot which utilizes vision and motion sensors. It is being developed within the purview of the Phoenix Dynamics robotics club. The goal of the project is to create a robot which can play soccer. The repository is a ROS 2 workspace and is divided into several sections:
- ROS code in src
- Arduino code in arduino
- CAD files
- Electronic schematics
- Documentation in manuals

The electronic architecture of Scrambler currently uses an Arduino or ESP32 connected to a computer. In the future, a single board computer (SBC) such as a Raspberry Pi may be integrated into Scrambler which could obviate the need for an Arduino.

## Operation

To bridge ROS 2 running on a computer with an Arduino, we'll use a serial link to relay standard ROS messages between them. This requires us to install the **rosserial** library in the Arduino IDE and install and then run the **rosserial_server** on the computer as follows:
># Install rosserial for ROS 2
>sudo apt install ros-jazzy-rosserial-server ros-jazzy-rosserial-msgs
>
># Start the serial server on /dev/ttyACM0 at 57600 baud (or other)
>ros2 run rosserial_server serial_node --port /dev/ttyACM0 --baud 57600


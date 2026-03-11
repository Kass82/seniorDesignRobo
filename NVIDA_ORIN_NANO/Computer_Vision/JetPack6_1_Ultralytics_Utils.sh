#!/bin/bash

sudo apt update
sudo apt install python3-pip -y
pip install -U pip

pip install ultralytics[export]

echo "Rebooting Device ... :)"
sudo reboot

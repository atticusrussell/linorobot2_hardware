import configparser
import json
import sys

""" This script parses the platformio.ini file and outputs a JSON array of environments to be used by GitHub Actions."""

# Get the list of ROS distributions from the command line arguments
ros_distributions = sys.argv[1:]

# Parse the platformio.ini file
config = configparser.ConfigParser()
config.read('firmware/platformio.ini')

# Extract the environment names from the sections
environments = []
for section in config.sections():
    if section.startswith("env:"):
        env_name = section.split("env:")[1]
        # Add an entry for each ROS distribution for each environment
        for ros_distro in ros_distributions:
            environments.append({"env": env_name, "ros_distro": ros_distro})

# Output the environments as a JSON array
print(json.dumps(environments))

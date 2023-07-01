import configparser
import json

config = configparser.ConfigParser()
config.read('firmware/platformio.ini')

environments = []
for section in config.sections():
    if section.startswith("env:"):
        env_name = section.split("env:")[1]
        build_flags = config[section].get("build_flags", "")
        environments.append({"env": env_name, "build_flags": build_flags})

print(json.dumps(environments))

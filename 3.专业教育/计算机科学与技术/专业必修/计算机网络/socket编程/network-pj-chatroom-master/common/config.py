import json
from pprint import pprint

with open('config.json') as config_file:
    config = json.load(config_file)


def get_config():
    return config

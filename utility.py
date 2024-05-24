import os
from git.repo import Repo
import toml
import json
from rich import print
from rich import print_json

cfg_file = toml.load("./depend.toml")

print_json(json.dumps(cfg_file))

download_path = os.path.join('build','lib','ulog')
Repo.clone_from(cfg_file["depend"]["ulog"]["url"],to_path=download_path)

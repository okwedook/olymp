from github import Github
from collections import namedtuple
import time
import os
import pathlib

NamedFile = namedtuple('NamedFile', ['name', 'content'])

def get_all_files_from_directory(repository, directory):
    print(f"Looking at directory: {directory}")
    contents = repo.get_contents(directory)
    files = []
    for file in contents:
        if file.content is not None:
            print(f"Got file: {directory + '/' + file.name}")
            files.append(NamedFile(file.name, file.decoded_content))
        else:
            files += get_all_files_from_directory(repository, file.path)
    return files

g = Github(login_or_token=os.environ["GITHUB_TOKEN"]) # TODO: remove token

repo_name = "okwedook/olymp" # TODO: add parameter for repo

repo = g.get_repo(repo_name)
print(f"Got repo: {repo_name}")

contents = get_all_files_from_directory(repo, "code")

for full_name, content in contents:
    if full_name.lower() == 'readme.md':
        continue
    name = full_name[:full_name.rindex('.')]
    print("Creating snippet:", name)
    file = open(str(pathlib.Path.home()) + f"/.config/sublime-text/Packages/User/{name}.sublime-snippet", "w")
    file.write((    
        "<snippet>"
        "    <content><![CDATA["
        f"{content.decode('utf8')}"
        "]]></content>"
        f"    <tabTrigger>{name}</tabTrigger>"
        "</snippet>"
    ))

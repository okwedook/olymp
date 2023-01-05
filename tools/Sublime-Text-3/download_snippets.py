from github import Github
import time
import os
import pathlib
import re

def get_all_files_from_directory(repository, directory):
    print(f"Looking at directory: {directory}")
    contents = repo.get_contents(directory)
    files = {}
    for file in contents:
        if file.content is not None:
            print(f"Got file: {directory + '/' + file.name}")
            files[file.name] = file.decoded_content.decode('utf8')
        else:
            files.update(get_all_files_from_directory(repository, file.path))
    return files

g = Github(login_or_token=os.environ["GITHUB_TOKEN"]) # TODO: remove token

repo_name = "okwedook/olymp" # TODO: add parameter for repo

repo = g.get_repo(repo_name)
print(f"Got repo: {repo_name}")

contents = get_all_files_from_directory(repo, "code")
dependency_graph = {}

for file_name, content in contents.items():
    dependencies = re.findall('#include "(.*)"', content)

    print(file_name, "depends on", dependencies)

    dependency_graph[file_name] = dependencies

visit_order = []

def dfs(file_name):
    if file_name in visit_order:
        return
    for dependency_file in dependency_graph[file_name]:
        dfs(dependency_file)
    visit_order.append(file_name)

for file_name in contents:
    dfs(file_name)

visit_order.reverse()

finalized = {}


for file_name in visit_order:
    for dependency_file in dependency_graph[file_name]:
        contents[file_name] = re.sub(
            f'#include "{dependency_file}"',
            lambda x: contents[dependency_file],
            contents[file_name]
        )

for file_name, content in contents.items():
    if file_name.lower() == 'readme.md':
        continue
    name = file_name[:file_name.rindex('.')]
    print("Creating snippet:", name)
    file = open(str(pathlib.Path.home()) + f"/.config/sublime-text/Packages/User/{name}.sublime-snippet", "w")
    file.write((    
        "<snippet>"
        "    <content><![CDATA["
        f"{content}"
        "]]></content>"
        f"    <tabTrigger>{name}</tabTrigger>"
        "</snippet>"
    ))

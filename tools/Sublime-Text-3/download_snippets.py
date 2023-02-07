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

import argparse

parser = argparse.ArgumentParser(description="""
    Download snippets from a git repo
    Put github token to ~/.github/snippets_token
""")
parser.add_argument(
    "--local",
    help="Get changes from a local repo",
    action='store_true'
)
parser.add_argument(
    "--use-env-token",
    help="Use environment variable token instead of ~/.github/snippets_token",
    action='store_true'
)
parser.add_argument(
    "--sublime-text",
    help="Change snippets for Sublime Text",
    action='store_true'
)

args = parser.parse_args()

if args.local:
    contents = {}
    path = os.path.dirname(__file__) + "/../../code"
    print(path)
    walker = os.walk(path)
    for (dir, subdir, file_names) in walker:
        for file_name in file_names:
            print(f"Read locally {file_name}")
            contents[file_name] = open(os.path.join(dir, file_name)).read()
else:
    if args.use_env_token:
        token = os.environ["GITHUB_TOKEN"]
    else:
        path = "~/.github/snippets_token"
        path = os.path.expanduser(path)
        token = str(open(path).read()).rstrip('\n')


    g = Github(login_or_token=token)

    repo_name = "okwedook/olymp"

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
    if args.sublime_text:
        print("(Sublime Text) Creating snippet:", name)
        file = open(str(pathlib.Path.home()) + f"/.config/sublime-text/Packages/User/{name}.sublime-snippet", "w")
        file.write((    
            "<snippet>"
            "    <content><![CDATA["
            f"{content}"
            "]]></content>"
            f"    <tabTrigger>{name}</tabTrigger>"
            "</snippet>"
        ))

## Basic startup
- Create a working folder, create `input.txt` file in it
- Choose a layout with 3 vertical columns in `View->Layout`. You might also use `Alt+Shift+3`
- Put `CPP.sublime-build` file to Build System directory and choose it as default Build System
- Use `Ctrl+Shift+P`, search `Install Package Control` and install it
- To install packages with Package Control  use `Ctrl+Shift+P`, find `Package Control: Install Package`
- Install wanted color theme via Package Control (I use `Monokai++`) and select the theme in `Preferences->Select Color Theme`
- Now you can use `Ctrl+Shift+B` to run any `.cpp` file
## Stress testing and linter
- Install `CppFastOlympicCoding` via Package Control
- Go to `Preferences->Package Settings->FastOlympicCoding` and change `c++11` to `c++17` (or `c++20`) if needed
- To run stress test on file `file.cpp`
	- Create `file__Good.cpp` with a definitely correct solution
	- Create `file__Generator.cpp` with test generator
	- The generator might read an integer seed from input, or use some high precision clocks for randomness ([[Random, clocks and seeds]])
	- Open `file.cpp` and use `Ctrl+Shift+P`, select `FastOlympicCoding: Make Stress` and voila
## Downloading snippets
- Set up git with ssh keys and clone this repository
- Install `pygithub` with `pip install pygithub`
- Place the github OAuth token and put it to `~/.github/snippets_token`
- You can also use the `GITHUB_TOKEN` environment variable with `--use-env-token`
```bash
export GITHUB_TOKEN=$(cat ~/.github/snippets_token)
```
- Or an inline version
```bash
export GITHUB_TOKEN=ghp_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
```
- Run the script
```bash
python3 download_snippets.py
```
- The default behaviour is dry-run, so the templates are only written to the terminal
- To save the templates use the `--sublime-text` script parameter
- You can also use `--local` to use the local repository files
- The script saves snippets to `/.config/sublime-text/Packages/User/` by default
- Now you can use tab completion in Sublime Text with code from the repository!
- For verbose help for the script use `python3 download_snippets.py --help`
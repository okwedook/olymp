## Basic startup
- Put sublime-build file to Build System directory and choose it as default Build System
- Go to `Preferences->Key Bindings` and setup wanted key combinations (I use `F5` to run build)
## Stress testing and linter
- Install package control with `Ctrl+Shift+P` and then install `CppFastOlympicCoding` with the same command
- Go to `Preferences->Package Settings->FastOlympicCoding` and change `c++11` to `c++17` (or `c++20`) if needed
- To run stress test on file `file.cpp`
	- Create `file__Good.cpp` with a definitely correct solution
	- Create `file__Generator.cpp` with test generator
	- The generator might read an integer seed from input, or use some high precision clocks for randomness ([[Random, clocks and seeds]])
	- Open `file.cpp` and use `Ctrl+Shift+P`, select `FastOlympicCoding: Make Stress` and voila
## Downloading snippets
- Put github API token into `GITHUB_TOKEN` environment variable (example for file lying in `~/.github/token`)
```bash
export GITHUB_TOKEN=$(cat ~/.github/token)
```
- Run the script
```bash
python3 download_snippets.py
```
- The script saves snippets to `/.config/sublime-text/Packages/User/` by default
- Now you can use tab completion in Sublime Text with code from the repository
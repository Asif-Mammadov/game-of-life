# Game of Life: Step 4

## Introduction
The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine. [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

## Launch
- Create a CMake-generated project directory by running: `cmake . -B build`
- Set it as current directory: `cd build`
- Run: `make`
- Start the program by compiling the generated binary file with version<sup>1</sup> option: `./gol -v <version>`
- You may also choose the type<sup>2</sup> of the game by option -t.

Example : `./gol -v clipped -t gui`

<sup>1</sup> Parameters for version can be either "circular" or "clipped". Make attention to the spelling.
<sup>2</sup> Parameters for type can be either "terminal" or "gui"

## Terminate
- Press `Ctrl + C`

## Documentation
The docs of this step can be generated by running `make doc` command in the **build** directory which creates a **doc** directory in the source folder. The generated HTML documentation can be viewed by pointing a browser to the *index.html* file in the **doc/html** directory.

## Build
For creating a distribution tar file for this program, `make dist` command in the **build** directory can be used. As a result of this command, a **dist** directory gets created containing the tar file which is free from files generated during compilation.

## Clear
Run `make clear` in the **build** directory to delete all files in the source directory that are created by compiling or building the program.

## Tests
Run `./tests` in the **build** directory to see the results of the tests.
<img src="res/sprites/MainMenu_Title.png"
     alt="Markdown Monster icon"
     style="float: left; margin-right: 10px;" />
## Usage
The Program starts with a main menu where you can select Human-Players and Bots by clicking on both sides. By clicking on `START GAME` you will start the Game session with the selected players.

Within the Game you can see a `MENU` Button on the top left that will pause the session, that you can continue by pressing `CONTINUE`. You can also start a new game from scratch by pressing the `START GAME` button again.

The Game lets Human players select their Dice-Combination by clicking on them, then you have the choise to continue by rolling the dice again or continue with the next player. If a player is a Bot cou can see their interaction highlighted and you can press continue to go to the next player.

`F11` will toggle the fullscreen mode.
## Build process
The build process is done via the MinGW-64 Compiler within a Linux environment. To build on Windows you need a running version of WSL to cross-compile the code.
The following example is done with an Ubuntu 22.04 LTS Instance in WSL2. WSL1 and Ubuntu 20.04 are also supported.
### Dependencies
The Dependencies for this Software are the following:
- `build-essential`,
- `git`
- `make`
- `mingw-w64-x86-64-dev`
- `g++-mingw-w64-x86-64`
- `libsdl2-dev`
- `libsdl2-image-dev`
- `libsdl2-ttf-dev`

They can be installed via the following command (Ubuntu):
```bash
sudo apt update && sudo apt install build-essential git make mingw-w64-x86-64-dev g++-mingw-w64-x86-64 libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

### Build
To build the project navigate to the project folder via the `cd` command. On WSL you can nacigate to your Windows Drives by navigating to the mount folder `/mnt/c/` for the `C:\` drive or any other drive letter on your computer.
Within your project folder you can start the build process via the `make` command.
Our project supports the following build-targets:
| Build configuration | Plattform |
|--|--|
| `debug` | `windows` |
| `release` | `linux` |
| `test` | |

The Build-configuration and Plattform can be combined like in the following examples:
- To build on windows in release mode you type `make release_windows`.
- To build the test on linux you can type `make test_linux`.
- If you'd like to run the code immediately you can prepend `run_`, for example `make run_debug_windows`. Right after building the program will be executed. 

To remove existing binaries you can run `make clean`. All binaries will be cleared and can now be recompiled.

With the `-j` suffix you can compile all files in parallel. For example `make run_debug_windows -j` will compile all files in parallel, and run the program. This cannot be combined with the `clean` command. But you can combine them in bash for example `make clean && make run_debug_windows -j`. This will first execute the clean command to remove all binaries and then compile all files in parallel.

WSL2 supports the starting of windows executables right from the linux-bash so you can compile and run windows-binaries right from the WSL. Linux-GUI applications are only supported on Windows 11. On Windows 10 you can compile the Linux binaries, but you can only run the tests (as they do not need a GUI).

### Binaries
The Binaries are located in the Porject folder `bin/[Platform]/`.
Nessesary dependecies like sprites and fonts are stored `bin/[Platform]/res`.

Windows binarys are staticly linked, to midigate dependency issues. Linux binarys are dynamically linked, they need the requiered dependencys (mentioned above) for the programs to run.

## Coding Guidelines
```c++
#include  <iostream>
// indentation using TABS not spaces!
// no trailing whitespaces!
// comments have a space after "//" (and before, if there's code before it)
// alsways use uint32_t and the like instead of standard integers
constexpr  uint32_t WINDOW_WIDTH =  800;
constexpr  uint32_t WINDOW_HEIGHT =  800;
// constants are all caps and in snake_case
// NO #define CONSTANTS! use the type system!
// struct and class names are capital and in CamelCase
class  MyCoolClass {
public: // start with explicit "public:" (except if there is nothing public), indentation like here
??? MyCoolClass() {
??? ??? // ...
??? } 
??? // functions and methods: small first letter, CamelCase
??? void  doDomethingCool() {
??? ??? // ...
??? }

// empty line before access specifier (except first one)
protected: // "protected:" after "public:" (if there is something protected)
??? uint8_t m_protectedInteger; // leading "m_" for protected AND private member variables

private: // "private:" after "protected:" (if there is something private)
??? int32_t m_privateSigned32BitInteger;
};

enum  class  CoolEnum {
??? VALUE_1, // enum values are constants (capital snake_case)!
??? VALUE_2,
??? VALUE_3
};

// pointer (*) and reference (&) symbols on the left side (not uint8_t *abc)
void  coolFunction(const  uint8_t*  abc, uint32_t&  def, int64_t*  const  ghi) {
??? // ...
}

// function names small and in CamelCase
void  anotherCoolFunction() {
??? // ...
}

int  main() { // bracket on same line
??? std::cout <<  "Hello World"  <<  std::endl;
??? return  0;
} // no empty line(s) at the end!

```

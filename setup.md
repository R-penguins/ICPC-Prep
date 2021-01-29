# C++ dev environment setup for VS Code and GCC on Windows

## Install GCC compiler from msys2

1. Download installer from www.msys2.org
2. Run installer. Record installation location (e.g. C:\msys2)
3. In msys2 prompt:

```
$ pacman -Syu
$ pacman -S mingw-w64-x86_64-gcc
$ pacman -S mingw-w64-x86_64-gdb
```

4. Add installation path in environment variables. Type "path" in Windows search. Under "Edit the system environment variables" - "Environment Variables", click `Path` for the current user and "Edit...". Add new value `INSTALL_LOC\mingw64\bin` (e.g. C:\msys2\mingw64\bin).

## Install VS Code and C/C++ plugin

1. Download and install VS Code https://code.visualstudio.com/
2. In Extensions tab, search and install the C/C++ Extension Pack.

## Begin developing

Open a folder from VS Code. Make a new .cpp file from Explorer. After coding, ctrl + alt + B and select "C/C++: g++.exe build active file". Run the program in terminal.

## Working on problems

The problem statements can be downloaded using the PowerShell scripts. `./getuva 1543 -View` downloads UVa1543 to `./uva-pdf/1543.pdf` and opens it.

The `run.ps1` script handles I/O redirection and timing. The program needs to be in `./bin` by default.

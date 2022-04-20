# GBA-3D
A small project trying to get 3D rendering on the Gameboy Advanced

# How to compile

## Linux
On systems running Linux, you first need to install devkitpro and devkitarm (Otherwise, you'll not be able to compile.) Make sure you also have
libtonc installed in your /opt/devkitpro/libtonc/ directory. After that, you should be able to
type the following to compile and run your program
```
make && ./run
```
I can't find any reliable tutorials on how to do that, so just try your luck at that.

Note: Make sure you have gcc and make installed either by using
```
sudo apt install gcc make
```
on Debian based systems (Ubuntu, Debian, Mint, etc.) or by using
```
sudo pacman -S gcc make
```

on Arch based systems (Arch, Garuda, Manjaro, etc.)

## Windows
I don't have any way to compile this code on windows yet. The code should still work there, so I'd recommend just copying the files onto a compiler
and building them from there.

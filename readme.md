# Stellar Engine - Vulkan
A custom game engine using C++ and Vulkan API
## Table of Contents
* [Introduction](#introduction)
* [Installation](#installation)
* [ToDo](#todo)

## Introduction
Stellar Engine is a cross-platform game engine using Vulkan API. 

Currently it is at the very initial state of development. It supports Windows10(64 bit) and Linux(64 bit)

## Installation

### Prerequisite

I will try to list as detailed as possible. However I have not tested the build on a fresh envrionment so you are welcomed to try it and provide some feedback.

- Vulkan
- C++17
- Windows:
    - Cygwin with GCC installed
- Linux:
    - GNU GCC
    - X11
- macOS:
    - IDK yet

### Running

To run, you need to compile the core engine first:

`cd Stellar && make`

Then, depending on your platform, a shared library will be generated and copied to `Sandbox/bin`. (`.dll` for Win64 and `.so` for Linux) 

Now you just need to build the Sandbox project:

`cd .. && cd Sandbox && make && make run`

## ToDo

- [ ] macOS support
- [ ] Window abstraction
- [ ] Layer
- [ ] Events
- [ ] ImGui
- [ ] Triangle
- [ ] Shader library
- [ ] Texture
- [ ] Renderer
- [ ] Networking
- [ ] Load model
- [ ] PBR
- [ ] IBL
- [ ] Deferred rendering
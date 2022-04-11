# StraubEngine: A 2D open source tile-based engine by Tyler Straub

## What is StraubEngine?

StraubEngine is a fully open source engine written in C++ and the SDL2 framework that runs on both Windows and macOS. It features integrated Tiled support, keyboard/mouse/controller input, hardware accelerated rendering, and more. StraubEngine makes use of a couple headers to add functionality such as Cute Sound and Tileson.

In its current state, StraubEngine is fairly barebones, and is certainly not a suitable alternative to many of the mainstream engines (or even any of the lesser known SDL2 engines). The purpose of StraubEngine rather is to provide a learning resource for those who want to create their own engine for smaller 2D games, as well as provide a boilerplate for prototypes.

## How to compile

Include is a CMakeLists.txt file which can be used to compile using CMake. Note that for Windows, all SDL2 related library paths are hard-coded in, so you will need to change these to fit your own build. Running your built executable also requires runtime libraries for SDL2, SDL2_image, and SDL2_ttf, as well as the usual C++ runtime libraries.

Tileson makes use of std::filesystem which is a C++ 17 include, so you will need to make sure your GCC or clang compiler is up to date enough to support that.

## Roadmap

StraubEngine is updated in line with the development of my other games; that is, when I add a feature or component to a personal game, it will get added to this engine repo. As a result, explicit development of this engine is not guaranteed. That being said, there are still some features I know will be added soon based on the future features of my own games.

Currently, these are main features to be added sometime in the near future:
- Entity component management system

There are other features that will certainly make their way as well, but for now this is all that is currently planned.

## Contribute

Have an issue? See some code that could be optimized? Open a PR or an issue on GitHub and I will look into it!
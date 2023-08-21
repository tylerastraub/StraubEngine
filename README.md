# StraubEngine: A 2D open source tile-based engine by Tyler Straub

## What is StraubEngine?

StraubEngine is a fully open source engine written in C++ and the SDL2 framework that runs on both Windows and macOS. It features integrated Tiled support, keyboard/mouse/controller input, hardware accelerated rendering, and more. StraubEngine makes use of EnTT, cute_sound, and tmxlite.

In its current state, StraubEngine lacks documentation, optimization, and does not follow a very "uniform" way of doing things. The purpose of StraubEngine rather is to provide a learning resource for those who want to create their own engine for smaller 2D games, as well as provide a boilerplate for prototypes for myself.

## How to compile

Included is a CMakeLists.txt file which can be used to compile using CMake. Note that for Windows, all SDL2 related library paths are hard-coded in, so you will need to change these to fit your own build. Running your built executable also requires runtime libraries for SDL2, SDL2_image, and SDL2_ttf, as well as the usual C++ runtime libraries.

Both EnTT and Tileson makes use of std::filesystem which is a C++ 17 include, so you will need to make sure your GCC or clang compiler is up to date enough to support that.

## Roadmap

StraubEngine is updated in line with the development of my other games; that is, when I add a feature or component to a personal game, it will get added to this engine repo. As a result, explicit development of this engine is pretty rare. Instead, there are usually random days where there is a flurry of commits containing new features or improvements from my personal projects.

Current TODO is:
- Update GUI to be more robust and less finicky
- Add more "default" systems that are frequently used in all games
- Create more detailed in-code comments to make understanding code purpose/use easier

## Contribute

Have an issue? See some code that could be optimized? Open a PR or an issue on GitHub and I will look into it!
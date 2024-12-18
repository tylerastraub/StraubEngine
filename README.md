# StraubEngine: A 2D open source tile-based engine by Tyler Straub

## What is StraubEngine?

StraubEngine is a fully open source engine written in C++ and the SDL2 framework that builds on both Windows and macOS. It features integrated Tiled support, keyboard/mouse/controller input, hardware accelerated rendering, and more. StraubEngine makes use of EnTT, cute_sound, tmxlite, and the nlohmann json parser.

In its current state, StraubEngine lacks documentation, optimization, and does not follow a very "uniform" way of doing things. The purpose of StraubEngine rather is to provide a learning resource for those who want to create their own engine for smaller 2D games, as well as act as a boilerplate for prototypes for my own personal projects.

## How to compile

Included is a CMakeLists.txt file which can be used to compile using CMake. Note that for Windows, all SDL2 related library paths are hard-coded in, so you will need to change these to fit your own build. Running your built executable also requires runtime libraries for SDL2, SDL2_image, and SDL2_ttf, as well as the usual C++ runtime libraries.

Both EnTT and Tileson makes use of std::filesystem which is a C++ 17 include, so you will need to make sure your GCC or clang compiler is configured to support that standard or newer.

## Roadmap

StraubEngine is updated in line with the development of my other games; that is, when I add a feature or component to a personal game, it will get added to this engine repo. As a result, explicit development of this engine is pretty rare. Instead, there are usually random days where there is a flurry of commits containing new features or improvements from my personal projects.

Current engine-specific TODO is:
- Continue multiplayer support
    - Add more robust packet/message creation
    - Create workflow for server/client interaction for more plug-and-play experience
- Improve on in-engine GUI
    - Add basic GUI components such as selections, drop down menus, sliders, text input
    - Add developer console
- Add system for managing entities based on position (aka something like a QuadTree)
- Update RenderSystem to be more flexible
    - Probably create similar system to IsoSprite struct in MysteryDungeon that allows us to render tiles and entities all in one go
    - Add renderPriority to RenderComponent, sort view in RenderSystem only when RenderComponent is added or updated
- Bolster the animation system
    - Support "transition" frames where after an animation ends, the y index changes
    - Support reverse animations
    - Allow for setting frame length of each individual frame for more flexible animations
- Add debug system
- Add more robust collision box/hitbox/hurtbox system that allows for easier creation and management of said boxes
    - Full HitSystem with spatial partitioning as well

## Contribute

Have an issue? See some code that could be optimized? Open a PR or an issue on GitHub and I will look into it!
# FiniGin (Finian Horrie Engine)

FiniGin is a 2D engine using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for c++ game projects. It contains the building blocks to create and maintain a 2D game. As an example, I made a version of Digger included with the engine

# Goal

FiniGin is my engine containing my self developed game as a submission to the course "Programming 4" at DAE. This project lasted an entire semester where the engine was built from a small template. Over the weeks, improvements were done and features were added untill the engine was at a point of usability to create a game as a demonstration.

# Design

FiniGin is built with a GameObject - Component system. A GameObject is added to a scene when all required Components are attached. Textures and Sounds should be preloaded into the ResourceManager. This is done to prevent multiple texture/sound loading and allow the user to get a resource with only a key afterwards.

Refer to the attached game, "Digger", to see how to use the engine features.

# Use

Download the latest release of this engine and compile/run in visual studio (.sln project).

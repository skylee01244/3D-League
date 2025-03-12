**__Pixel Pursuit__** 3D horror chasing game is a high-performance application developed in **C++** using SFML. It features a custom **raycasting** engine for real-time 3D rendering and integrates the **A* pathfinding algorithm** for dynamic enemy AI. Designed with an optimized object-oriented architecture, the game ensures efficient memory management, event-driven programming, and real-time computations, showcasing advanced C++ game development techniques.

![Screenshot of Game Screen.](/rpg-game/Resources/Game_Images/game_screen_1.png)

How To Build:
1) Install CMake https://cmake.org/download/
2) Open the project folder in the terminal
3) Build using CMake
> For a multi-configuration generator (Windows)
```
cmake -S . -B build
cmake --build build --config Release
```
> For a single-configuration generator (LINUX & MACOS)
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
4) Move the build/bin/Release/main.exe In the directory with Resources and Run


W A S D: to move
M: To show MiniMap
Mouse: To look around


> [!TIP]
> Try to reach the other side of the map without being captured



https://lodev.org/cgtutor/raycasting.html
- Used this tutorial to learn Ray Casting 

https://www.piskelapp.com/p/create/sprite
- Used this website to draw Spritesheets and the MapSketch

https://www.youtube.com/watch?v=OpIS1zoz6fU
- Used this youtuber's videos to learn how to implement the code

https://cmake.org/cmake/help/latest/index.html
- CMake official website to learn CMake

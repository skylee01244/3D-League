# **__Pixel Pursuit__!!**  
a 3D horror chasing game is a high-performance application developed in **C++** using SFML. It features a custom **raycasting**  for real-time 3D rendering and integrates the __A* pathfinding algorithm__ for dynamic enemy AI. Designed with an optimized object-oriented architecture, the game ensures efficient memory management, and real-time computations, showcasing advanced C++ game development techniques.

![Screenshot of Game Screen.](/rpg-game/Resources/Game_Images/game_screen_1.png)

## Build Instructions
How To Build:
1) Install CMake https://cmake.org/download/
2) Navigate to Your Project Directory
Open your terminal and navigate to the project directory where `CMakeLists.txt` is located.
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
4) Run the Application  
To run the application, execute the `main.exe` file located in `build/bin/Release/`.


## Play the game!
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

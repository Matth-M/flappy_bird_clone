# Playing
Press any key to jump, except `r` to restart and `esc` to quit.

# Build
## Dependencies

- [SDL2](https://www.libsdl.org/)
- [CMake](https://cmake.org/)

## Creating build directory

Only once to create the build directory.
```bash
mkdir build 
cd build 
cmake ..
```

## Compiling and running
```bash
cmake --build ./build && ./build/bin/main # From project's root
```
# TODO

- Show score, speed on the screen
- Make window resizable / playable in fullscreen
- Use time based updates to vx and vy to be independent from framerate
- Use `SDL_Texture` and `SDL_RenderCopy`

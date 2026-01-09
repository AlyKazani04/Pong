# Pong (Raylib)
This is a small two-player Pong game built in C using the Raylib framework. The project was created as a personal exercise in game programming, state management, and basic collision handling.

## Overview
The game includes a title screen, an instructions page, a color selection menu for both players, the main game loop, and a simple credits screen. Each player controls a paddle, and both players start with three lives. When the ball passes a player's side, that player loses a life. When a player's lives run out, the other player wins. \
All assets and logic are contained in a single source file:
- `pong.c`

## Features
- Multiple screens (title, instructions, color selection, gameplay, credits)
- Two-player controls
  - Player 1: W and S
  - Player 2: Up and Down arrow keys
- Color selection for each paddle
- Simple collision logic for ball and paddles
- Life system for both players
- Fancy UI using Raylib fonts and gradients

## Preview
<img width="1002" height="633" alt="image" src="https://github.com/user-attachments/assets/84886dd0-ab18-483b-9e91-b6fd15834b54" />
<img width="1002" height="633" alt="image" src="https://github.com/user-attachments/assets/270372ec-3162-4d72-8fa3-83d8f6d2c30d" />
<img width="1002" height="633" alt="image" src="https://github.com/user-attachments/assets/705210a2-1707-4f58-80c1-b0e77b3bfb18" />
<img width="1002" height="633" alt="image" src="https://github.com/user-attachments/assets/32eae003-b255-4911-9e18-192e222452e6" />
<img width="1002" height="633" alt="image" src="https://github.com/user-attachments/assets/ee075e4e-59a7-4022-b93f-6e4b4c59063b" />
<img width="1002" height="633" alt="image" src="https://github.com/user-attachments/assets/418f4e4d-ad53-4625-bfd8-25ba45f4d8b7" />

## Requirements
- Raylib installed and configured on your system
- C compiler: GCC

## Building
Compile the project using your Raylib setup. The command for GCC that statically links Raylib on Windows is:

```
gcc /path/to/src/pong.c -o /path/to/pong.exe -I/path/to/Pong/include -L/path/to/Pong/bin -static -static-libgcc -static-libstdc++ -lgcc -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
```
Where: \
`-I/path/to/Pong/include`: Path to Raylib include directory \
`-L/path/to/Pong/bin`: Path to Raylib library directory \
`-o /path/to/pong.exe`: Output executable path \
`-static -static-libgcc -static-libstdc++`: Necessary flags for a static executable release \
`-mwindows`: Optional flag to disable console window on Windows

Adjust paths and libraries depending on your environment.

## Running
After building, run the output executable:
`./pong`

> [!NOTE]
> This was a solo project created for learning and experimentation. The code is kept in one file for simplicity, and the structure intentionally avoids abstraction to keep everything visible in one place.

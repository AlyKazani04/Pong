#!/bin/bash

# Define Raylib version
RAYLIB_DIR="raylib-5.0_win64_mingw-w64"
ZIP_FILE="${RAYLIB_DIR}.zip"
URL="https://github.com/raysan5/raylib/releases/download/5.0/${ZIP_FILE}"

echo "Checking for Raylib..."

# 1. Download Raylib if not present
if [ ! -d "$RAYLIB_DIR" ]; then
    if [ ! -f "$ZIP_FILE" ]; then
        echo "Downloading Raylib for MinGW..."
        wget "$URL"
    fi
    echo "Extracting Raylib..."
    unzip -q "$ZIP_FILE"
fi

# 2. Compile Statically
echo "Compiling pong.exe (Static Linking)..."
x86_64-w64-mingw32-gcc src/pong.c -o pong.exe \
    -I "${RAYLIB_DIR}/include" \
    -L "${RAYLIB_DIR}/lib" \
    -lraylib -lgdi32 -lwinmm -static

echo "Done! Created pong.exe"

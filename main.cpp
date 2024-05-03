#include "grid.hpp"
#include "raylib.h"
#include <iostream>

int main() {
  InitWindow(800, 600, "Grid");
  SetTargetFPS(60);

  /*
   * Grid setup
   */
  int tileSize = 16; // In pixels
  int gridSizeX = GetScreenWidth() / tileSize;
  int gridSizeY = GetScreenHeight() / tileSize;
  Grid grid(gridSizeX, gridSizeY);

  // Testing code
  for (int y = grid.getSizeY() / 2 - 5; y < grid.getSizeY() / 2 + 5; y += 2) {
    for (int x = grid.getSizeX() / 2 - 7; x < grid.getSizeX() / 2 + 7; x += 2) {
      grid.setState(x, y, true);
    }
  }

  /*
   * Game loop
   */
  while (!WindowShouldClose()) { // Detect window close or ESC key
    ClearBackground(BLACK);
    BeginDrawing();

    for (int y = 0; y < grid.getSizeY(); y++) {
      for (int x = 0; x < grid.getSizeX(); x++) {
        if (grid.getState(x, y))
          DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, WHITE);
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
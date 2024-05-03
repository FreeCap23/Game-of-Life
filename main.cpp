#include "grid.hpp"
#include "raylib.h"
#include <iostream>

int main() {
  bool shouldShowNeighbors = false;

  InitWindow(1600, 1200, "Grid");
  SetTargetFPS(60);

  /*
   * Grid setup
   */
  int tileSize = 32; // In pixels
  int gridSizeX = GetScreenWidth() / tileSize;
  int gridSizeY = GetScreenHeight() / tileSize;
  Grid grid(gridSizeX, gridSizeY);

  // Testing code
  for (int y = 0; y < grid.getSizeY(); y += 2) {
    for (int x = 0; x < grid.getSizeX(); x += 1) {
      grid.setState(x, y, true);
    }
  }

  /*
   * Game loop
   */
  while (!WindowShouldClose()) { // Detect window close or ESC key
    if (IsKeyPressed(KEY_D))
      shouldShowNeighbors = shouldShowNeighbors ? false : true;
    if (IsKeyPressed(KEY_R))
      grid.reset();

    // !TODO: Finite automata or something like that so you can cancel a click
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      Vector2 pos = GetMousePosition();
      int x = pos.x / tileSize;
      int y = pos.y / tileSize;
      grid.switchState(x, y);
    }

    ClearBackground(BLACK);
    BeginDrawing();

    for (int y = 0; y < grid.getSizeY(); y++) {
      for (int x = 0; x < grid.getSizeX(); x++) {
        if (grid.getState(x, y)) {
          // !TODO: Find a way to use a single draw call for all rectangles
          DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, WHITE);
          if (shouldShowNeighbors) {
            const char *text = TextFormat("%d", grid.getAliveNeighbors(x, y));
            DrawText(text, x * tileSize, y * tileSize, tileSize, RED);
          }
        } else {
          DrawRectangleLines(x * tileSize, y * tileSize, tileSize, tileSize,
                             GRAY);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
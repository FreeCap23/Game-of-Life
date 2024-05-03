#pragma once
#include <vector>

class Grid {
private:
  int _x, _y;
  std::vector<std::vector<bool>> _matrix;

public:
  Grid() = delete; // Forbid the use of the default destructor
  Grid(int x, int y) : _x(x), _y(y), _matrix(y, std::vector<bool>(x)) {
    _matrix.reserve(y);
    for (int i = 0; i < y; i++) {
      _matrix[i].reserve(x);
    }
  }
  int getSizeX() { return _x; }
  int getSizeY() { return _y; }
  bool getState(int x, int y) {
    if (x >= 0 && x < _x && y >= 0 && y < _y)
      return _matrix[y][x];
    return false;
  }
  void setState(int x, int y, bool state) {
    if (x >= 0 && x < _x && y >= 0 && y < _y)
      _matrix[y][x] = state;
  }
  void switchState(int x, int y) {
    if (x >= 0 && x < _x && y >= 0 && y < _y)
      _matrix[y][x] = !_matrix[y][x];
  }
  int getAliveNeighbors(int x, int y) {
    int result = 0;
    const std::vector<std::vector<int>> neighbors = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (auto pair : neighbors) {
      int dx = pair[1];
      int dy = pair[0];
      int nx = x + dx;
      int ny = y + dy;
      if ((nx >= 0 && nx < _x) && (ny >= 0 && ny < _y) && _matrix[ny][nx])
        result++;
    }
    return result;
  }
  void reset() {
    for (int y = 0; y < _y; y++) {
      _matrix[y].assign(_x, false);
    }
  }
  void update() {
    std::vector<std::vector<int>> positionsToUpdate;
    for (int y = 0; y < _y; y++) {
      for (int x = 0; x < _x; x++) {
        int liveNeighbors = this->getAliveNeighbors(x, y);
        // Any live cell with
        if (_matrix[y][x]) {
          // Fewer than 2 or more than 3 live neighbors dies
          if (liveNeighbors < 2 || liveNeighbors > 3)
            positionsToUpdate.push_back(std::vector<int>({y, x}));
          // Any dead cell with exactly 3 live neighbors becomes alive
        } else if (liveNeighbors == 3)
          positionsToUpdate.push_back(std::vector<int>({y, x}));
      }
    }
    for (auto pair : positionsToUpdate) {
      this->switchState(pair[1], pair[0]);
    }
  }
};
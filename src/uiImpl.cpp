#include <raylib.h>

__declspec(dllexport) void InsideLoop() { DrawFPS(501, 500); }

__declspec(dllexport) void ToggleFullScreenWindow() {

  if (!IsWindowFullscreen()) {
    int display = GetCurrentMonitor();

    SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    ToggleFullscreen();

  } else {

    SetWindowSize(800, 800);
    ToggleFullscreen();
  }
}

__declspec(dllexport) void DrawTextOnScreen(int X, int Y, int Height,
                                            int width) {}

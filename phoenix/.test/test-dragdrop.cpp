#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

struct MainWindow : Window {
  VerticalLayout layout;
  Viewport viewport;
  Canvas canvas;

  MainWindow() {
    layout.setMargin(64);
    layout.append(viewport, {~0, ~0});
    layout.append(canvas, {~0, ~0});
    append(layout);

    setDroppable();
    canvas.setDroppable();
    viewport.setDroppable();

    setFrameGeometry({64, 64, 640, 480});
    setVisible();

    onClose = &Application::quit;

    onDrop =
    viewport.onDrop =
    canvas.onDrop =
    [&](lstring list) {
      for(auto& item : list) print(item, "\n");
    };
  }
} *mainWindow = nullptr;

int main() {
  mainWindow = new MainWindow;
  Application::run();
  return 0;
}

#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : public Window {
  VerticalLayout layout;
  Viewport viewport;
  Button button;

  void create();
} application;

void Application::create() {
  setTitle("Test");

  setStatusText("Hello");
  setStatusVisible();

  layout.setMargin(5);
  layout.append(viewport, ~0, ~0, 5);
  layout.append(button, ~0, 0);
  append(layout);

  onClose = [&] {
    OS::quit();
  };

  button.onTick = [&] {
    static bool fs = false;
    this->setFullScreen(fs = !fs);
  };

  setGeometry({ 128, 128, 640, 360 });
  setVisible();
}

int main() {
  application.create();
  OS::main();
  return 0;
}

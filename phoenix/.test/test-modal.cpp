#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Modal : Window {
  bool close;

  string run() {
    close = false;
    onClose = [&] { close = true; };
    setModal(true);
    setVisible();
    while(close == false) {
      OS::processEvents();
    }
    return "Hello, world";
  }

  Modal() {
    setTitle("Modal Window");
    setGeometry({256, 256, 320, 240});
  }
} *modal = nullptr;

struct Application : Window {
  VerticalLayout layout;
  Button button;
  CheckBox checkBox;

  Application() {
    setTitle("Main Window");
    setGeometry({128, 128, 640, 480});

    layout.setMargin(5);
    button.setText("Show Modal Window");
    checkBox.setText("Test Check Box");
    append(layout);
    layout.append(button, {~0, ~0}, 5);
    layout.append(checkBox, {~0, 0});

    setVisible();
    onClose = &OS::quit;
    button.onActivate = [&] { print(modal->run(), "\n"); };
  }
} *application = nullptr;

int main() {
  application = new Application;
  modal = new Modal;
  OS::main();
  return 0;
}

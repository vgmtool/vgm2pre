#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : Window {
  Timer timer1;
  Timer timer2;

  void create() {
    setFrameGeometry({ 64, 64, 640, 480 });

    onClose = &OS::quit;

    setVisible();

    timer1.onTimeout = [this]() { print("Timeout 1\n"); };
    timer1.setInterval(1000);
    timer1.setEnabled();

    timer2.onTimeout = [this]() { print("Timeout 2\n"); timer2.setEnabled(false); };
    timer2.setInterval(3000);
    timer2.setEnabled();
  }
} application;

int main() {
  Geometry geom = OS::availableGeometry();
  print(geom.x, ",", geom.y, ",", geom.width, ",", geom.height, "\n");

  print(file::exists("test-gtk"), ",", file::exists("test-fake"), "\n");
  print(file::size("test-gtk"), "\n");

  application.create();
  OS::main();
  return 0;
}

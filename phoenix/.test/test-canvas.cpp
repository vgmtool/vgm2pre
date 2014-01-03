#include <nall/platform.hpp>
#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

#include "laevateinn.hpp"

struct Application : Window {
  VerticalLayout layout;
  Canvas canvas;

  void create() {
    setTitle("phoenix");
    setGeometry({128, 128, 298, 370});
    setVisible();
    OS::processEvents();

    layout.setMargin(5);
    layout.append(canvas, {288, 360});
    append(layout);

    canvas.setSize({288, 360});
    image buffer(0, 32u, 255u << 24, 255u << 16, 255u << 8, 255u << 0);
    buffer.loadPNG(laevateinn, sizeof laevateinn);
    buffer.alphaBlend(backgroundColor().rgb());
    canvas.setImage(buffer);
    canvas.update();

    onClose = &OS::quit;
  }

  Application() {
  }
} application;

int main() {
  application.create();
  OS::main();
  return 0;
}

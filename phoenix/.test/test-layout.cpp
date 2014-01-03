#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : Window {
  VerticalLayout layout;
  Button button1;
  Button button2;
  Button button3;

  Application() {
    setStatusText("???");
    setStatusVisible();

    setFrameGeometry({ 64, 64, 640, 400 });
    button1.setText("Button 1");
    button2.setText("Button 2");
    button3.setText("Button 3");

    append(layout);
    layout.setMargin(5);
    layout.append(button1, ~0, 0, 5);
    layout.append(button2, ~0, 0, 5);
    layout.append(button3, ~0, 0, 5);

    onClose = &OS::quit;

    button1.onTick = [&] { layout.append(button3, ~0, 0, 5); };
    button2.onTick = [&] { layout.remove(button3); };
    button3.onTick = [&] { setFullScreen(!fullScreen()); };

    setVisible();
  }
};

/*
struct Application : Window {
  VerticalLayout layout;
  HorizontalLayout aLayout;
  HorizontalLayout bLayout;
  Button button1;
  Button button2;
  Button button3;
  Button button4;
  Button button5;
  ListView list;

  Application() {
    setGeometry({ 256, 256, 640, 400 });
    button1.setText("Button 1");
    button2.setText("Button 2");
    button3.setText("Button 3");
    button4.setText("Button 4");
    button5.setText("Button 5");

    list.append("Item 1");
    list.append("Item 2");
    list.append("Item 3");
    list.append("Item 4");
    list.append("Item 5");

    layout.setMargin(5);
    layout.append(aLayout, ~0, 0, 5);
    layout.append(bLayout, ~0, 0, 5);
    aLayout.append(button1, ~0, 25, 5);
    aLayout.append(button2, ~0, 25, 5);
    aLayout.append(button3, ~0, 25, 5);
    bLayout.append(button4, ~0, 25, 5);
    bLayout.append(button5, ~0, 25, 5);
    layout.append(list, ~0, ~0);
    append(layout);

    onClose = &OS::quit;

    button1.onTick = [&] { aLayout.append(button3, ~0, 25, 5); };
    button2.onTick = [&] { aLayout.remove(button3); };
    button3.onTick = [&] {};
    button4.onTick = [&] { layout.append(aLayout, ~0, 0, 5); };
    button5.onTick = [&] { layout.remove(aLayout); };

    setVisible();
  }
};
*/

int main() {
  auto application = new Application;
  OS::main();
  delete application;
  return 0;
}

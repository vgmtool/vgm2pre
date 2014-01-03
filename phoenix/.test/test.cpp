#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

struct MainWindow : Window {
  VerticalLayout layout;
  ListView listView;

  MainWindow() {
    setFrameGeometry({64, 64, 640, 480});

    layout.setMargin(5);
    listView.append("Item 1");
    listView.append("Item 2");
    listView.append("Item 3");
    listView.setSelection(1);
    layout.append(listView, {~0, ~0});
    append(layout);

    onClose = &Application::quit;

    listView.onActivate = [&] {
      if(modal() == false) {
        print("Base = ", listView.selection(), "\n");
        setModal(true);
      } else {
        print("Slot = ", listView.selection(), "\n");
        setModal(false);
        setVisible(false);
      }
    };

    setVisible();
    listView.setFocused();
  }
};

int main() {
  new MainWindow;
  Application::run();
  return 0;
}

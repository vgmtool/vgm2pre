#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct TestWindow : Window {
  TestWindow() {
    setGeometry({64, 64, 480, 640});
    setTitle("Test Window");

    onClose = [&] {
      setVisible(false);
    };
  }
} *testWindow = nullptr;

struct Application : Window {
  VerticalLayout layout;
  ListView listView;
  ListView test;
  ComboBox comboView;
  Button button;
  Label label;
  Menu file;
  Menu submenu;
  Item quit;

  Application() {
    setTitle("Main Window");
    setGeometry({128, 128, 640, 480});

    file.setText("File");
    submenu.setText("Submenu");
    submenu.setImage(image("folder.png"));
    quit.setText("Quit");
    quit.setImage(image("image.png"));

  //submenu.setImage();
  //quit.setImage();

    setMenuVisible();
    append(file);
    file.append(submenu);
    file.append(quit);

    listView.setHeaderText("Column 1", "Column 2", "Column 3");
    listView.setHeaderVisible();
    listView.setCheckable();
    listView.append("A", "B", "C");
    listView.append("D", "E", "F");
    listView.append("G", "H", "I");

    test.setHeaderText("Column 1", "Column 2");
    test.setHeaderVisible();
    test.append("A", "B");
    test.append("C", "D");
    test.append("E", "F");

    listView.setImage(0, 0, image("image.png"));
    listView.setImage(1, 0, image("folder.png"));
    listView.setImage(2, 2, image("folder.png"));
  //listView.setImage(0, 0);
  //listView.setImage(1, 0);

  //button.setText("Hello");
    button.setImage(image("image.png"));
  //button.setImage();

    label.setText("Label");

    append(layout);
    layout.setMargin(5);
    layout.append(listView, {~0, ~0}, 5);
    layout.append(test, {~0, ~0}, 5);
    layout.append(comboView, {~0, 0}, 5);
    layout.append(button, {~0, 0}, 5);
    layout.append(label, {~0, 0});

    comboView.append("item1", "item2*", "item3", "item4", "item5", "item6", "item7", "item8");

    button.onActivate = [&] {
      testWindow->setVisible();
      //DialogWindow::folderSelect(*this, "c:/users/byuu/appdata/roaming/emulation");  //, "All files (*)");
      //listView.remove(1);
      //comboView.modify(1, "item2");
      //comboView.remove(2);
    };

    setVisible();
    onClose = &OS::quit;
  }
} *application = nullptr;

int main() {
  OS::setName("higan");
  testWindow = new TestWindow;
  application = new Application;
  OS::main();
  return 0;
}

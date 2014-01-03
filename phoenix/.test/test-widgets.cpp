#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

Timer timer;

struct SubWindow : Window {
  VerticalLayout layout;
    LineEdit lineEdit;
    ListView listView;
    Button button1;
    Button button2;
    Button button3;
    Button button4;

  SubWindow();
} *subWindow = nullptr;

SubWindow::SubWindow() {
  subWindow = this;
  setGeometry({1080, 128, 320, 480});
  setTitle("Phoenix - Sub Window");

  layout.setMargin(5);
  listView.append("Item 1");
  listView.append("Item 2");
  listView.append("Item 3");
  listView.append("Item 4");
  listView.append("Item 5");
  button1.setText("Set Modal");
  button2.setText("Clear Modal");
  button3.setText("Browser");
  button4.setText("Message");

  append(layout);
  layout.append(lineEdit, {~0, 0}, 5);
  layout.append(listView, {~0, ~0}, 5);
  layout.append(button1, {~0, 0}, 5);
  layout.append(button2, {~0, 0}, 5);
  layout.append(button3, {~0, 0}, 5);
  layout.append(button4, {~0, 0});

  button1.onActivate = [&] {
    setModal(true);
    print(lineEdit.text(), "\n");
  };

  button2.onActivate = [&] {
    setModal(false);
  };

  button3.onActivate = [&] {
    string filename = BrowserWindow()
    .setParent(*this)
    .setTitle("Open File!!")
    .setFilters("Text documents (*.txt)", "All files (*)")
    .setPath("c:/users/byuu/downloads")
    .directory();
    print("{", filename, "}\n");
  };

  button4.onActivate = [&] {
    auto response = MessageWindow("Do you want to quit?")
    .setParent(*this)
    .setTitle("Phoenix Title")
    .question(MessageWindow::Buttons::YesNoCancel);
    print("[", (unsigned)response, "]\n");
  };

  onClose = [&] {
    setModal(false);
    setVisible(false);
  //Application::quit();
  };

//setVisible();
}

struct MainWindow : Window {
  Menu system;
    Menu load;
      RadioItem loadFamicom;
      RadioItem loadSuperFamicom;
      RadioItem loadGameBoy;
    CheckItem power;
    CheckItem reset;
  Menu settings;
  Menu help;
    Item documentation;

  VerticalLayout layout;
    HorizontalLayout testLayout;
      Label label;
      ComboButton comboButton;
    HorizontalLayout radioLayout;
      RadioButton radio1;
      RadioButton radio2;
      RadioButton radio3;
    HorizontalLayout controlLayout;
      LineEdit lineEdit;
      Button button;
    TextEdit textEdit;
    ListView listView;

  MainWindow();
} *mainWindow = nullptr;

MainWindow::MainWindow() {
  mainWindow = this;
  setTitle("Phoenix");
  setGeometry({128, 128, 640, 480});
//setWidgetFont(Font::sans(8, "Bold"));

  system.setText("System");
    load.setImage({"image.png"});
    load.setText("Load");
      loadFamicom.setText("Famicom ...");
      loadSuperFamicom.setText("Super Famicom ...");
      loadGameBoy.setText("Game Boy ...");
      RadioItem::group(loadFamicom, loadSuperFamicom, loadGameBoy);
    power.setText("Power");
    reset.setText("Reset");
  settings.setText("Settings");
  help.setText("Help");
    documentation.setImage({"image.png"});
    documentation.setText("Documentation ...");

  append(system);
    system.append(load);
      load.append(loadFamicom);
      load.append(loadSuperFamicom);
      load.append(loadGameBoy);
    system.append(power);
    system.append(reset);
  append(settings);
  append(help);
    help.append(documentation);

  setMenuVisible();

  layout.setMargin(5);
  label.setText("Test Label");
  comboButton.append("Item 1", "Item 2", "Long Item 3");
  radio1.setText("Radio 1");
  radio2.setText("Radio 2");
  radio3.setText("Radio 3");
  RadioButton::group(radio1, radio2, radio3);
  button.setImage({"image.png"});
  button.setText("Fullscreen");
  textEdit.setText("Test1\nTest2");
//listView.setFont(Font::sans(20, "Bold"));
  listView.setHeaderVisible();
  listView.setHeaderText("Column 1", "Column 2", "Column 3");
  listView.append("Alpha",   "1B",     "1C");
  listView.append("Beta",    "Red",    "2C");
  listView.append("Delta",   "3B",     "3C");
  listView.append("Epsilon", "4B",     "4C");
  listView.append("Gamma",   "5B",     "5C");
  listView.append("Zeta",    "Yellow", "6C");
  listView.setImage(1, 1, {"image.png"});
  listView.autoSizeColumns();

  append(layout);
  layout.append(testLayout, {~0, 0}, 5);
    testLayout.append(label, {~0, 0}, 5);
    testLayout.append(comboButton, {0, 0});
  layout.append(radioLayout, {~0, 0}, 5);
    radioLayout.append(radio1, {~0, 0}, 5);
    radioLayout.append(radio2, {~0, 0}, 5);
    radioLayout.append(radio3, {~0, 0});
  layout.append(controlLayout, {~0, 0}, 5);
    controlLayout.append(lineEdit, {~0, 0}, 5);
    controlLayout.append(button, {0, 0});
  layout.append(textEdit, {~0, 100}, 5);
  layout.append(listView, {~0, ~0});

/*canvas.setSize({256, 256});
  uint32_t *data = canvas.data();
  for(unsigned y = 0; y < 256; y++) {
    for(unsigned x = 0; x < 256; x++) {
      double xs = 1.0 / (256.0 / x);
      double ys = 1.0 / (256.0 / y);
      double cs = (xs * 0.5 + ys * 0.5) * 256.0;
      uint8_t color = min(cs, 255.0);
      *data++ = (255u << 24) | color;
    }
  }
  canvas.update();*/

  setVisible();
  onClose = &Application::quit;
  button.onActivate = [&] {
  //setFullScreen(!fullScreen());
    subWindow->setVisible();
    subWindow->listView.setSelection(2);
    subWindow->listView.setFocused();
    subWindow->setModal();
  };
}

int main() {
  Application::setName("Phoenix/Test");
  Application::Cocoa::onQuit = &Application::quit;

  print("Phoenix\n");
  new SubWindow;
  new MainWindow;
  Application::main = [&] {
    static unsigned counter = 0;
    if(++counter == 10) {
      auto margin = mainWindow->frameMargin();
      print(margin.x, ",", margin.y, ",", margin.width, ",", margin.height, "\n");
      print(Desktop::size().width, "x", Desktop::size().height, "\n");
      margin = Desktop::workspace();
      print(margin.x, ",", margin.y, ",", margin.width, ",", margin.height, "\n");
    }
    usleep(10 * 1000);
  };
  Application::Windows::onModalBegin = [] { print("Modal Begin\n"); };
  Application::Windows::onModalEnd = [] { print("Modal End\n"); };
  timer.onActivate = [] { static unsigned counter = 0; print(counter++, "\n"); };
  timer.setInterval(20);
//timer.setEnabled();
  Application::run();
  print("Terminate\n");
  return 0;
}

#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

struct MainWindow : Window {
  VerticalLayout layout;
  Console console;

  MainWindow();
  void command(string);
} *mainWindow = nullptr;

MainWindow::MainWindow() {
  mainWindow = this;

  setTitle("Console");
  setGeometry({128, 128, 640, 320});
  layout.setMargin(0);
  console.setFont(Font::monospace(8));
  console.print("phoenix/Console\n");
  console.print("\n");
  console.print("$ ");

  append(layout);
  layout.append(console, {~0, ~0});

  onClose = &Application::quit;
  console.onActivate = {&MainWindow::command, this};

  setVisible();
}

void MainWindow::command(string s) {
  if(s.empty()) {
  } else if(s == "quit" || s == "exit") {
    Application::quit();
  } else if(s == "clear" || s == "reset") {
    console.reset();
  } else if(s == "uname") {
    console.print("phoenix/console");
  } else {
    console.print("error: command not found: ", s);
  }
  if(s && s != "clear" && s != "reset") console.print("\n");
  console.print("$ ");
}

int main() {
  new MainWindow;
  Application::run();
  return 0;
}

#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

struct MainWindow : Window {
  VerticalLayout layout;
  HexEdit hexEdit;

  uint8_t buffer[16 * 64 + 1];

  MainWindow();
  uint8_t onRead(unsigned addr);
  void onWrite(unsigned addr, uint8_t data);
};

MainWindow::MainWindow() {
  setSmartGeometry({64, 64, 560, 370});  //Windows
//setSmartGeometry({64, 64, 555, 395});  //GTK+
//setSmartGeometry({64, 64, 560, 405});  //Qt
  setTitle("Hex Edit");

  for(unsigned n = 0; n < sizeof(buffer); n++) buffer[n] = n;

  layout.setMargin(5);
  hexEdit.setFont(Font::monospace(8));
  hexEdit.setColumns(16);
  hexEdit.setRows(32);
  hexEdit.setOffset(0);
  hexEdit.setLength(sizeof(buffer));

  append(layout);
  layout.append(hexEdit, {~0, ~0});

  onClose = &Application::quit;
  hexEdit.onRead = {&MainWindow::onRead, this};
  hexEdit.onWrite = {&MainWindow::onWrite, this};

  hexEdit.update();
  setVisible();
  hexEdit.setFocused();
}

uint8_t MainWindow::onRead(unsigned addr) {
  return buffer[addr];
}

void MainWindow::onWrite(unsigned addr, uint8_t data) {
  buffer[addr] = data;
}

int main() {
  Application::setName("higan");
  new MainWindow;
  Application::run();
  return 0;
}

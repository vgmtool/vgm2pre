#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : Window {
  Menu fileMenu;
    Menu fileMode;
      RadioItem fileRead;
      RadioItem fileWrite;
      Separator fileModeSeparator;
      CheckItem fileOption1;
      CheckItem fileOption2;
    Separator fileSeparator;
    Item fileQuit;
  Menu helpMenu;
    Item helpAbout;

  VerticalLayout layout;
  Label label;
  ProgressBar progress;
  HorizontalSlider slider;
  Button button;
  Viewport viewport;
  HorizontalLayout checkLayout;
  CheckBox check1;
  CheckBox check2;
  HorizontalLayout radioLayout;
  RadioBox radio1;
  RadioBox radio2;
  HorizontalLayout controlLayout;
  LineEdit lineEdit;
  ComboBox comboBox;
  TextEdit textEdit;
  ListView list;

  Application() {
    setTitle("phoenix/Windows");

    fileMenu.setText("File");
      fileMode.setText("Mode");
        fileRead.setText("Read");
        fileWrite.setText("Write");
        RadioItem::group(fileRead, fileWrite);
        fileOption1.setText("Option 1");
        fileOption2.setText("Option 2");
        fileOption2.setChecked();
      fileQuit.setText("Quit");
    helpMenu.setText("Help");
      helpAbout.setText("About ...");

    append(fileMenu);
      fileMenu.append(fileMode);
        fileMode.append(fileRead);
        fileMode.append(fileWrite);
        fileMode.append(fileModeSeparator);
        fileMode.append(fileOption1);
        fileMode.append(fileOption2);
      fileMenu.append(fileSeparator);
      fileMenu.append(fileQuit);
    append(helpMenu);
      helpMenu.append(helpAbout);

    setStatusText("Ready");

    setMenuVisible();
    setStatusVisible();

    label.setText("Line 1\nLine 2\nLine 3");
    progress.setPosition(33);
    slider.setLength(101);
    button.setText("Button");
    check1.setText("Check 1");
    check2.setText("Check 2");
    radio1.setText("Radio 1");
    radio2.setText("Radio 2");
    RadioBox::group(radio1, radio2);
    lineEdit.setText("LineEdit");
    comboBox.append("Combo 1");
    comboBox.append("Combo 2");
    textEdit.setText("Line 1\nLine 2\nLine 3");
    list.setHeaderText("Column 1", "Column 2", "Column 3");
    list.setHeaderVisible();
    list.setCheckable();
    list.append("Item 1A", "Item 1B");
    list.append("Item 2A");
    list.modify(1, "Item 2A", "Item 2B", "Item 2C");
    list.append("Item 3A", "Item 3B");
    list.setChecked(2, true);
    list.setSelection(1);

    layout.setMargin(5);
    layout.append(label, ~0, 0, 5);
    layout.append(progress, ~0, 30, 5);
    layout.append(slider, ~0, 25, 5);
    layout.append(button, ~0, 30, 5);
  //layout.append(viewport, 0, 100, 5);
    checkLayout.append(check1, ~0, 0, 5);
    checkLayout.append(check2, ~0, 0);
    layout.append(checkLayout, ~0, 0);
    radioLayout.append(radio1, ~0, 0, 5);
    radioLayout.append(radio2, ~0, 0);
    layout.append(radioLayout, ~0, 0, 5);
    controlLayout.append(lineEdit, ~0, 0, 5);
    controlLayout.append(comboBox, ~0, 0);
    layout.append(controlLayout, ~0, 0, 5);
    layout.append(textEdit, ~0, 50, 5);
    layout.append(list, ~0, ~0);
    append(layout);

    setFrameGeometry({ 128, 128, 640, 480 });
    setVisible();

    Color color = backgroundColor();
    color.alpha = 224;
    setBackgroundColor(color);

    onMove = [this]() {
      Geometry geometry = this->frameGeometry();
      print("move ", geometry.x, ",", geometry.y, ",", geometry.width, ",", geometry.height, "\n");
    };

    onSize = [this]() {
      Geometry geometry = this->frameGeometry();
      print("size ", geometry.x, ",", geometry.y, ",", geometry.width, ",", geometry.height, "\n");
    };

    onClose = fileQuit.onTick = [this]() {
      Geometry geometry = this->frameGeometry();
    //MessageWindow::information(Window::None, { geometry.x, ",", geometry.y, ",", geometry.width, ",", geometry.height, "\n" });
      OS::quit();
    };
    button.onTick = [this]() { static bool fs = false; fs = !fs; this->setFullScreen(fs); };
    list.onTick = [this](unsigned row) { print("List::tick(", row, ") = ", this->list.checked(row), "\n"); };
  //list.onChange = [this]() { if(auto selection = this->list.selection()) print("List::change(", selection(), ")\n"); };
  //list.onActivate = [this]() { if(auto selection = this->list.selection()) print("List::activate(", selection(), ")\n"); };
  }
} application;

int main() {
  OS::main();
  return 0;
}

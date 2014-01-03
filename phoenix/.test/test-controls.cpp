#include "phoenix.hpp"
#include <nall/directory.hpp>
using namespace nall;
using namespace phoenix;

struct Application : Window {
  VerticalLayout layout;
  HorizontalLayout buttonLayout;
  Label label;
  Button button1;
  Button button2;
  CheckBox check1;
  CheckBox check2;
  RadioBox radio1;
  RadioBox radio2;
  HorizontalLayout controlLayout;
  ComboBox combo;
  LineEdit line;
  ProgressBar progress;
  HorizontalSlider slider;
  HorizontalScrollBar scroll;
  TextEdit textEdit;
  ListView listView;

  void create() {
    Color color = backgroundColor();
    print((unsigned)color.red, ",", (unsigned)color.green, ",", (unsigned)color.blue, "\n");
  //setBackgroundColor({ 64, 64, 64, 128 });
  //setResizable(false);

    label.setText("Label:");
    button1.setText("Button 1");
    button2.setText("Button 2");
    check1.setText("Check 1");
    check2.setText("Check 2");
    radio1.setText("Radio 1");
    radio2.setText("Radio 2");
    RadioBox::group(radio1, radio2);
    combo.append("Item 1");
    combo.append("Item 2");
    line.setText("Line Edit");
    progress.setPosition(33);
    textEdit.setText("Line 1\nLine 2\nLine 3");
//  textEdit.setWordWrap(false);
    listView.setHeaderText("Column 1", "Column 2", "Column 3");
    listView.setHeaderVisible();
    listView.append("Item 1A", "Item 1B", "Item 1C");
    listView.append("Item 2A", "Item 2B");
    listView.append("Item 3A", "Item 3B", "Item 3C");

    layout.setMargin(5);
    buttonLayout.append(label,     { 0,  0}, 5);
    buttonLayout.append(button1,   { 0,  0}, 5);
    buttonLayout.append(button2,   {~0,  0}, 5);
    buttonLayout.append(check1,    { 0,  0}, 5);
    buttonLayout.append(check2,    { 0,  0}, 5);
    buttonLayout.append(radio1,    { 0,  0}, 5);
    buttonLayout.append(radio2,    { 0,  0}   );
    layout.append(buttonLayout,    {~0,  0}, 5);
    controlLayout.append(combo,    { 0,  0}, 5);
    controlLayout.append(line,     { 0,  0}, 5);
    controlLayout.append(progress, {~0,  0}   );
    layout.append(controlLayout,   {~0,  0}, 5);
    layout.append(slider,          {~0,  0}, 5);
    layout.append(scroll,          {~0,  0}, 5);
    layout.append(textEdit,        {~0, ~0}, 5);
    layout.append(listView,        {~0, ~0}   );
    append(layout);

    setTitle("phoenix");
    setFrameGeometry({ 128, 128, layout.minimumGeometry().width, layout.minimumGeometry().height + 160 });
    setVisible();

    lstring folders = directory::folders("c:/test");
    for(auto &folder : folders) print(folder, "\n");

    button1.onActivate = [&] {
      setFullScreen(!fullScreen());
    };

    button2.onActivate = [&] {
      listView.setSelection(1);
    };

    scroll.onChange = [&]() {
      print(this->scroll.position(), "\n");
      Color color = this->backgroundColor();
      print((unsigned)color.red, ",", (unsigned)color.green, ",", (unsigned)color.blue, ",", (unsigned)color.alpha, "\n");
    };

    onClose = [&]() {
      Geometry geometry = this->frameGeometry();
    //MessageWindow::information(Window::None, { geometry.x, ",", geometry.y, ",", geometry.width, ",", geometry.height, "\n" });
      OS::quit();
    };
  }
} application;

int main() {
  application.create();
  OS::main();
  return 0;
}

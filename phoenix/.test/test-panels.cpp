#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct VideoPanel : HorizontalLayout {
  Widget spacer;
  VerticalLayout layout;
  Label label;

  VideoPanel() {
    setMargin(5);
    append(spacer, 120, ~0, 5);
    append(layout, ~0, ~0);
    label.setFont("Sans, 16, Bold");
    label.setText("Video");
    layout.append(label, ~0, 0, 5);
  }
};

struct AudioPanel : HorizontalLayout {
  Widget spacer;
  VerticalLayout layout;
  Label label;
  ListView list;

  AudioPanel() {
    setMargin(5);
    append(spacer, 120, ~0, 5);
    append(layout, ~0, ~0);
    label.setFont("Sans, 16, Bold");
    label.setText("Audio");
    list.setCheckable();
    list.append("Item");
    list.append("Item");
    list.append("Item");
    list.append("Item");
    list.append("Item");
    layout.append(label, ~0, 0, 5);
    layout.append(list, ~0, ~0);

    list.onTick = [&](unsigned n) { print("Row ", n, "\n"); };
  }
};

struct InputPanel : HorizontalLayout {
  Widget spacer;
  VerticalLayout layout;
  Label label;

  InputPanel() {
    setMargin(5);
    append(spacer, 120, ~0, 5);
    append(layout, ~0, ~0);
    label.setFont("Sans, 16, Bold");
    label.setText("Input");
    layout.append(label, ~0, 0, 5);
  }
};

struct Application : Window {
  HorizontalLayout layout;
  ListView list;
  VideoPanel videoPanel;
  AudioPanel audioPanel;
  InputPanel inputPanel;

  void create() {
    layout.setMargin(5);
    list.append("Video");
    list.append("Audio");
    list.append("Input");
    list.setSelection(0);

    append(layout);
    append(videoPanel);
    append(audioPanel);
    append(inputPanel);
    layout.append(list, 120, ~0, 5);
    select();

    setStatusText("???");
    setStatusVisible();

    setTitle("Layout List");
    setFrameGeometry({ 64, 64, 640, 360 });
    setVisible();

    onClose = &OS::quit;
    list.onChange = { &Application::select, this };
  }

  void select() {
    videoPanel.setVisible(false);
    audioPanel.setVisible(false);
    inputPanel.setVisible(false);

    if(list.selected()) switch(list.selection()) {
    case 0: return videoPanel.setVisible();
    case 1: return audioPanel.setVisible();
    case 2: return inputPanel.setVisible();
    }
  }
} application;

int main() {
  application.create();
  OS::main();
  return 0;
}

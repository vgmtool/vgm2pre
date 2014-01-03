#include "phoenix.hpp"
using namespace nall;
using namespace phoenix;

struct Application : Window {
  VerticalLayout layout;
    Button button;
    HorizontalLayout groupA;
      RadioBox itemA[3];
    HorizontalLayout groupB;
      RadioBox itemB[3];
    HorizontalLayout groupC;
      RadioBox itemC[3];

  Application() {
    setGeometry({256, 256, 640, 400});

    layout.setMargin(5);
    button.setText("Toggle");
    itemA[0].setText("Item A0");
    itemA[1].setText("Item A1");
    itemA[2].setText("Item A2");
    RadioBox::group(itemA[0], itemA[1], itemA[2]);
    itemB[0].setText("Item B0");
    itemB[1].setText("Item B1");
    itemB[2].setText("Item B2");
    RadioBox::group(itemB[0], itemB[1], itemB[2]);
    itemC[0].setText("Item C0");
    itemC[1].setText("Item C1");
    itemC[2].setText("Item C2");
    RadioBox::group(itemC[0], itemC[1], itemC[2]);

    append(layout);
    layout.append(button, {~0, 0}, 5);
    layout.append(groupA, {~0, 0}, 5);
      groupA.append(itemA[0], {~0, 0}, 5);
      groupA.append(itemA[1], {~0, 0}, 5);
      groupA.append(itemA[2], {~0, 0});
    layout.append(groupB, {~0, 0}, 5);
      groupB.append(itemB[0], {~0, 0}, 5);
      groupB.append(itemB[1], {~0, 0}, 5);
      groupB.append(itemB[2], {~0, 0});
    layout.append(groupC, {~0, 0}, 5);
      groupC.append(itemC[0], {~0, 0}, 5);
      groupC.append(itemC[1], {~0, 0}, 5);
      groupC.append(itemC[2], {~0, 0});

    onClose = &OS::quit;

    itemC[0].onActivate = [] { print("C0\n"); };
    itemC[1].onActivate = [] { print("C1\n"); };
    itemC[2].onActivate = [] { print("C2\n"); };

    button.onActivate = [&] {
//print("Before: ", itemC[0].checked(), ",", itemC[1].checked(), ",", itemC[2].checked(), "\n");
      static bool visible = true;
      if(visible) {
        layout.remove(groupC);
      } else {
        layout.append(groupC, {~0, 0}, 5);
      }
      visible = !visible;
//print("After!: ", itemC[0].checked(), ",", itemC[1].checked(), ",", itemC[2].checked(), "\n");
    };

    setVisible();
  }
};

int main() {
  auto application = new Application;
  OS::main();
  delete application;
  return 0;
}

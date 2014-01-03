#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

struct TestWindow : Window {
  VerticalLayout layout;
  TabFrame tabFrame;
  VerticalLayout tabLayout;
  TabFrame innerFrame;
  VerticalLayout innerLayout;
  TabFrame finalFrame;
  VerticalLayout finalLayout;
  Label label;
  HorizontalSlider slider;
  ComboButton comboButton;
  ListView listView;
  HorizontalSlider outerSlider;

  TestWindow() {
    setWindowGeometry({64, 760, 480, 320});
    setBackgroundColor({128, 64, 64, 128});

    for(unsigned n = 0; n < 16; n++) comboButton.append({"Item ", n});

    layout.setMargin(5);
    tabFrame.append("Item 1");
    tabFrame.append("Item 2");
    layout.append(tabFrame, {~0, ~0}, 5);
    tabLayout.setMargin(5);
    innerFrame.append("Tab 1");
    innerFrame.append("Tab 2");
    innerFrame.append("Tab 3");
    innerLayout.setMargin(5);
    finalFrame.append("Final 1");
    finalFrame.append("Final 2");
    finalLayout.setMargin(5);
    label.setText("Test\nLabel");
    slider.setLength(101);
    finalLayout.append(label, {~0, 0}, 5);
    finalLayout.append(slider, {~0, 0}, 5);
    finalLayout.append(comboButton, {~0, 0}, 5);
    finalLayout.append(listView, {~0, ~0});
    finalFrame.setLayout(0, finalLayout);
    innerLayout.append(finalFrame, {~0, ~0});
    innerFrame.setLayout(0, innerLayout);
    tabLayout.append(innerFrame, {~0, ~0});
    tabFrame.setLayout(0, tabLayout);
    layout.append(outerSlider, {~0, 0});
    append(layout);

    finalFrame.onChange = [&] { print("TabFrame::setSelection(", finalFrame.selection(), ")\n"); };
    finalFrame.setSelection(1);

    setVisible();
    onClose = &Application::quit;
  }
};

struct MainWindow : Window {
  VerticalLayout layout;
    TabFrame tabFrame;
      VerticalLayout tabLayout0;
        TabFrame innerFrame;
          VerticalLayout innerLayout0;
            ListView listView;
            Frame frame;
              VerticalLayout frameLayout;
                TextEdit frameLabel;
      VerticalLayout tabLayout1;
        Canvas canvas;

  MainWindow() {
    setWindowGeometry({64, 64, 800, 640});
    setTitle("TabFrame Demo");

    layout.setMargin(5);

    tabFrame.append("Famicom");
    tabFrame.append("Super Famicom", {"folder.png"});
    tabFrame.append("Game Boy");
    tabFrame.append("Game Boy Color");
    tabFrame.append("Game Boy Advance");

    tabLayout0.setMargin(5);

    innerFrame.append("First");
    innerFrame.append("Second");

    innerLayout0.setMargin(5);

    listView.append("Chrono Trigger");
    listView.append("Super Metroid");
    listView.append("Wanderers from Ys");

    frame.setText("Information");

    frameLayout.setMargin(5);

    frameLabel.setText("Title: Chrono Trigger\nPublisher: Nintendo");

    tabLayout1.setMargin(5);

    nall::image image("higan.png");
    canvas.setSize({image.width, image.height});
    canvas.setImage(image);

    //

    innerLayout0.append(listView, {~0, ~0}, 5);
    frameLayout.append(frameLabel, {~0, ~0});
    frame.setLayout(frameLayout);
    innerLayout0.append(frame, {~0, 80});
    innerFrame.setLayout(0, innerLayout0);
    tabLayout0.append(innerFrame, {~0, ~0});
    tabFrame.setLayout(0, tabLayout0);
    tabLayout1.append(canvas, {~0, ~0});
    tabFrame.setLayout(1, tabLayout1);
    layout.append(tabFrame, {~0, ~0});
    append(layout);


    onClose = &Application::quit;
    setVisible();

    listView.setSelection(1);
    listView.setFocused();
    listView.onActivate = [&] { print(listView.selection(), "\n"); };

    #if 0
    animation.onActivate = [&] {
      if(phase == 4) return;

      nall::image backdrop;
      backdrop.allocate(512, 512);
      backdrop.fill(0);
      nall::image logo("higan.png");

      if(phase == 0) {
        logo.crop(offset, offset, 256, 256);
        backdrop.impose(image::blend::sourceColor, offset, offset, logo, 0, 0, 256, 256);

        if(++offset == 256) phase = 1;
      } else if(phase == 1) {
        if(--offset == 128) phase = 2;

        logo.crop(offset, offset, 256, 256);
        backdrop.impose(image::blend::sourceColor, offset, offset, logo, 0, 0, 256, 256);
      } else if(phase == 2) {
        if(--offset == 0) phase = 3;

        unsigned size = (256 - offset) * 2;
        logo.crop(offset, offset, size, size);
        backdrop.impose(image::blend::sourceColor, offset, offset, logo, 0, 0, size, size);
      } else if(phase == 3) {
        backdrop.verticalGradient((offset << 24) + 255, 0);
        backdrop.impose(image::blend::sourceAlpha, 0, 0, logo, 0, 0, 512, 512);

        if(++offset == 256) phase = 4;
      }

      canvas.setImage(backdrop);
    };

    animation.setInterval(1);
    animation.setEnabled();
    #endif
  }
};

int main() {
  new TestWindow;
  new MainWindow;
  Application::run();
  return 0;
}

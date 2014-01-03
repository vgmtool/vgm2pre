#include <phoenix/phoenix.hpp>
using namespace nall;
using namespace phoenix;

struct MainWindow : Window {
  VerticalLayout layout;
    HorizontalLayout tabLayout;
      Label title;
      RadioButton button[5];
      Widget spacer;
      Button importButton;
    Viewport separator;
    HorizontalLayout viewLayout;
      ListView view;
      VerticalLayout screenshotLayout;
        Canvas screenshot;
    HorizontalLayout infoLayout;
      Canvas canvas;
      Label infoLabel;
      VerticalLayout loadLayout;
        Widget loadSpacer;
        Button loadButton;

  MainWindow() {
    setTitle("Tab Bar Demo");
    setSmartGeometry({64, 64, 860, 480});

    layout.setMargin(5);
    title.setFont(Font::sans(8, "Bold"));
    title.setText("Library");
    button[0].setText("Famicom");
    button[1].setText("Super Famicom");
    button[2].setText("Game Boy");
    button[3].setText("Game Boy Color");
    button[4].setText("Game Boy Advance");
    importButton.setText("Import Game ...");
    view.append("Chrono Trigger (NA) (1.0)");
    view.append("Legend of Zelda - A Link to the Past, The (NA) (1.0)");
    view.append("Super Metroid (NA) (1.1)");
    screenshot.setSize({256, 256});
    screenshot.fill({255, 64, 64}, {127, 32, 32}, {127, 32, 32}, {0, 0, 0});
    nall::image image("/usr/local/share/pixmaps/higan.png");
    image.alphaBlend(backgroundColor().rgb());
    image.scale(48, 48, Interpolation::Hermite);
    canvas.setImage(image);
    canvas.update();
    infoLabel.setText(
      "Title: The Legend of Zelda - A Link to the Past\n"
      "Version: 1.0 (North America)\n"
      "Developer: Nintendo\n"
      "Release Date: April 18th, 1994"
    );
    loadButton.setText("Load Game");

    for(auto& b : button) {
      nall::image image("/usr/local/share/pixmaps/higan.png");
      image.scale(16, 16, Interpolation::Hermite);
      b.setImage(image);
      b.onActivate = [&]() { print(b.checked(), "\n"); };
    };

    RadioButton::group(button[0], button[1], button[2], button[3], button[4]);
    button[1].setChecked();

    append(layout);
    layout.append(tabLayout, {~0, 0}, 5);
    tabLayout.append(title, {0, ~0}, 5);
    tabLayout.append(button[0], {0, ~0}, 5);
    tabLayout.append(button[1], {0, ~0}, 5);
    tabLayout.append(button[2], {0, ~0}, 5);
    tabLayout.append(button[3], {0, ~0}, 5);
    tabLayout.append(button[4], {0, ~0}, 5);
    tabLayout.append(spacer, {~0, ~0}, 0);
    tabLayout.append(importButton, {0, ~0}, 0);
    layout.append(separator, {~0, 1}, 5);
    layout.append(viewLayout, {~0, ~0}, 5);
    viewLayout.append(view, {~0, ~0}, 5);
    viewLayout.append(screenshotLayout, {0, ~0});
    screenshotLayout.append(screenshot, {256, 256});
    layout.append(infoLayout, {~0, 0});
    infoLayout.append(canvas, {48, 48}, 5);
    infoLayout.append(infoLabel, {~0, ~0}, 5);
    infoLayout.append(loadLayout, {0, ~0});
    loadLayout.append(loadSpacer, {0, ~0});
    loadLayout.append(loadButton, {0, 0});

    onClose = &Application::quit;
    setVisible();
    view.setFocused();
  }
};

int main() {
  new MainWindow;
  Application::run();
  return 0;
}

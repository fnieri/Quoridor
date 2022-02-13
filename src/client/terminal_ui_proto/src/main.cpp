#include <unistd.h>
#include <iostream>
#include <iterator>
#include <memory>  // for allocator, shared_ptr, __shared_ptr_access
#include <sstream>
#include <string>  // for char_traits, operator+, to_string
#include <thread>
#include <vector>  // for vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, operator|, Element, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color

// Try
#include "ftxui/component/component_options.hpp"  // for ButtonOption
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/screen/box.hpp"
#include "ftxui/util/ref.hpp"
//

using namespace ftxui;

class MyScreen {
  std::string message;
  int actionToggleSelected = 0;
  ToggleOption actionToggleOption;
  ButtonOption buttonOption;
  std::vector<std::string> actionToggleEntries = {
      "Move",
      "Wall",
  };
  std::vector<std::string> mainTabValues{
      "Game",
      "Friends",
      "Settings",
  };
  std::vector<std::vector<std::string>> chatMessages;
  int mainTabSelect = 0;
  int rightSize = 40;

  auto createBoardButtonsContainer(int size) {
    // https://github.com/ArthurSonzogni/FTXUI/blob/master/examples/component/checkbox_in_frame.cpp
    // maybe better with Container_>Add ?

    buttonOption.border = false;
    std::vector<Component> buttonsGrid;
    for (int i = 0; i < size; i++) {
      std::vector<Component> row_components;
      for (int j = 0; j < size; j++) {
        row_components.push_back(Button(
            "o ",
            [i, j, this] {
              std::cout << "Clicked " << i << " " << j << std::endl;
            },
            &buttonOption));
      }
      auto buttonsRow = Container::Horizontal(row_components);
      buttonsGrid.push_back(buttonsRow);
    }

    auto buttonsContainer = Container::Vertical({
        buttonsGrid,
    });
    return buttonsContainer;
  }

  auto createChatInput() { return Input(&message, "Aa"); }

  auto createActionToggle() {
    actionToggleOption.style_selected = color(Color::Blue);
    actionToggleOption.style_focused = bold | color(Color::White);
    actionToggleOption.style_selected_focused = bold | color(Color::BlueLight);
    return Toggle(&actionToggleEntries, &actionToggleSelected,
                  &actionToggleOption);
  }

  auto createMainTab() { return Toggle(&mainTabValues, &mainTabSelect); }

  auto createBoardRenderer() {
    auto actionToggle = createActionToggle();
    auto buttonsContainer = createBoardButtonsContainer(9);
    auto boardContainer = Container::Vertical({
        actionToggle,
        buttonsContainer,
    });
    return Renderer(boardContainer, [buttonsContainer, actionToggle] {
      return vbox({border(buttonsContainer->Render() | center),
                   actionToggle->Render() | center});
    });
  }

  auto createChatRenderer() {
    auto chatInput = createChatInput();
    chatMessages.push_back({"Louis", "Hello"});
    return Renderer(chatInput, [&, chatInput] {
      std::vector<Element> chatElements;
      for (auto mess : chatMessages) {
        chatElements.push_back(text(mess[0] + ": " + mess[1]));
      }
      auto chatVbox = vbox(chatElements);
      return vbox({
          chatVbox | vscroll_indicator | frame |
              size(HEIGHT, LESS_THAN, 10),
          separator(),
          hbox({text(">"), chatInput->Render()})
      });
    });
  }

  auto createFriendsRenderer() {
    return Renderer([] { return text("Friends") | center; });
  }

  auto createSettingsRenderer() {
    return Renderer([] { return text("Settings") | center; });
  }

  auto createMainTabContainer() {
    auto chat = createChatRenderer();
    auto boardTab = createBoardRenderer();
    auto resizeContainer = boardTab;
    resizeContainer = ResizableSplitRight(chat, resizeContainer, &rightSize);

    auto friends = createFriendsRenderer();
    auto settings = createSettingsRenderer();
    auto tabContainer = Container::Tab(
        {
            resizeContainer,
            friends,
            settings,
        },
        &mainTabSelect);
    return tabContainer;
  }

  auto createMainRenderer() {
    auto tabToggle = createMainTab();

    auto tabContainer = createMainTabContainer();

    auto mainContainer = Container::Vertical({
        tabToggle,
        tabContainer,
    });
    return Renderer(mainContainer, [tabContainer, tabToggle] {
      return vbox({
                 tabToggle->Render(),
                 separator(),
                 tabContainer->Render(),
             }) |
             border;
      ;
    });
  }

 public:
  void run() {
    auto mainRenderer = createMainRenderer();
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(mainRenderer);
  }

  void addChatMessage(std::string username, std::string message) {
    chatMessages.push_back({username, message});
  }
};

int main(int argc, const char* argv[]) {
  system("clear");
  MyScreen screen;
  std::thread t1(&MyScreen::run, &screen);
//  sleep(3);
  for (int i = 0; i < 10; i++) {
    screen.addChatMessage("User", "test");
  }
  screen.addChatMessage("User", "Hello World !");
  t1.join();
}

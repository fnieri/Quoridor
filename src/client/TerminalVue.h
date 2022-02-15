//
// Created by louis on 10/02/2022.
//

#pragma once

#include <iostream>
#include <iterator>
#include <memory> // for allocator, shared_ptr, __shared_ptr_access
#include <sstream>
#include <string> // for char_traits, operator+, to_string
#include <string>
#include <thread>
#include <unistd.h>
#include <vector> // for vector

#include "ftxui/component/captured_mouse.hpp" // for ftxui
#include "ftxui/component/component.hpp" // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp" // for separator, operator|, Element, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp" // for Color

// Try
#include "ftxui/component/component_options.hpp" // for ButtonOption
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/screen/box.hpp"
#include "ftxui/util/ref.hpp"

using namespace ftxui;

class TerminalVue
{
    std::string message;
    int actionToggleSelected = 0;
    ToggleOption actionToggleOption;
    ButtonOption buttonOption;
    std::vector<std::string> actionToggleEntries {
        "Move",
        "Wall",
    };
    std::vector<std::string> mainTabValues {
        "Game",
        "Friends",
        "Settings",
    };
    std::vector<std::vector<std::string>> chatMessages;
    int mainTabSelect = 0;
    int rightSize = 40;

    auto createBoardButtonsContainer(int size);

    auto createChatInput();

    auto createActionToggle();

    auto createMainTab();

    auto createBoardRenderer();

    auto createChatRenderer();

    auto createFriendsRenderer();

    auto createSettingsRenderer();

    auto createMainTabContainer();

    auto createMainRenderer();

public:
    void run();

    void addChatMessage(std::string username, std::string message);
};

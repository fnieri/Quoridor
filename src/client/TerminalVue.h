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
#include "ftxui/component/component_options.hpp" // for ButtonOption
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/canvas.hpp" // for Canvas
#include "ftxui/dom/elements.hpp" // for separator, operator|, Element, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/box.hpp"
#include "ftxui/screen/color.hpp" // for Color
#include "ftxui/util/ref.hpp"

using namespace ftxui;

class TerminalVue
{
    std::string message, username = "TestUser", password, registerUsername, registerPassword, registerRepeatPassword;
    int actionToggleSelected = 0;
    int mouse_x = 0;
    int mouse_y = 0;
    bool mousePressed = false;
    int wallOrientation = 0;
    std::vector<std::vector<int>> testCanvasGrid {
        {0, 5, 0, 5, 0, 5, 0, 6, 0}, {5, 5, 7, 7, 7, 5, 5, 6, 5}, {0, 5, 0, 5, 0, 5, 0, 6, 0}, {5, 5, 5, 5, 5, 5, 5, 5, 5}};

    ToggleOption actionToggleOption;
    ButtonOption buttonOption;
    int chatSelected = 0;
    std::vector<std::string> chatElements;
    std::vector<std::string> actionToggleEntries {
        "Move",
        "Wall",
    };
    std::vector<std::string> mainTabValues {
        "Game",
        "Friends",
        "Settings",
    };
    std::vector<std::string> loginTabValues {
        "Login",
        "Register",
    };
    std::vector<Component> mainTabComponents;
    int mainTabSelect = 0, loginTabSelect = 0;
    int rightSize = 40;
    bool isLoggedIn = true; // change this to true to stay logged in

    auto createBoardButtonsContainer(int size);

    auto createCanvas();

    bool mouseInCell(int x, int y);

    void handleButtonClick(int x, int y);

    auto createChatInput();

    auto createActionToggle();

    auto createMainTab();

    auto createBoardRenderer();

    auto createChatRenderer();

    auto createFriendsRenderer();

    auto createSettingsRenderer();

    auto createMainTabContainer();

    auto createLoginRenderer();

    auto createRegisterRenderer();

    auto createMainRenderer();

    void loginUser();

public:
    void run();

    void addChatMessage(std::string username, std::string message);
};

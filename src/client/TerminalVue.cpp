//
// Created by louis on 10/02/2022.
//

#include "TerminalVue.h"

bool TerminalVue::mouseInCell(int x, int y)
{
    return abs(x - mouse_x) <= 1 && abs(y - mouse_y) <= 2;
}

auto TerminalVue::createCanvas()
{
    return Renderer([&] {
        std::vector<std::vector<int>> canvasGrid {
            {0, 0, 1, 0, -2, 0, 1, 0, 1}};
        auto c = Canvas(100, 100);
        //        for (auto &row : canvasGrid) {
        //            for (auto &cell : row) {
        //                if (cell == 1) {
        //                    c.DrawText("\u25A1", , mouse_y);
        //                }
        //            }
        //        }

                int dy = 5;
                for (int i = 0; i < canvasGrid.size(); i++) {
                    int dx = 5;
                    for (int j = 0; j < canvasGrid[i].size(); j++) {
                        if (canvasGrid[i][j] == 0) {
                            if (mouseInCell(dx, dy) && mousePressed) {
                                c.DrawText(dx, dy, "\u25A0");
                            } else {
                                c.DrawText(dx, dy, "\u25A1");
                            }
                        }
                        else if (canvasGrid[i][j] == -2) {
                            c.DrawPointLine(dx, dy, dx, dy + 2);
                        } else {
                            c.DrawText(dx, dy, "\u25A0", Color::Red);
                        }
                        dx += 5;
                    }
                    dy += 5;
                }

        //        if (mouseInCell(20, 20) && mousePressed) {
        //            c.DrawText(20, 20, "\u25A0", Color::White);
        //        } else {
        //            c.DrawPointLine(0, 0, 20, 0, [](Pixel &p) {
        //                p.character = "-";
        //                p.foreground_color = Color::White;
        //                p.bold = true;
        //            });
        //            c.DrawText(20, 20, "\u25A1");
        //        }
        //        c.DrawText(20, 20, "\u25A1", Color::White);

        //        c.DrawBlock(mouse_x, mouse_y, true, Color::Red);

        return canvas(std::move(c));
    });
}

void TerminalVue::handleButtonClick(int x, int y)
{
    return;
}

auto TerminalVue::createChatInput()
{
    return Input(&message, "Aa");
}

auto TerminalVue::createActionToggle()
{
    actionToggleOption.style_selected = color(Color::Blue);
    actionToggleOption.style_focused = bold | color(Color::White);
    actionToggleOption.style_selected_focused = bold | color(Color::BlueLight);
    return Toggle(&actionToggleEntries, &actionToggleSelected, &actionToggleOption);
}

auto TerminalVue::createMainTab()
{
    return Toggle(&mainTabValues, &mainTabSelect);
}

auto TerminalVue::createBoardRenderer()
{
    auto actionToggle = createActionToggle();
    auto boardCanvas = createCanvas();
    auto boardContainer = Container::Vertical({
        actionToggle,
        boardCanvas,
    });

    return Renderer(boardContainer, [actionToggle, boardCanvas] {
        return vbox({border(boardCanvas->Render() | center), actionToggle->Render() | center});
    });
}

auto TerminalVue::createChatRenderer()
{
    auto chatInput = createChatInput();
    chatMessages.push_back({"Louis", "Hello"});
    return Renderer(chatInput, [&, chatInput] {
        std::vector<Element> chatElements;
        for (auto mess : chatMessages) {
            chatElements.push_back(text(mess[0] + ": " + mess[1]));
        }
        auto chatVbox = vbox(chatElements);
        return vbox({chatVbox | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10), separator(), hbox({text(">"), chatInput->Render()})});
    });
}

auto TerminalVue::createFriendsRenderer()
{
    return Renderer([] { return text("Friends") | center; });
}

auto TerminalVue::createSettingsRenderer()
{
    return Renderer([] { return text("Settings") | center; });
}
auto TerminalVue::createLoginRenderer()
{
    auto usernameInput = Input(&username, "Username");
    auto passwordInput = Input(&password, "Password");
    auto loginButton = Button(
        "Login", [this] {loginUser();}, &buttonOption);
    auto loginFieldsContainer = Container::Vertical({usernameInput, passwordInput, loginButton});
    return Renderer(loginFieldsContainer, [loginFieldsContainer] { return vbox({loginFieldsContainer->Render() | center}); });
}

auto TerminalVue::createRegisterRenderer()
{
    auto usernameInput = Input(&registerUsername, "Username");
    auto passwordInput = Input(&registerPassword, "Password");
    auto repeatPasswordInput = Input(&registerRepeatPassword, "Repeat password");
    auto registerButton = Button(
        "Register", [] {}, &buttonOption);
    auto registerFieldsContainer = Container::Vertical({usernameInput, passwordInput, repeatPasswordInput, registerButton});
    return Renderer(registerFieldsContainer, [registerFieldsContainer] { return vbox({registerFieldsContainer->Render() | center}); });
}

auto TerminalVue::createMainTabContainer()
{
    auto chat = createChatRenderer();
    auto boardTab = createBoardRenderer();
    auto resizeContainer = boardTab;
    resizeContainer = ResizableSplitRight(chat, resizeContainer, &rightSize);
    auto friends = createFriendsRenderer();
    auto settings = createSettingsRenderer();
    auto tabContainer = Container::Tab({resizeContainer, friends, settings}, &mainTabSelect);
    return tabContainer;
}

auto TerminalVue::createMainRenderer()
{
    auto tabToggle = createMainTab();

    auto tabContainer = createMainTabContainer();

    auto tabWithMouse = CatchEvent(tabContainer, [&](Event e) {
        if (e.is_mouse()) {
            mouse_x = (e.mouse().x - 2) * 2;
            mouse_y = (e.mouse().y - 4) * 4;
            if (e.mouse().button == Mouse::Left) {
                if (e.mouse().motion == Mouse::Pressed) {
                    mousePressed = true;
                } else if (e.mouse().motion == Mouse::Released) {
                    mousePressed = false;
                }
            }
            //            mousePressed = e.mouse().motion.Pressed == 1;
        }
        return false;
    });

    auto loginToggle = Toggle(&loginTabValues, &loginTabSelect);
    auto loginContainer = Container::Tab(
        {
            createLoginRenderer(),
            createRegisterRenderer(),
        },
        &loginTabSelect);
    auto mainContainer = Container::Vertical({
        tabWithMouse,
        tabToggle,
        tabContainer,
        loginToggle,
        loginContainer,
    });

    return Renderer(mainContainer, [this, tabContainer, tabToggle, loginToggle, loginContainer] {
        if (!this->isLoggedIn) {
            return vbox({
                loginToggle->Render(),
                separator(),
                loginContainer->Render(),
            }) | border;
        }
        return vbox({tabToggle->Render(), separator(), tabContainer->Render()}) | border;
    });
};

void TerminalVue::loginUser()
{
    if (username.empty() || password.empty()) {
        return;
    }
    // interact with server
    isLoggedIn = true;
}

void TerminalVue::run()
{
    auto mainRenderer = createMainRenderer();
    auto screen = ScreenInteractive::TerminalOutput();
//    loginUser();
    screen.Loop(mainRenderer);
}

void TerminalVue::addChatMessage(std::string username, std::string message)
{
    chatMessages.push_back({username, message});
}
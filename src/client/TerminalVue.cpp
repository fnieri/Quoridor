//
// Created by louis on 10/02/2022.
//

#include "TerminalVue.h"

bool TerminalVue::mouseInCell(int x, int y)
{
    return abs(x - mouse_x) <= 1 && abs(y - mouse_y) <= 3;
}

auto TerminalVue::createCanvas()
{
    return Renderer([&] {
        const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
                  occupiedHorizontalQuoridor = 7;
        auto c = Canvas(100, 100);
        std::vector<Color> playerColors {Color::Red, Color::Green, Color::Blue, Color::Purple};
        std::vector<std::vector<int>> quoridorDirection {{0, 2}, {2, 0}}; // 0 = vertical, 1 = horizontal

        // dx and dy represent the distance between cells

        c.DrawPoint(mouse_x, mouse_y, Color::Yellow);
        //        c.DrawText(10, 50, "Height: , Width: " , Color::White);
        int dy = 5;
        for (int i = 0; i < testCanvasGrid.size(); i++) {
            int dx = 5;
            for (int j = 0; j < testCanvasGrid[i].size(); j++) {
                int gridValue = testCanvasGrid[i][j];
                switch (gridValue) {
                case freeCell:
                    // draw a free cell
                    // TODO: check if click is possible (gotta wait for merge with model and controller)
                    if (mouseInCell(dx, dy) && mousePressed) {
                        // if mouse is pressed on this cell/quoridor
                        c.DrawText(dx, dy, "\u25A0");
                        // TODO: handle mouse click with controller
                    } else {
                        c.DrawText(dx, dy, "\u25A1");
                    }
                    break;

                case emptyQuoridor:
                    if (mouseInCell(dx, dy) && mousePressed) {
                        // TODO sacha: if mouse is pressed on empty quoridor then draw a quoridor and also handle wallOrientation
                    }
                    // don't draw anything otherwise
                    break;

                case occupiedVerticalQuoridor:
                case occupiedHorizontalQuoridor: {
                    std::vector<int> direction = quoridorDirection[gridValue - occupiedVerticalQuoridor];
                    c.DrawBlockLine(dx - direction[0], dy - direction[1], dx + direction[0], dy + direction[1]);
                    break;
                }

                case playerOne:
                case playerTwo:
                case playerThree:
                case playerFour:
                    // draw a player one cell
                    c.DrawText(dx, dy, "\u25A0", playerColors[gridValue - 1]);
                    break;

                default:
                    break;
                }
                dx += 5;
            }
            dy += 5;
        }

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
    auto tabWithMouse = CatchEvent(boardCanvas, [&](Event e) {
        if (e.is_mouse()) {
            mouse_x = (e.mouse().x - 1) * 2;
            mouse_y = (e.mouse().y - 2) * 4;
            if (e.mouse().button == Mouse::Left) {
                if (e.mouse().motion == Mouse::Pressed) {
                    mousePressed = true;
                } else if (e.mouse().motion == Mouse::Released) {
                    mousePressed = false;
                }
            }
        }
        return false;
    });
    auto boardContainer = Container::Vertical({
        tabWithMouse,
        actionToggle,
        boardCanvas,
    });

    return Renderer(boardContainer, [actionToggle, boardCanvas] { return vbox(boardCanvas->Render(), separator(), actionToggle->Render() | center );
});
}

auto TerminalVue::createChatRenderer()
{
    buttonOption.border = false;
    auto chatInput = createChatInput();

    auto chatMenu = Menu(&chatElements, &chatSelected);
    auto sendButton = Button(
        "Send",
        [&] {
            if (!message.empty()) {
                // TODO: actually send message to server
                addChatMessage(username, message);
            }
        },
        buttonOption);
    auto chatContainer = Container::Vertical({chatMenu, chatInput, sendButton});
    return Renderer(chatContainer, [&, chatInput, chatMenu, sendButton] {
        return vbox({chatMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10), separator(),
            hbox({text(">"), chatInput->Render(), sendButton->Render()})});
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
        "Login", [this] { loginUser(); }, &buttonOption);
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

    auto loginToggle = Toggle(&loginTabValues, &loginTabSelect);
    auto loginContainer = Container::Tab(
        {
            createLoginRenderer(),
            createRegisterRenderer(),
        },
        &loginTabSelect);
    auto mainContainer = Container::Vertical({
        //        tabWithMouse,
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
                   })
                | border;
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
    chatElements.push_back(std::string(username + ": " + message));
}
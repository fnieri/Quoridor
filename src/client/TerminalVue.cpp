//
// Created by louis on 10/02/2022.
//

#include "TerminalVue.h"

bool TerminalVue::mouseInCell(int x, int y)
{
    if (actionToggleSelected != 0)
        return false;
    return abs(x - mouse_x) <= 3 && abs(y - mouse_y) <= 3;
}

bool TerminalVue::mouseInQuoridor(int x, int y)
{
    if (actionToggleSelected != 1)
        return false;
    return abs(x - mouse_x) <= (wallOrientation == 0 ? 3 : 15) && abs(y - mouse_y) <= (wallOrientation == 0 ? 15 : 3);
}

bool TerminalVue::isPlayerTurn()
{
    return playerTurn == player;
}

bool TerminalVue::isClickValid(int x, int y)
{
    return mouseInCell(x, y) && mousePressed && isPlayerTurn();
}

bool TerminalVue::isMoveValid(int x, int y)
{
    // check if move is actually valid
    return gameController->isMoveValid(x, y);
}

bool TerminalVue::isWallPlacementValid(int x, int y)
{
    // check if wall placement is actually valid
    return gameController->isWallValid(x, y, wallOrientation);
}

auto TerminalVue::createCanvas()
{
    return Renderer([&] {
        gameController->updateBoardIntMatrix(boardIntMatrix);
        const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
                  occupiedHorizontalQuoridor = 7;
        auto c = Canvas(200, 200);
        std::vector<Color> playerColors {Color::Red, Color::Green, Color::Blue, Color::Purple};
        std::vector<std::vector<int>> quoridorDirection {{0, 4}, {5, 0}}; // 0 = vertical, 1 = horizontal

        c.DrawPoint(mouse_x, mouse_y, Color::Yellow);

        std::string remainingWallsText;
        for (int player = 0; player < remainingWalls.size(); ++player) {
            if (remainingWalls[player] > 0) {
                remainingWallsText += "Player " + std::to_string(player + 1) + ": " + std::to_string(remainingWalls[player]) + ", ";
            }
        }
        c.DrawText(0, 185, "You are player: " + std::to_string(player), Color::Purple);
        c.DrawText(0, 190, "Player's turn: " + std::to_string(playerTurn), playerTurn == player ? Color::Green : Color::Red);
        c.DrawText(0, 195, "Remaining walls: " + remainingWallsText.substr(0, remainingWallsText.size() - 2), Color::Red);

        // dx and dy represent the distance between cells
        int dy = 10;
        for (int i = 0; i < boardIntMatrix.size(); i++) {
            int dx = 10;
            for (int j = 0; j < boardIntMatrix[i].size(); j++) {
                int gridValue = boardIntMatrix[i][j];
                Point pos = Point(j, i);
                switch (gridValue) {
                case freeCell:
                    // draw a free cell
                    if (isClickValid(dx, dy) && isMoveValid(j, i)) {
                        // if mouse is pressed on this cell/quoridor
                        c.DrawText(dx, dy, "\u25A0");
                        handleCellClick(j, i);
                    } else if (mouseInCell(dx, dy) && isPlayerTurn()) {
                        // if mouse is pressed on this cell/quoridor
                        c.DrawText(dx, dy, "\u25A0", isMoveValid(j, i) ? Color::Green : Color::Red);
                        c.DrawText(150, 185, "x: " + std::to_string(j) + ", y: " + std::to_string(i));
                    } else {
                        c.DrawText(dx, dy, "\u25A1");
                    }
                    break;

                case emptyQuoridor:
                    if (mouseInQuoridor(dx, dy) && mousePressed && isWallPlacementValid(j, i)) {
                        std::vector<int> direction = quoridorDirection[wallOrientation];
                        c.DrawBlockLine(dx - direction[0], dy - direction[1], dx + direction[0], dy + direction[1]);
                        handleWallAdd(j, i);
                    } else if (mouseInQuoridor(dx, dy) && isPlayerTurn() && isWallPlacementValid(j, i)) {
                        std::vector<int> direction = quoridorDirection[wallOrientation];
                        c.DrawBlockLine(dx - direction[0], dy - direction[1], dx + direction[0], dy + direction[1], Color::Green);
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
                dx += 10;
            }
            dy += 10;
        }

        return canvas(std::move(c));
    });
}

void TerminalVue::handleCellClick(int x, int y)
{
    // interact with controller
    gameController->movePlayer(x, y);
}

void TerminalVue::handleWallAdd(int x, int y)
{
    // interact with controller
    gameController->placeWall(x, y, wallOrientation);
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

auto TerminalVue::createOrientationToggle()
{
    return Toggle(&orientationToggleEntries, &wallOrientation, &actionToggleOption);
}

auto TerminalVue::createMainTab()
{
    return Toggle(&mainTabValues, &mainTabSelect);
}

auto TerminalVue::createBoardRenderer()
{
    auto actionToggle = createActionToggle();
    auto orientationToggle = createOrientationToggle();
    auto boardCanvas = createCanvas();
    auto tabWithMouse = CatchEvent(boardCanvas, [&](Event e) {
        if (e.is_mouse()) {
            mouse_x = (e.mouse().x - 1) * 2;
            mouse_y = (e.mouse().y - 2) * 4 - 2;
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
        orientationToggle,
        boardCanvas,
    });

    return Renderer(boardContainer, [actionToggle, boardCanvas, orientationToggle] {
        return vbox(boardCanvas->Render(), separator(), hbox(actionToggle->Render(), separator(), orientationToggle->Render()) | center);
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
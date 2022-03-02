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

auto TerminalVue::createSearchInput()
{
    return Input(&searchField, "Search a friend...");
}

auto TerminalVue::createChatFriendInput()
{
    return Input(&messageToFriend, "Type a message...");
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

auto TerminalVue::createMainGameScreen()
{
    std::vector<std::string> entries = {
        "entry 1",
        "entry 2",
        "entry 3",
    };
    int selected = 0;

    MenuOption option;
    auto menu = Menu(&entries, &selected, &option);

    auto mainGameScreenContainer = Container::Vertical({menu});
    return Renderer(mainGameScreenContainer, [menu] { return vbox(text("Pick a game"), menu->Render()); });
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

    auto createGameBtn = Button(
        "Create a Game", [&] { isCreatingGame = true; }, buttonOption);
    auto joinGameBtn = Button(
        "Join Game", [&] { isGameStarted = true; }, buttonOption);
    auto inviteAndCreateGameBtn = Button(
        "Create game",
        [&] {
            int friendSelected = 0;
            for (bool *state : friendsListStates) {
                if (*state) {
                    friendSelected++;
                }
            }
            if (friendSelected == 2 || friendSelected == 4) {
                // TODO: create a game
                isGameStarted = true;
                isCreatingGame = false;
            }
        },
        buttonOption);
    auto cancelGameCreateGamme = Button(
        "Cancel", [&] { isCreatingGame = false; }, buttonOption);
    auto gamePickMenu = Menu(&gameList, &gameSelected);
    Component friendsListContainer = Container::Vertical({});

    for (int i = 0; i < friendsList.size(); ++i) {
        friendsListContainer->Add(Checkbox(&friendsList[i], friendsListStates[i]));
    }

    auto boardContainer = Container::Vertical({tabWithMouse, actionToggle, orientationToggle, boardCanvas, createGameBtn, joinGameBtn, gamePickMenu,
        friendsListContainer, inviteAndCreateGameBtn, cancelGameCreateGamme});

    return Renderer(boardContainer,
        [&, actionToggle, boardCanvas, orientationToggle, createGameBtn, joinGameBtn, gamePickMenu, friendsListContainer, inviteAndCreateGameBtn,
            cancelGameCreateGamme] {
            if (isCreatingGame) {
                return vbox(text("Pick friends to play with"),
                    friendsListContainer->Render() | vscroll_indicator | frame | border | size(HEIGHT, LESS_THAN, 10), inviteAndCreateGameBtn->Render(),
                    separator(), cancelGameCreateGamme->Render());
            }
            if (!isGameStarted) {
                return vbox(text("Welcome to Quoridor!"), separator(), createGameBtn->Render(), separator(), text("Join an existing game"),
                    gamePickMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10) | border, joinGameBtn->Render());
            }

            return vbox(boardCanvas->Render(), separator(), hbox(actionToggle->Render(), separator(), orientationToggle->Render()) | center);
        });
}

auto TerminalVue::createChatRenderer()
{
    buttonOption.border = false;
    passwordOption.password = true;
    auto chatInput = createChatInput();

    auto chatMenu = Menu(&chatElements, &chatSelected);
    auto sendButton = Button(
        "Send",
        [&] {
            if (!message.empty()) {
                addChatMessage(username, message);
            }
        },
        buttonOption);
    auto chatContainer = Container::Vertical({chatMenu, chatInput, sendButton});
    return Renderer(chatContainer, [&, chatInput, chatMenu, sendButton] {
        if (isGameStarted) {
            return vbox({chatMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10), separator(),
                hbox({text(">"), chatInput->Render(), sendButton->Render()})});
        }
        return vbox();
    });
}

auto TerminalVue::createFriendsListRenderer()
{
    auto friendList = Window("Friends List", Menu(&friendsList, &friend_selected));
    auto friendChat = Menu(&chatEntry, &chat_message_selected);
    auto chatToFriendInput = createChatFriendInput();
    auto sendChatToFriendButton = Button(
        "Send",
        [&] {
            if (!messageToFriend.empty()) {
                addChatFriendMessage(username, messageToFriend);
            }
        },
        buttonOption);

    auto friendsListContainer = Container::Vertical({
        friendList,
        friendChat,
        chatToFriendInput,
        sendChatToFriendButton,
    });

    return Renderer(friendsListContainer, [&, friendList, friendChat, chatToFriendInput, sendChatToFriendButton] {
        chatEntry = chatEntries[friend_selected];
        return hbox({
            vbox({
                friendList->Render() | frame | size(HEIGHT, LESS_THAN, 15),
            }) | xflex |yflex,
            separator(),
            vbox({
                text("Chat") | center,
                separator(),
                friendChat->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 15),
                text(L"") | focus,
                separator(),
                hbox({text(">"), chatToFriendInput->Render(), sendChatToFriendButton->Render()}),
            }) | yframe | yflex | xflex,
        });
    });
}

auto TerminalVue::createFriendUtilitariesRenderer()
{
    auto searchInput = createSearchInput();
    auto addButton = Button(
        "Add",
        [&] {
            if (!searchField.empty()) {
                addFriend(searchField);
            }
        },
        buttonOption);

    auto delButton = Button("Delete someone", [&] { depth = 1; });

    auto notifBox = Window("Notifications", Menu(&notifications, &notif_selected));
    auto utilitariesContainer = Container::Vertical({
        searchInput,
        addButton,
        delButton,
        notifBox,
    });

    return Renderer(utilitariesContainer, [&, searchInput, addButton, delButton, notifBox] {
        return vbox({
            hbox({text(">"), searchInput->Render(), addButton->Render()}),
            separator(),
            delButton->Render() | center,
            notifBox->Render() | yflex  | frame | size(HEIGHT, LESS_THAN, 9),
        });
    });
}

auto TerminalVue::createLeaderBoardRenderer()
{  

    for(int i = 0; i < leaders.size(); i++){
        listLeadersWithElo.push_back(std::to_string(i+1) + ". " + leaders[i] + " (" + std::to_string(elos[i])+")");
    }
    
    auto listLeaders = Menu(&listLeadersWithElo, &leader_selected);
    auto leaderBoardContainer = Container::Vertical({
        listLeaders,
    });

    return Renderer(leaderBoardContainer, [&, listLeaders] { 
        return vbox({
            // text("LeaderBoard") | center,
            color(Color::YellowLight,text("Best players of the moment")),
            separator(),
            listLeaders->Render(),
        }) | center;
    });
}

auto TerminalVue::createLoginRenderer()
{
    auto usernameInput = Input(&username, "Username");
    auto passwordInput = Input(&password, "Password", passwordOption);
    auto loginButton = Button(
        "Login", [this] { loginUser(); }, &buttonOption);
    auto loginFieldsContainer = Container::Vertical({usernameInput, passwordInput, loginButton});
    return Renderer(loginFieldsContainer, [loginFieldsContainer] { return vbox({loginFieldsContainer->Render() | center}); });
}

auto TerminalVue::createRegisterRenderer()
{
    auto usernameInput = Input(&registerUsername, "Username");
    auto passwordInput = Input(&registerPassword, "Password", passwordOption);
    auto repeatPasswordInput = Input(&registerRepeatPassword, "Repeat password", passwordOption);
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
    auto friendsList = createFriendsListRenderer();
    auto friendUtilitaries = createFriendUtilitariesRenderer();
    auto resizeFriendTab = friendsList;
    resizeFriendTab = ResizableSplitRight(friendUtilitaries, resizeFriendTab, &rightSizeFriends);
    auto LeaderBoard = createLeaderBoardRenderer();
    auto tabContainer = Container::Tab({resizeContainer, resizeFriendTab, LeaderBoard}, &mainTabSelect);
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

auto TerminalVue::createFinalContainer()
{
    auto mainContent = createMainRenderer();
    auto deleteSomeoneMenu = Menu(&friendsList, &friend_selected);
    auto quitButton = Button("Quit", [&] { depth = 0; });
    auto wantToDelete = Button("Delete", [&] { depth = 2; }); //color(Color::Red, text("Deletion Menu"))

    auto dialogBox = Container::Vertical({
        deleteSomeoneMenu,
        quitButton,
        wantToDelete
    });

    auto deleteConfirmation = Container::Vertical({
        Button("Confirm",
            [&] {
                deleteFriend();
                depth = 0;
            }), // Close all dialogs
        Button("Cancel", [&] { depth = 1; }), // returns to the selection of a person to delete from friendsList
    });

    auto mainContainer = Container::Vertical({
        mainContent,
    });
    
    auto finalTab = Container::Tab(
        {
            mainContainer,
            dialogBox,
            deleteConfirmation,
        },
        &depth);

    return Renderer(finalTab, [&, dialogBox, deleteConfirmation, mainContainer] {

        if (depth == 1) {
            return vbox({
                       color(Color::Red, text("Deletion Menu")),
                       separator(),
                       vbox(dialogBox->Render()),
                   })
                | border | center;
        }

        if (depth == 2) {
            return vbox({
                       color(Color::Red, text("Are you sure to delete " + friendsList[friend_selected])),
                       separator(),
                       vbox(deleteConfirmation->Render()),
                   })
                | border | center;
        }
        return mainContainer->Render();
    });
}

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
    auto mainRenderer = createFinalContainer();
    auto screen = ScreenInteractive::TerminalOutput();
    //    loginUser();
    screen.Loop(mainRenderer);
}

void TerminalVue::addChatMessage(std::string username, std::string messagetosend)
{
    chatElements.push_back(std::string(username + ": " + messagetosend));
    message.clear();
}

void TerminalVue::addChatFriendMessage(std::string username, std::string message)
{
    chatEntries[friend_selected].push_back(std::string(username + ": " + message));
    messageToFriend.clear();
}

void TerminalVue::addFriend(std::string username)
{
    friendsList.push_back(username);
    chatEntries.push_back(std::vector<std::string> {""});
    notifications.push_back("Added: " + username);
    handleFriendAdd(username);
    searchField.clear();
}

void TerminalVue::deleteFriend()
{
    notifications.push_back("Deleted: " + friendsList[friend_selected]);
    friendsList.erase(friendsList.begin() + friend_selected);
    chatEntries.erase(chatEntries.begin() + friend_selected);
    handleFriendDelete(friendsList[friend_selected]);
}

void TerminalVue::handleFriendDelete(const std::string &friendUsername)
{

}

void TerminalVue::handleFriendAdd(const std::string &friendUsername)
{
    
}
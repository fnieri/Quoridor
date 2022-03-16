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
    //     return gameController->isMoveValid(x, y);
}

bool TerminalVue::isWallPlacementValid(int x, int y)
{
    // check if wall placement is actually valid
    //     return gameController->isWallValid(x, y, wallOrientation);
}

auto TerminalVue::createCanvas()
{
    return Renderer([&] {
        //        GameModel *gameModel = mainModel.getCurrentGame();
        //        gameController->updateBoardIntMatrix(boardIntMatrix);
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
        // TODO get game data
        c.DrawText(0, 185, "You are player: " + std::to_string(player), Color::Purple);
        c.DrawText(0, 190, "Player's turn: " + std::to_string(playerTurn), playerTurn == player ? Color::Green : Color::Red);
        c.DrawText(0, 195, "Remaining walls: " + remainingWallsText.substr(0, remainingWallsText.size() - 2), Color::Red);

        // dx and dy represent the distance between cells
        int dy = 10;
        for (int i = 0; i < boardIntMatrix.size(); i++) {
            int dx = 10;
            for (int j = 0; j < boardIntMatrix[i].size(); j++) {
                int gridValue = boardIntMatrix[i][j];
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
    //    gameController->movePlayer(Point{x, y});
}

void TerminalVue::handleWallAdd(int x, int y)
{
    // interact with controller
    //    gameController->placeWall(Point{x, y}, wallOrientation);
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

auto TerminalVue::createChatRenderer()
{
    auto chatInput = createChatInput();

    auto chatMenu = Menu(&chatElements, &chatSelected);
    auto sendButton = Button(
        "Send",
        [&] {
            // TODO send message
            if (!message.empty()) {
                addChatMessage(username, message);
                sendMessageGame(message, currentGameId);
            }
        },
        &buttonOption);
    auto chatContainer = Container::Vertical({chatMenu, chatInput, sendButton});
    return Renderer(chatContainer, [&, chatInput, chatMenu, sendButton] {
        return vbox({chatMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10), separator(),
            hbox({text(">"), chatInput->Render(), sendButton->Render()})});
    });
}

auto TerminalVue::createBoardRenderer()
{
    auto actionToggle = createActionToggle();
    auto orientationToggle = createOrientationToggle();
    auto pauseGameButton = Button(
        "Pause",
        [&] {
            // TODO pause game
            homeTabIndex = 0;
        },
        &buttonOption);
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
        "Create a Game", [&] { homeTabIndex = 1; }, &buttonOption);
    auto joinGameBtn = Button(
        "Join Game",
        [&] { // TODO join game
            homeTabIndex = 2;
            rightSize = 40;
        },
        &buttonOption);
    auto inviteAndCreateGameBtn = Button(
        "Create game", [&] { userCreateGame(); }, &buttonOption);
    auto cancelGameCreateGamme = Button(
        "Cancel", [&] { homeTabIndex = 0; }, &buttonOption);
    auto gamePickMenu = Menu(&gameList, &gameSelected);

    Component playWithContainer = Container::Vertical({});
    for (int i = 0; i < friendsList.size(); ++i) {
        friendsListStates.push_back(CheckboxState {false});
    }
    for (int i = 0; i < friendsList.size(); ++i) {
        //        friendsListStates.push_back(CheckboxState {false});
        playWithContainer->Add(Checkbox(&friendsList[i], &(friendsListStates[i].checked)));
    }

    auto boardContainer = Container::Vertical({tabWithMouse, actionToggle, orientationToggle, boardCanvas, createGameBtn, joinGameBtn, gamePickMenu,
        inviteAndCreateGameBtn, cancelGameCreateGamme, playWithContainer});

    auto creatingGameContainer = Container::Vertical({
        playWithContainer,
        inviteAndCreateGameBtn,
        cancelGameCreateGamme,
    });
    auto creatingGameRender = Renderer(creatingGameContainer, [playWithContainer, inviteAndCreateGameBtn, cancelGameCreateGamme] {
        return vbox(
            {text("Create a game with friends"), separator(), playWithContainer->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10) | border,
                inviteAndCreateGameBtn->Render(), separator(), cancelGameCreateGamme->Render()});
    });

    auto homeScreenContainer = Container::Vertical({
        createGameBtn,
        joinGameBtn,
        gamePickMenu,
    });
    auto homeScreenRender = Renderer(homeScreenContainer, [createGameBtn, joinGameBtn, gamePickMenu] {
        return vbox({text("Welcome to Quoridor ! Join or create game"), separator(),
            gamePickMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10) | border, joinGameBtn->Render(), separator(),
            createGameBtn->Render()});
    });

    auto boardGameContainer = Container::Vertical({boardCanvas, actionToggle, orientationToggle, pauseGameButton, tabWithMouse});
    auto boardGameRender = Renderer(boardGameContainer, [boardCanvas, actionToggle, orientationToggle, pauseGameButton] {
        return vbox({boardCanvas->Render(), separator(),
            hbox(actionToggle->Render(), separator(), orientationToggle->Render(), separator(), pauseGameButton->Render()) | center});
    });

    auto gameChat = createChatRenderer();
    auto resizeContainer = boardGameRender;
    resizeContainer = ResizableSplitRight(gameChat, resizeContainer, &rightSize);

    auto homeTab = Container::Tab({homeScreenRender, creatingGameRender, resizeContainer}, &homeTabIndex);

    return Renderer(homeTab, [homeTab] { return homeTab->Render(); });
}

auto TerminalVue::createFriendsListRenderer()
{
    auto friendList = Window("Friends List", Menu(&friendsList, &friend_selected));
    auto friendChat = Menu(&chatEntry, &chat_message_selected);
    auto chatToFriendInput = createChatFriendInput();
    auto sendChatToFriendButton = Button(
        "Send",
        [&] {
            // TODO send friend chat
            if (!messageToFriend.empty()) {
                addChatFriendMessage(username, messageToFriend);
                sendUserMessage(messageToFriend, friendsList[friend_selected]);
            }
        },
        &buttonOption);

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
            }) | xflex,
            separator(),
            vbox({
                text("Chat") | center,
                separator(),
                friendChat->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 15),
                separator(),
                hbox({text(">"), chatToFriendInput->Render(), sendChatToFriendButton->Render()}),
            }) | yframe
                | yflex | xflex,
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
        &buttonOption);

    auto notifBox = Window("Notifications", Menu(&notifications, &notif_selected));
    auto utilitariesContainer = Container::Vertical({
        searchInput,
        addButton,
        notifBox,
    });

    return Renderer(utilitariesContainer, [&, searchInput, addButton, notifBox] {
        return vbox({
            hbox({text(">"), searchInput->Render(), addButton->Render()}),
            separator(),

            notifBox->Render() | yflex,
        });
    });
}

auto TerminalVue::createLeaderBoardRenderer()
{
    auto listLeaders = Menu(&listLeadersWithElo, &leader_selected);
    auto leaderBoardContainer = Container::Vertical({
        listLeaders,
    });

    return Renderer(leaderBoardContainer, [&, listLeaders] {
    auto userElo = mainModel->getELO();
        auto leaderboard = mainModel->getLeaderboard();
        listLeadersWithElo.clear();
        if (!leaderboard->empty()) {
            for (auto &leader : *leaderboard) {
                listLeadersWithElo.push_back(leader.first + " : " + std::to_string(leader.second));
            }
        }
        return vbox({text("LeaderBoard") | center, color(Color::YellowLight, text("Best players of the moment")), separator(), listLeaders->Render(),
                   separator(), text("Your Elo : " + std::to_string(*userElo))})
            | center;
    });
}

auto TerminalVue::createLoginRenderer()
{
    auto usernameInput = Input(&username, "Username");
    auto passwordInput = Input(&password, "Password", passwordOption);
    auto loginButton = Button(
        "Login", [this] { loginUser(); }, &buttonOption);
    auto loginFieldsContainer = Container::Vertical({usernameInput, passwordInput, loginButton});
    return Renderer(loginFieldsContainer, [&, loginFieldsContainer] {
        return vbox({loginFieldsContainer->Render() | center, color(Color::Red, text(errorLoginMessage))});
    });
}

auto TerminalVue::createRegisterRenderer()
{
    auto usernameInput = Input(&registerUsername, "Username");
    auto passwordInput = Input(&registerPassword, "Password", passwordOption);
    auto repeatPasswordInput = Input(&registerRepeatPassword, "Repeat password", passwordOption);
    auto registerButton = Button(
        "Register", [&] { registerUser(); }, &buttonOption);
    auto registerFieldsContainer = Container::Vertical({usernameInput, passwordInput, repeatPasswordInput, registerButton});
    return Renderer(registerFieldsContainer, [&, registerFieldsContainer] {
        return vbox({registerFieldsContainer->Render() | center, color(Color::Red, text(registerMessage))});
    });
}

auto TerminalVue::createFriendsRenderer()
{
    auto searchInput = Input(&searchField, "Add friend");
    auto addButton = Button(
        "Add", [&] { addFriend(searchField); }, &buttonOption);
    auto friendsMenu = Menu(mainModel->getFriendList(), &friend_selected);
    auto friendsChat = Menu(&chatEntry, &chat_message_selected);
    auto friendMessageInput = Input(&messageToFriend, "Aa");
    auto sendFriendMessageButton = Button(
        "Send",
        [&] {
            sendUserMessage(messageToFriend, friendsList[friend_selected]); // fix this
        },
        &buttonOption);
    auto removeFriendsButton = Button("Remove", [&] {
        // TODO delete friend
    });

    auto notificationContainer = Container::Vertical({});

    auto friendRequestsReceived = mainModel->getFriendRequestsReceived();

    for (auto &friendRequest : *friendRequestsReceived) {
        auto friendsRequestAcceptBtn = Button("Accept", [&] {
            // TODO accept friend request
        });

        auto friendsRequestDeclineBtn = Button("Decline", [&] {
            // TODO decline friend request
        });
        auto requestsBtnContainer = Container::Vertical({friendsRequestAcceptBtn, friendsRequestDeclineBtn});
        notificationContainer->Add(Renderer(requestsBtnContainer, [friendsRequestAcceptBtn, friendsRequestDeclineBtn, friendRequest] {
            return hbox({text(friendRequest + " sent you a friend request"), friendsRequestAcceptBtn->Render(), friendsRequestDeclineBtn->Render()});
        }));
    }

    auto friendContainer = Container::Vertical(
        {searchInput, addButton, friendsMenu, friendsChat, friendMessageInput, sendFriendMessageButton, removeFriendsButton, notificationContainer});

    return Renderer(friendContainer,
        [&, searchInput, addButton, friendsMenu, friendsChat, friendMessageInput, sendFriendMessageButton, removeFriendsButton, notificationContainer] {
            //            chatEntry = chatEntries[friend_selected]; // update chat entry with server
            updateChatEntries();
            return vbox({
                hbox({friendsMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10), separator(),
                    vbox({text("Chat                 "), separator(), friendsChat->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10),
                        separator(), hbox({friendMessageInput->Render(), sendFriendMessageButton->Render()})}),
                    separator(), vbox({text("Friend actions"), separator(), removeFriendsButton->Render(), separator(), notificationContainer->Render()})}),
                separator(),
                hbox({searchInput->Render(), addButton->Render()}),
            });
        });
}

auto TerminalVue::createMainTabContainer()
{
    auto board = createBoardRenderer();
    auto friendRenderer = createFriendsRenderer();
    auto LeaderBoard = createLeaderBoardRenderer();
    auto tabContainer = Container::Tab({board, friendRenderer, LeaderBoard}, &mainTabSelect);
    return tabContainer;
}

auto TerminalVue::createMainRenderer()
{
    auto tabToggle = createMainTab();

    auto tabContainer = createMainTabContainer();

    auto loginToggle = Toggle(&loginTabValues, &loginTabSelect);
    auto loginRenderer = createLoginRenderer();
    auto registerRender = createRegisterRenderer();
    auto loginRegisterContainer = Container::Tab(
        {
            loginRenderer,
            registerRender,
        },
        &loginTabSelect);

    auto loginRegisterToggleContainer = Container::Vertical({loginToggle, loginRegisterContainer});

    auto loginRender = Renderer(loginRegisterToggleContainer, [loginRegisterContainer, loginToggle] {
        return vbox({
            loginToggle->Render(),
            separator(),
            loginRegisterContainer->Render(),
        });
    });

    auto mainContainer = Container::Vertical({
        tabToggle,
        tabContainer,
    });
    auto mainRender = Renderer(mainContainer, [&, tabToggle, tabContainer] {
        return vbox({
            tabToggle->Render(),
            separator(),
            tabContainer->Render(),
        });
    });

    auto mainContainerTab = Container::Tab({loginRender, mainRender}, &mainPageIndex);

    return Renderer(mainContainerTab, [mainContainerTab] { return mainContainerTab->Render() | border; });
};

auto TerminalVue::createFinalContainer()
{
    auto mainContent = createMainRenderer();

    return Renderer(mainContent, [mainContent] { return mainContent->Render(); });
}

void TerminalVue::loginUser()
{
    if (username.empty() || password.empty()) {
        errorLoginMessage = "Username and password cannot be empty";
        return;
    }
    // TODO interact with server
    // isLoggedIn = gameController->logIn(username, password);
    if (!serverController->login(username, password)) {
        errorLoginMessage = "Wrong username or password";
    } else {
        serverController->fetchData();
        errorLoginMessage = "";
        mainPageIndex = 1;
    }
    system("clear");
}

void TerminalVue::run()
{
    //    mainModel = mainController.getMainModel();
    //    mainModel->setFriendList({"test1", "test2", "test3", "test4", "test5", "test6", "test7", "test8", "test9", "test10"});
    //    mainModel->addFriendMessage("test1", "test message");
    //    mainModel->addFriendRequestReceived("aTestFriend");
    buttonOption.border = false;
    passwordOption.password = true;
    auto mainRenderer = createFinalContainer();
    auto screen = ScreenInteractive::TerminalOutput();
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
    if (!searchField.empty()) {
        friendsList.push_back(username);
        chatEntries.push_back(std::vector<std::string> {""});
        notifications.push_back("Added: " + username);
        handleFriendAdd(username);
        searchField.clear();
    }
}

void TerminalVue::deleteFriend()
{
    notifications.push_back("Deleted: " + friendsList[friend_selected]);
    chatEntries.erase(chatEntries.begin() + friend_selected);
    handleFriendDelete(friendsList[friend_selected]);
    friendsList.erase(friendsList.begin() + friend_selected);
    friend_selected -= 1;
}

void TerminalVue::registerUser()
{
    if (registerPassword == registerRepeatPassword && !registerUsername.empty() && !registerPassword.empty()) {
        if (serverController->registerUser(registerUsername, registerPassword)) {
            username = registerUsername;
            registerMessage = "Successfully registered. You can now log in.";
        } else {
            registerMessage = "Error creating account. Username probably already exists";
        }
        system("clear");
    } else {
        registerMessage = "Passwords don't match or username is empty";
    }
}

void TerminalVue::handleFriendDelete(const std::string &friendUsername)
{
    // gameController->deleteFriend(friendUsername);
}

void TerminalVue::handleFriendAdd(const std::string &friendUsername)
{
    // gameController->sendFriendRequest(friendUsername, username);
}

// void TerminalVue::handleFriendRequestAccept()
// {

// }

void TerminalVue::userCreateGame()
{
    //    int friendSelected = 0;
    //    for (bool &state : friendsListStates) {
    //        if (state) {
    //            friendSelected++;
    //        }
    //    }
    //    if (friendSelected == 2 || friendSelected == 4) {
    //        // TODO: create a game
    //        homeTabIndex = 2;
    //    }
}

void TerminalVue::loadFriends()
{
    // json friendsListJson = gameController->getFriendsList()[0];
    // friendsList.clear();
    // for (auto &friendL : friendsListJson) {
    //     friendsList.push_back(friendL["username"]);
    // }
}

void TerminalVue::loadFriendChats()
{
    // json friendChatsJson = gameController->getFriendChats()[0];
    // chatEntries.clear();
    // for (auto &friendChat : friendChatsJson) {
    //     chatEntries.push_back(std::vector<std::string> {});
    //     for (auto &m : friendChat["messages"]) {
    //         chatEntries.back().push_back(m["username"] + ": " + m["message"]);
    //     }
    // }
}

void TerminalVue::loadLeaderboard()
{
}

void TerminalVue::loadMessages()
{
}

void TerminalVue::sendMessageGame(std::string mess, int gameId)
{
}

void TerminalVue::sendUserMessage(const std::string& mess, const std::string& receiver)
{
    serverController->sendFriendMessage(*mainModel->getUsername(), receiver, mess);
    //
    //    gameController->sendUserMessage(mess, receiver);
}
void TerminalVue::updateChatEntries()
{
    auto friendList = mainModel->getFriendList();
    auto friendChatEntries = mainModel->getChatWith((*friendList)[friend_selected]);
    chatEntry.clear();
    for (auto &chat : *friendChatEntries) {
        std::string mess = chat.sender + ": " + chat.sentMessage;
        chatEntry.push_back(mess);
    }
}

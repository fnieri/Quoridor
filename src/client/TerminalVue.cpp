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
    return gameModel->isMoveValid(Point(x, y));
}

bool TerminalVue::isWallPlacementValid(int x, int y)
{
    // check if wall placement is actually valid
    return gameModel->isWallValid(Point(x, y), wallOrientation == 0 ? WallOrientation::Horizontal : WallOrientation::Vertical);
}

auto TerminalVue::createCanvas()
{
    return Renderer([&] {
        //        auto gModel = *mainModel->getCurrentGame()
        if (gameModel) {
            gameModel->updateBoardIntMatrix(boardIntMatrix);
            const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
                      occupiedHorizontalQuoridor = 7;
            auto c = Canvas(200, 200);
            std::vector<Color> playerColors {Color::Red, Color::Green, Color::Blue, Color::Purple};
            std::vector<std::vector<int>> quoridorDirection {{0, 4}, {5, 0}}; // 0 = vertical, 1 = horizontal

            c.DrawPoint(mouse_x, mouse_y, Color::Yellow);

            // TODO get game data
            std::string remainingWallsText;
            for (int p = 0; p < remainingWalls.size(); ++p) {
                if (remainingWalls[p] > 0) {
                    remainingWallsText += "Player " + std::to_string(p + 1) + ": " + std::to_string(remainingWalls[p]) + ", ";
                }
            }
            c.DrawText(0, 185, "You are player: " + std::to_string(player), Color::Purple);
            c.DrawText(0, 190, "Player's turn: " + std::to_string(*gameModel->getCurrentPlayer()), playerTurn == player ? Color::Green : Color::Red);
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
        }

        gameModel = mainModel->getCurrentGame();
        return text("Loading...");
    });
}

void TerminalVue::handleCellClick(int x, int y)
{
    auto playerAction = gameModel->getPlayerAction(Point {x, y});
    gameModel->processAction(playerAction.serialized().dump());
}

void TerminalVue::handleWallAdd(int x, int y)
{
    auto wallAction = gameModel->getWallAction(Point {x, y}, wallOrientation ? WallOrientation::Horizontal : WallOrientation::Vertical);
    gameModel->processAction(wallAction.serialized().dump());
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
    auto chatInput = Input(&message, "Aa");

    auto chatMenu = Menu(&chatElements, &chatSelected);
    auto sendButton = Button(
        "Send",
        [&] {
            // TODO send message
            if (!message.empty()) {
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

auto TerminalVue::createBoardGameRenderer()
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
    auto boardGameContainer = Container::Vertical({boardCanvas, actionToggle, orientationToggle, pauseGameButton, tabWithMouse});
    return Renderer(boardGameContainer, [boardCanvas, actionToggle, orientationToggle, pauseGameButton, tabWithMouse] {
        return vbox({boardCanvas->Render(), separator(),
            hbox(actionToggle->Render(), separator(), orientationToggle->Render(), separator(), pauseGameButton->Render()) | center});
    });
}

auto TerminalVue::createBoardRenderer()
{
    //    auto actionToggle = createActionToggle();
    //    auto orientationToggle = createOrientationToggle();
    //    auto pauseGameButton = Button(
    //        "Pause",
    //        [&] {
    //            // TODO pause game
    //            homeTabIndex = 0;
    //        },
    //        &buttonOption);
    //    auto boardCanvas = createCanvas();
    //    auto tabWithMouse = CatchEvent(boardCanvas, [&](Event e) {
    //        if (e.is_mouse()) {
    //            mouse_x = (e.mouse().x - 1) * 2;
    //            mouse_y = (e.mouse().y - 2) * 4 - 2;
    //            if (e.mouse().button == Mouse::Left) {
    //                if (e.mouse().motion == Mouse::Pressed) {
    //                    mousePressed = true;
    //                } else if (e.mouse().motion == Mouse::Released) {
    //                    mousePressed = false;
    //                }
    //            }
    //        }
    //        return false;
    //    });

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

    auto boardContainer = Container::Vertical({createGameBtn, joinGameBtn, gamePickMenu, inviteAndCreateGameBtn, cancelGameCreateGamme, playWithContainer});

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

    //    auto boardGameContainer = Container::Vertical({boardCanvas, actionToggle, orientationToggle, pauseGameButton, tabWithMouse});
    //    auto boardGameRender = Renderer(boardGameContainer, [boardCanvas, actionToggle, orientationToggle, pauseGameButton] {
    //        return vbox({boardCanvas->Render(), separator(),
    //            hbox(actionToggle->Render(), separator(), orientationToggle->Render(), separator(), pauseGameButton->Render()) | center});
    //    });
    auto boardGameRender = createBoardGameRenderer();

    auto gameChat = createChatRenderer();
    auto resizeContainer = boardGameRender;
    resizeContainer = ResizableSplitRight(gameChat, resizeContainer, &rightSize);

    auto homeTab = Container::Tab({homeScreenRender, creatingGameRender, resizeContainer}, &homeTabIndex);

    return Renderer(homeTab, [homeTab] { return homeTab->Render(); });
}

auto TerminalVue::createLeaderBoardRenderer()
{
    auto listLeaders = Menu(&listLeadersWithElo, &leader_selected);
    auto refreshBtn = Button(
        "Refresh", [&] { serverController->fetchLeaderboard(); }, &buttonOption);
    auto leaderBoardContainer = Container::Vertical({listLeaders, refreshBtn});

    return Renderer(leaderBoardContainer, [&, listLeaders, refreshBtn] {
        auto userElo = mainModel->getELO();
        auto leaderboard = mainModel->getLeaderboard();
        listLeadersWithElo.clear();
        if (!leaderboard->empty()) {
            for (auto &leader : *leaderboard) {
                listLeadersWithElo.push_back(leader.first + " : " + std::to_string((int)leader.second));
            }
        }
        return vbox({text("LeaderBoard") | center, color(Color::YellowLight, text("Best players of the moment")), separator(), listLeaders->Render(),
                   separator(), text("Your Elo : " + std::to_string((int)*userElo)), separator(), refreshBtn->Render()})
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

auto TerminalVue::createTrainingRenderer()
{
    auto boardRender = createBoardGameRenderer();

    auto trainingContainer = Container::Vertical({boardRender});
    return Renderer(trainingContainer, [&, boardRender] { return vbox({text("Training"), boardRender->Render()}); });
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
        "Add", [&] { sendFriendRequest(); }, &buttonOption);
    auto friendsMenu = Menu(mainModel->getFriendList(), &friend_selected);
    auto friendsChat = Menu(&chatEntry, &chat_message_selected);
    auto friendMessageInput = Input(&messageToFriend, "Aa");
    auto sendFriendMessageButton = Button(
        "Send", [&] { sendUserMessage(); }, &buttonOption);
    auto removeFriendsButton = Button("Remove", [&] { friendDeleteIndex = 1; });
    auto confirmFriendDeleteButton = Button("Confirm", [&] { deleteFriend(); });
    auto cancelFriendDeleteButton = Button("Cancel", [&] { friendDeleteIndex = 0; });

    auto confirmDeleteFriendContainer = Container::Horizontal({confirmFriendDeleteButton, cancelFriendDeleteButton});

    auto deleteFriendTabContainer = Container::Tab({removeFriendsButton, confirmDeleteFriendContainer}, &friendDeleteIndex);

    auto friendsRequestAcceptBtn = Button("Accept", [&] { acceptFriendRequest(); });
    auto friendsRequestDeclineBtn = Button("Decline", [&] { declineFriendRequest(); });
    auto friendsRequestButtonsContainer = Container::Horizontal({friendsRequestAcceptBtn, friendsRequestDeclineBtn});
    auto friendRequestButtonsTabContainer
        = Container::Tab({friendsRequestButtonsContainer, Renderer([] { return text("No friend request received"); })}, &friendRequestIndex);

    auto friendRequestsReceived = mainModel->getFriendRequestsReceived();

    auto notificationMenu = Menu(friendRequestsReceived, &friendRequestSelected);

    auto friendChatContainer = Container::Vertical({friendsChat, friendMessageInput, sendFriendMessageButton});
    auto friendChatTabContainer
        = Container::Tab({Renderer(friendChatContainer,
                              [friendsChat, friendMessageInput, sendFriendMessageButton] {
                                  return vbox({window(text("Chat"), friendsChat->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10) | xflex),
                                      hbox({friendMessageInput->Render(), sendFriendMessageButton->Render()})});
                              }),
                             Renderer([] { return vbox(); })},
            &friendChatIndex);

    auto friendActionTabContainer = Container::Tab({Renderer(deleteFriendTabContainer,
                                                        [deleteFriendTabContainer] {
                                                            return vbox({window(text("Friend actions"), deleteFriendTabContainer->Render()), separator()});
                                                        }),
                                                       Renderer([] { return vbox(); })},
        &friendChatIndex);

    auto friendContainer = Container::Vertical(
        {searchInput, addButton, friendsMenu, friendChatTabContainer, friendActionTabContainer, notificationMenu, friendRequestButtonsTabContainer});

    return Renderer(friendContainer,
        [&, searchInput, addButton, friendsMenu, friendChatTabContainer, friendActionTabContainer, notificationMenu, friendRequestButtonsTabContainer] {
            updateChatEntries();
            updateFriendTabsIndex();

            return vbox({
                hbox({friendsMenu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10), separator(), friendChatTabContainer->Render() | xflex,
                    separator(),
                    vbox({friendActionTabContainer->Render(),
                        window(
                            text("Friend request received"), vbox({notificationMenu->Render(), separator(), friendRequestButtonsTabContainer->Render()}))})}),
                separator(),
                hbox({searchInput->Render(), addButton->Render()}),
            });
        });
}

void TerminalVue::updateFriendTabsIndex()
{
    if (mainModel->getHasFriends())
        friendChatIndex = 0;
    else
        friendChatIndex = 1;

    if (mainModel->getFriendRequestsReceived()->empty())
        friendRequestIndex = 1;
    else
        friendRequestIndex = 0;
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
    auto tabToggle = Toggle(&mainTabValues, &mainTabSelect);
    auto tabContainer = createMainTabContainer();

    auto exitButton = Button(
        "Exit",
        [&] {
            auto f {screen->ExitLoopClosure()};
            f();
        },
        &buttonOption);
    auto loginExit = Button(
        "Exit",
        [&] {
            auto f {screen->ExitLoopClosure()};
            f();
        },
        &buttonOption);

    auto loginToggle = Toggle(&loginTabValues, &loginTabSelect);
    auto loginRenderer = createLoginRenderer();
    auto registerRender = createRegisterRenderer();
    auto trainingRender = createTrainingRenderer();
    auto loginRegisterContainer = Container::Tab(
        {
            loginRenderer,
            registerRender,
            trainingRender,
        },
        &loginTabSelect);

    auto loginRegisterToggleContainer = Container::Vertical({loginToggle, loginRegisterContainer, loginExit});

    auto loginRender = Renderer(loginRegisterToggleContainer, [&, loginRegisterContainer, loginToggle, loginExit] {
        if (loginTabSelect == 2 && !mainModel->getCurrentGame()) {
            // create ai game
            mainModel->createAiGame();
        }
        return vbox({
            hbox({loginToggle->Render(), filler(), loginExit->Render()}),
            separator(),
            loginRegisterContainer->Render(),
        });
    });

    auto mainContainer = Container::Vertical({
        tabToggle,
        tabContainer,
        exitButton,
    });
    auto mainRender = Renderer(mainContainer, [&, tabToggle, tabContainer, exitButton] {
        updateNotifications();
        return vbox({
            hbox({tabToggle->Render(), exitButton->Render()}),
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

    if (!serverController->login(username, password)) {
        errorLoginMessage = "Wrong username or password";
    } else {
        serverController->fetchData();
        errorLoginMessage = "";
        mainPageIndex = 1;
    }
    system("clear");
}

void TerminalVue::sendFriendRequest()
{
    if (!searchField.empty()) {
        serverController->sendFriendRequest(*mainModel->getUsername(), searchField);
        searchField.clear();
    }
}

void TerminalVue::deleteFriend()
{
    auto friendList = mainModel->getFriendList();
    auto friendToDelete = (*friendList)[friend_selected];
    serverController->removeFriend(*mainModel->getUsername(), friendToDelete);
    serverController->fetchFriends();
    friendDeleteIndex = 0;
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

void TerminalVue::sendMessageGame(const std::string &mess, int gameId)
{
}

void TerminalVue::sendUserMessage()
{
    auto friendList = mainModel->getFriendList();
    auto receiver = (*friendList)[friend_selected];
    serverController->sendFriendMessage(*mainModel->getUsername(), receiver, messageToFriend);
    messageToFriend.clear();
    serverController->fetchFriendMessages(*mainModel->getUsername(), receiver);
}

void TerminalVue::updateChatEntries()
{
    auto friendList = mainModel->getFriendList();
    auto friendChatToGet = (*friendList)[friend_selected];
    auto friendChatEntries = mainModel->getChatWith(friendChatToGet);
    if (mainModel->getHasFriends() && friend_selected != previousFriendSelected) {
        previousFriendSelected = friend_selected;
        serverController->fetchFriendMessages(*mainModel->getUsername(), friendChatToGet);
    }
    chatEntry.clear();
    for (const auto &chat : *friendChatEntries) {
        std::string mess = chat.sender + ": " + chat.sentMessage;
        chatEntry.push_back(mess);
    }
}

void TerminalVue::updateNotifications()
{
    if (mainTabSelect != 1 && mainModel->hasFriendNotification()) {
        mainTabValues[1] = "Friends*";
    } else {
        mainTabValues[1] = "Friends";
    }
    if (mainTabSelect != 0 && mainModel->hasGameNotification()) {
        mainTabValues[0] = "Games*";
    } else {
        mainTabValues[0] = "Games";
    }
}

void TerminalVue::acceptFriendRequest()
{
    serverController->acceptFriendRequest((*mainModel->getFriendRequestsReceived())[friendRequestSelected], *mainModel->getUsername());
    serverController->fetchFriendRequestsReceived();
    serverController->fetchFriends();
}

void TerminalVue::declineFriendRequest()
{
    serverController->declineFriendRequest((*mainModel->getFriendRequestsReceived())[friendRequestSelected], *mainModel->getUsername());
    serverController->fetchFriendRequestsReceived();
}

void TerminalVue::run()
{
    buttonOption.border = false;
    passwordOption.password = true;
    auto mainRenderer = createFinalContainer();
    auto _screen = ScreenInteractive::TerminalOutput();
    screen = &_screen;
    screen->Loop(mainRenderer);
}

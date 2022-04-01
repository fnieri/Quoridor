//
// Created by louis on 10/02/2022.
//

/**
 * @file TerminalVue.h
 * @author Louis Vanstappen, [Sacha Testaert]
 * @brief Regroups all methods needed to Render a terminal interface
 * @date 2022-02-10
 */

#pragma once

#include <bits/stdc++.h>
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

#include "MainModel.h"
#include "ServerController.h"
#include "src/common/Message.h"
#include "src/common/Point.h"

using namespace ftxui;

struct CheckboxState {
    bool checked = false;
    std::string username;
};

/**
 * @brief TUI of Quoridor using ftxui to display more easily the required components
 * [@details You can find the documentation of the author of FTXUI at : https://arthursonzogni.github.io/FTXUI/]
 */
class TerminalVue : public Observer
{
    MainController mainController;
    MainModel *mainModel = mainController.getMainModel();
    GameModel *gameModel = mainModel->getCurrentGame();
    ServerController *serverController = new ServerController {&mainController};

    ScreenInteractive *screen;

    std::string message, searchField, messageToFriend, username = "aa", password = "aa", registerUsername, registerPassword, registerRepeatPassword;

    int actionToggleSelected = 0;
    int mouse_x = 0;
    int mouse_y = 0;
    bool mousePressed = false;
    int wallOrientation = 0; // indicate the orientation of the wall
    int chatSelected = 0;
    int friend_selected = 0, previousFriendSelected = -1, friendRequestSelected = 0;
    int chat_message_selected = 0;
    int gameSelected = 0;
    int leader_selected = 0;

    int player = -1; // indicate which player the client is
    const int *playerTurn; // indicate which player's turn it is
    std::vector<std::vector<int>> boardIntMatrix;

    ToggleOption actionToggleOption;
    ButtonOption buttonOption;

    std::vector<std::string> chatElements;
    std::vector<std::string> gameList;
    std::vector<int> gameListId;
    std::vector<CheckboxState> friendsListStates;
    std::vector<std::string> chatEntry;

    std::vector<std::string> listLeadersWithElo;

    std::vector<std::string> actionToggleEntries {
        "Move",
        "Wall",
    };
    std::vector<std::string> orientationToggleEntries {
        "Vertical",
        "Horizontal",
    };
    std::vector<std::string> mainTabValues {
        "Game",
        "Friends",
        "LeaderBoard",
    };
    std::vector<std::string> loginTabValues {
        "Login",
        "Register",
        "Training",
    };
    int mainTabSelect = 0, loginTabSelect = 0;
    int rightSize = 0;
    InputOption passwordOption;
    int currentGameId = 69;
    std::string errorLoginMessage;
    std::string registerMessage;
    int homeTabIndex = 0, mainPageIndex = 0, friendDeleteIndex = 0, friendRequestIndex = 0, friendChatIndex = 0, notificationTabIndex = 1;
    int previousHomeTabIndex = homeTabIndex;
    Component playWithContainer = Container::Vertical({});


    void updateChatEntries();

    /**
     * @brief Checks if it's someone's turn
     *
     * @return true
     * @return false
     */
    bool isPlayerTurn() const;

    /**
     * @brief Checks if move is actually valid
     *
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     * @return true
     * @return false
     */
    bool isMoveValid(int x, int y);

    /**
     * @brief Checks if wall placement is actually valid
     *
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     * @return true
     * @return false
     */
    bool isWallPlacementValid(int x, int y);

    /**
     * @brief Checks if the click can be accepted
     * [@details returns true if  (mouseInCell(x, y) && mousePressed && isPlayerTurn())]
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     * @return true
     * @return false
     */
    bool isClickValid(int x, int y);

    /**
     * @brief Create a Canvas object; when rendered displays the board and game indications
     *
     * @return Renderer
     */
    auto createCanvas();

    /**
     * @brief Create a Main Game Screen object; renders a game menu selector
     *
     * @return Renderer
     */
    auto createMainGameScreen();

    /**
     * @brief Checks if mouse is targeting a player move cell.
     *
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     * @return true
     * @return false
     */
    bool mouseInCell(int x, int y) const;

    /**
     * @brief Checks if mouse is targeting a corridor
     *
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     * @return true
     * @return false
     */
    bool mouseInQuoridor(int x, int y) const;

    /**
     * @brief view method that interacts with controller to handle a Cell click
     *
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     */
    void handleCellClick(int x, int y);

    /**
     * @brief
     *
     * @param x
     * @param y
     */
    void handleWallAdd(int x, int y);

    /**
     * @brief Create a Action Toggle object, to chose either to Move or place a Wall
     *
     * @return Toggle
     */
    auto createActionToggle();

    auto createTrainingRenderer();
    auto createBoardGameRenderer();

    /**
     * @brief Create a Orientation Toggle object, to chose in which direction you place your wall
     *
     * @return Toggle
     */
    auto createOrientationToggle();

    /**
     * @brief Create a Main Tab object containing all of the tabs you can toggle to
     *
     * @return Toggle
     */
    auto createMainTab();

    /**
     * @brief Create a Board Renderer object that renders all board features
     *
     * @return Renderer
     */
    auto createBoardRenderer();

    /**
     * @brief create Renderer of Chat Container rendering in-game chat functionalities
     *
     * @return Renderer
     */
    auto createChatRenderer();

    /**
     * @brief Create a LeaderBoard Renderer object
     *
     *[@return text("LeaderBoard") for now]
     */
    auto createLeaderBoardRenderer();

    /**
     * @brief Create a Main Tab Container object containing all windows you can toggle to
     *
     * @return Renderer of container
     */
    auto createMainTabContainer();

    /**
     * @brief Create a Login Renderer object in which you can complete a form to login
     *
     * @return Renderer
     */
    auto createLoginRenderer();

    auto createFriendsRenderer();

    /**
     * @brief Create a Register Renderer object in which you can complete a form to register
     *
     * @return Renderer of container
     */
    auto createRegisterRenderer();

    /**
     * @brief Create a Main container
     * [@details This container contains the biggest part to render]
     * @return Renderer of container
     */
    auto createMainRenderer();

    /**
     * @brief Create a Final container, containing dialogs to confirm or not a friend deletion
     * [@details This container will be permanently refreshed in order to display the interface and any updates]
     * @return Renderer of container
     */
    auto createFinalContainer();

    /**
     * @brief Detects if someone is logged in
     *
     */
    void loginUser();

    void registerUser();

    void sendMessageGame(const std::string &message, int gameId);

    void sendUserMessage();

    void userCreateGame();

    /**
     * @brief Add a friend to your friends list
     * @param username String of the user you want to add to your friends
     *
     */
    void sendFriendRequest();

    /**
     * @brief Delete a friend from your friends list
     *
     */
    void deleteFriend();

    void acceptFriendRequest();

    void declineFriendRequest();

    void updateFriendTabsIndex();

    void updateNotifications();

    void updateFriendsListCheckboxes();

    void updateGameIds();

    void joinGame();

    void unloadCurrentGame();

public:
    TerminalVue();

    void run();

    bool isConnectedToServer() const;

    void update(QuoridorEvent) override;
};

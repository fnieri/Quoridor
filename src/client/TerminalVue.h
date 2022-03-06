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

#include "GameController.h"
//#include "ViewController.h"
//#include "ServerController.h"

using namespace ftxui;

struct CheckboxState {
    bool checked = false;
};

/**
 * @brief TUI of Quoridor using ftxui to display more easily the required components
 * [@details You can find the documentation of the author of FTXUI at : https://arthursonzogni.github.io/FTXUI/]
 */
class TerminalVue
{
    GameController *gameController = new GameController {2, 0, 1};
    std::string message, searchField, messageToFriend, username = "TestUser", password, registerUsername, registerPassword, registerRepeatPassword;
    int actionToggleSelected = 0;
    int mouse_x = 0;
    int mouse_y = 0;
    bool mousePressed = false;
    int player = 1; // indicate which player the client is
    int playerTurn = 1; // indicate which player's turn it is
    int wallOrientation = 0; // indicate the orientation of the wall
    std::vector<int> remainingWalls {1, 2, -1, -1}; // each index represents a player. if -1, then player is not in game.
    std::vector<std::vector<int>> testCanvasGrid {{0, 5, 0, 5, 0, 5, 0, 6, 0}, {5, 5, 7, 7, 7, 5, 5, 6, 5}, {0, 5, 0, 5, 0, 5, 0, 6, 0},
        {5, 5, 5, 5, 5, 5, 5, 5, 5}, {0, 5, 0, 5, 0, 5, 0, 6, 0}, {5, 5, 7, 7, 7, 5, 5, 6, 5}, {0, 5, 0, 5, 0, 5, 0, 6, 0}};
    std::vector<std::vector<int>> boardIntMatrix;
    ToggleOption actionToggleOption;
    ButtonOption buttonOption;
    ButtonOption addButtonOption;
    int chatSelected = 0;
    std::vector<std::string> chatElements;
    int friend_selected = 0;
    int chat_message_selected = 0;
    int gameSelected = 0;
    std::vector<std::string> gameList {"12. UserA, UserB", "14. UserA, UserC, UserD, UserH", "69. Louis, Ryan Reynolds"};
    std::vector<std::string> friendsList {
        "Hector", "Lulu", "Bernard", "Léon", "Charlotte", "Merlin", "Pierre", "Fleure", "Edouard", "José", "Mireille", "Tonio", "Ivan", "Edgard", "Ginette"};
    std::vector<std::string> testFriendList {
        "Hector", "Lulu", "Bernard", "Léon", "Charlotte", "Merlin", "Pierre", "Fleure", "Edouard", "José", "Mireille", "Tonio", "Ivan", "Edgard", "Ginette"};

    std::vector<std::vector<std::string>> chatEntries {
        {"Hello Hector"},
        {"On se fait", "une partie ?"},
        {"Salut", "comment ça va", "Bernard?"},
        {"Salut", "comment ça va", "utilisateur 3?"},
        {"Salut", "comment ça va", "utilisateur 4?"},
        {"Salut", "comment ça va", "utilisateur 5?"},
        {""},
        {""},
        {""},
        {""},
        {""},
        {""},
        {""},
        {""},
        {""},
    };
    std::vector<CheckboxState> friendsListStates;
//    std::vector<Component> playWithCheckbox;
    std::vector<std::string> chatEntry;
    int notif_selected = 0;
    std::vector<std::string> notifications {
        "User1 wants to add you!   (A)ccept or (D)eny ?",
        "UserTest2 wants to add you!   (A)ccept or (D)eny ?",
    };

    int leader_selected = 0;
    std::vector<std::string> leaders {"Hector", "Charlotte", "Nescafé", "Guy", "Auguste"};
    std::vector<int> elos {1480, 1276, 920, 919, 874};
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
    };
    std::vector<Component> mainTabComponents;
    int mainTabSelect = 0, loginTabSelect = 0;
    int rightSize = 0;
    int rightSizeFriends = 70;
    bool isLoggedIn = true; // change this to true to stay logged in
    bool isGameStarted = false;
    bool isCreatingGame = false;
    InputOption passwordOption;
    int depth = 0;
    int currentGameId = 69;
    std::string errorLoginMessage = "";
    std::string registerMessage = "";
    int homeTabIndex = 0;
    int mainPageIndex = 0;

    /**
     * @brief Checks if it's someone's turn
     *
     * @return true
     * @return false
     */
    bool isPlayerTurn();

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
    bool mouseInCell(int x, int y);

    /**
     * @brief Checks if mouse is targeting a corridor
     *
     * @param x column of the matrix in wich stands the mousepointer
     * @param y row of t he matrix in which stands the mousepointer
     * @return true
     * @return false
     */
    bool mouseInQuoridor(int x, int y);

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
     * @brief Create a Chat Input object for the game on
     *
     * @return Input
     */
    auto createChatInput();

    /**
     * @brief Create a Search field Input object to find someone to add to your friends list
     *
     * @return Input
     */
    auto createSearchInput();

    /**
     * @brief Create a Chat Input object to talk with a friend
     *
     * @return Input
     */
    auto createChatFriendInput();

    /**
     * @brief Create a Action Toggle object, to chose either to Move or place a Wall
     *
     * @return Toggle
     */
    auto createActionToggle();

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
     * @brief Create a Friends List Renderer object; renders the friends list
     *  and a chat window to communicate with any of them
     *
     * @return Renderer
     */
    auto createFriendsListRenderer();

    /**
     * @brief create Renderer of the container of notifications and the friend searchbar
     *
     * @return Renderer
     */
    auto createFriendUtilitariesRenderer();

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

    void handleFriendDelete(const std::string &friendUsername);

    void handleFriendAdd(const std::string &friendUsername);

    /**
     * @brief Creates Wraper window object that renders a rounded box shape with a title
     *
     * @param title Text that will be shown above the rendered window
     * @param component Component that has to be shown within the window
     * @return Renderer
     */
    Component Window(std::string title, Component component)
    {
        return Renderer(component, [component, title] { //
            return window(text(title), component->Render()) | flex;
        });
    }

    void loadFriends();

    void loadFriendChats();

    void loadLeaderboard();

    void registerUser();

    void loadMessages();

    void sendMessageGame(std::string message, int gameId);

    void sendUserMessage(std::string message, std::string receiver);

    void userCreateGame();

public:
    void run();

    /**
     * @brief Add a message to the in-game chat window
     * @param username String of the sender's username
     * @param message String of user's typing
     *
     */
    void addChatMessage(std::string username, std::string message);

    /**
     * @brief Add a friend to your friends list
     * @param username String of the user you want to add to your friends
     *
     */
    void addFriend(std::string username);

    /**
     * @brief Delete a friend from your friends list
     *
     */
    void deleteFriend();

    /**
     * @brief Add a message to the conversation you have with your friend
     *
     * @param username String of the sender's username
     * @param message String of the user's typing
     */
    void addChatFriendMessage(std::string username, std::string message);
};

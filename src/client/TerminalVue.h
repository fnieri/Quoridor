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


/**
 * @brief TUI of Quoridor using ftxui to display more easily the required components
 * [@details You can find the documentation of the author of FTXUI at : https://arthursonzogni.github.io/FTXUI/]
 */
class TerminalVue
{
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

    ToggleOption actionToggleOption;
    ButtonOption buttonOption;
    ButtonOption addButtonOption;
    int chatSelected = 0;
    std::vector<std::string> chatElements;
    int friend_selected = 0;
    int chat_message_selected = 0;
    std::vector<std::string> friendsElements {"Hector","Lulu","Bernard","Léon","Charlotte","Merlin","Pierre","Fleure","Edouard", "José", "Mireille", "Tonio", "Ivan", "Edgard", "Ginette"};
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
    std::vector<std::string> chatEntry;
    int notif_selected = 0;
    std::vector<std::string> notifs{
        "User1 wants to add you!   (A)ccept or (D)eny ?",
        "UserTest2 wants to add you!   (A)ccept or (D)eny ?",
    };

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
        "Settings",
    };
    std::vector<std::string> loginTabValues {
        "Login",
        "Register",
    };
    std::vector<Component> mainTabComponents;
    int mainTabSelect = 0, loginTabSelect = 0;
    int rightSize = 40;
    int rightSizeFriends = 70;
    bool isLoggedIn = true; // change this to true to stay logged in

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
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool isMoveValid(int x, int y);

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
     * @brief Checks if mouse is targeting a player move cell.
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool mouseInCell(int x, int y);

    /**
     * @brief Checks if mouse is targeting a corridor
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool mouseInQuoridor(int x, int y);

    /**
     * @brief view method that interacts with controller to handle a Cell click
     * 
     * @param x column position of the mouse pointer in the matrix
     * @param y row position of the mouse pointer in the matrix
     */
    void handleCellClick(int x, int y);

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
     * @brief create Renderer of the container of notifications and the friend searchbar
     * 
     * @return Renderer
     */
    auto createFriendUtilitariesRenderer();

    /**
     * @brief Create a Settings Renderer object
     * 
     *[@return text("Settings") for now]
     */
    auto createSettingsRenderer();

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

    /**
     * @brief Create a Register Renderer object in which you can complete a form to register
     * 
     * @return Renderer of container
     */
    auto createRegisterRenderer();

    /**
     * @brief Create a Main container
     * [@details This container will be permanently refreshed in order to display the interface and any updates]
     * @return Renderer of container
     */
    auto createMainRenderer();

    /**
     * @brief Detects if someone is logged in
     * 
     */
    void loginUser();

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
     * @brief Add a message to the conversation you have with your friend
     * 
     * @param username String of the sender's username
     * @param message String of the user's typing
     */
    void addChatFriendMessage(std::string username, std::string message);

    /**
     * @brief Creates Wraper window object that renders a rounded box shape with a title
     * 
     * @param title Text that will be shown above the rendered window
     * @param component Component that has to be shown within the window 
     * @return Renderer
     */
    Component Window(std::string title, Component component) {
        return Renderer(component, [component, title] {  //
            return window(text(title), component->Render()) | flex;
        });
    }

};

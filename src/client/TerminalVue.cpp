//
// Created by louis on 10/02/2022.
//

#include "TerminalVue.h"

auto TerminalVue::createBoardButtonsContainer(int size)
{
    // https://github.com/ArthurSonzogni/FTXUI/blob/master/examples/component/checkbox_in_frame.cpp
    // maybe better with Container_>Add ?

    buttonOption.border = false;
    std::vector<Component> buttonsGrid;
    for (int i = 0; i < size; i++) {
        std::vector<Component> row_components;
        for (int j = 0; j < size; j++) {
            row_components.push_back(Button(
                "o ", [i, j, this] { std::cout << "Clicked " << i << " " << j << std::endl; }, &buttonOption));
        }
        auto buttonsRow = Container::Horizontal(row_components);
        buttonsGrid.push_back(buttonsRow);
    }

    auto buttonsContainer = Container::Vertical({
        buttonsGrid,
    });
    return buttonsContainer;
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
    auto buttonsContainer = createBoardButtonsContainer(9);
    auto boardContainer = Container::Vertical({
        actionToggle,
        buttonsContainer,
    });
    return Renderer(boardContainer, [buttonsContainer, actionToggle] {
        return vbox({border(buttonsContainer->Render() | center), actionToggle->Render() | center});
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

auto TerminalVue::createMainTabContainer()
{
    auto chat = createChatRenderer();
    auto boardTab = createBoardRenderer();
    auto resizeContainer = boardTab;
    resizeContainer = ResizableSplitRight(chat, resizeContainer, &rightSize);

    auto friends = createFriendsRenderer();
    auto settings = createSettingsRenderer();
    auto tabContainer = Container::Tab(
        {
            resizeContainer,
            friends,
            settings,
        },
        &mainTabSelect);
    return tabContainer;
}

auto TerminalVue::createMainRenderer()
{
    auto tabToggle = createMainTab();

    auto tabContainer = createMainTabContainer();

    auto mainContainer = Container::Vertical({
        tabToggle,
        tabContainer,
    });
    return Renderer(mainContainer, [tabContainer, tabToggle] {
        return vbox({
                   tabToggle->Render(),
                   separator(),
                   tabContainer->Render(),
               })
            | border;
        ;
    });
};

void TerminalVue::run()
{
    auto mainRenderer = createMainRenderer();
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(mainRenderer);
}

void TerminalVue::addChatMessage(std::string username, std::string message)
{
    chatMessages.push_back({username, message});
}
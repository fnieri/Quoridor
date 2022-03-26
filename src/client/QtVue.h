
#pragma once


#include "MainModel.h"
#include "ServerController.h"

#include <QApplication>
#include <QScopedPointer>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class QtVue
{

private:
    MainController mainController;
    MainModel *mainModel = mainController.getMainModel();
    ServerController *serverController = new ServerController {&mainController};

    QScopedPointer<QApplication> app;

    /* === Register Window === */
    QWidget *registerMainWidget;
    QHBoxLayout *horizontalLayout_r1;
    QGroupBox *registerGroupBox;
    QVBoxLayout *verticalLayout_r1;
    QWidget *usernameVBoxRegister;
    QVBoxLayout *verticalLayout_r2;
    QLabel *usernameLabelRegister;
    QLineEdit *usernameLineEditRegister;
    QWidget *passwordVBoxRegister;
    QVBoxLayout *verticalLayout_r3;
    QLabel *passwordLabelRegister;
    QLineEdit *passwordLineEditRegister;
    QWidget *confirmPassVBox;
    QVBoxLayout *verticalLayout_r4;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordLineEdit;
    QPushButton *registerButton;

    void setupRegisterUI();

    /* === Login Window === */
    QWidget *loginMainWidget;
    QHBoxLayout *horizontalLayout_l1;
    QGroupBox *loginGroupBox;
    QVBoxLayout *verticalLayout_l1;
    QWidget *usernameVBoxLogin;
    QVBoxLayout *verticalLayout_l2;
    QLabel *usernameLabelLogin;
    QLineEdit *usernameLineEditLogin;
    QWidget *passwordVBoxLogin;
    QVBoxLayout *verticalLayout_l3;
    QLabel *passwordLabelLogin;
    QLineEdit *passwordLineEditLogin;
    QPushButton *loginButton;
    QLabel *registerLabel;
    QPushButton *registerButtonLogin;

    void setupLoginUI();

    /* === Game Window === */
    QWidget *gameMainWidget;
    QVBoxLayout *verticalLayout;
    QFrame *topBar;
    QHBoxLayout *horizontalLayout;
    QWidget *topBarButtons;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *gameButton;
    QPushButton *friendsButton;
    QPushButton *leaderboardButton;
    QSpacerItem *topBarSpacer;
    QWidget *topBarUser;
    QHBoxLayout *horizontalLayout_3;
    QWidget *userInfo;
    QVBoxLayout *verticalLayout_2;
    QLabel *usernameLabel;
    QLabel *eloLabel;
    QPushButton *logOutButton;
    QStackedWidget *mainStacked;
    QWidget *gamePage;
    QHBoxLayout *horizontalLayout_4;
    QFrame *gameSidebar;
    QVBoxLayout *verticalLayout_3;
    QPushButton *createGameButton;
    QPushButton *joinGameButton;
    QSpacerItem *verticalSpacerSidebar;
    QStackedWidget *gameMainStacked;
    QWidget *createGamePage;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *gameConfigurationBox;
    QVBoxLayout *verticalLayout_5;
    QLabel *gameConfigurationLabel;
    QLabel *playerNumberLabel;
    QHBoxLayout *playerNumberChoices;
    QRadioButton *twoPlayersChoice;
    QRadioButton *fourPlayersChoice;
    QLabel *gameModeLabel;
    QHBoxLayout *gameModeChoices;
    QRadioButton *originalModeChoice;
    QRadioButton *quotetrisModeChoice;
    QRadioButton *timerModeChoice;
    QRadioButton *trainingModeChoice;
    QHBoxLayout *gameStartContainer;
    QSpacerItem *startLeftSpacer;
    QPushButton *startButton;
    QSpacerItem *startRightSpacer;
    QGroupBox *inviteFriendsBox;
    QVBoxLayout *inviteFriendsBoxVLayout;
    QSpacerItem *inviteFriendsUpSpacer;
    QGroupBox *inviteGroupBox;
    QVBoxLayout *inviteFriendsVLayout;
    QLabel *inviteFriendsLabel;
    QScrollArea *inviteFriendsScrollArea;
    QWidget *inviteFriendsScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_17;
    QSpacerItem *inviteFriendsDownSpacer;
    QWidget *joinGamePage;
    QHBoxLayout *horizontalLayout_27;
    QFrame *liveGamesFrame;
    QVBoxLayout *livesgamesVLayout;
    QSpacerItem *liveGamesUpSpacer;
    QLabel *LivesGamesLabel;
    QGroupBox *UMPGroupBox;
    QHBoxLayout *UMPHLayout_2;
    QLabel *usernameUMPLabel;
    QLabel *modeUMPLabel;
    QLabel *playerNumberUMPLabel;
    QScrollArea *liveGamesScrollArea;
    QWidget *liveGamesScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *liveGamesDownSpacer;
    QFrame *filtersFrame;
    QVBoxLayout *notificationsVLayout_2;
    QGroupBox *filtersGroupBox;
    QVBoxLayout *verticalLayout_6;
    QLabel *filtersPlayerNumberLabel;
    QComboBox *filtersNumberChoices;
    QLabel *filterModeLabel;
    QComboBox *filtersModeChoices;
    QWidget *ingamePage;
    QHBoxLayout *horizontalLayout_33;
    QFrame *inGameSidebar;
    QVBoxLayout *gamesideBarHLayout;
    QSpacerItem *quitButtonUpSpacer;
    QPushButton *quitButton;
    QGroupBox *gameFlowBox;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *gameFlowLayout;
    QLabel *gameStatusLabel;
    QLabel *playerTurnLabel;
    QFrame *GameBoardFrame;
    QFrame *gameChatFrame;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *inGameChatBox;
    QVBoxLayout *chatVLayout_2;
    QGroupBox *inGameMessageContainerBox;
    QVBoxLayout *messagesVLayout_2;
    QScrollArea *inGameMessageScrollArea;
    QWidget *inGameScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_20;
    QHBoxLayout *inGameWritingLayout;
    QLineEdit *inGameTextInput;
    QPushButton *inGameSendMessageButton;
    QWidget *friendsPage;
    QHBoxLayout *horizontalLayout_8;
    QFrame *friendsSidebar;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *addFriendContainer;
    QLabel *addFriendLabel;
    QHBoxLayout *addFriendLayout;
    QLineEdit *addFriendTextInput;
    QPushButton *addFriendButton;
    QVBoxLayout *friendsLayout;
    QLabel *friendsListLabel;
    QScrollArea *friendsScrollArea;
    QWidget *friendsScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *friendsChatBox;
    QVBoxLayout *chatVLayout;
    QGroupBox *friendsMessageContainerBox;
    QVBoxLayout *messagesVLayout;
    QScrollArea *friendsMessageScrollArea;
    QWidget *friendsMessageScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *friendsWritingLayout;
    QLineEdit *friendsTextInput;
    QPushButton *friendsSendMessageButton;
    QFrame *friendsNotifications;
    QVBoxLayout *notificationsVLayout;
    QLabel *notificationsLabel;
    QScrollArea *notificationsScrollArea;
    QWidget *notificationsScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_10;
    QWidget *leaderboardPage;
    QHBoxLayout *horizontalLayout_7;
    QWidget *leaderboardLeftSpacer;
    QWidget *leaderboardCenter;
    QVBoxLayout *LeaderBoardVLayout;
    QGroupBox *leaderboardPlayersBox;
    QVBoxLayout *bestplayersVLayout;
    QGroupBox *LBGroupBox;
    QHBoxLayout *RUSHLayout;
    QLabel *rankLBLabel;
    QLabel *usernameLBLabel;
    QLabel *scoreLBLabel;
    QScrollArea *leaderBoardScrollArea;
    QWidget *leaderboardScrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *myLeaderboardBox;
    QHBoxLayout *yourscoreVLayout;
    QSpacerItem *myBoxLeftSpacer;
    QGroupBox *myScoreBox;
    QHBoxLayout *myscoreHLayout;
    QLabel *myRankLabel;
    QLabel *myLabel;
    QLabel *myScoreLabel;
    QSpacerItem *myBoxRightSpacer;
    QWidget *leaderboardRightSpacer;

    void setupGameUI();

public:
    QtVue(int argc, char *argv[]);
    virtual ~QtVue();

    int run();

public slots:
    void loginButtonPressed();
    void registerButtonPressed();

    void loginFieldsUpdated();
    void registerFieldsUpdated();

    void gameButtonPressed();
    void createGameButtonPressed();
    void joinGameButtonPressed();
    void friendsButtonPressed();
    void leaderboardButtonPressed();
};

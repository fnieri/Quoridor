
#pragma once


#include "MainModel.h"
#include "ServerController.h"

#include <QApplication>
#include <QScopedPointer>
#include <string>

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

    void resetController();

    QScopedPointer<QApplication> app;
    
    /* === Main App Window === */
    QWidget *appMainWidget;
    QStackedWidget *appMainStacked;
    QGridLayout *gridLayout;

    void setupMainUI();

    /* === Register Window === */
    QWidget *registerMainWidget;
    QHBoxLayout *horizontalLayout_r1;
    QGroupBox *registerGroupBox;
    QVBoxLayout *verticalLayout_r1;
    QLabel *messageLabelRegister;
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
    QLabel *messageLabelLogin;
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
    QPushButton *logoutButton;
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
    QLabel *livesGamesLabel;
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
    QFrame *gameBoardFrame;
    QGridLayout *boardGrid;
    QLabel *r0c0, *r0c1, *r0c2, *r0c3, *r0c4, *r0c5, *r0c6, *r0c7, *r0c8, *r0c9, *r0c10, *r0c11, *r0c12, *r0c13, *r0c14, *r0c15, *r0c16, *r1c0, *r1c1, *r1c2, *r1c3, *r1c4, *r1c5, *r1c6, *r1c7, *r1c8, *r1c9, *r1c11, *r1c12, *r1c13, *r1c14, *r1c15, *r1c16, *r2c0, *r2c1, *r2c2, *r2c3, *r2c4, *r2c5, *r2c6, *r2c7, *r2c8, *r2c9, *r2c10, *r2c11, *r2c12, *r2c13, *r2c14, *r2c15, *r2c16, *r3c0, *r3c1, *r3c2, *r3c3, *r3c4, *r3c5, *r3c6, *r3c7, *r3c8, *r3c9, *r3c10, *r3c11, *r3c12, *r3c13, *r3c14, *r3c15, *r3c16, *r4c0, *r4c1, *r4c2, *r4c3, *r4c4, *r4c5, *r4c6, *r4c7, *r4c8, *r4c9, *r4c10, *r4c11, *r4c12, *r4c13, *r4c14, *r4c15, *r4c16, *r5c0, *r5c1, *r5c2, *r5c3, *r5c4, *r5c5, *r5c6, *r5c7, *r5c8, *r5c9, *r5c10, *r5c11, *r5c12, *r5c13, *r5c14, *r5c15, *r5c16, *r6c0, *r6c1, *r6c2, *r6c3, *r6c4, *r6c5, *r6c6, *r6c7, *r6c8, *r6c9, *r6c10, *r6c11, *r6c12, *r6c13, *r6c14, *r6c15, *r6c16, *r7c0, *r7c1, *r7c2, *r7c3, *r74, *r7c5, *r7c6, *r7c7, *r7c8, *r7c9, *r7c10, *r7c11, *r7c12, *rc13, *r7c14, *r7c15, *r7c16, *r8c0, *r8c1, *r8c2, *r8c3, *r8c4, *r8c5, *r8c6, *r8c7, *r8c8, *r8c9, *r8c10, *r8c11, *r8c12, *r8c13, *r8c14, *r8c15, *r8c16, *r9c0, *r9c1, *r9c2, *r9c3, *r9c4, *r9c5, *r9c6, *r9c7, *r9c8, *r9c9, *r9c10, *r9c11, *r9c12, *r9c14, *r9c16_2, *r9c15, *r9c16, *r10c0, *r10c1, *r10c2, *r10c3, *r10c4, *r10c5, *r10c6, *r10c7, *r10c8, *r10c9, *r10c10, *r10c11, *r10c12, *r10c13, *r10c14, *r10c15, *r10c16, *r11c0, *r11c1, *r11c2, *r11c3, *r11c4, *r11c5, *r11c6, *r11c7, *r11c8, *r11c9, *r11c10, *r11c12, *r11c13, *r11c14, *r11c15, *r11c16, *r12c0, *r12c1, *r12c2, *r12c3, *r12c4, *r12c5, *r12c6, *r12c8, *r12c9, *r12c10, *r12c11, *r12c12, *r12c13, *r12c14, *r12c15, *r12c16, *r13c0, *r13c1, *r13c2, *r13c3, *r13c4, *r13c5, *r13c6, *r13c7, *r13c8, *r13c9, *r13c10, *r13c11, *r13c12, *r13c13, *r13c14, *r13c15, *r13c16, *r14c0, *r14c1, *r14c2, *r14c3, *r14c4, *r14c5, *r14c6, *r14c7, *r14c8, *r14c9, *r14c10, *r14c11, *r14c12, *r14c13, *r14c14, *r14c15, *r14c16, *r15c0, *r15c1, *r15c2, *r15c3, *r15c4, *r15c5, *r15c6, *r15c7, *r15c8, *r15c9, *r15c10, *r15c11, *r15c12, *r15c13, *r15c14, *r15c15, *r15c16, *r16c0, *r16c1, *r16c2, *r16c3, *r16c4, *r16c5, *r16c6, *r16c7_2, *r16c8_2, *r16c9_2, *r16c10, *r16c11, *r16c12, *r16c13, *r16c14, *r16c15, *r16c16, *r1c10, *r12c7, *r11c11;
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
    QVBoxLayout *leaderboardScrollAreaWidgetContentsLayout;
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

    QWidget *createLeaderboardBox(QWidget *parent, int rank, std::string username, int score);

    void updateLeaderboard();

public:
    QtVue(int argc, char *argv[]);
    virtual ~QtVue();

    int run();
    
    void gotoRegisterWindow();
    void gotoLoginWindow();
    void gotoGameWindow();

    void loginButtonPressed();
    void registerButtonPressed();
    void logoutButtonPressed();

    void gameButtonPressed();
    void createGameButtonPressed();
    void joinGameButtonPressed();
    void friendsButtonPressed();
    void leaderboardButtonPressed();
};

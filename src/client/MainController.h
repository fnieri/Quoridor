#pragma once

#include <iostream>
#include <string>

#include "MainModel.h"
#include "src/common/MessageEnums/Actions/AuthActions.h"
#include "src/common/MessageEnums/Actions/ChatBoxActions.h"
#include "src/common/MessageEnums/Actions/FriendActions.h"
#include "src/common/MessageEnums/Status.h"
#include "src/common/Message.h"

class MainModel;

class MainController
{
private:
    MainModel *m_mainModel;

public:
    MainController();

    MainModel *getMainModel();

    void processRequest(const std::string &);

    void processAuth(const std::string &);

    void processRelations(const std::string &);

    void processResourceRequest(const std::string &);

    void processChatBox(const std::string &);

    void processGameSetup(const std::string &);
};
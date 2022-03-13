#pragma once

#include <string>
#include <iostream>

#include "src/common/MessageEnums/Actions/AuthActions.h"
#include "src/common/MessageEnums/Actions/FriendActions.h"
#include "src/common/MessageEnums/Actions/ChatBoxActions.h"
#include "src/common/MessageEnums/Status.h"
#include "src/client/MainModel.h"

class MainController
{
private:
    MainModel m_mainModel;
public:
    MainModel *getMainModel();

    void processRequest(const std::string &);

    void processAuth(const std::string &);

    void processRelations(const std::string &);

    void processResourceRequest(const std::string &);

    void processChatBox(const std::string&);

    void processGameSetup(const std::string&);
};
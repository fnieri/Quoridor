#pragma once

#include <string>
#include "MainModel.h"
#include "../common/MessageEnums/Actions/AuthActions.h"
#include "../common/MessageEnums/Actions/FriendActions.h.h"
#include "../common/MessageEnums/Actions/ChatBoxActions.h.h"
#include "../common/MessageEnums/Actions/.h"

class MainController
{
private:
    MainModel m_mainModel;
public:

    void processRequest(const std::string &);

    void processAuth(const std::string &);

    void processRelations(const std::string &);

    void processResourceRequest(const std::string &);

    void processChatBox(const std::string&);

    void processGameSetup(const std::string&);
};
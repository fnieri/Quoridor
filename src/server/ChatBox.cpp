#include "ChatBox.h"

#include "UserHandler.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ChatBox::ChatBox(UserHub &userHub)
    : m_userHub {userHub}
{
}

void ChatBox::processMessage(const std::string &serMessage)
{
    recordMessage(serMessage);
    relayMessage(serMessage);
}

void ChatBox::recordMessage(const std::string &serMessage)
{
    auto deserMessage {json::parse(serMessage)};
    // TODO: link with db
}

void ChatBox::relayMessage(const std::string &serMessage)
{
    auto deserMessage {json::parse(serMessage)};

    // Usually sent to one person, but may be many in the future
    for (auto &r : deserMessage["recipient"])
        m_userHub.relayMessageTo(r, serMessage);
}

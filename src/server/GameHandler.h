#pragma once

class GameHandler
{
private:
    bool m_isPlaying;
    std::vector<std::shared_ptr<UserHandler>> m_players;

public:
    GameHandler(std::shared_ptr<UserHandler>, std::shared_ptr<UserHandler>);
};

class GameHub
{
private:
    /**
     * Needed to see if users are indeed connected and
     * access their handlers.
     */
    UserHub &m_userHub;
    std::vector<GameHandler> m_games;

public:
    /**
     * Create game with two users' usernames.
     */
    void createGame(const std::string &, const std::string &);
};

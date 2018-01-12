#ifndef PLAYER_HPP
#define PLAYER_HPP

class GameWindowInfo;

class Player
{
  public:
    Player(const GameWindowInfo* gameWindowInfo);

  public:
    int getCurrentMapId();

  private:
    const GameWindowInfo *m_gameWindowInfo;
};

#endif // PLAYER_HPP

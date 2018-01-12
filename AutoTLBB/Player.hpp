#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <QDebug>

class GameWindowInfo;

class Player
{
  public:
    struct Position
    {
        float x;
        float y;
    };

  public:
    Player(const GameWindowInfo* gameWindowInfo);

  public:
    std::string getName() const;
    int getMapId() const;
    int getHp() const;
    int getMaxHp() const;
    int getMp() const;
    int getMaxMp() const;
    int getMenpaiId() const;
    Position getPosition() const;
    float getPosX() const;
    float getPosY() const;

  private:
    const GameWindowInfo *m_gameWindowInfo;

  private:
    friend QDebug operator<<(QDebug qdb, const Player& player);
};

#endif // PLAYER_HPP

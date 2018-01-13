#ifndef PLAYER_HPP
#define PLAYER_HPP

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
    QString getName() const;
    int getSceneId() const;
    QString getSceneName() const;
    int getHp() const;
    int getMaxHp() const;
    float getHpPercent() const;
    int getMp() const;
    int getMaxMp() const;
    float getMpPercent() const;
    int getMenpaiId() const;
    QString getMenpaiName() const;
    Position getPosition() const;
    float getPosX() const;
    float getPosY() const;

  private:
    const GameWindowInfo *m_gameWindowInfo;

  private:
    friend QDebug operator<<(QDebug qdb, const Player& player);
};

#endif // PLAYER_HPP

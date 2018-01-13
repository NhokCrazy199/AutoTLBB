#include "Player.hpp"

#include "GameWindowInfo.hpp"

Player::Player(const GameWindowInfo* gameWindowInfo) :
  m_gameWindowInfo(gameWindowInfo)
{
}

QDebug operator<<(QDebug qdb, const Player& player)
{
  qdb << "Name: " << player.getName();
  qdb << "HP: " << player.getHp();
  qdb << "Max Hp: " << player.getMaxHp();
  qdb << "Mp: " << player.getMp();
  qdb << "Max Mp: " << player.getMaxMp();
  qdb << "MenpaiId: " << player.getMenpaiId();
  qdb << "Pos(x, y)" << player.getPosX() << "," << player.getPosY();
  qdb << "MapId: " << player.getMapId();

  return qdb;
}

char* Player::getName() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0xC, 0x1EC, 0x4, 0x3C
  };

  return m_gameWindowInfo->readMemory<char*>(adrs);
}

int Player::getMapId() const
{
  DWORD adr = 0xA8F060;
  int mapId = m_gameWindowInfo->readMemory<int>(adr);

  return mapId;
}

QString Player::getMapName() const
{
  int mapId = this->getMapId();

  return "+";
}

int Player::getHp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0xC, 0x1EC, 0x4, 0x2760
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

int Player::getMaxHp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0xC, 0x1EC, 0x4, 0x27D8
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

float Player::getHpPercent() const
{
  return this->getHp() / this->getMaxHp() * 100;
}

int Player::getMp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0xC, 0x1EC, 0x4, 0x2764
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

int Player::getMaxMp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0xC, 0x1EC, 0x4, 0x27DC
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

float Player::getMpPercent() const
{
  return this->getMp() / this->getMaxMp() * 100;
}

int Player::getMenpaiId() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0xC, 0x1EC, 0x4, 0xF4
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

QString Player::getMenpaiName() const
{
  int menpaiId = this->getMenpaiId();

  return "";
}

Player::Position Player::getPosition() const
{
  Position pos;

  pos.x = this->getPosX();
  pos.y = this->getPosY();

  return pos;
}

float Player::getPosX() const
{
  std::vector<DWORD> adrs{
    0x145EA78, 0x5C
  };

  return m_gameWindowInfo->readMemory<float>(adrs);
}

float Player::getPosY() const
{
  std::vector<DWORD> adrs{
    0x145EA78, 0x64
  };

  return m_gameWindowInfo->readMemory<float>(adrs);
}

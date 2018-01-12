#include "Player.hpp"

#include "GameWindowInfo.hpp"

Player::Player(const GameWindowInfo* gameWindowInfo) :
  m_gameWindowInfo(gameWindowInfo)
{
}

QDebug operator<<(QDebug qdb, const Player& player)
{
  qdb << "HP: " << player.getHp();
  qdb << "Max Hp: " << player.getMaxHp();
  qdb << "Mp: " << player.getMp();
  qdb << "Max Mp: " << player.getMaxMp();

  return qdb;
}

int Player::getMapId() const
{
  DWORD adr = 0x00A8F060;
  int mapId = m_gameWindowInfo->readMemory<int>(adr);

  return mapId;
}

int Player::getHp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0x2760, 0x04, 0x1EC, 0x0C
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

int Player::getMaxHp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0x2760, 0x04, 0x1EC, 0x0C
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

int Player::getMp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0x2760, 0x04, 0x1EC, 0x0C
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

int Player::getMaxMp() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0x2760, 0x04, 0x1EC, 0x0C
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
}

int Player::getMenpaiId() const
{
  std::vector<DWORD> adrs{
    0x145EB34, 0x2760, 0x04, 0x1EC, 0x0C
  };

  return m_gameWindowInfo->readMemory<int>(adrs);
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
    0x0145EA78, 0x5C
  };

  return m_gameWindowInfo->readMemory<float>(adrs);
}

float Player::getPosY() const
{
  std::vector<DWORD> adrs{
    0x0145EA78, 0x64
  };

  return m_gameWindowInfo->readMemory<float>(adrs);
}

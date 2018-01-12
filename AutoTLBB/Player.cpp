#include "Player.hpp"

#include "GameWindowInfo.hpp"

Player::Player(const GameWindowInfo* gameWindowInfo) :
  m_gameWindowInfo(gameWindowInfo)
{
}

int Player::getCurrentMapId()
{
  DWORD address = 0x00A8F060;
  int mapId = m_gameWindowInfo->readMemory<int>(address);

  return mapId;
}

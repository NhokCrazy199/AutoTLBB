#include "GameWindowInfo.hpp"

#include "Player.hpp"
#include "Settings.hpp"

GameWindowInfo::GameWindowInfo()
{
  m_hwnd = nullptr;
  m_handle = nullptr;
  m_player = new Player(this);
  m_settings = new Settings(this);
}

GameWindowInfo::~GameWindowInfo()
{
  delete m_player;
  delete m_settings;
}

QDebug operator<<(QDebug qdb, const GameWindowInfo& gameWindowInfo)
{
  qdb << "Hwnd:";
  qdb << gameWindowInfo.m_hwnd;
  qdb << "Process Id:";
  qdb << gameWindowInfo.m_processId;
  return qdb;
}

void GameWindowInfo::setHwnd(const HWND hwnd)
{
  m_hwnd = hwnd;
}

HWND GameWindowInfo::getHwnd() const
{
  return m_hwnd;
}

void GameWindowInfo::setProcessId(const DWORD processId)
{
  m_processId = processId;
}

DWORD GameWindowInfo::getProcessId() const
{
  return m_processId;
}

void GameWindowInfo::setHandle(const HANDLE handle)
{
  m_handle = handle;
}

HANDLE GameWindowInfo::getHandle() const
{
  return m_handle;
}

Player* GameWindowInfo::getPlayer() const
{
  return m_player;
}

void GameWindowInfo::sendMessage(const UINT msg, const WPARAM wParam, const LPARAM lParam) const
{
  ::SendMessage(m_hwnd, msg, wParam, lParam);
}

void GameWindowInfo::postMessage(const UINT msg, const WPARAM wParam, const LPARAM lParam) const
{
  ::PostMessage(m_hwnd, msg, wParam, lParam);
}

Settings* GameWindowInfo::getSettings() const
{
  return m_settings;
}

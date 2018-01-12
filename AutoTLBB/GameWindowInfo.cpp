#include "GameWindowInfo.hpp"

GameWindowInfo::GameWindowInfo()
{
  m_hwnd = nullptr;
  m_handle = nullptr;
}

GameWindowInfo::~GameWindowInfo()
{
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

HWND& GameWindowInfo::getHwnd()
{
  return m_hwnd;
}

void GameWindowInfo::setProcessId(const DWORD processId)
{
  m_processId = processId;
}

DWORD& GameWindowInfo::getProcessId()
{
  return m_processId;
}

void GameWindowInfo::setHandle(const HANDLE handle)
{
  m_handle = handle;
}

HANDLE& GameWindowInfo::getHandle()
{
  return m_handle;
}

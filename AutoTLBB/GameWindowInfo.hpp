#ifndef GAMEWINDOWINFO_HPP
#define GAMEWINDOWINFO_HPP

#include <Windows.h>

class GameWindowInfo
{
  public:
    GameWindowInfo();

  public:
    void setHwnd(const HWND hwnd);
    HWND& getHwnd();
    void setHandle(const HANDLE handle);
    HANDLE& getHandle();
    void setProcessId(const DWORD processId);
    DWORD& getProcessId();

  private:
    HWND m_hwnd;
    HANDLE m_handle;
    DWORD m_processId;
};

#endif // GAMEWINDOWINFO_HPP

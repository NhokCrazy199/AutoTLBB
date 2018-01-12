#ifndef GAMEWINDOWINFO_HPP
#define GAMEWINDOWINFO_HPP

#include <QDebug>

#include <Windows.h>

class Player;

class GameWindowInfo
{
  public:
    GameWindowInfo();
    ~GameWindowInfo();

  public:
    void setHwnd(const HWND hwnd);
    HWND getHwnd() const;
    void setHandle(const HANDLE handle);
    HANDLE getHandle() const;
    void setProcessId(const DWORD processId);
    DWORD getProcessId() const;
    Player* getPlayer() const;

  public:
    template<typename T>
    T readMemory(const DWORD address) const
    {
      T value;

      ::ReadProcessMemory(
            this->m_handle,
            reinterpret_cast<LPVOID>(address),
            &value, sizeof(value), nullptr
            );

      return value;
    }

  private:
    HWND m_hwnd;
    HANDLE m_handle;
    DWORD m_processId;
    Player *m_player;

  private:
    friend QDebug operator<<(QDebug qdb, const GameWindowInfo& gameWindowInfo);
};

QDebug operator<<(QDebug qdb, const GameWindowInfo& gameWindowInfo);

#endif // GAMEWINDOWINFO_HPP

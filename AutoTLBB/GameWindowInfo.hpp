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
            &value, sizeof(T), nullptr
            );

      return value;
    }

    template<typename T>
    T readMemory(const std::vector<DWORD>& adrs) const
    {
      qDebug() << "CALLED";

      DWORD nextOffset = *adrs.cbegin();
      for (std::size_t i = 0; i < adrs.size() - 1; i++)
      {
        nextOffset = this->readMemory<DWORD>(nextOffset) + adrs.at(i+1);
      }

      return this->readMemory<T>(nextOffset);
    }

  private:
    HWND m_hwnd;
    HANDLE m_handle;
    DWORD m_processId;
    Player *m_player;

  private:
    friend QDebug operator<<(QDebug qdb, const GameWindowInfo& gameWindowInfo);
};

#endif // GAMEWINDOWINFO_HPP

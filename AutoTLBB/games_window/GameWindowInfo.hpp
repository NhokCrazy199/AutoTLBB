#ifndef GAMEWINDOWINFO_HPP
#define GAMEWINDOWINFO_HPP

#include <QDebug>

#include <Windows.h>

class Player;
class Settings;

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
    void sendMessage(const UINT msg, const WPARAM wParam, const LPARAM lParam) const;
    void postMessage(const UINT msg, const WPARAM wParam, const LPARAM lParam) const;
    Settings* getSettings() const;

  public:
    template<typename T>
    T readMemory(const DWORD address) const
    {
      T value;

      auto r = ::ReadProcessMemory(
            this->m_handle,
            reinterpret_cast<LPCVOID>(address),
            reinterpret_cast<LPVOID>(&value),
            sizeof(T), nullptr
            );
      if (!r)
      {
        qDebug() << "Can not read memory";
      }

      return value;
    }

    template<typename T>
    T readMemory(const std::vector<DWORD>& adrs) const
    {
      DWORD nextOffset = *adrs.cbegin();
      for (std::size_t i = 1; i < adrs.size(); i++)
      {
        nextOffset = this->readMemory<DWORD>(nextOffset) + adrs.at(i);
      }

      return this->readMemory<T>(nextOffset);
    }

  private:
    HWND m_hwnd;
    HANDLE m_handle;
    DWORD m_processId;
    Player *m_player;
    Settings * m_settings;

  private:
    friend QDebug operator<<(QDebug qdb, const GameWindowInfo& gameWindowInfo);
};

#endif // GAMEWINDOWINFO_HPP

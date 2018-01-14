#ifndef SETTINGS_HPP
#define SETTINGS_HPP

class GameWindowInfo;

class Settings
{
  public:
    Settings(const GameWindowInfo* gWI);

  private:
    const GameWindowInfo *m_gameWindowInfo;
};

#endif // SETTINGS_HPP

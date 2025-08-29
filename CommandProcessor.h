#pragma once
#include "Index.h"

template<uint BUFFER_SIZE, uint INDEX_SIZE>
class CommandProcessor {
public:
  // Конструкторы
  CommandProcessor();
  template <uint COMMAND_COUNT> CommandProcessor(Command (&aCommandList)[COMMAND_COUNT]);

  // Основной цикл обработки ввода
  CommandProcessor& readInput();
  void processCommand();

  // Управление буфером и состоянием
  CommandProcessor& resetBuffer();
  CommandProcessor& setTerminator(char terminator);
  CommandProcessor& setTrimSpaces(bool enable);

  // Работа с командами
  Command* findCommand(const char *name);
  CommandProcessor& showSimilarCommands(const char *filter);
  template <uint COMMAND_COUNT> CommandProcessor& setCommands(Command (&commands)[COMMAND_COUNT]);
  CommandProcessor& setCommands(Command *commands, uint count);

  // Работа с токенами (аргументами)
  char* getToken(uint index);
  char* operator[](uint index);
  int getArgumentCount() const;

  // Настройка интерфейса пользователя
  CommandProcessor& setPrompt(const char* prompt);
  CommandProcessor& showWelcome();
  CommandProcessor& setDebugMode(bool enable);

  // Вспомогательные методы (опционально, можно показать как пример "продвинутости")
  CommandProcessor& tokenizeInput(int expectedArgs = -1);
  CommandProcessor& extractFirstToken(uint *firstWordEnd);
};

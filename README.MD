# CommandProcessor

**Мощный и легковесный процессор команд для встроенных систем (Embedded C++) с поддержкой токенизации, цветного вывода и автодополнения.**

Этот проект представляет собой шаблонный класс на C++ для обработки текстовых команд в интерфейсах командной строки (CLI). Он разработан с учетом работы на микроконтроллерах (AVR) и на ПК, поддерживает динамическую токенизацию, цветной вывод, обработку escape-последовательностей и поиск команд.

## Особенности

* **Кросс-платформенность:** Работает как на AVR (Arduino), так и на PC (Linux/Windows/MacOS).
* **Шаблонный дизайн:** Размеры буферов и индексов задаются на этапе компиляции для контроля потребления памяти.
* **Динамическая токенизация:** Гибкое разбиение входной строки на аргументы с различными режимами.
* **Цветной вывод:** Поддержка ANSI-цветов для удобства отладки и пользовательского интерфейса.
* **Система команд:** Простая регистрация и поиск команд с указанием количества ожидаемых аргументов.
* **Автодополнение:** Функция для показа похожих команд по подстроке.
* **Экранирование символов:** Встроенная обработка escape-последовательностей (\n, \t, \r и др.).

## Быстрый старт
### Минимальный пример использования
```C++
#include "CommandProcessor.h"
#include "io.h"

CommandProcessor<32, 16> cli;

void say() {
  io::println("Скажи", cli[1]);
}

double NewtonRaphsonSqrt(double x, double initial_guess, double iterations, bool verbose = false) {
  // Метод Ньютона-Рафсона
  double result = initial_guess;
  for (int i = 0; i < iterations; ++i) {
    result = 0.5 * (result + x / result);
    if (verbose)
      io::cout << i << ": " << result << io::endl;
  }
  return result;
}

void sqrt() {
  io::cli.showWelcome().setDebugMode(false);
  int result = NewtonRaphsonSqrt(utils::d(cli[1], utils::d(cli[2], utils:i(cli[3]));
  io::println(io::ORANGE, result, io::NO);
}

Command cmd[] = {
  {"say", say, -1},
  {"sqrt", sqrt, -1},
}

void setup() {
  io::init(115200);
  cli.setCommands(cmd);
}

void loop() {
  cli.readInput();
}
```

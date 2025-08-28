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
#include "utils.h"

using utils::i; // char* to int
using utils::d; // char* to double

CommandProcessor<64, 16> cli;

void say() {
  io::println(io::YELLOW, "!!! ", cli[1], " !!!", io::NO);
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
  int result = NewtonRaphsonSqrt( d(cli[1]), d(cli[2]), i(cli[3]) );
  io::println(io::ORANGE, result, io::NO);
}

Command cmd[] = {
  {"say", say, -1},
  {"sqrt", sqrt, -1},
};

void setup() {
  io::init(115200);
  cli.set.Prompt(">> ").showWelcome().setDebugMode(false);
  cli.setCommands(cmd);
}

void loop() {
  cli.readInput();
}
```

### Либо ещё проще
```C++
#include "CommandProcessor.h"
#include "io.h"
#include "utils.h"

using utils::d; // char* to double

CommandProcessor<64, 16> cli;

void half_sum() {
  double a = d(cli[1]);
  double b = d(cli[2]);
  double result = (a + b) / 2;
  io::println("The half-sum of " a, " and ", b, " is ", io::BLUE, result, io::NO);
}

Command cmd[] = {
  {"hsum", half_sum, -1},
};

int main() {
  cli.run(cmd, false, ">>> "); 
  return 0;
}
```

# CommandProcessor

```markdown

<p align="center">
  <strong>Мощный и легковесный процессор команд для встроенных систем (Embedded C++)</strong>
  <br>
  <br>
  <img src="https://img.shields.io/badge/C++-17+-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/Platforms-AVR%20%7C%20PC-green.svg" alt="Platforms">
  <img src="https://img.shields.io/badge/Memory-Static%20Allocation-brightgreen.svg" alt="Static Memory">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License">
</p>

```

**Поддержка токенизации, цветного вывода и автодополнения для embedded-систем и не только.**


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
### Пример 1.
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
  cli.setPrompt(">> ").showWelcome().setDebugMode(false);
  cli.setCommands(cmd);
}

void loop() {
  cli.readInput();
}
```

### Пример 2.
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
  io::println("The half-sum of ", a, " and ", b, " is ", io::BLUE, result, io::NO);
}

Command cmd[] = {
  {"hsum", half_sum, -1},
};

int main() {
  cli.run(cmd, false, ">>> "); // debugMode = false, prompt = ">>> "
  return 0;
}
```

### Логика отделения аргументов
В строке

```C++
{"cmd", cmd, -1},
```
"cmd"  — это псевдоним к функции, по которому к этой функции можно обращаться интерактивно;

cmd    — сама функция;

-1     — способ разбияния строки для отделения аргументов ```expectedArgCount```.

В зависимости от способа на выходе получается разная интерпретация:

```text
"cmd arg1 arg2 arg3 arg4" → ["cmd", "arg1 arg2 arg3 arg4"] при expectedArgCount = 1 → отделяется ровно одно слово — название команды.
"cmd arg1 arg2 arg3 arg4" → ["cmd", "arg1", "arg2 arg3 arg4"] при expectedArgCount = 2 → отделяется команда и первый аргумент, всё остальное идёт вторым аргументом.
"cmd arg1 arg2 arg3 arg4" → ["cmd", "arg1", "arg2", "arg3 arg4"] при expectedArgCount = 3 → отделяется команда и первый и второй аргументы, всё остальное идёт третьим аргументом.
И т.д.
"cmd arg1 arg2 arg3 arg4" → ["cmd arg1 arg2 arg3 arg4"] при expectedArgCount = 0 → не отделяется ничего, но команда идентифицируется, и вместе с аргументами подаётся как единое целое.
"cmd arg1 arg2 arg3 arg4" → ["cmd", "arg1", "arg2", "arg3", "arg4"] при expectedArgCount = 0 → отделяются все слова, первое слово — команда, все остальные — аргументы.
```

Для аргументов, которые подаются в комлексе, может быть использован специальный парсер, разработанный пользователем.

## Структура проекта
```text
.
├── CommandProcessor.h  # Основной класс процессора команд
├── index.h             # Класс для работы с индексами (статический/динамический буфер)
├── io.h                # Абстракция ввода/вывода с поддержкой цветов (ANSI)
├── internal.h          # Внутренние платформо-зависимые функции (AVR/PC)
├── utils.h             # Вспомогательные утилиты (строки, математика)
└── examples/           # Папка с примерами использования (рекомендуется создать)
```


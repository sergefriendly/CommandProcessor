namespace io {

// Класс для управления вводом-выводом и также цветом текса
class IO {
public:
    
    void init(unsigned long baud);
    int available();
    char read();

    // Вариадические шаблоны
    template<typename T, typename... Args>
    void print(T first, Args... args);

    // Система цветов
    struct Color {
        Code RED{"\e[1;31m", "", &isEnabled_};
        Code GREEN{"\e[1;32m", "", &isEnabled_};
        Code NO{"\e[0m", "\e[0m", &isEnabled_};
        // ...
    };
};

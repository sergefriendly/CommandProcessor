namespace io {

// Покажите главный класс и его возможности
class IO {
public:
    // Покажите, что есть инициализация для разных платформ
    void init(unsigned long baud);
    int available();
    char read();

    // Вариадические шаблоны - это солидно
    template<typename T, typename... Args>
    void print(T first, Args... args);

    // Покажите систему цветов - это "вау"-эффект
    struct Color {
        Code RED{"\e[1;31m", "", &isEnabled_};
        Code GREEN{"\e[1;32m", "", &isEnabled_};
        Code NO{"\e[0m", "\e[0m", &isEnabled_};
        // ...
    };
};

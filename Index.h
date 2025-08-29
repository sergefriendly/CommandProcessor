template<uint STATIC_BUFFER_LENGTH = 0>
class Index {
public:
    // Конструкторы для разных сценариев использования
    Index(); // для статического буфера
    Index(uint size); // для динамического
    Index(int* external_buffer, uint size); // для внешнего

    // Основной интерфейс
    bool add(int value);
    Index& operator+=(int value);
    void clear();

    // Доступ к данным
    int& operator[](uint i);
    uint capacity() const;
    uint position() const;

    // Это очень круто для embedded - фабричные методы
    static Index createStatic();
    static Index createDynamic(uint size);
};

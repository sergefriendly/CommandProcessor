namespace utils {

// Конвертирует char* в double
double d(const char* str);

// Конвертирует char* в int
int i(const char* str);

// Эта функция сразу говорит о качестве
void replaceEscapeSequencesIn(char *const code);

// Показывает работу со строками без STL
bool areStringsEqual(const char *a, const char *b);

// Демонстрирует алгоритмическое мышление
bool isSubsequence(const char *sequence, const char *subsequence);

} // namespace utils

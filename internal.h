#pragma once

// Макросы, определяющие платформу
#define IS_AVR defined(__AVR)
#define IS_PC !IS_AVR

namespace io { namespace internal {

// Нижеприведённые функции описываются под платформы
void init(unsigned long baud);
int available();
char read();

}} // namespace io::internal

// Программа содержит намеренную ошибку работы с памятью.
// ИЗМЕНЯТЬ ФАЙЛ НЕЛЬЗЯ. Задача — собрать с AddressSanitizer, запустить
// и разобрать отчёт: тип ошибки, строка, чтение или запись, размер.
//
// Сборка и запуск:  make apps && ./build/bug_demo

#include <cstdio>

static int checksum(const int* data, int count) {
    int sum = 0;
    for (int i = 0; i <= count; ++i) {
        sum += data[i];
    }
    return sum;
}

int main() {
    const int n = 8;
    int* buf = new int[n];
    for (int i = 0; i < n; ++i) buf[i] = i + 1;

    std::printf("контрольная сумма: %d\n", checksum(buf, n));

    delete[] buf;
    return 0;
}

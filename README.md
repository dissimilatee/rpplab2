# Лабораторна робота №2: OpenMP Odd-Even Sort

## Компіляція
```bash
g++ openmp_odd_even.cpp -O2 -fopenmp -o openmp_odd_even
```

## Запуск
```bash
./openmp_odd_even 16384 1
./openmp_odd_even 16384 2
./openmp_odd_even 16384 4
./openmp_odd_even 16384 8
```

Перший параметр — розмір масиву, другий — кількість потоків.

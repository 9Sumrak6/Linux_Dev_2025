#!/bin/bash
# build_and_run.sh

echo "=== Очистка и сборка ==="
rm -rf build
mkdir -p build
cd build

echo "=== Конфигурация CMake ==="
cmake ..

echo "=== Сборка ==="
make

echo ""
echo "=== Запуск программы ==="
LANGUAGE=ru_RU.UTF-8 LANG=ru_RU.UTF-8 LC_ALL=ru_RU.UTF-8 ./bin/guess

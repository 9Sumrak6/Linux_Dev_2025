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

# echo "=== Проверка структуры ==="
# echo "Содержимое build:"
# find . -name "*.mo" -type f | xargs -I {} ls -la {} | head -20

echo ""
echo "=== Запуск программы ==="
LANGUAGE=ru_RU.UTF-8 LANG=ru_RU.UTF-8 LC_ALL=ru_RU.UTF-8 ./bin/guess

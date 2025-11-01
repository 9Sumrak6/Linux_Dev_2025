# Rhasher


Простая утилита для подсчёта хешей (MD5, SHA1, TTH) для строк и файлов.


## Установка зависимостей (Ubuntu)
```bash
sudo apt update
sudo apt install librhash-dev libreadline-dev autoconf automake libtool gcc make
```


## Сборка
```bash
./autogen.sh
./configure [--disable-readline]
make
```


## Тестирование
```bash
make check
```


## Использование
```bash
./src/rhasher
```
Вводите команды в формате:
```
<HashName> <"строка"|файл>
```
Заглавная первая буква — вывод в hex, строчная — в base64.


## Очистка
```bash
make clean
make distclean
```
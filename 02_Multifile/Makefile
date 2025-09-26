CC = gcc
CFLAGS = -Wall -Wextra -fPIC

GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.* *.noargs *.one *.three

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: liboutput_static.a liboutput.so prog prog-a prog-so README

liboutput_static.a: fun.o const.o
	ar rcs $@ $^

liboutput.so: fun.o const.o
	$(CC) -shared -o $@ $^

prog: prog.o fun.o const.o
	$(CC) -o $@ $^

prog-a: prog.o liboutput_static.a
	$(CC) -o $@ prog.o ./liboutput_static.a

prog-so: prog.o liboutput.so
	$(CC) -o $@ prog.o -L. -loutput -Wl,-rpath,.

README: prog
	./$< 2> $@

test: prog prog-a prog-so
	@echo "=== Запуск тестов ==="
	@for bin in prog prog-a prog-so; do \
		echo "Running $$bin..."; \
		./$$bin > $$bin.noargs 2>&1; \
		./$$bin onearg > $$bin.one 2>&1; \
		./$$bin arg1 arg2 arg3 > $$bin.three 2>&1; \
	done
	@echo "=== Сравнение вывода ==="
	@cmp prog.noargs prog-a.noargs
	@cmp prog.noargs prog-so.noargs
	@cmp prog.one prog-a.one
	@cmp prog.one prog-so.one
	@cmp prog.three prog-a.three
	@cmp prog.three prog-so.three
	@echo "Все тесты успешно пройдены!"

clean:
	rm -f $(TRASH)

distclean: clean
	rm -f $(GENERATES)

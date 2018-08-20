CC = gcc

transparentwindow: main.c
	$(CC) -Wall -o transparentwindow main.c -lX11

install: transparentwindow
	sudo ln -s $(PWD)/transparentwindow /usr/local/bin/transparentwindow

uninstall:
	sudo rm /usr/local/bin/transparentwindow

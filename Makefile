all:
	gcc src/main.c \
		-static \
		-static-libgcc \
		-O2 \
		-o lewentweb.exe

CC = gcc
CFLAGS0 = -Wall -Wpedantic -Wextra -std=c99
CFLAGS1 = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fstack-protector-strong
ALLFLAGS = $(CFLAGS0) $(CFLAGS1)
OBJS := $(addprefix $(OBJD)/, *.o)
DEBUG = mains/debug.c
OBJD = dest
TARGETD = bin
#me dejo el template del ayudante a mano

export

all:
	@echo "===================="
	@echo "creating directories"
	mkdir -p $(OBJD)
	mkdir -p $(TARGETD)
	@echo "===================="
	@echo "compiling source into obj"
#calls makefile in tads
	+$(MAKE) -C mains

######## Opciones de la línea de comandos. ########
# Esto significa que 'make autodebug' compila en modo TEST_AUTODEBUG,
# 'make normal' en modo TEST_NORMAL y así. El comando 'make clean'
# borra todo lo que esté en el directorio de output y termine en '.o'.
.PHONY: autodebug
.PHONY: clean
.PHONY: debug
.PHONY: normal

#if dest/something.o is a non resolved dependency, check in current directory

#we don’t want to rebuild all the targets whenever the directory’s
#timestamp changes. One way to manage this is with order-only prerequisites:
#make the directory an order-only prerequisite on all the targets
$(OBJdir): | $(targetd)

.PHONY: clean

clean:
	rm -rf ./$(TARGETD)/* ./results/*

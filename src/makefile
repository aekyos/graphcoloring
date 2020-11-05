OBJ := $(patsubst %.c,%.o,$(wildcard *.c))
##this variable lists all c files via wildcard and turns them into object files so
##that no manual list of object files to import is needed
build: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS0) -c $< -o ../$(OBJD)/$@

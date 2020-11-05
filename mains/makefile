SRC := $(wildcard *.c)
OBJ1 := $(SRC:.c=.o)
SOURCES_PATH = ../tads/
SOURCES1 = $(wildcard $(SOURCES_PATH)*.c)
######## Tipos de testeo. ########
TEST_NORMAL = -O3 $(SOURCES1)
TEST_DEBUG = -O0 -g $(SOURCES1)
TEST_AUTODEBUG = -O3 -g $(SOURCES1) $(DEBUG)

normal: $(OBJ1)

%.o: %.c
	$(CC) $(CFLAGS0) $(TEST_DEBUG) $< -o ../$(TARGETD)/$(subst main_for_,,$(subst .o,,$@))


object: $(SRC)
	$(CC) $(CFLAGS0) -c $(SRC)
	mv *.o ../bin

clean:
	rm *.o
# end

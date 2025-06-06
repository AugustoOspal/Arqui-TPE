include ../Makefile.inc

MODULE    = 0000-sampleCodeModule.bin
LDSCRIPT  = sampleCodeModule.ld

# buscamos lib.h en ./include y en UserLib/include
MY_CFLAGS = $(GCCFLAGS) -I./include -I./UserLib/include

# fuentes y objetos
USER_CSOURCES  = $(wildcard [^_]*.c)
USER_COBJECTS  = $(USER_CSOURCES:.c=-c.o)
USER_ASMSOURCES= $(wildcard *.asm)
USER_ASMOBJECTS= $(USER_ASMSOURCES:.asm=-asm.o)
LOADER_C       = _loader.c
LOADER_O       = _loader.o
ALL_OBJECTS    = $(LOADER_O) $(USER_COBJECTS) $(USER_ASMOBJECTS)

.PHONY: all clean
all: $(MODULE)

# 1) compila el loader
$(LOADER_O): $(LOADER_C)
	$(GCC) $(MY_CFLAGS) -c $< -o $@

# 2) compila .c de usuario
%-c.o: %.c
	$(GCC) $(MY_CFLAGS) -c $< -o $@

# 3) ensambla .asm de usuario
%-asm.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# 4) linkea con la lib que quedó en UserLib/libuserland.a
$(MODULE): $(ALL_OBJECTS) $(LDSCRIPT) UserLib/libuserland.a
	$(GCC) $(MY_CFLAGS) -T $(LDSCRIPT) \
	  $(ALL_OBJECTS) UserLib/libuserland.a \
	  -o ../$(MODULE) $(LDFLAGS)

clean:
	rm -rf $(LOADER_O) *-c.o *-asm.o ../$(MODULE)

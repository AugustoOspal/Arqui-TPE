include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
LDSCRIPT=sampleCodeModule.ld

# Archivos C de usuario (ej: sampleCodeModule.c)
# El patrón [^_]*.c excluye archivos que comienzan con '_', como _loader.c
USER_CSOURCES=$(wildcard [^_]*.c)
# Genera nombres de objeto como nombre-c.o
USER_COBJECTS=$(patsubst %.c,%-c.o,$(USER_CSOURCES))

# Archivos ASM de usuario (ej: sampleCodeModule.asm)
USER_ASMSOURCES=$(wildcard *.asm)
# Genera nombres de objeto como nombre-asm.o
USER_ASMOBJECTS=$(patsubst %.asm,%-asm.o,$(USER_ASMSOURCES))

# Archivo loader, tratado por separado, mantendrá el .o simple
LOADER_C=_loader.c
LOADER_O=$(_loader.c:.c=.o) # Sigue siendo _loader.o

# Todos los archivos objeto que formarán el módulo final
ALL_OBJECTS=$(sort $(LOADER_O) $(USER_COBJECTS) $(USER_ASMOBJECTS))

# Asegúrate de que ASM (ej. nasm) y ASMFLAGS (ej. -f elf64) estén definidos en ../Makefile.inc
# GCC, GCCFLAGS, LDFLAGS también deberían venir de ../Makefile.inc o definirse aquí.

all: $(MODULE)

# Regla para enlazar el módulo final
$(MODULE): $(ALL_OBJECTS) $(LDSCRIPT) Makefile
	$(GCC) $(GCCFLAGS) -T $(LDSCRIPT) $(ALL_OBJECTS) -o ../$(MODULE) $(LDFLAGS)

# Regla para compilar el _loader.c a objeto.
# Mantenemos _loader.o como nombre de objeto para el loader.
$(LOADER_O): $(LOADER_C) Makefile
	$(GCC) $(GCCFLAGS) -I./include -c $(LOADER_C) -o $(LOADER_O)

# Regla genérica para compilar archivos .c de usuario a objeto nombre-c.o
%-c.o: %.c Makefile
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

# Regla genérica para ensamblar archivos .asm a objeto nombre-asm.o
%-asm.o : %.asm Makefile
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *-c.o *-asm.o _loader.o ../$(MODULE) # Actualizado para limpiar los nuevos nombres de objeto

.PHONY: all clean

# #Original
# include ../Makefile.inc

# MODULE=0000-sampleCodeModule.bin
# SOURCES=$(wildcard [^_]*.c)

# all: $(MODULE)

# $(MODULE): $(SOURCES)
# 	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) -o ../$(MODULE)

# clean:
# 	rm -rf *.o

# .PHONY: all clean print
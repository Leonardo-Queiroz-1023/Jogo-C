# Nome do nosso executável
TARGET = jogo

# Compilador do seu MSYS2
CC = clang

# Bibliotecas (Raylib e Matemática)
LIBS = -lraylib -lm

all: $(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET).exe $(LIBS)

clean:
	rm -f $(TARGET).exe
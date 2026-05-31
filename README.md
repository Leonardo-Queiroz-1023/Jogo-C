# Defesa Celestial - Core Upgrade

Este é um jogo arcade desenvolvido em **C** utilizando a biblioteca **raylib**. O jogador tem o objetivo de defender uma base orbital de uma chuva de asteroides.

## 🛠️ Pré-requisitos

Para compilar e jogar, você precisa de algumas ferramentas instaladas no seu ambiente (preferencialmente utilizando **MSYS2** no Windows):

1. **Compilador C (clang):** O arquivo Makefile está configurado para usar o Clang.
2. **Make:** Utilitário para executar o Makefile e orquestrar a compilação.
3. **Raylib:** A biblioteca gráfica utilizada pelo jogo.

Você pode instalar tudo isso no MSYS2 (UCRT64) com os pacotes correspondentes.

## ⚙️ Como Compilar

1. Abra o seu terminal (ex: **MSYS2 UCRT64** ou terminal integrado do VS Code configurado).
2. Navegue até a pasta raiz do jogo (onde o `Makefile` se encontra).
3. Execute o comando:
   ```bash
   make
   ```
   Isso irá verificar qualquer dependência do arquivo fonte `main.c` e gerar o executável `jogo.exe`.

## 🚀 Como Jogar

Após a compilação bem servida, você pode executar o jogo com o seguinte comando no terminal:

```bash
./jogo.exe
```

*(Alternativamente, você pode dar dois cliques no `jogo.exe` direto pelo seu explorador de arquivos do Windows).*

**Comandos do jogo:**
* **Mouse (Mira):** Move a mira na tela.
* **Clique Esquerdo:** Dispara contra os asteroides.
* **S:** Abre a interface de registros para consultar suas pontuações e saúde atual.
* **Enter:** Inicia o jogo ou retorna aos menus principais.
* **Backspace:** Retorna para a tela anterior nos menus.

## 🧹 Limpeza (Opcional)

Se precisar recompilar tudo do zero ou limpar os executáveis gerados, você pode rodar:

```bash
make clean
```
Isso vai remover o arquivo `jogo.exe` e limpar a pasta do projeto.

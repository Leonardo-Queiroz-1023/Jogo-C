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

Após a compilação, você pode executar o jogo com o seguinte comando no terminal:

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

## 🎮 Recursos Implementados

* Tela inicial com acesso ao jogo e aos registros de score.
* Campo de batalha com estrelas animadas e chuva de asteroides.
* Mira controlada pelo mouse e disparos contra os asteroides.
* Sistema de colisão, pontuação, recorde e integridade da nave.
* Tela de game over e reinicialização da partida.
* Salvamento local das pontuações no arquivo `DADOS.txt`.

## ✅ Teste de Execução

O jogo foi compilado e executado com sucesso em **31 de maio de 2026**.

Durante o teste, foram verificados:

* Compilação do código sem erros.
* Inicialização da janela com a biblioteca raylib.
* Carregamento da textura dos asteroides.
* Exibição da tela inicial e inicialização do loop principal do jogo.
* Uso do desenho alternativo da nave quando o arquivo opcional `assets/nave.png` não está presente.

Na primeira execução, o arquivo `DADOS.txt` ainda não existe. Ele será utilizado para armazenar os scores após o encerramento das partidas.

## 📹 Demonstração

Assista à gravação de uma partida:

[▶️ Ver demonstração do jogo](demo/defesa-celestial-demo.mov)

## 🧹 Limpeza (Opcional)

Se precisar recompilar tudo do zero ou limpar os executáveis gerados, você pode rodar:

```bash
make clean
```
Isso vai remover o arquivo `jogo.exe` e limpar a pasta do projeto.

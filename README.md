# 🚢 **Batalha Naval – Projeto PIF 2025.2**

Projeto final da disciplina **Programação Imperativa e Funcional (PIF)** do curso de **Sistemas de Informação – CESAR School**.

---

## 📝 **1. Descrição**

Este projeto consiste na implementação do clássico jogo **Batalha Naval** em linguagem **C**, simulando uma partida entre um **jogador humano** e o **computador (CPU)**.

O foco acadêmico está na prática de conceitos essenciais e avançados da linguagem C:

- Manipulação de **ponteiros**
- Uso de **structs** para modelagem de dados
- **Alocação dinâmica** (`malloc` e `free`)
- Organização modular do código (arquivos `.h` e `.c`)
- Boas práticas de desenvolvimento em C

---

## 🧑‍💻 **2. Autores**

- **Maria Júlia Magalhães Ribeiro** – (mjmr@cesar.school)  
- **Jorge Tadeu Gomes da Silva Filho** – (jtgsf@cesar.school)

**Professor:** João Victor Tinoco

---

## 🛠️ **3. Tecnologias e Restrições**

- **Linguagem:** C (C99 ou superior)  
- **Bibliotecas permitidas:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`  
- **Restrições:**  
  - Não é permitido utilizar bibliotecas externas  
  - Não é permitida interface gráfica (GUI)  
  - Todo o jogo roda exclusivamente no terminal (**CLI**)

---

## 📂 **4. Estrutura de Diretórios**
...
.
├── Makefile            # Script de automação para compilação
├── README.md           # Documentação do projeto
└── src/                # Código-fonte
    ├── main.c          # Ponto de entrada da aplicação
    ├── board.c
    ├── board.h         # Estrutura e manipulação do tabuleiro
    ├── fleet.c
    ├── fleet.h         # Modelagem dos navios e da frota
    ├── game.c
    ├── game.h          # Regras, turnos e lógica do jogo
    ├── io.c
    ├── io.h            # Interações com o usuário (entrada/saída)
    ├── rnd.c
    └── rnd.h           # Funções de aleatoriedade
...

## ⚙️ **5. Funcionalidades Implementadas**

- **Modos de Posicionamento da Frota**
  - Manual (usuário escolhe posição e orientação)
  - Automático (CPU posiciona aleatoriamente)

- **Validação Completa de Regras**
  - Impede sobreposição de navios  
  - Garante posições válidas no tabuleiro

- **CPU com Inteligência Básica**
  - Algoritmo simples de disparos contra o jogador

- **Sistema de Representação Visual**
  - `O` → Água  
  - `X` → Acerto  
  - `S` → Navio

- **Relatório Final**
  - Estatísticas de precisão  
  - Estado final dos tabuleiros  
  - Vencedor da partida

---

## 🧠 **6. Decisões de Design**

### **1. Modularização e Separação de Responsabilidades**
- O módulo **`io`** trata exclusivamente da interação com o usuário.  
- O módulo **`game`** concentra toda a lógica do jogo.  
- O módulo **`board`** encapsula a estrutura interna da matriz, tratando o tabuleiro como um objeto opaco.

### **2. Gerenciamento de Memória**
- Todo o tabuleiro e frota são alocados dinamicamente.  
- A função `game_cleanup()` libera **toda** memória alocada, garantindo ausência de *memory leaks*.

### **3. Representação do Tabuleiro**
- A matriz 2D é linearizada em um vetor 1D:  
# Jogo da Batalha Naval - PIF 2025.2

Projeto final da disciplina de Programação Imperativa e Funcional (PIF) do Curso de Sistemas de Informação da CESAR School.

## 1. Descrição

Implementação do clássico jogo **Batalha Naval** em linguagem C. O projeto simula uma partida entre um jogador humano e o computador (CPU).

O foco acadêmico do projeto é o domínio de conceitos avançados da linguagem C, incluindo:
* Manipulação de **Ponteiros**.
* Uso de **Structs** para modelagem de dados.
* **Alocação Dinâmica de Memória** (`malloc` e `free`).
* Modularização de código (Header files e Source files).

## 2. Autores

* **Maria Júlia Magalhães Ribeiro** - (mjmr@cesar.school)
* **Jorge Tadeu Gomes da Silva Filho** - (jtgsf@cesar.school)

**Professor:** João Victor Tinoco

## 3. Tecnologias e Restrições

* **Linguagem:** C (C99 ou superior).
* **Bibliotecas Padrão:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`, `ctype.h`.
* **Restrições:** Proibido o uso de bibliotecas externas ou interfaces gráficas (GUI). Todo o jogo roda via terminal (CLI).

## 4.  Estrutura de Diretórios

O projeto foi organizado utilizando modularização. A estrutura abaixo facilita a compreensão:

```text
.
├── Makefile            # Script de automação para compilação
├── README.md           # Documentação do projeto
└── src/                # Código-fonte
    ├── main.c          # Ponto de entrada da aplicação
    ├── board.c         # Implementação do tabuleiro
    ├── board.h         # Definição das estruturas do tabuleiro
    ├── fleet.c         # Implementação da frota
    ├── fleet.h         # Modelagem dos navios
    ├── game.c          # Lógica principal e turnos
    ├── game.h          # Regras do jogo
    ├── io.c            # Interações com o usuário (telas)
    ├── io.h            # Cabeçalhos de entrada/saída
    ├── rnd.c           # Funções de aleatoriedade
    └── rnd.h           # Header de aleatoriedade
```
##  **5. Funcionalidades Implementadas**

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

##  **6. Decisões de Design**

### **1. Modularização e Separação de Responsabilidades**
- O módulo **`io`** trata exclusivamente da interação com o usuário.  
- O módulo **`game`** concentra toda a lógica do jogo.  
- O módulo **`board`** encapsula a estrutura interna da matriz, tratando o tabuleiro como um objeto opaco.

### **2. Gerenciamento de Memória**
- Todo o tabuleiro e frota são alocados dinamicamente.  
- A função `game_cleanup()` libera **toda** memória alocada, garantindo ausência de *memory leaks*.

### **3. Representação do Tabuleiro**
- A matriz 2D é linearizada em um vetor 1D:  

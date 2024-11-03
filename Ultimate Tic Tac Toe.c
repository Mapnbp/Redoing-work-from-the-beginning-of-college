// MATHEUS ARAUJO PINHEIRO 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

// Semelhante a estrutura original, mas agora guardamos quantas casas estao ocupadas
typedef struct {
	char jogo[3][3];
    int casasOcupadas;
}jogoDaVelha;

// Armazena a posição (linha, coluna) da jogada, e o score usado pela IA
typedef struct {
    int score;
    int position[2];
} MinimaxResult;

// Conjunto de funcoes meramente visuais, implementada abaixo da main para evitar poluicao visual do codigo
void print_menu_de_abertura();
void print_regras();
void print_configuracoes();
void print_configuracoes_pve();
void print_quadrante_de_jogadas();
void print_resultado(int algGanhou, int jogador, int modo);
void print_pos_PVE(int qPC, int quadrante, int jogada);

// Conjunto de funcoes que imprimem e controlam o tabuleiro
void esvaziar_tabuleiro(jogoDaVelha tabuleiro[]);
void print_tabmain(char secao[3][3]); 
void print_tabuleiro(jogoDaVelha tab[]);

// Conjunto de funcoes que realizam e verificam as jogadas
int faz_jogada(int vez, int jogada, int quadrante, jogoDaVelha tabuleiro[]);
int verifica_jogada(jogoDaVelha tab[], int tipo, int quadrante);

// Conjunto de funcoes PVE
int verifica_vitoria(jogoDaVelha tabuleiro[], int quadrante, char jogador);
int modo_facil(jogoDaVelha tabuleiro[], int *jogador);
int executa_jogada_PVE_normal(jogoDaVelha tabuleiro[], int quadrante);
int modo_normal(jogoDaVelha tabuleiro[], int *jogador);
int avaliar_controle_quadrante(jogoDaVelha tabuleiro[], char jogadorAtual);
int avaliar_heuristica(jogoDaVelha *tabuleiro, int quadrante, char jogadorAtual);
int avaliar_estado(jogoDaVelha *tabuleiro, int quadrante);
int modo_dificil(jogoDaVelha tabuleiro[], int *jogador);
MinimaxResult minimax(jogoDaVelha tabuleiro[], int profundidade, int alpha, int beta, int isMaximizing, int quadrante);
void executa_jogada_PVE_imp(int *quadrante, int *jogada, int A, jogoDaVelha tabuleiro[]);
int modo_impossivel(jogoDaVelha tabuleiro[], int *jogador);

int main () {
    int opcao, modo = 1, dificuldade = 0, quadrante, jogada, jogador;
    int algGanhou = 0, rodada = 0;
    int lixo;
    jogoDaVelha tabuleiro[10]; // Utilizaremos [0] como tabuleiro principal, assim como no codigo original
    srand(time(0));

    do{ // Menu do jogo, em loop ate que o jogador decida iniciar
        print_menu_de_abertura();
        scanf("%d", &opcao);
        system("cls");
        switch (opcao) {
            case 1: // Iniciar jogo
                break;
            case 2: // Ver as regras
                print_regras();
                scanf("%d", &lixo);
                system("cls");
                break;
            case 3: // Configuracoes de jogo
                print_configuracoes();
                scanf("%d", &modo);
                system("cls");
                if(modo == 2) {
                    print_configuracoes_pve();
                    scanf("%d", &dificuldade);
                    system("cls");
                }
                break;
            default: // Fecha o jogo
                return (-1);
        }
    } while(opcao != 1); // Fim do loop do Menu
    esvaziar_tabuleiro(tabuleiro);

    if(modo == 1) { // PVP
        print_tabuleiro(tabuleiro);
        printf("JOGO DA VELHA (Jogador x Jogador)\n\n");
        printf("Quem jogar primeiro eh o 'X' e o seguinte eh o 'O'\n");
        printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
        printf("JOGADOR 1, escolha um quadrante (jogo da velha interno) para comecar: ");
        scanf("%d", &quadrante);
        quadrante = verifica_jogada(tabuleiro, 1, quadrante);
        jogada = quadrante;

        while(rodada < 81 && algGanhou == 0) {
            if (rodada > 0) {
                quadrante = jogada; // O quadrante eh definido pela ultima jogada feita.
                quadrante = verifica_jogada(tabuleiro, 2, quadrante);
                printf("A jogada sera feita no quadrante %d\n", quadrante);
            }

            // Define qual jogador esta jogando.
            jogador = (rodada % 2) + 1;
            printf("Jogador %d, escolha sua jogada: ", jogador);
            scanf("%d", &jogada);
            jogada = faz_jogada(jogador, jogada, quadrante, tabuleiro);

            algGanhou = verifica_jogada(tabuleiro, 3, 0);
            system ("cls");
            printf("JOGO DA VELHA (Jogador x Jogador)\n\n");
            printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
            print_tabuleiro(tabuleiro);
            rodada++;
        }

    } else { //PVE
        switch (dificuldade){
        case 1: // Facil
            algGanhou = modo_facil(tabuleiro, &jogador);
            break;
        case 2: // Normal
            algGanhou = modo_normal(tabuleiro, &jogador);
            break;
        case 3: // Dificil
            algGanhou = modo_dificil(tabuleiro, &jogador);
            break;
        default: // Impossivel
            algGanhou = modo_impossivel(tabuleiro, &jogador);
            break;
        }
    }
    print_resultado(algGanhou, jogador, modo);

    return (0);
}

// Uma funcao separada para executar a jogada, evitando repeticoes no codigo, e deixando a main mais limpa
int faz_jogada(int vez, int jogada, int quadrante, jogoDaVelha tabuleiro[]){
    int linha = (jogada - 1) / 3, coluna = (jogada - 1) % 3;

	// Verifica se a jogada eh valida.
	while (jogada < 1 || jogada > 9 || tabuleiro[quadrante].jogo[linha][coluna] != ' ') {
		printf("Esta jogada eh invalida, escolha outra: ");
		scanf("%d", &jogada);
		linha = (jogada - 1) / 3;
        coluna = (jogada - 1) % 3;
	}
	if (vez == 1) { //Faz a jogada escolhida pelo jogador 1
		tabuleiro[quadrante].jogo[linha][coluna] = 'X';
        tabuleiro[quadrante].casasOcupadas++;
	}
	else { //Faz a jogada escolhida pelo jogador 2
		tabuleiro[quadrante].jogo[linha][coluna] = 'O';
        tabuleiro[quadrante].casasOcupadas++;
	}

    linha = (quadrante - 1) / 3;
    coluna = (quadrante - 1) % 3;
    // Caso tenha sido ganho, coloca no tabuleiro geral.
    if (verifica_jogada(tabuleiro, 3, quadrante) == 1 && tabuleiro[0].jogo[linha][coluna] == ' ') {
        tabuleiro[0].jogo[linha][coluna] = (vez == 1) ? 'X' : 'O';
    }
    // Caso nao tenha sido ganho, verifica se deu empate.
    if (tabuleiro[0].jogo[linha][coluna] == ' ' && tabuleiro[quadrante].casasOcupadas == 9) {
        tabuleiro[0].jogo[linha][coluna] = '#';
    }

    return (jogada);
}

int verifica_jogada(jogoDaVelha tab[], int tipo, int quadrante) {
    int verificador;

    switch (tipo) {
    case 1: // Verifica se o quadrante eh valido
        while (quadrante < 1 || quadrante > 9) {
            printf("Escolha outro quadrante: ");
            scanf("%d", &quadrante);
        }
        verificador = quadrante;
        break;
    case 2: // Verifica se o quadrante esta cheio
        while (tab[quadrante].casasOcupadas == 9){
            printf("Este quadrante esta cheio, escolha outro para jogar: ");
			scanf("%d", &quadrante);
        }
        verificador = quadrante;
        break;
    case 3: // Verifica se um quadrante foi ganho
        for (int i = 0; i < 3; i++) { // Verifica linhas e colunas
            if ((tab[quadrante].jogo[i][0] != ' ' && tab[quadrante].jogo[i][0] == tab[quadrante].jogo[i][1] && tab[quadrante].jogo[i][0] == tab[quadrante].jogo[i][2]) 
                || (tab[quadrante].jogo[0][i] != ' ' && tab[quadrante].jogo[0][i] == tab[quadrante].jogo[1][i] && tab[quadrante].jogo[0][i] == tab[quadrante].jogo[2][i])) {
                return 1;
            }
        }
        if (tab[quadrante].jogo[1][1] != ' ') { // Verifica diagonais
            if ((tab[quadrante].jogo[0][0] == tab[quadrante].jogo[1][1] && tab[quadrante].jogo[0][0] == tab[quadrante].jogo[2][2]) ||
                (tab[quadrante].jogo[0][2] == tab[quadrante].jogo[1][1] && tab[quadrante].jogo[0][2] == tab[quadrante].jogo[2][0])) {
                return 1;
            }
        }
        verificador = 0;
    default:
        break;
    }

    return (verificador);
}

// Na epoca nao tinha conhecimento da biblioteca string.h e nem de suas funcoes, agora podemos fazer isso de maneira mais eficiente e elegante
void esvaziar_tabuleiro(jogoDaVelha tabuleiro[]){
    for (int i = 0; i < 10; i++) {
        memset(tabuleiro[i].jogo, ' ', sizeof(tabuleiro[i].jogo));
        tabuleiro[i].casasOcupadas = 0;
    }
    return;
}

// Funcao auxiliar para imprimir tabuleiro principal
void print_tabmain(char secao[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", secao[i][0], secao[i][1], secao[i][2]);
        if (i < 2) {
            printf("---+---+---\n");
        }
    }
    printf("\n\n");
}

// Funcao que imprime o tabuleiro inteiro em que o jogo esta acontecendo
void print_tabuleiro(jogoDaVelha tab[]){
    print_quadrante_de_jogadas();
    printf("Tabuleiro de quadrantes:\n\n");
    print_tabmain(tab[0].jogo);
    for (int i = 1; i < 10; i += 3) {
        for (int j = 0; j < 3; j++) { 
            printf(" %c | %c | %c      ", tab[i].jogo[j][0], tab[i].jogo[j][1], tab[i].jogo[j][2]);
            printf(" %c | %c | %c      ", tab[i + 1].jogo[j][0], tab[i + 1].jogo[j][1], tab[i + 1].jogo[j][2]);
            printf(" %c | %c | %c \n", tab[i + 2].jogo[j][0], tab[i + 2].jogo[j][1], tab[i + 2].jogo[j][2]);
            if (j < 2) {
                printf("---+---+---     ---+---+---     ---+---+---\n");
            }
        }
        printf("\n\n\n");
    }
}

// Joga baseado em Aleatoriedade
int modo_facil(jogoDaVelha tabuleiro[], int *jogador) {
    int rodada = 1, qPC, algGanhou = 0;
    int quadrante = 5, jogada = 5;
    tabuleiro[quadrante].jogo[1][1] = 'X';
    tabuleiro[quadrante].casasOcupadas++;

    system("cls");
    printf("JOGO DA VELHA (Jogador x Computador)\n\n");
    printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
    printf("Voce escolheu o modo facil\n");
    print_tabuleiro(tabuleiro);
    while (rodada < 81 && algGanhou == 0) {
        *jogador = (rodada % 2) + 1;
        qPC = quadrante;
        quadrante = jogada;
        
        if (*jogador == 1) {
            while(tabuleiro[quadrante].casasOcupadas == 9) {
                quadrante = ((quadrante + 1) % 9) + 1;
            }
            do {
                jogada = (rand() % 9) + 1;
            } while(tabuleiro[quadrante].jogo[(jogada - 1) / 3][(jogada - 1) % 3] != ' ');
            jogada = faz_jogada(1, jogada, quadrante, tabuleiro);
        } else {
            quadrante = verifica_jogada(tabuleiro, 2, quadrante);
            print_pos_PVE(qPC, quadrante, jogada);
            scanf("%d", &jogada);
            jogada = faz_jogada(*jogador, jogada, quadrante, tabuleiro);
        }
        algGanhou = verifica_jogada(tabuleiro, 3, 0);
        system("cls");
        print_tabuleiro(tabuleiro);
        rodada++;
    }
    return(algGanhou);
}

// Funcao para verificar se ha vitoria em um quadrante
int verifica_vitoria(jogoDaVelha tabuleiro[], int quadrante, char jogador) {
    for (int i = 0; i < 3; i++) {
        if ((tabuleiro[quadrante].jogo[i][0] == jogador) && (tabuleiro[quadrante].jogo[i][1] == jogador) && (tabuleiro[quadrante].jogo[i][2] == jogador)) return 1;
        if ((tabuleiro[quadrante].jogo[0][i] == jogador) && (tabuleiro[quadrante].jogo[1][i] == jogador) && (tabuleiro[quadrante].jogo[2][i] == jogador)) return 1;
    }
    if ((tabuleiro[quadrante].jogo[0][0] == jogador) && (tabuleiro[quadrante].jogo[1][1] == jogador) && (tabuleiro[quadrante].jogo[2][2] == jogador)) return 1;
    if ((tabuleiro[quadrante].jogo[0][2] == jogador) && (tabuleiro[quadrante].jogo[1][1] == jogador) && (tabuleiro[quadrante].jogo[2][0] == jogador)) return 1;
    return 0;
}

// Funcao para a fazer uma jogada
int executa_jogada_PVE_normal(jogoDaVelha tabuleiro[], int quadrante) { 
    int jogada;
    int linha, coluna;

    for (jogada = 1; jogada < 10; jogada++) { // Tentativa de vitoria
        linha = (jogada - 1) / 3;
        coluna = (jogada - 1) % 3;
        if (tabuleiro[quadrante].jogo[linha][coluna] == ' ') {
            tabuleiro[quadrante].jogo[linha][coluna] = 'X';
            if (verifica_vitoria(tabuleiro, quadrante, 'X')) return (jogada);
            tabuleiro[quadrante].jogo[linha][coluna] = ' ';
        }
    }
    for (jogada = 1; jogada < 10; jogada++) { // Tentativa de bloqueio
        linha = (jogada - 1) / 3;
        coluna = (jogada - 1) % 3;
        if (tabuleiro[quadrante].jogo[linha][coluna] == ' ') {
            tabuleiro[quadrante].jogo[linha][coluna] = 'O';
            if (verifica_vitoria(tabuleiro, quadrante, 'O')) {
                tabuleiro[quadrante].jogo[linha][coluna] = 'X';
                return (jogada);
            }
            tabuleiro[quadrante].jogo[linha][coluna] = ' ';
        }
    }
    do { // Escolhe aleatoriamente
        jogada = (rand() % 9) + 1;
    } while(tabuleiro[quadrante].jogo[(jogada - 1) / 3][(jogada - 1) % 3] != ' ');
    tabuleiro[quadrante].jogo[(jogada - 1) / 3][(jogada - 1) % 3] = 'X';

    return (jogada);
}

int modo_normal(jogoDaVelha tabuleiro[], int *jogador) {
    int rodada = 1, qPC, algGanhou = 0;
    int quadrante = 5, jogada = 5;
    tabuleiro[quadrante].jogo[1][1] = 'X';
    tabuleiro[quadrante].casasOcupadas += 1;

    system("cls");
    printf("JOGO DA VELHA (Jogador x Computador)\n\n");
    printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
    printf("Voce escolheu o modo normal\n");
    print_tabuleiro(tabuleiro);
    while (rodada < 81 && algGanhou == 0) {
        *jogador = (rodada % 2) + 1;
        qPC = quadrante;
        quadrante = jogada;
        
        if (*jogador == 1) {
            while(tabuleiro[quadrante].casasOcupadas == 9) {
                quadrante = ((quadrante + 1) % 9) + 1;
            }
            jogada = executa_jogada_PVE_normal(tabuleiro, quadrante);
            tabuleiro[quadrante].casasOcupadas += 1;
            if (verifica_jogada(tabuleiro, 3, quadrante) == 1 && tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] == ' ') {
                tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] = (*jogador == 1) ? 'X' : 'O';
            }
            if (tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] == ' ' && tabuleiro[quadrante].casasOcupadas == 9) {
                tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] = '#';
            }
        } else {
            quadrante = verifica_jogada(tabuleiro, 2, quadrante);
            print_pos_PVE(qPC, quadrante, jogada);
            scanf("%d", &jogada);
            jogada = faz_jogada(*jogador, jogada, quadrante, tabuleiro);
        }
        algGanhou = verifica_jogada(tabuleiro, 3, 0);
        system("cls");
        print_tabuleiro(tabuleiro);
        rodada++;
    }
    return(algGanhou);
}

// Avalia o controle do quadrante principal
int avaliar_controle_quadrante(jogoDaVelha tabuleiro[], char jogadorAtual) {
    int diagPrincipal = 0, diagSecundaria = 0, score = 0;
    char oponente = (jogadorAtual == 'X') ? 'O' : 'X';
    int pesoQuadrante[3][3] = {
        {6, 4, 6}, {4, 18, 4}, {6, 4, 6}
    };

    for (int i = 0; i < 3; i++) { // Avalia o controle de cada quadrante do tabuleiro principal
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[0].jogo[i][j] == jogadorAtual) {
                score += pesoQuadrante[i][j]; // Adiciona peso por controle de quadrante
            } else if (tabuleiro[0].jogo[i][j] == oponente) {
                score -= pesoQuadrante[i][j]; // Subtrai pontuação se o oponente controla o quadrante
            }
        }
    }
    for (int i = 0; i < 3; i++) { // Avalia controle de linhas e colunas no tabuleiro principal
        int linhaScore = 0, colunaScore = 0;
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[0].jogo[i][j] == jogadorAtual) {
                linhaScore += 4;
            } else if (tabuleiro[0].jogo[i][j] == oponente) {
                linhaScore -= 4;
            }
            if (tabuleiro[0].jogo[j][i] == jogadorAtual) {
                colunaScore += 4;
            } else if (tabuleiro[0].jogo[j][i] == oponente) {
                colunaScore -= 4;
            }
        }
        score += linhaScore + colunaScore;
    }
    for (int i = 0; i < 3; i++) { // Avalia diagonais no tabuleiro principal
        if (tabuleiro[0].jogo[i][i] == jogadorAtual) {
            diagPrincipal += 6;
        } else if (tabuleiro[0].jogo[i][i] == oponente) {
            diagPrincipal -= 6;
        }

        if (tabuleiro[0].jogo[i][2 - i] == jogadorAtual) {
            diagSecundaria += 6;
        } else if (tabuleiro[0].jogo[i][2 - i] == oponente) {
            diagSecundaria -= 6;
        }
    }
    score += diagPrincipal + diagSecundaria;

    return score;
}

// Funcao de avaliacao completa
int avaliar_heuristica(jogoDaVelha *tabuleiro, int quadrante, char jogadorAtual) {
    int score = avaliar_controle_quadrante(tabuleiro, jogadorAtual);

    if (tabuleiro[quadrante].jogo[1][1] == jogadorAtual) { // Bonus por controle de centro no quadrante
        score += 18;
    }
    for (int i = 0; i < 3; i++) { // Avaliação de linhas, colunas
        if (tabuleiro[quadrante].jogo[i][0] == jogadorAtual && tabuleiro[quadrante].jogo[i][1] == jogadorAtual)
            score += 4;
        if (tabuleiro[quadrante].jogo[0][i] == jogadorAtual && tabuleiro[quadrante].jogo[1][i] == jogadorAtual)
            score += 4;
    }
    if (tabuleiro[quadrante].jogo[0][0] == jogadorAtual && tabuleiro[quadrante].jogo[1][1] == jogadorAtual) { // Diagonais
        score += 6;
    }

    return score;
}

int avaliar_estado(jogoDaVelha *tabuleiro, int quadrante) {
    if (verifica_vitoria(tabuleiro, quadrante, 'X')) {
        return 10; 
    } else if (verifica_vitoria(tabuleiro, quadrante, 'O')) {
        return -10;
    }
    return 0;
}

// Funcao minimax (IA)
MinimaxResult minimax(jogoDaVelha tabuleiro[], int profundidade, int alpha, int beta, int isMaximizing, int quadrante) {
    MinimaxResult resultado;
    resultado.score = isMaximizing ? -(INT_MAX / 2) : (INT_MAX / 2);
    resultado.position[0] = -1;
    resultado.position[1] = -1;
    int estado = avaliar_estado(tabuleiro, quadrante);
    int movimentos[9][2], numMovimentos = 0; // Lista e quantidade de movimentos possíveis

    if (estado != 0 || profundidade == 0) {
        resultado.score = estado != 0 ? estado : avaliar_heuristica(tabuleiro, quadrante, isMaximizing ? 'X' : 'O');
        return resultado;
    }
    for (int i = 0; i < 3; i++) { // Coleta todos os movimentos possíveis
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[quadrante].jogo[i][j] == ' ') {
                movimentos[numMovimentos][0] = i;
                movimentos[numMovimentos][1] = j;
                numMovimentos++;
            }
        }
    }
    for (int m = 0; m < numMovimentos; m++) { // Avalia cada movimento
        int i = movimentos[m][0];
        int j = movimentos[m][1];

        for (char simbolo = isMaximizing ? 'X' : 'O'; ; simbolo = (simbolo == 'X' ? 'O' : 'X')) { // Tentativa de vitoria ou bloqueio
            tabuleiro[quadrante].jogo[i][j] = simbolo;
            if (verifica_vitoria(tabuleiro, quadrante, simbolo)) {
                resultado.score = (simbolo == 'X') ? INT_MAX : -INT_MAX;
                resultado.position[0] = i;
                resultado.position[1] = j;
                tabuleiro[quadrante].jogo[i][j] = ' ';
                return resultado;
            }
            if (simbolo == (isMaximizing ? 'O' : 'X')) break;
        }
        tabuleiro[quadrante].jogo[i][j] = isMaximizing ? 'X' : 'O';
        MinimaxResult res = minimax(tabuleiro, profundidade - 1, alpha, beta, !isMaximizing, quadrante);
        tabuleiro[quadrante].jogo[i][j] = ' '; 
        if (isMaximizing) {
            if (res.score > resultado.score) { // Atualiza o resultado com base na pontuação de maximizacao ou minimizacao
                resultado.score = res.score;
                resultado.position[0] = i;
                resultado.position[1] = j;
            }
            alpha = (alpha > resultado.score) ? alpha : resultado.score;
        } else {
            if (res.score < resultado.score) {
                resultado.score = res.score;
                resultado.position[0] = i;
                resultado.position[1] = j;
            }
            beta = (beta < resultado.score) ? beta : resultado.score;
        }
        if (beta <= alpha) break; // Poda alpha-beta
    }

    return resultado;
}

int modo_dificil(jogoDaVelha tabuleiro[], int *jogador) {
    int rodada = 1, qPC, algGanhou = 0;
    int quadrante = 5, jogada = 5;
    tabuleiro[quadrante].jogo[1][1] = 'X';
    tabuleiro[quadrante].casasOcupadas++;

    system("cls");
    printf("JOGO DA VELHA (Jogador x Computador)\n\n");
    printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
    printf("Voce escolheu o modo facil\n");
    print_tabuleiro(tabuleiro);
    while (rodada < 81 && algGanhou == 0) {
        *jogador = (rodada % 2) + 1;
        qPC = quadrante;
        quadrante = jogada;
        if (*jogador == 1) {
            while(tabuleiro[quadrante].casasOcupadas == 9) {
                quadrante = ((quadrante + 1) % 9) + 1;
            }
            MinimaxResult melhorJogada = minimax(tabuleiro, 7, -(INT_MAX/2), INT_MAX/2, 1, quadrante);
            if( melhorJogada.position[0] == -1) { // Seleciona uma posicao vazia arbitrariamente 
                if (tabuleiro[quadrante].casasOcupadas == 9) {
                    do {
                        quadrante = (rand() % 9) + 1;
                    } while (tabuleiro[quadrante].casasOcupadas == 9);
                }
                for (int i = 0; i < 3; i++) { 
                    for (int j = 0; j < 3; j++) {
                        if (tabuleiro[quadrante].jogo[i][j] == ' ') {
                            melhorJogada.position[0] = i;
                            melhorJogada.position[1] = j;
                        }
                    }
                }
            }
            tabuleiro[quadrante].jogo[melhorJogada.position[0]][melhorJogada.position[1]] = 'X';
            tabuleiro[quadrante].casasOcupadas++;
            jogada = (melhorJogada.position[0] * 3 + melhorJogada.position[1]) + 1;
            if (verifica_jogada(tabuleiro, 3, quadrante) == 1 && tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] == ' ') {
                tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] = (*jogador == 1) ? 'X' : 'O';
            }
            if (tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] == ' ' && tabuleiro[quadrante].casasOcupadas == 9) {
                tabuleiro[0].jogo[(quadrante - 1) / 3][(quadrante - 1) % 3] = '#';
            }
        } else {
            quadrante = verifica_jogada(tabuleiro, 2, quadrante);
            print_pos_PVE(qPC, quadrante, jogada);
            scanf("%d", &jogada);
            jogada = faz_jogada(*jogador, jogada, quadrante, tabuleiro);
        }
        algGanhou = verifica_jogada(tabuleiro, 3, 0);
        system("cls");
        print_tabuleiro(tabuleiro);
        rodada++;
    }
    return(algGanhou);
}

// Realiza a jogada  do computador no modo impossivel apos a 16a rodada
void executa_jogada_PVE_imp(int *quadrante, int *jogada, int A, jogoDaVelha tabuleiro[]) {
    if (*jogada == 5) {
        *quadrante = 10 - A;  // Escolhe o quadrante oposto a A
        *jogada = A;
    } else {
        *jogada = (tabuleiro[*quadrante].jogo[(A - 1) / 3][(A - 1) % 3] == ' ') ? A : 10 - A;
    }
    *jogada = faz_jogada(1, *jogada, *quadrante, tabuleiro);
}

int modo_impossivel(jogoDaVelha tabuleiro[], int *jogador) {
    int rodada = 1, qPC, A, algGanhou = 0;
    int quadrante = 5, jogada = 5;
    tabuleiro[quadrante].jogo[1][1] = 'X';
    tabuleiro[quadrante].casasOcupadas++;

    system("cls");
    printf("JOGO DA VELHA (Jogador x Computador)\n\n");
    printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
    printf("Boa sorte (mesmo que nem ela possa te ajudar)\n");
    print_tabuleiro(tabuleiro);

    while (rodada < 81 && algGanhou == 0) {
        *jogador = (rodada % 2) + 1;
        qPC = quadrante;
        quadrante = jogada;
        quadrante = verifica_jogada(tabuleiro, 2, quadrante);

        if (rodada < 16) {
            if (*jogador == 1) {
                jogada = 5;
                tabuleiro[quadrante].jogo[1][1] = 'X';
            } else {
                print_pos_PVE(qPC, quadrante, jogada);
                scanf("%d", &jogada);
                jogada = faz_jogada(*jogador, jogada, quadrante, tabuleiro);
            }
        } 
        if (rodada == 16) {
            quadrante = jogada;
            A = jogada;
            jogada = faz_jogada(*jogador, jogada, quadrante, tabuleiro);
            system("cls");
        } else if (rodada > 16) {
            if (*jogador == 1) {
                executa_jogada_PVE_imp(&quadrante, &jogada, A, tabuleiro);
            } else {
                print_pos_PVE(qPC, quadrante, jogada);
                scanf("%d", &jogada);
                jogada = faz_jogada(*jogador, jogada, quadrante, tabuleiro);
            }
            algGanhou = verifica_jogada(tabuleiro, 3, 0);
        }
        
        print_tabuleiro(tabuleiro);
        rodada++;
    }
    return(algGanhou);
}

// Imprime o menu de Abertura
void print_menu_de_abertura() {
    printf("***************************************\n");
    printf("*         Ultimate TicTacToe          *\n");
    printf("***************************************\n");
    printf("\nEscolha uma das opcoes abaixo:\n");
    printf("---------------------------------------\n");
    printf("1 - Iniciar Jogo - Escolha o modo em 3\n");
    printf("2 - Regras\n");
    printf("3 - Configuracoes\n");
    printf("4 - Sair\n");
    printf("---------------------------------------\n");
    printf("\nDigite sua escolha: ");
    return;
}

//Imprime as Regras do jogo
void print_regras(){
    printf("Ultimate Tic-Tac-Toe - Regras Resumidas\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("O tabuleiro principal tem 9 sub-tabuleiros de jogo da velha (3x3).\n");
    printf("O objetivo eh ganhar tres sub-tabuleiros em linha (horizontal, vertical ou diagonal).\n");
    printf("O primeiro jogador pode jogar em qualquer casa.\n");
    printf("A jogada de um jogador determina onde o proximo deve jogar.\n");
    printf("Vence um sub-tabuleiro quem fizer tres em linha nele.\n");
    printf("Se o sub-tabuleiro estiver vencido ou cheio, o jogador pode escolher outro.\n");
    printf("O jogo termina quando alguem vence tres sub-tabuleiros em linha no tabuleiro principal.\n");
    printf("Caso todos estejam cheios e ninguem venca, o jogo termina em empate.\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("Digite qualquer numero para voltar ao menu: \n");
    return;
}

void print_configuracoes() {
    printf("Selecione o modo de jogo:\n");
    printf("----------------------------------\n");
    printf("1. PvP (Player vs Player)\n");
    printf("2. PvE (Player vs Environment)\n");
    printf("----------------------------------\n");
    printf("Digite o numero da sua escolha: ");
    return;
}

void print_configuracoes_pve(){
    printf("\nVoce escolheu o modo PvE!\n");
    printf("Selecione o nivel de dificuldade:\n");
    printf("----------------------------------\n");
    printf("1. Facil\n");
    printf("2. Normal\n");
    printf("3. Dificil\n");
    printf("4. Impossivel\n");
    printf("----------------------------------\n");
    printf("Digite o numero da sua escolha: ");
    return;
}

void print_quadrante_de_jogadas() {
    printf("Utilize esse padrao de coordenadas para escolher sua jogada em cada quadrante:\n\n");
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n\n");
    return;
}

void print_resultado(int algGanhou, int jogador, int modo) {
    if (modo == 1){
        if (algGanhou == 1) {
            printf("                       _                     \n");
            printf("                      | |                    \n");
            printf(" _ __   __ _ _ __ __ _| |__   ___ _ __  ___  \n");
            printf("| '_ | / _` | '__/ _` | '_ | / _ | '_ |/ __| \n");
            printf("| |_) | (_| | | | (_| | |_) |  __/ | | |__ | \n");
            printf("| .__/ |__,_|_|  |__,_|_.__/ |___|_| |_|___/ \n");
            printf("| |       JOGADOR %d, VOCE GANHOU                                       \n", jogador);
            printf("|_|                                          \n");
        }
    } else if(modo == 2) {
        if (algGanhou == 1 && jogador == 2) {
            printf("                       _                     \n");
            printf("                      | |                    \n");
            printf(" _ __   __ _ _ __ __ _| |__   ___ _ __  ___  \n");
            printf("| '_ | / _` | '__/ _` | '_ | / _ | '_ |/ __| \n");
            printf("| |_) | (_| | | | (_| | |_) |  __/ | | |__ | \n");
            printf("| .__/ |__,_|_|  |__,_|_.__/ |___|_| |_|___/ \n");
            printf("| |                                          \n");
            printf("|_|                                          \n");
        } else {
            printf("                                           _            \n");
            printf("                                          | |           \n");
            printf(" __   _____   ___ ___   _ __   ___ _ __ __| | ___ _   _ \n");
            printf(" | | / | _ | / __/ _ | | '_ | / _ | '__/ _` |/ _ | | | |\n");
            printf("  | V | (_) | (_|  __/ | |_) |  __/ | | (_| |  __/ |_| |\n");
            printf("   |_| |___| |___|___| | .__/ |___|_|  |__,_||___||__,_|\n");
            printf("                       | |                              \n");
            printf("                       |_|                              \n");
        }
    }
    else {
        printf("                             _        \n");
        printf("                            | |       \n");
        printf("   ___ _ __ ___  _ __   __ _| |_ ___  \n");
        printf("  / _ | '_ ` _ || '_ | / _` | __/ _ | \n");
        printf(" |  __/ | | | | | |_) | (_| | ||  __/ \n");
        printf("  |___|_| |_| |_| .__/ |__,_|_| |___| \n");
        printf("                | |                   \n");
        printf("                |_|                   \n");
    }
    return;
}

void print_pos_PVE(int qPC, int quadrante, int jogada) {
    printf("O Computador jogou no quadrante %d e casa %d\n", qPC, jogada);
    printf("A jogada sera feita no quadrante %d\n", quadrante);
    printf("JOGADOR, escolha sua jogada: ");
    return;
}
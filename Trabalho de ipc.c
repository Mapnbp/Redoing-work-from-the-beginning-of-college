// ARLEN TOJAL DE LUCENA
// MATHEUS ARAUJO PINHEIRO 

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char jogo[3][3];
}jogo_da_velha;

// Funcao que recebe o tabuleiro e imprime na tela a legenda, o tabuleiro de quadrantes e o tabuleiro geral.
void exibir_tabuleiro (jogo_da_velha *tab) {
	printf("Utilize esse padrao de coordenadas para escolher sua jogada em cada quadrante:\n\n");
    printf(" 1 | 2 | 3 \n");
    printf("---+---+---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---+---+---\n");
    printf(" 7 | 8 | 9 \n\n");

    // Mostra os quadrantes atualizados.
    printf("Tabuleiro de quadrantes:\n\n");
    printf(" %c | %c | %c \n", tab[0].jogo[0][0], tab[0].jogo[0][1], tab[0].jogo[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", tab[0].jogo[1][0], tab[0].jogo[1][1], tab[0].jogo[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n\n", tab[0].jogo[2][0], tab[0].jogo[2][1], tab[0].jogo[2][2]);

    // Mostra o tabuleiro atualizado.
    printf("Tabuleiro geral:\n\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n", tab[1].jogo[0][0], tab[1].jogo[0][1], tab[1].jogo[0][2], tab[2].jogo[0][0], tab[2].jogo[0][1], tab[2].jogo[0][2], tab[3].jogo[0][0], tab[3].jogo[0][1], tab[3].jogo[0][2]);
    printf("---+---+---     ---+---+---     ---+---+---\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n", tab[1].jogo[1][0], tab[1].jogo[1][1], tab[1].jogo[1][2], tab[2].jogo[1][0], tab[2].jogo[1][1], tab[2].jogo[1][2], tab[3].jogo[1][0], tab[3].jogo[1][1], tab[3].jogo[1][2]);
    printf("---+---+---     ---+---+---     ---+---+---\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n\n\n\n", tab[1].jogo[2][0], tab[1].jogo[2][1], tab[1].jogo[2][2], tab[2].jogo[2][0], tab[2].jogo[2][1], tab[2].jogo[2][2], tab[3].jogo[2][0], tab[3].jogo[2][1], tab[3].jogo[2][2]);
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n", tab[4].jogo[0][0], tab[4].jogo[0][1], tab[4].jogo[0][2], tab[5].jogo[0][0], tab[5].jogo[0][1], tab[5].jogo[0][2], tab[6].jogo[0][0], tab[6].jogo[0][1], tab[6].jogo[0][2]);
    printf("---+---+---     ---+---+---     ---+---+---\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n", tab[4].jogo[1][0], tab[4].jogo[1][1], tab[4].jogo[1][2], tab[5].jogo[1][0], tab[5].jogo[1][1], tab[5].jogo[1][2], tab[6].jogo[1][0], tab[6].jogo[1][1], tab[6].jogo[1][2]);
    printf("---+---+---     ---+---+---     ---+---+---\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n\n\n\n", tab[4].jogo[2][0], tab[4].jogo[2][1], tab[4].jogo[2][2], tab[5].jogo[2][0], tab[5].jogo[2][1], tab[5].jogo[2][2], tab[6].jogo[2][0], tab[6].jogo[2][1], tab[6].jogo[2][2]);
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n", tab[7].jogo[0][0], tab[7].jogo[0][1], tab[7].jogo[0][2], tab[8].jogo[0][0], tab[8].jogo[0][1], tab[8].jogo[0][2], tab[9].jogo[0][0], tab[9].jogo[0][1], tab[9].jogo[0][2]);
    printf("---+---+---     ---+---+---     ---+---+---\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n", tab[7].jogo[1][0], tab[7].jogo[1][1], tab[7].jogo[1][2], tab[8].jogo[1][0], tab[8].jogo[1][1], tab[8].jogo[1][2], tab[9].jogo[1][0], tab[9].jogo[1][1], tab[9].jogo[1][2]);
    printf("---+---+---     ---+---+---     ---+---+---\n");
    printf(" %c | %c | %c       %c | %c | %c       %c | %c | %c \n\n\n\n", tab[7].jogo[2][0], tab[7].jogo[2][1], tab[7].jogo[2][2], tab[8].jogo[2][0], tab[8].jogo[2][1], tab[8].jogo[2][2], tab[9].jogo[2][0], tab[9].jogo[2][1], tab[9].jogo[2][2]);

    return;
}

// Funcao que recebe o vetor tabuleiro e o quadrante, verifica se ele esta cheio e devolve 0 ou 1 (se ele nao estiver ou se ele estiver, respectivamente).
int verificar_quadrante_cheio (jogo_da_velha *tab, int qdrt) {
	int i, j, casas_ocupadas;

	for (i = 0, casas_ocupadas = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (tab[qdrt].jogo[i][j] != ' ') {
				casas_ocupadas++;
			}
		}
	}

	if (casas_ocupadas == 9) {
		return 1;
	}
	return 0;
}

// Funcao que recebe o vetor tabuleiro e o quadrante, verifica se ele foi ganho ou empatado e coloca o resultado na casa correspondente do tab[0] (tabuleiro geral).
void verificar_quadrante (jogo_da_velha *tab, int qdrt, int jogador)  {
	int ganho, verificador, i;

	ganho = 0;

	// Verifica se fechou alguma linha ou coluna.
	for (i = 0; (i < 3) && (ganho == 0); i++) {
		if ((tab[qdrt].jogo[i][0] != ' ' && tab[qdrt].jogo[i][0] == tab[qdrt].jogo[i][1] && tab[qdrt].jogo[i][0] == tab[qdrt].jogo[i][2]) || (tab[qdrt].jogo[0][i] != ' ' && tab[qdrt].jogo[0][i] == tab[qdrt].jogo[1][i] && tab[qdrt].jogo[0][i] == tab[qdrt].jogo[2][i])) {
			ganho = 1;

		}
	}

	// Verifica se fechou alguma diagonal.
	if (tab[qdrt].jogo[1][1] != ' ') {
		if ((tab[qdrt].jogo[0][0] == tab[qdrt].jogo[1][1] && tab[qdrt].jogo[0][0] == tab[qdrt].jogo[2][2]) || (tab[qdrt].jogo[0][2] == tab[qdrt].jogo[1][1] && tab[qdrt].jogo[0][2] == tab[qdrt].jogo[2][0])) {
			ganho = 1;
		}
	}

	// Caso tenha sido ganho, coloca no tabuleiro geral.
	if (ganho == 1 && tab[0].jogo[(qdrt - 1) / 3][(qdrt - 1) % 3] == ' ') {
		if ( jogador == 1 ) {
			tab[0].jogo[(qdrt - 1) / 3][(qdrt - 1) % 3] = 'X';
		}
		else {
			tab[0].jogo[(qdrt - 1) / 3][(qdrt - 1) % 3] = 'O';
		}
	}

	verificador = verificar_quadrante_cheio (tab, qdrt);

	// Caso nao tenha sido ganho, verifica se deu empate.
	if (tab[0].jogo[(qdrt - 1) / 3][(qdrt - 1) % 3] == ' ' && verificador == 1) {
		tab[0].jogo[(qdrt - 1) / 3][(qdrt - 1) % 3] = '#';
	}
	return;
}

// Funcao que recebe o vetor tabuleiro, verifica se o tabuleiro[0] (tabuleiro de quadrantes) foi ganho e devolve 0 ou 1.
int verificar_alguem_ganhou (jogo_da_velha *tab) {
	int ganho, i;

	ganho = 0;

 	// Verifica se fechou alguma linha ou coluna.
	for (i = 0; (i < 3) && (ganho == 0); i++) {
		if ((tab[0].jogo[i][0] != ' ' && tab[0].jogo[i][0] == tab[0].jogo[i][1] && tab[0].jogo[i][0] == tab[0].jogo[i][2]) || (tab[0].jogo[0][i] != ' ' && tab[0].jogo[0][i] == tab[0].jogo[1][i] && tab[0].jogo[0][i] == tab[0].jogo[2][i])) {
			ganho = 1;
    	}
    }

	// Verifica se fechou alguma diagonal.
	if (tab[0].jogo[1][1] != ' ') {
		if ((tab[0].jogo[0][0] == tab[0].jogo[1][1] && tab[0].jogo[0][0] == tab[0].jogo[2][2]) || (tab[0].jogo[0][2] == tab[0].jogo[1][1] && tab[0].jogo[0][2] == tab[0].jogo[2][0])) {
			ganho = 1;
		}
	}
	return (ganho);
}

// Funcao principal.
int main () {
	jogo_da_velha tabuleiro[10];
	int versao, i, j, k, alguem_ganhou, rodada, jogador, quadrante, jogada, linha, coluna;

	// Apresenta o jogo e pede para escolher a versao.
    printf("JOGO DA VELHA (criado por Arlen e Matheus)\n\n");
    printf("Escolha a versao (Digite 1 para Jogador x Jogador ou digite 2 para Jogador x Computador): ");
   	scanf("%d", &versao);

    // Pede para digitar novamente, caso nao tenha sido digitado 1 ou 2.
   	while ((versao != 1) && (versao != 2)) {
       	printf("Tente novamente: ");
      	scanf("%d", &versao);
   	}

	// Deixa o tabuleiro vazio.
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				tabuleiro[i].jogo[j][k] = ' ';
			}
		}
	}

	// Executa a versao Jogador contra Jogador.
	if (versao == 1) {
		// Limpa a tela.
		system("cls");

		// Imprime na tela a legenda e o tabuleiro.
		printf("JOGO DA VELHA (Jogador x Jogador)\n\n");
		printf("Quem jogar primeiro eh o 'X' e o seguinte eh o 'O'\n");
		printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
		exibir_tabuleiro(tabuleiro);

		// Pergunta ao jogador 1 qual quadrante ele vai comecar a jogar.
		printf("JOGADOR 1, escolha um quadrante (jogo da velha interno) para comecar: ");
		scanf("%d", &quadrante);

		jogada = quadrante;
		alguem_ganhou = 0;

		// Verifica se o quadrante escolhido eh valido.
		while (quadrante < 1 || quadrante > 9) {
			printf("Escolha outro quadrante: ");
			scanf("%d", &quadrante);
		}

		// Executa as rodadas ate alguem ganhar ou ate atingir o maximo de rodadas (empate).
		for (rodada = 0; (rodada < 81) && (alguem_ganhou == 0); rodada++) {
			if (rodada > 0) {
				// O quadrante eh definido pela ultima jogada feita.
				quadrante = jogada;

				i = verificar_quadrante_cheio(tabuleiro, quadrante);

				// Pede para escolher outro quadrante para jogar caso ele esteja cheio.
				while (i == 1) {
					printf("Este quadrante esta cheio, escolha outro para jogar: ");
					scanf("%d", &quadrante);
					i = verificar_quadrante_cheio(tabuleiro, quadrante);
				}
				printf("A jogada sera feita no quadrante %d\n", quadrante);
			}

			// Define qual jogador esta jogando.
			jogador = (rodada % 2) + 1;

			printf("JOGADOR %d, escolha sua jogada: ", jogador);
			scanf("%d", &jogada);

			linha = (jogada - 1) / 3;
			coluna = (jogada - 1) % 3;

			// Verifica se a jogada eh valida.
			while (jogada < 1 || 9 < jogada || tabuleiro[quadrante].jogo[linha][coluna] != ' ') {
				printf("Esta jogada eh invalida, escolha outra: ");
				scanf("%d", &jogada);
				linha = (jogada - 1) / 3;
				coluna = (jogada - 1) % 3;
			}

			//Faz a jogada escolhida pelo jogador.
			if (jogador == 1) {
				tabuleiro[quadrante].jogo[linha][coluna] = 'X';
			}
			else {
				tabuleiro[quadrante].jogo[linha][coluna] = 'O';
			}

			// Verifica se o jogo foi ganho.
			verificar_quadrante (tabuleiro, quadrante, jogador);
			alguem_ganhou = verificar_alguem_ganhou(tabuleiro);

			// Limpa a tela.
			system ("cls");

			//Mostra a legenda.
			printf("JOGO DA VELHA (Jogador x Jogador)\n\n");
			printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
			exibir_tabuleiro(tabuleiro);
		}

		if (alguem_ganhou == 1) {
			printf("                       _                     \n");
			printf("                      | |                    \n");
			printf(" _ __   __ _ _ __ __ _| |__   ___ _ __  ___  \n");
			printf("| '_ | / _` | '__/ _` | '_ | / _ | '_ |/ __| \n");
			printf("| |_) | (_| | | | (_| | |_) |  __/ | | |__ | \n");
			printf("| .__/ |__,_|_|  |__,_|_.__/ |___|_| |_|___/ \n");
			printf("| |       JOGADOR %d, VOCE GANHOU                                       \n", jogador);
			printf("|_|                                          \n");
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
	}

	// Executa a versao Jogador contra Computador.
	if (versao == 2) {
		// Limpa a tela.
        system("cls");

		// Faz a primeira jogada do Computador no quadrante 5 e casa 5.
		quadrante = 5;
		jogada = 5;
		tabuleiro[5].jogo[1][1] = 'X';

		// Imprime na tela a legenda e o tabuleiro.
       	printf("JOGO DA VELHA (Jogador x Computador)\n\n");
      	printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
    	printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
   	    exibir_tabuleiro(tabuleiro);

		// Executa ate a rodada 15. O Computador sempre escolhe a jogada 5.
		for (rodada = 1; rodada < 16; rodada++) {
			jogador = (rodada % 2) + 1;
			int quadrante_computador = quadrante; // Esta variavel guarda o quadrante no qual o computador jogou para mostrar ao jogador.
			quadrante = jogada;

			if (jogador == 1) {
				jogada = 5;
				tabuleiro[quadrante].jogo[1][1] = 'X';
			}
			else {
				printf("O Computador jogou no quadrante %d e casa %d\n", quadrante_computador, jogada);
				printf("A jogada sera feita no quadrante %d\n", quadrante);
				printf("JOGADOR, escolha sua jogada: ");
				scanf("%d", &jogada);

				linha = (jogada - 1) / 3;
                coluna = (jogada - 1) % 3;

				// Verifica se a jogada eh valida.
				while (jogada < 1 || jogada > 9 || tabuleiro[quadrante].jogo[linha][coluna] != ' ') {
					printf("Esta jogada eh invalida, escolha outra: ");
					scanf("%d", &jogada);
					linha = (jogada - 1) / 3;
                	coluna = (jogada - 1) % 3;
				}

				// Faz a jogada do jogador.
				tabuleiro[quadrante].jogo[linha][coluna] = 'O';
			}

			// Verifica se o quadrante foi ganho.
			verificar_quadrante(tabuleiro,quadrante,jogador);

			// Limpa a tela.
            system("cls");

            // Imprime na tela a legenda e o tabuleiro atualizados.
            printf("JOGO DA VELHA (Jogador x Computador)\n\n");
            printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
            printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
            exibir_tabuleiro(tabuleiro);
		}

		// Na rodada 16, o Computador joga na mesma casa jogada pelo Jogador na rodada 15, essa casa eh chamada de A.
		quadrante = jogada;
		int A = jogada;

		linha = (A - 1) / 3;
		coluna = (A - 1) % 3;
		tabuleiro[quadrante].jogo[linha][coluna] = 'X';

		// Limpa a tela.
        system("cls");

        // Imprime na tela a legenda e o tabuleiro atualizados.
        printf("JOGO DA VELHA (Jogador x Computador)\n\n");
        printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
        printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
        exibir_tabuleiro(tabuleiro);

        // Executa todas as rodadas a partir da 17 ate alguem ganhar ou ate atingir o maximo de rodadas (empate).
        // Na pratica, executa ate o computador vencer.
        for (rodada = 17, alguem_ganhou = 0; (rodada < 81) && (alguem_ganhou == 0); rodada++) {
            jogador = (rodada % 2) + 1;
            int quadrante_computador = quadrante;
			quadrante = jogada;

			// Executa a jogada do Computador conforme a Estrategia Vencedora.
			if (jogador == 1) {
                int aux = 0; // Esta variavel auxiliar garante que o computador faca apenas uma jogada por rodada.

                // Se o jogador enviou o computador para o quadrante do meio (ou seja, a jogada foi 5), entao ele escolhe o quadrante oposto de A (10 - A) e faz a jogada A.
                if (jogada == 5) {
                    quadrante = 10 - A;
                    jogada = A;

                    linha = (jogada - 1) / 3;
                    coluna = (jogada - 1) % 3;
                    tabuleiro[quadrante].jogo[linha][coluna] = 'X';

                    aux = 1;
                }

                // Se o jogador enviou o computador para um quadrante cuja casa A esta vazia, entao ele faz a jogada A.
                if (aux == 0 && tabuleiro[quadrante].jogo[(A - 1) / 3][(A - 1) % 3] == ' ') {
                    jogada = A;

                    linha = (jogada - 1) / 3;
                    coluna = (jogada - 1) % 3;
                    tabuleiro[quadrante].jogo[linha][coluna] = 'X';

                    aux = 1;
                }

                // Se o jogador enviou o computador para um quadrante cuja casa A esta ocupada, entao ele faz a jogada 10 - A.
                if (aux == 0 && tabuleiro[quadrante].jogo[(A - 1) / 3][(A - 1) % 3] != ' ') {
                    jogada = 10 - A;

                    linha = (jogada - 1) / 3;
                    coluna = (jogada - 1) % 3;
                    tabuleiro[quadrante].jogo[linha][coluna] = 'X';

                    aux = 1;
                }
			}

			// Executa a rodada do Jogador.
			else {
                printf("O Computador jogou no quadrante %d e casa %d\n", quadrante_computador, jogada);
				printf("A jogada sera feita no quadrante %d\n", quadrante);
				printf("JOGADOR, escolha sua jogada: ");
				scanf("%d", &jogada);

				linha = (jogada - 1) / 3;
                coluna = (jogada - 1) % 3;

				// Verifica se a jogada eh valida.
				while (jogada < 1 || jogada > 9 || tabuleiro[quadrante].jogo[linha][coluna] != ' ') {
					printf("Esta jogada eh invalida, escolha outra: ");
					scanf("%d", &jogada);
					linha = (jogada - 1) / 3;
                	coluna = (jogada - 1) % 3;
				}

				// Faz a jogada do jogador.
				tabuleiro[quadrante].jogo[linha][coluna] = 'O';
			}

			// Verifica se o jogo foi ganho.
			verificar_quadrante(tabuleiro,quadrante,jogador);
            alguem_ganhou = verificar_alguem_ganhou(tabuleiro);

			// Limpa a tela.
            system("cls");

            // Imprime na tela a legenda e o tabuleiro atualizados.
            printf("JOGO DA VELHA (Jogador x Computador)\n\n");
            printf("O Computador eh o 'X' e o Jogador eh o 'O'\n");
            printf("O tabuleiro de quadrantes mostra o resultado de cada jogo da velha interno ('#' se der velha)\n");
            exibir_tabuleiro(tabuleiro);
        }

        // Imprime o resultado do jogo. Na pratica, sempre o Computador ganha:
        if (alguem_ganhou == 1 && jogador == 1) {
            printf("                                           _            \n");
            printf("                                          | |           \n");
            printf(" __   _____   ___ ___   _ __   ___ _ __ __| | ___ _   _ \n");
            printf(" | | / | _ | / __/ _ | | '_ | / _ | '__/ _` |/ _ | | | |\n");
            printf("  | V | (_) | (_|  __/ | |_) |  __/ | | (_| |  __/ |_| |\n");
            printf("   |_| |___| |___|___| | .__/ |___|_|  |__,_||___||__,_|\n");
            printf("                       | |                              \n");
            printf("                       |_|                              \n");
        }

        if (alguem_ganhou == 1 && jogador == 2) {
            printf("Parabens! Voce venceu o Invencivel!\n");
        }

        if (alguem_ganhou == 0) {
            printf("Parabens! Voce empatou com a I.A. impossivel de empatar!\n");
        }
	}

    return (0);
}


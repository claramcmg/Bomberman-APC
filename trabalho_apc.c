/*Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Algoritmos   e   Programação   de   Computadores  
–2/2019
Aluno(a): < Maria Clara Mendes Gonçalves >
Matricula: < 19/0100168 >
Turma: A
Versão do compilador: <versao utilizada> 
Descricao: < Jogo Bomberman >*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define INICIO_COLUNA 1
#define FIM_LINHA 13
#define MEDIA_TEMPO 7
#define ERRO_TEMPO 3
#define RAND(MEDIA_TEMPO, ERRO_TEMPO)(MEDIA_TEMPO + (rand()%(2*ERRO_TEMPO + 1) - ERRO_TEMPO))

char tabuleiro[15][28];
long int tempo_partida=0;
long int inic_time;
int posicao[2] = {FIM_LINHA, INICIO_COLUNA};
int tempo_bomba=-1;
int bomba = 0;
int ibomba;
int jbomba;

/*Inicializa o campo*/ 
void InicializaTabuleiro(){
	char Inicio[28] = " _________________________ ";
	char Fim[28] = "|_________________________|";
    char Meio1[28] = "|                         |";
	char Meio2[28] = "| + + + + + + + + + + + + |";
	int i;
	
	strcpy(tabuleiro[0], Inicio);
		for (i=1; i<14; i++){
			if (i%2!=0){
				strcpy(tabuleiro[i], Meio1);
			}
			if (i%2==0){
				strcpy(tabuleiro[i], Meio2);
			}
		}

	strcpy(tabuleiro[14], Fim);
}

/*Imprime o tabuleiro com os valores da matriz*/
void PrintarTabuleiro(){

int i, j;

	for (i=0; i<15; i++){
		for (j=0; j<28; j++){
			printf("%c", tabuleiro[i][j]);
		}
		printf("\n");
	}
}

/*Imprime o cabecalho e chama a funcao de imprimir o tabuleiro*/
void Printar(){
	
	system("clear");
	
	tempo_partida = time(0)-inic_time;

	printf("TEMPO RESTANTE: %ld\n", 200-(tempo_partida));
	printf("A-esquerda \t D-direita \t S-cima \nX-baixo \t B-bomba \t E-encerrar\n");
	
	PrintarTabuleiro();
	printf("Opcao: ");

	if ((200-tempo_partida)<=0){
		printf("Seu tempo acabou :/\n");
		exit(0);
	}
}

/*Imprime a primeira pagina e espera o enter*/	
void PaginaInicial(){

char c;

	system("clear");	
	printf ("*************** BOMBERMAN ***************\n\n\n\n");

	PrintarTabuleiro();	
	printf("Tecle <enter> para comecar o jogo\n");
	
	/*Caso nao se digite enter, escaneia novamente*/
	do{
		scanf("%c", &c);
	}while(c!=10);
}

/*Inicia contagem do tempo e distribui os componentes no tabuleiro*/
void ComecaPartida (){

char aleatorio[3] = " #@";
int i, j;

	inic_time = time(0);	
	srand (time(0));

	for (i=1; i<14; i++){
		for (j=1; j<25; j++){
			int l = rand ()%11;
			if (tabuleiro[i][j]!='+'){
				if (l<2){
					tabuleiro[i][j] = aleatorio[2];
				}
				else if (l<5){
					tabuleiro[i][j] = aleatorio[1];
				}
				else if (l<=10){
					tabuleiro[i][j] = aleatorio[0];
				}	
			}			
		}	
	}
	tabuleiro[FIM_LINHA][INICIO_COLUNA] = '&';

	Printar();
}

/*Troca os valores para movimentar o jogador*/
void MudarPosicao(int i, int j){

	if (tabuleiro[posicao[0]][posicao[1]]!= '*'){
		if (tabuleiro[i][j] == ' '){
			tabuleiro[posicao[0]][posicao[1]] = ' ';
			tabuleiro[i][j] = '&';

			posicao[0] = i;
			posicao[1] = j;	
		}
		if (tabuleiro[i][j] == '@'){
			printf("Voce foi atacado por um inimigo e morreu :/\n");
			exit(0);
		}
	}
	else{
		if (tabuleiro[i][j] == ' '){
			tabuleiro[i][j] = '&';

			posicao[0] = i;
			posicao[1] = j;	
		}
		if (tabuleiro[i][j] == '@'){
			printf("Voce foi atacado por um inimigo e morreu :/\n");
			exit(0);
		}
	}	
}

/*Explodir componentes perto da bomba*/
void ExplodeBomba(){

int linha, coluna;

linha = ibomba;
coluna = jbomba;

	if (time(0)>tempo_bomba){
		for((linha=ibomba-1); (linha<=ibomba+1); linha++){
			for((coluna=jbomba-1); (coluna<=jbomba+1); coluna++){
				if (tabuleiro[linha][coluna]=='@'||tabuleiro[linha][coluna]=='#'){
					tabuleiro[linha][coluna] = ' ';
				}
				if (tabuleiro[linha][coluna]=='&'){
					printf("Voce foi explodido por uma bomba e morreu :/\n");
					exit(0);	
				}
			}
		}
		tabuleiro[ibomba][jbomba]=' ';

		bomba = 0;
	}
}

/*Determina posicoes para cada opcao digitada pelo usuario*/
void RecebeJogadas(char Jogo){

	int i = posicao[0];
	int j = posicao[1];
	
	switch(Jogo){

		case 'A':
			MudarPosicao(i,j-1);
		break;

		case 'D':
			MudarPosicao(i, j+1);
		break;

		case 'S':
			MudarPosicao(i-1, j);
		break;

		case 'X':
			MudarPosicao(i+1, j);
		break;

		case 'B':
			if(!bomba){
				tabuleiro[i][j] = '*';
				ibomba = i;
				jbomba = j;
				bomba = 1;
				tempo_bomba = time(0)+RAND(MEDIA_TEMPO, ERRO_TEMPO);
			}

		break;

		case 'E':
			printf("Voce saiu do jogo\n");
			exit(0);
		break;
	}
}


/*Checa se venceu*/
void ChecarStatus(){

int vence=1, i, j;

	for (i=0; i<15; i++){
		for (j=0; j<28; j++){
			if (tabuleiro[i][j]=='@'){
				vence=0;
			}
		}
	}

	if (vence==1){
		printf("Parabens!! Você ganhou o jogo :)");
	}
	
}

int main () {

char Jogo;

	InicializaTabuleiro();
	PaginaInicial();
	ComecaPartida();

	while(1){
		scanf("%c", &Jogo);
		if (Jogo>='a'){
			Jogo -= 32;
		}
		RecebeJogadas(Jogo);
		ExplodeBomba();
		Printar();
		ChecarStatus();
	}
	
return 0;
}
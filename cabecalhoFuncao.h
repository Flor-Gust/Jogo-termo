#ifndef CABECALHOFUNCAO_H_INCLUDED
#define CABECALHOFUNCAO_H_INCLUDED
#define tam 100

// Fun��o principal, trata da l�gica do c�digo
void primeiraOpcao (int flag, char palavraSorteada[]);


// Valida uma palavra inserida pelo usu�rio
void tratarPalavra (char palavra[], int flagaux);


// Armazena palavra digitada pelo usu�rio
void receberPalavra (char palavra[]);


// Verifica se string cont�m espa�os em branco
int contemEspaco (char palavra[]);


// Exibe a interface do jogo
void menuPalavraSecreta (char palavraTentada[], char palavra[], char mostrarPalavrasTentadas[][tam], char letrasErradas[][tam], int aux, int aux2);


// Atualiza a palavra escondida substituindo letras repetidas que n�o correspondem � posi��o correta.
void ocorrenciaLetras(char palavraEscondida[], char palavraFinal[]);


// Fun��o para definir a cor do texto no console.
void letrasIguais(char palavra[], int ocorrencia[]);


// Fun��o para definir a cor do texto no console.
void colorir (int cor);


// Escolha palavra secreta aleat�ria
void segundaOpcao ();


// Exibe manual
void manual();
#endif // CABECALHOFUNCAO_H_INCLUDED

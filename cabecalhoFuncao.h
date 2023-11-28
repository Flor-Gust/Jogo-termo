#ifndef CABECALHOFUNCAO_H_INCLUDED
#define CABECALHOFUNCAO_H_INCLUDED
#define tam 100

// Função principal, trata da lógica do código
void primeiraOpcao (int flag, char palavraSorteada[]);


// Valida uma palavra inserida pelo usuário
void tratarPalavra (char palavra[], int flagaux);


// Armazena palavra digitada pelo usuário
void receberPalavra (char palavra[]);


// Verifica se string contém espaços em branco
int contemEspaco (char palavra[]);


// Exibe a interface do jogo
void menuPalavraSecreta (char palavraTentada[], char palavra[], char mostrarPalavrasTentadas[][tam], char letrasErradas[][tam], int aux, int aux2);


// Atualiza a palavra escondida substituindo letras repetidas que não correspondem à posição correta.
void ocorrenciaLetras(char palavraEscondida[], char palavraFinal[]);


// Função para definir a cor do texto no console.
void letrasIguais(char palavra[], int ocorrencia[]);


// Função para definir a cor do texto no console.
void colorir (int cor);


// Escolha palavra secreta aleatória
void segundaOpcao ();


// Exibe manual
void manual();
#endif // CABECALHOFUNCAO_H_INCLUDED

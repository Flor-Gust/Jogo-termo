#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#define tam 100
#define qtd 5
#include "cabecalhoFuncao.h"
#define CHAR_SET_SIZE 256

// Fun��o para definir a cor do texto no console.
void colorir (int cor){
    //Obt�m o identificador do manipulador para a s�ida padr�o do console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Define a cor do texto usando o identidicador do console e o valor fornecido
    SetConsoleTextAttribute(hConsole, cor);
}

// Fun��o para contar a ocorr�ncia de cada letra em uma palavra.
void letrasIguais(char palavra[], int ocorrencia[]) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = palavra[i];
        ocorrencia[c]++;
    }
}

// Atualiza a palavra escondida substituindo letras repetidas que n�o correspondem � posi��o correta.
void ocorrenciaLetras(char palavraEscondida[], char palavraFinal[]) {
    //armazena a contagem de cada letra nas palavras
    int ocorrenciaEscondida[CHAR_SET_SIZE] = {0};
    int ocorrenciaPalavraFinal[CHAR_SET_SIZE] = {0};

    //cria uma c�pia em min�scula para compara��o
    char palavraAux[tam] = {""};
    for (int i = 0; palavraEscondida[i] != '\0'; i++) {
        palavraAux[i] = tolower(palavraEscondida[i]);
    }

    //conta a ocorr�ncia de cada letra nas palavras escondida e final
    letrasIguais(palavraAux, ocorrenciaEscondida);
    letrasIguais(palavraFinal, ocorrenciaPalavraFinal);

    //percorre cada letra da palavra escondida
    for (int i = 0; palavraEscondida[i] != '\0'; i++) {
        char letra = palavraEscondida[i];

        if (islower(letra)) {  // Verifica se � uma letra min�scula
            tentar:
                // Verifica se a letra ocorre mais vezes na palavra escondida do que na palavra final
                if (ocorrenciaEscondida[letra] > ocorrenciaPalavraFinal[letra]) {
                    //Percorre a palavra escondida de tr�s para frente
                    for (int aux = strlen(palavraEscondida); aux >= 0 ; aux--) {
                        //substitui letra repitida e na posi��o errada por "_" e ajusta contagem de ocorrencia
                        if (palavraEscondida[aux] == letra) {
                            palavraEscondida[aux] = '_';
                            ocorrenciaEscondida[letra]--;
                            //reinicia a verifica��o para garantir que todas as letras sejam tratadas
                            goto tentar;
                        }
                    }
                }
        }
    }
}

// Exibe a interface do jogo
void menuPalavraSecreta (char palavraTentada[], char palavraEscondida[], char mostrarPalavrasTentadas[][tam], char letrasErradas[][tam], int aux, int qtdTentativas){
    char auxiliar[tam];

    system("cls");

    printf("----------------T E R M O----------------\n");

        //se for a primeira tentativa exibe apenas sublinhados
         if (aux == 0){
            printf("            |");

            for (int i = 0; i < strlen(palavraEscondida); i++){
                auxiliar[i] = '_';
                printf(" %c ", auxiliar[i]);
            }
            printf("|");

        }

        //copia as letras descobertas para as matrizes de letras tentadas.
        strcpy(mostrarPalavrasTentadas[qtdTentativas-1], palavraEscondida);
        strcpy(letrasErradas[qtdTentativas-1], palavraTentada);

        //exibe as letras tentadas e as letras descobertas at� o momento.
        for (int j = 0; j < qtdTentativas; j++){
            printf("            ");
            printf("|");
            for (int h = 0; h < strlen(palavraEscondida); h++){
                if (isupper(mostrarPalavrasTentadas[j][h])){
                    //se letra for maiuscula, portanto, est� na posi��o correta. Exibe em verde
                    colorir(10);
                    printf(" %c ", mostrarPalavrasTentadas[j][h]);
                    colorir(7);
                } else if(islower(mostrarPalavrasTentadas[j][h])){
                    //se letra for minuscula, portanto, est� na posi��o incorreta. Exibe em amarelo
                    colorir(6);
                    printf(" %c ", mostrarPalavrasTentadas[j][h]);
                    colorir(7);
                } else {
                    //letra n�o existe na palavra. Exibre letra em cinza
                    colorir(8);
                    printf(" %c ", letrasErradas[j][h]);
                    colorir(7);
                }
            }
            printf("|");
            printf("\n");
        }

    //exibe a tentativa atual
    if (qtdTentativas > 0){

        printf("\nQuantidade de tentativas: %d", qtdTentativas);

    }

}

// Verifica se string cont�m espa�os em branco
int contemEspaco (char palavraRecebida[]){
    for (int i = 0; i < strlen(palavraRecebida); i++){
        if (isspace(palavraRecebida[i])){
            //se encontrar espa�o em branco, retorna 1
            return 1;
        }
    }
    return 0;
}

// Armazena palavra digitada pelo usu�rio
void receberPalavra (char palavraRecebida[]){
    //limpa o buffer de entrada
    fflush(stdin);

    //l� a palavra do usu�rio e armazena na vari�vel palavraRecebida
    fgets(palavraRecebida, tam, stdin);

    //remove o caractere de nova linha ('\n') do final da palavraRecebida
    palavraRecebida[strcspn(palavraRecebida, "\n")] = '\0';
}

// Valida uma palavra inserida pelo usu�rio
void tratarPalavra(char palavra[], int flagaux){
    receberPalavra(palavra);

    //se a op��o de jogo for palavra sorteada pelo computador (op��o 2) dev�-se verificar as palavras testadas do usu�rio. Verificar se existe na lista
    if (flagaux == 2){
        FILE *file2;
        //abre o arquivo que cont�m palavras de cinco letras para leitura
        file2 = fopen("palavrasCincoLetras.txt", "r");
        char auxPalavra[100];
        int flag = 0;

        //l� cada linha do arquivo
        while (fgets(auxPalavra, sizeof(auxPalavra), file2) != NULL){
            //remove o caractere de nova linha ('\n') do final da palavra lida
            auxPalavra[ strcspn(auxPalavra, "\n")] = '\0';

            //verifica se a palavra lida � diferente da palavra inserida pelo usu�rio
            if (strcmp(auxPalavra, palavra) != 0){
                flag = 1;
            } else {
                flag = 2;
                break;
            }
        }

        //fecha o arquivo ap�s leitura
        fclose(file2);

        //palavra n�o encontrada na lista
        if (flag == 1){
            colorir(12);
            printf("\nE R R O\nN�o conhe�o essa palavra, tente outra.\n: ");
            colorir(7);
            tratarPalavra(palavra, flagaux);
        }
    }

    //enquanto a palavra n�o atender aos crit�rios de comprimento e n�o conter espa�os, continua pedindo uma nova palavra.
    while (strlen(palavra) < 5 || palavra[0] == '\n' || contemEspaco(palavra)){
        colorir(12);
        printf("\nE R R O\nEssa palavra � inv�lida, tente outra.\n: ");
        colorir(7);
        tratarPalavra(palavra, flagaux);
    }

}

// Fun��o principal, trata da l�gica do c�digo
void primeiraOpcao(int flag, char palavraSorteada[]){
    char palavraSecreta[tam] = {""}; //vari�vel que armazena a palavra secreta, a resposta final do jogo
    char palavraFinal [tam] = {""}; //vari�vel auxiliar que armazena a palavraSecreta
    char palavraTentada[tam]= {""}; //vari�vel que armazena a palavra tentada pelo usu�rio
    char palavraEscondida[tam] = {""}; //vari�vel que armazena as valida��es entre palavraTentada e palavraFinal
    char mostrarPalavrasTentadas [qtd][tam] = {""}; //vari�vel que armazena palavraEscondia para mostrar na tela as palavras tentadas
    char letrasErradas [qtd][tam] = {""}; //vari�vel que armazena a palavraTentada para mostrar as letras incorretas
    int contadorAuxiliar = 0; //vari�vel para primeira execu��o do menu
    int qtdTentativas = 0; //vari�vel que guarda a tentativa atual

    //se flag for 1(primeira op��o), jogador dever� informar a palavra secreta
    if (flag == 1){
        printf("Informe a palavra secreta.\nObserva��o: deve conter cinco letras\n: ");
        //chama fun��o para tratar a palavra tentada do usu�rio.
        tratarPalavra(palavraSecreta, flag);

        //converte palavraSecreta informada pelo usu�rio para min�sculas
        for (int i = 0; i < strlen(palavraSecreta); i++){
            palavraSecreta[i] = tolower(palavraSecreta[i]);
        }

    } else {
        //palavraSecreta recebe a palavra sorteada pelo computador
        strcpy(palavraSecreta, palavraSorteada);
    }

    //inicializa as c�pias da palavra escondida e da palavra final.
    strcpy(palavraEscondida, palavraSecreta);
    strcpy(palavraFinal, palavraSecreta);

    //chama a fun��o menuPalavraSecreta para exibir a interface inicial.
    menuPalavraSecreta(palavraTentada, palavraEscondida, mostrarPalavrasTentadas, letrasErradas, contadorAuxiliar, qtdTentativas);
    contadorAuxiliar++;

    //entra em um loop at� que o jogador acerte a palavra ou atinja o limite de tentativas (5).
    while (strcmp(palavraTentada, palavraSecreta) != 0  && qtdTentativas != 5){
        printf("\n\nInforme a palavra que queira tentar: ");
        //solicita ao jogador que informe uma palavra.
        tratarPalavra(palavraTentada, flag);

        //verifica se a palavra tem o mesmo comprimento da palavra escondida.
        while (strlen(palavraTentada) != strlen(palavraEscondida)){
            colorir(12);
            printf("\nE R R O\nEssa palavra � inv�lida, tente outra.\n: ");
            colorir(7);
            tratarPalavra(palavraTentada, flag);
        }

        //atualiza a palavra escondida com as letras corretas.
        for (int i = 0; i < strlen(palavraTentada); i++){
            palavraEscondida[i] = '_';
            for (int j = 0; j < strlen(palavraSecreta); j++){
                if (palavraTentada[i] == palavraFinal[j]){
                    if (i == j){
                        //se a letra estiver na posi��o correta, torna a letra mai�scula.
                        palavraEscondida[i] = toupper(palavraTentada[i]);
                        palavraFinal [j] = '_';
                        break;
                    } else {
                        //se a letra estiver na posi��o errada, torna a letra min�scula.
                        palavraEscondida[i] = tolower(palavraTentada[i]);
                        palavraFinal [j] = '_';
                    }
                }
            }
            //atualiza a c�pia da palavra final para verifica��es em cada loop.
            strcpy(palavraFinal, palavraSecreta);
        }

        //atualiza a palavra escondida considerando a ocorr�ncia de letras.
        ocorrenciaLetras(palavraEscondida, palavraFinal);

        qtdTentativas++;
        menuPalavraSecreta(palavraTentada, palavraEscondida, mostrarPalavrasTentadas, letrasErradas, contadorAuxiliar, qtdTentativas);
    }

    //verifica se o jogador ganhou ou perdeu e exibe a mensagem correspondente.
    if (qtdTentativas == 5 && strcmp(palavraFinal, palavraTentada) != 0){
        printf("\n\nVoc� perdeu!!\nA palavra correta era: %s\n", palavraSecreta);
    } else printf("\nParab�ns!!! Voc� acertou.\n");

}

// Escolha palavra secreta aleat�ria
void segundaOpcao(){
    char palavraSorteada [tam]; //vari�vel para armazenar a palavra sorteada.
    int qtdLinhas = 0; //vari�vel para armazenar o n�mero de linhas no arquivo.
    int linhaSorteada = 0; //vari�vel para armazenar o n�mero da linha sorteada.

    FILE *file;
    //abre o arquivo que cont�m palavras de cinco letras para leitura
    file = fopen("palavrasCincoLetras.txt", "r");


    if (!file){
        printf("\nArquivo n�o existe\n");
        return 0;
    }

    //conta o n�mero de linhas no arquivo para escolher uma aleatoriamente.
    while (fgets(palavraSorteada, sizeof(palavraSorteada), file) != NULL){
        qtdLinhas++;
    }

    //retorna ao in�cio do arquivo
    fseek(file, 0, SEEK_SET);

    //inicializa a semente para gerar n�meros aleat�rios.
    srand((unsigned int)time(NULL));

    //escolhe aleaotoriamente uma linha
    linhaSorteada = rand() % qtdLinhas + 1;

    //percorre as linhas do arquivo at� chegar � linha sorteada.
    for (int i = 0; i<=linhaSorteada; i++){
        fgets(palavraSorteada, sizeof(palavraSorteada), file);
    }

    //remove o caractere de nova linha.
    palavraSorteada[strcspn(palavraSorteada, "\n")] = '\0';

    //fecha o arquivo
    fclose(file);

    //chama a fun��o com flag 2 para palavra sorteda
    primeiraOpcao(2, palavraSorteada);
}

// Exibe manual
void manual (){
    int opcExemplo = 0;

    //apresenta as instru��es do jogo.
    printf("---M A N U A L---\n");
    printf("TERMO � um jogo de adivinha��o de palavras, ele � semelhante ao jogo da forca.\nNele voc� ter� cinco tentativas para tentar descobrir a palavra correta. \nNo jogo, as letras incorretas tentadas v�o ficar na cor cinza, as letras \nque existam na palavra, por�m na posi��o errada ficar� marcada em \nmin�sculo e da cor amarela, j� as letras que existam na palavra e estejam corretas ficaram mai�sculas e verde.");
    printf("\n\nPrimeira op��o:\nNa primeira op��o voc� escolher� uma palavra na inten��o de desafiar um amigo\na acert�-la, lembre-se, ele ter� apenas cinco tentativas.");
    printf("\n\nSegunda op��o:\nNa segunda op��o o computador ir� sortear uma palavra de cinco letras e voc� ter�\nque adivinh�-la, lembre-se, voc� ter� apenas cinco tentativas");
    printf("\n\nCaso queira ver um exemplo aperte o n�mero 1, caso j� tenha entendido digite o n�mero 2: ");
    scanf("%d", &opcExemplo);

    //valida a entrada do usu�rio
    while (opcExemplo < 1 || opcExemplo > 2){
        colorir(12);
        printf("\n\nE R R O\nInforme um valor entre [1..2]: ");
        scanf("%d", &opcExemplo);
        colorir(7);
    }

    //apresenta um exemplo se o usu�rio escolheu a op��o 1
    if (opcExemplo == 1){
        system("cls");
        printf("---E X E M P L O---");
        printf("\n\nPalavra secreta: 'Casa'\nComo ser� mostrado na tela:\n\n_ _ _ _\nInforme sua tentativa: 'Amor'\n\na _ _ _\nInforme sua tentativa: 'Caso'\n\nC A S _\nInforme sua tentativa: 'Casa'\n\nResultado na tela: \nPalavra correta!! Parab�bns.");
    }
}



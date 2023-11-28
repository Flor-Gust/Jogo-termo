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

// Função para definir a cor do texto no console.
void colorir (int cor){
    //Obtém o identificador do manipulador para a sáida padrão do console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Define a cor do texto usando o identidicador do console e o valor fornecido
    SetConsoleTextAttribute(hConsole, cor);
}

// Função para contar a ocorrência de cada letra em uma palavra.
void letrasIguais(char palavra[], int ocorrencia[]) {
    for (int i = 0; palavra[i] != '\0'; i++) {
        char c = palavra[i];
        ocorrencia[c]++;
    }
}

// Atualiza a palavra escondida substituindo letras repetidas que não correspondem à posição correta.
void ocorrenciaLetras(char palavraEscondida[], char palavraFinal[]) {
    //armazena a contagem de cada letra nas palavras
    int ocorrenciaEscondida[CHAR_SET_SIZE] = {0};
    int ocorrenciaPalavraFinal[CHAR_SET_SIZE] = {0};

    //cria uma cópia em minúscula para comparação
    char palavraAux[tam] = {""};
    for (int i = 0; palavraEscondida[i] != '\0'; i++) {
        palavraAux[i] = tolower(palavraEscondida[i]);
    }

    //conta a ocorrência de cada letra nas palavras escondida e final
    letrasIguais(palavraAux, ocorrenciaEscondida);
    letrasIguais(palavraFinal, ocorrenciaPalavraFinal);

    //percorre cada letra da palavra escondida
    for (int i = 0; palavraEscondida[i] != '\0'; i++) {
        char letra = palavraEscondida[i];

        if (islower(letra)) {  // Verifica se é uma letra minúscula
            tentar:
                // Verifica se a letra ocorre mais vezes na palavra escondida do que na palavra final
                if (ocorrenciaEscondida[letra] > ocorrenciaPalavraFinal[letra]) {
                    //Percorre a palavra escondida de trás para frente
                    for (int aux = strlen(palavraEscondida); aux >= 0 ; aux--) {
                        //substitui letra repitida e na posição errada por "_" e ajusta contagem de ocorrencia
                        if (palavraEscondida[aux] == letra) {
                            palavraEscondida[aux] = '_';
                            ocorrenciaEscondida[letra]--;
                            //reinicia a verificação para garantir que todas as letras sejam tratadas
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

        //exibe as letras tentadas e as letras descobertas até o momento.
        for (int j = 0; j < qtdTentativas; j++){
            printf("            ");
            printf("|");
            for (int h = 0; h < strlen(palavraEscondida); h++){
                if (isupper(mostrarPalavrasTentadas[j][h])){
                    //se letra for maiuscula, portanto, está na posição correta. Exibe em verde
                    colorir(10);
                    printf(" %c ", mostrarPalavrasTentadas[j][h]);
                    colorir(7);
                } else if(islower(mostrarPalavrasTentadas[j][h])){
                    //se letra for minuscula, portanto, está na posição incorreta. Exibe em amarelo
                    colorir(6);
                    printf(" %c ", mostrarPalavrasTentadas[j][h]);
                    colorir(7);
                } else {
                    //letra não existe na palavra. Exibre letra em cinza
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

// Verifica se string contém espaços em branco
int contemEspaco (char palavraRecebida[]){
    for (int i = 0; i < strlen(palavraRecebida); i++){
        if (isspace(palavraRecebida[i])){
            //se encontrar espaço em branco, retorna 1
            return 1;
        }
    }
    return 0;
}

// Armazena palavra digitada pelo usuário
void receberPalavra (char palavraRecebida[]){
    //limpa o buffer de entrada
    fflush(stdin);

    //lê a palavra do usuário e armazena na variável palavraRecebida
    fgets(palavraRecebida, tam, stdin);

    //remove o caractere de nova linha ('\n') do final da palavraRecebida
    palavraRecebida[strcspn(palavraRecebida, "\n")] = '\0';
}

// Valida uma palavra inserida pelo usuário
void tratarPalavra(char palavra[], int flagaux){
    receberPalavra(palavra);

    //se a opção de jogo for palavra sorteada pelo computador (opção 2) devê-se verificar as palavras testadas do usuário. Verificar se existe na lista
    if (flagaux == 2){
        FILE *file2;
        //abre o arquivo que contém palavras de cinco letras para leitura
        file2 = fopen("palavrasCincoLetras.txt", "r");
        char auxPalavra[100];
        int flag = 0;

        //lê cada linha do arquivo
        while (fgets(auxPalavra, sizeof(auxPalavra), file2) != NULL){
            //remove o caractere de nova linha ('\n') do final da palavra lida
            auxPalavra[ strcspn(auxPalavra, "\n")] = '\0';

            //verifica se a palavra lida é diferente da palavra inserida pelo usuário
            if (strcmp(auxPalavra, palavra) != 0){
                flag = 1;
            } else {
                flag = 2;
                break;
            }
        }

        //fecha o arquivo após leitura
        fclose(file2);

        //palavra não encontrada na lista
        if (flag == 1){
            colorir(12);
            printf("\nE R R O\nNão conheço essa palavra, tente outra.\n: ");
            colorir(7);
            tratarPalavra(palavra, flagaux);
        }
    }

    //enquanto a palavra não atender aos critérios de comprimento e não conter espaços, continua pedindo uma nova palavra.
    while (strlen(palavra) < 5 || palavra[0] == '\n' || contemEspaco(palavra)){
        colorir(12);
        printf("\nE R R O\nEssa palavra é inválida, tente outra.\n: ");
        colorir(7);
        tratarPalavra(palavra, flagaux);
    }

}

// Função principal, trata da lógica do código
void primeiraOpcao(int flag, char palavraSorteada[]){
    char palavraSecreta[tam] = {""}; //variável que armazena a palavra secreta, a resposta final do jogo
    char palavraFinal [tam] = {""}; //variável auxiliar que armazena a palavraSecreta
    char palavraTentada[tam]= {""}; //variável que armazena a palavra tentada pelo usuário
    char palavraEscondida[tam] = {""}; //variável que armazena as validações entre palavraTentada e palavraFinal
    char mostrarPalavrasTentadas [qtd][tam] = {""}; //variável que armazena palavraEscondia para mostrar na tela as palavras tentadas
    char letrasErradas [qtd][tam] = {""}; //variável que armazena a palavraTentada para mostrar as letras incorretas
    int contadorAuxiliar = 0; //variável para primeira execução do menu
    int qtdTentativas = 0; //variável que guarda a tentativa atual

    //se flag for 1(primeira opção), jogador deverá informar a palavra secreta
    if (flag == 1){
        printf("Informe a palavra secreta.\nObservação: deve conter cinco letras\n: ");
        //chama função para tratar a palavra tentada do usuário.
        tratarPalavra(palavraSecreta, flag);

        //converte palavraSecreta informada pelo usuário para minúsculas
        for (int i = 0; i < strlen(palavraSecreta); i++){
            palavraSecreta[i] = tolower(palavraSecreta[i]);
        }

    } else {
        //palavraSecreta recebe a palavra sorteada pelo computador
        strcpy(palavraSecreta, palavraSorteada);
    }

    //inicializa as cópias da palavra escondida e da palavra final.
    strcpy(palavraEscondida, palavraSecreta);
    strcpy(palavraFinal, palavraSecreta);

    //chama a função menuPalavraSecreta para exibir a interface inicial.
    menuPalavraSecreta(palavraTentada, palavraEscondida, mostrarPalavrasTentadas, letrasErradas, contadorAuxiliar, qtdTentativas);
    contadorAuxiliar++;

    //entra em um loop até que o jogador acerte a palavra ou atinja o limite de tentativas (5).
    while (strcmp(palavraTentada, palavraSecreta) != 0  && qtdTentativas != 5){
        printf("\n\nInforme a palavra que queira tentar: ");
        //solicita ao jogador que informe uma palavra.
        tratarPalavra(palavraTentada, flag);

        //verifica se a palavra tem o mesmo comprimento da palavra escondida.
        while (strlen(palavraTentada) != strlen(palavraEscondida)){
            colorir(12);
            printf("\nE R R O\nEssa palavra é inválida, tente outra.\n: ");
            colorir(7);
            tratarPalavra(palavraTentada, flag);
        }

        //atualiza a palavra escondida com as letras corretas.
        for (int i = 0; i < strlen(palavraTentada); i++){
            palavraEscondida[i] = '_';
            for (int j = 0; j < strlen(palavraSecreta); j++){
                if (palavraTentada[i] == palavraFinal[j]){
                    if (i == j){
                        //se a letra estiver na posição correta, torna a letra maiúscula.
                        palavraEscondida[i] = toupper(palavraTentada[i]);
                        palavraFinal [j] = '_';
                        break;
                    } else {
                        //se a letra estiver na posição errada, torna a letra minúscula.
                        palavraEscondida[i] = tolower(palavraTentada[i]);
                        palavraFinal [j] = '_';
                    }
                }
            }
            //atualiza a cópia da palavra final para verificações em cada loop.
            strcpy(palavraFinal, palavraSecreta);
        }

        //atualiza a palavra escondida considerando a ocorrência de letras.
        ocorrenciaLetras(palavraEscondida, palavraFinal);

        qtdTentativas++;
        menuPalavraSecreta(palavraTentada, palavraEscondida, mostrarPalavrasTentadas, letrasErradas, contadorAuxiliar, qtdTentativas);
    }

    //verifica se o jogador ganhou ou perdeu e exibe a mensagem correspondente.
    if (qtdTentativas == 5 && strcmp(palavraFinal, palavraTentada) != 0){
        printf("\n\nVocê perdeu!!\nA palavra correta era: %s\n", palavraSecreta);
    } else printf("\nParabéns!!! Você acertou.\n");

}

// Escolha palavra secreta aleatória
void segundaOpcao(){
    char palavraSorteada [tam]; //variável para armazenar a palavra sorteada.
    int qtdLinhas = 0; //variável para armazenar o número de linhas no arquivo.
    int linhaSorteada = 0; //variável para armazenar o número da linha sorteada.

    FILE *file;
    //abre o arquivo que contém palavras de cinco letras para leitura
    file = fopen("palavrasCincoLetras.txt", "r");


    if (!file){
        printf("\nArquivo não existe\n");
        return 0;
    }

    //conta o número de linhas no arquivo para escolher uma aleatoriamente.
    while (fgets(palavraSorteada, sizeof(palavraSorteada), file) != NULL){
        qtdLinhas++;
    }

    //retorna ao início do arquivo
    fseek(file, 0, SEEK_SET);

    //inicializa a semente para gerar números aleatórios.
    srand((unsigned int)time(NULL));

    //escolhe aleaotoriamente uma linha
    linhaSorteada = rand() % qtdLinhas + 1;

    //percorre as linhas do arquivo até chegar à linha sorteada.
    for (int i = 0; i<=linhaSorteada; i++){
        fgets(palavraSorteada, sizeof(palavraSorteada), file);
    }

    //remove o caractere de nova linha.
    palavraSorteada[strcspn(palavraSorteada, "\n")] = '\0';

    //fecha o arquivo
    fclose(file);

    //chama a função com flag 2 para palavra sorteda
    primeiraOpcao(2, palavraSorteada);
}

// Exibe manual
void manual (){
    int opcExemplo = 0;

    //apresenta as instruções do jogo.
    printf("---M A N U A L---\n");
    printf("TERMO é um jogo de adivinhação de palavras, ele é semelhante ao jogo da forca.\nNele você terá cinco tentativas para tentar descobrir a palavra correta. \nNo jogo, as letras incorretas tentadas vão ficar na cor cinza, as letras \nque existam na palavra, porém na posição errada ficará marcada em \nminúsculo e da cor amarela, já as letras que existam na palavra e estejam corretas ficaram maiúsculas e verde.");
    printf("\n\nPrimeira opção:\nNa primeira opção você escolherá uma palavra na intenção de desafiar um amigo\na acertá-la, lembre-se, ele terá apenas cinco tentativas.");
    printf("\n\nSegunda opção:\nNa segunda opção o computador irá sortear uma palavra de cinco letras e você terá\nque adivinhá-la, lembre-se, você terá apenas cinco tentativas");
    printf("\n\nCaso queira ver um exemplo aperte o número 1, caso já tenha entendido digite o número 2: ");
    scanf("%d", &opcExemplo);

    //valida a entrada do usuário
    while (opcExemplo < 1 || opcExemplo > 2){
        colorir(12);
        printf("\n\nE R R O\nInforme um valor entre [1..2]: ");
        scanf("%d", &opcExemplo);
        colorir(7);
    }

    //apresenta um exemplo se o usuário escolheu a opção 1
    if (opcExemplo == 1){
        system("cls");
        printf("---E X E M P L O---");
        printf("\n\nPalavra secreta: 'Casa'\nComo será mostrado na tela:\n\n_ _ _ _\nInforme sua tentativa: 'Amor'\n\na _ _ _\nInforme sua tentativa: 'Caso'\n\nC A S _\nInforme sua tentativa: 'Casa'\n\nResultado na tela: \nPalavra correta!! Parabébns.");
    }
}



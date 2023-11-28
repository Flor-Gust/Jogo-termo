#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#define tam 100
#include "cabecalhoFuncao.h"

int main()
{
    //terminal em portugues
    setlocale(LC_ALL, "Portuguese");

    //cria��o das variavies
    int opc = 0;
    int flag = 0;

    //menu principal
    do{
        system("cls");
        printf("|======================================================|\n");
        printf("|-----------------------T E R M O----------------------|\n");
        printf("|======================================================|\n");
        printf("|1 - Escolha uma palavra:                              |\n");
        printf("|2 - Adivinhe uma palavra escolhida pelo computados:   |\n");
        printf("|3 - Manual.                                           |\n");
        printf("|4 - Sair.                                             |\n");
        printf("|Informe sua escolha:                                  |\n");
        printf("|");

        //valida op��o do usu�rio
        while (scanf("%d", &opc) != 1){
            fflush(stdin);
            colorir(12);
            printf("\nE R R O!");
            printf("\nInforme um valor v�lido [1..4]: ");
            colorir(7);
            continue;
        }

        //valida op��o do usu�rio
        while (opc < 1 || opc > 4){
            colorir(12);
            printf("\nE R R O!");
            printf("\nInforme um valor v�lido [1..4]: ");
            colorir(7);
            scanf("%d", &opc);

        }

        system("cls");

        //entra dentro da fun��o de acordo com op��o desejado pelo usu�rio
        switch (opc){
            case 1:
                flag = 1;
                primeiraOpcao(flag, " ");
                break;
            case 2:
                segundaOpcao(flag);
                break;
            case 3:
                manual();
                break;
            default:
                opc = 4;
        }

        if (opc != 4){
            printf("\n\n");
            //pausa o programa antes de continuar para a pr�xima itera��o
            system("pause");

        } else {
            printf("F I M");
        }
    }while (opc != 4);
}

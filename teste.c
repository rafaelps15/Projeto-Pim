#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>


int main()
{
    char nome[20];
    fgets(nome,sizeof(nome),stdin);
    printf("%s",nome);

    return 0;

}


/*
Tarefa 1: Arquivo fixo.dad
O arquivo fixo.dad possui 10 registros gravados em um formato de campos e registros
de tamanho fixo. Essa organização é uma das mais simples. Para a leitura de todos os
dados tem-se duas opções principais:
1.  Pode-se fazer uma chamada a fread para cada registro;
2.  Pode-se definir um vetor de registros e ler todos os 10 registros com uma única
chamada a fread. Para isso, ajuste o terceiro parâmetro do fread.
Em ambas as opções,  utilize  sizeof  para calcular  o tamanho em bytes ocupado por
um  registro.  Por  exemplo,  sizeof(reg)  retorna  o  número  de  bytes  ocupados  pelo
registro reg.
Para a leitura de um registro pedido pelo usuário deve-se utilizar a função fseek. Para
tanto,  deve-se  calcular  o  número  de  bytes  existentes  entre  o  início  do  arquivo  e  o
registro  de  interesse.  Novamente,  sizeof  é  útil  para  descobrir  quantos  bytes  ocupa
cada registro.
*/

#include <stdio.h>
#include <string.h>

struct cadastro
{
    char nome[15];
    char sobrenome[15];
    char endereco[26];
    int numero;
};
typedef struct cadastro cadastro;


int main (void)
{
    //int escolha = 1;
    FILE *arquivo;
    cadastro bufferCadastro;

    //char c[] = "this is a string";
    char buffer[100];

    if ((arquivo = fopen("fixo.dad","w+b")) == NULL)
    {
        printf("Erro: Arquivo nao aberto!\n");
        return 0;
    }
    else
    {
        printf("Arquivo aberto com sucesso!\n");
    }


    /* Write data to the file */
    //fwrite(c, strlen(c) + 1, 1, fp);

    /* Seek to the beginning of the file */
    fseek(arquivo, SEEK_SET, 0);

    /* Read and display data */
    fread(buffer, 10, 1, arquivo);
    printf("%s\n", buffer);

    fclose(arquivo);

    return 0;
}

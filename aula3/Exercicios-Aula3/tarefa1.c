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
#include <stdlib.h>

struct cadastro
{
    char nome[15];
    char sobrenome[15];
    char endereco[26];
    int numero;
};
typedef struct cadastro cadastro;

void imprimeRegistro(char *buffer)
{
    cadastro cadastroBuffer;
    char aux[4];
    unsigned int numero;
    printf("%s\n", buffer);

    strncpy(cadastroBuffer.nome, buffer, 15);
    strncpy(cadastroBuffer.sobrenome, buffer+15, 15);
    strncpy(cadastroBuffer.endereco, buffer+30, 26);
    strncpy(aux, buffer+56, 4);

    //fread(buffer+56, numero, 1, fp);

    printf("\nNome: %s", cadastroBuffer.nome);
    printf("\nSobrenome: %s", cadastroBuffer.sobrenome);
    printf("\nEndereco: %s", cadastroBuffer.endereco);

    numero = (unsigned int)*aux;

    printf("\nNumero (string): %s", aux);
    printf("\nNumero: %d - (imprimindo sign Int)", numero);
    printf("\nNumero: %u (unsigned int)\n", numero);
    ///printf("\nNumero: %d", cadastroBuffer->numero);
}

int main (void)
{
    //int escolha = 1;
    FILE *arquivo;

    char buffer[60];
    int opcao;
    int tamanhoRegistro, offset;

    tamanhoRegistro = sizeof(cadastro);

    if ((arquivo = fopen("fixo.dad","r+")) == NULL)
    {
        printf("Erro: Arquivo nao aberto!\n");
        return 0;
    }
    else
    {
        printf("Arquivo aberto com sucesso!\n");
    }

    printf("\nTamanho do Struct: %d", tamanhoRegistro);

    printf("\nDigite o registro a ser lido (1 a 10):");
    scanf("%d", &opcao);

    /* Seek to the beginning of the file */
    offset = (opcao-1) * tamanhoRegistro;
    fseek(arquivo, offset, SEEK_SET);  //coloca o cursor na posicao a ser lido o registro

    /* Read and display data */
    fread(buffer, tamanhoRegistro, 1, arquivo);

    //bufferCadastro = buffer;
    imprimeRegistro(buffer);

    fclose(arquivo);

    return 0;
}

/*
Exercicio lista 4 - ED2
Profa Veronica
Alunos Dalton Lima & Lucas Pinheiro
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct contato{
  int codigo;
  char nome[128];
  char telefone[16];
};
typedef struct contato contato;

contato readContact()
{
  contato buffer;
  printf("\nDigite o nome: ");
  fgets(buffer.nome, sizeof(buffer.nome), stdin);
  //scanf("%s", );

  printf("\nDigite o telefone: ");
  fgets(buffer.telefone, sizeof(buffer.telefone), stdin);
  return buffer;
}

int main()
{
  FILE *arq;
  contato buffer;

  if ( (arq = fopen("dados.dat", "r+")) == NULL )
  {
      printf("Arquivo nao encontrado! Criando arquivo 'dados.dat'!\n");
      arq = fopen("dados.dat", "w+");  // create a new file
  }
  else
  {
    printf("Arquivo aberto com sucesso!\n");
  }

  buffer = readContact();

  puts(buffer.nome);
  puts(buffer.telefone);

  return 0;
}

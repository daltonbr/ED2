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
  char *nome;
  char *telefone;
};

int main()
{
  FILE *arq;

  if ( (arq = fopen("dados.dat", "r+")) == NULL )
  {
      printf("Arquivo nao encontrado! Criando arquivo 'dados.dat'!\n");
      arq = fopen("dados.dat", "w+");  // create a new file
  }
  else
  {
    printf("Arquivo aberto com sucesso!\n");
  }



  return 0;
}

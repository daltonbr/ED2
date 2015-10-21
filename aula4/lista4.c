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

int sizeOfReg(contato reg);
contato readContact();

contato readContact()
{
  contato reg;

  printf("\nDigite o codigo: ");
  scanf("%d", &reg.codigo);
  printf("\nDigite o nome: ");
  fpurge(stdin);   // fflush(stdin)  // no windows
  fgets(reg.nome, sizeof(reg.nome), stdin);

  printf("\nDigite o telefone: ");
  fgets(reg.telefone, sizeof(reg.telefone), stdin);
  return reg;
}

// Calculate the size of the register
int sizeOfReg(contato reg)
{
  int length = 0;

  return length;
}

int concatenateReg (contato reg, char *buffer)
{
  int length = 0, offset = 0;

  //calculating the size of the register
  length = strlen(reg.nome) -1;   //not counting the terminator
  length += strlen(reg.telefone) -1;
  length += sizeof(int) + 4; // adds the 'key' plus the 4 pipes '|'

  //concatenating
  offset = strlen(reg.nome)-1;
  strncpy(buffer, reg.nome, offset);
  buffer[offset] = '|';
  strncpy(buffer+offset+1, reg.telefone, strlen(reg.telefone)-1 ) ;
  offset += strlen(reg.telefone);
  buffer[offset] = '|';

  return length;
}

int main()
{
  FILE *arq;
  contato reg;
  int sizeReg;
  char buffer[256];
  //buffer = NULL;

  if ( (arq = fopen("dados.dat", "r+")) == NULL )
  {
      printf("Arquivo nao encontrado! Criando arquivo 'dados.dat'!\n");
      // creating new file
      arq = fopen("dados.dat", "w+");  // create a new file
  }
  else
  {
    printf("Arquivo aberto com sucesso!\n");
  }

  reg = readContact();

  printf("%d\n", reg.codigo);
  puts(reg.nome);
  puts(reg.telefone);

  sizeReg = concatenateReg(reg, buffer);  //mount the register in order to be stored

  printf("\nDebug: Registro a ser escrito: %s \n", buffer);
  
  printf("\nDebug: Tamanho do Registro a ser escrito: %d \n", sizeReg);

  return 0;
}

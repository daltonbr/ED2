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
  printf("Digite o nome: ");
  fpurge(stdin);   // fflush(stdin)  // no windows
  fgets(reg.nome, sizeof(reg.nome), stdin);

  printf("Digite o telefone: ");
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
  length += sizeof(int) + 2; // adds the 'codigo' plus the 2 pipes '|' = 6

  //concatenating: 4bytes offset + '@' + 4bytes Codigo + name + '|' + phone + '|'
  offset += snprintf ( buffer+offset, 5, "%04x", length);  //converting int to hex (string)
  buffer[offset] = '@'; offset++;
  offset += snprintf ( buffer+offset, 5, "%04x", reg.codigo);  //converting int to hex (string)

  strncpy(buffer+offset, reg.nome, strlen(reg.nome)-1);
  offset += strlen(reg.nome)-1;
  buffer[offset] = '|'; offset++;

  strncpy(buffer+offset, reg.telefone, strlen(reg.telefone)-1 ) ;
  offset += strlen(reg.telefone)-1;
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
  /* Debug
  printf("%d\n", reg.codigo);
  puts(reg.nome);
  puts(reg.telefone);
  */

  sizeReg = concatenateReg(reg, buffer);  //mount the register in order to be stored

  printf("\nDebug: Registro a ser escrito: %s", buffer);
  printf("\nDebug: Tamanho do Registro a ser escrito: %d \n", sizeReg);

  return 0;
}

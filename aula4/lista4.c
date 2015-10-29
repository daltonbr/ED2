/*
Exercicio lista 4 - ED2
Profa Veronica
Alunos Dalton Lima & Lucas Pinheiro
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  // fsync

struct contato{
  int codigo;
  char nome[128];
  char telefone[16];
};
typedef struct contato contato;

// global IndexMap
int indexMap[1000];

//function pre Declarations
int sizeOfReg(contato reg);
contato readContact();
void clearScreen();
int drawMenu();
void menu(int opcao, contato reg, char *buffer, FILE *arq);
void createIndexMap(FILE* arq);
void printIndexMap(int arr[]);
int nextAvailable (FILE *arq, int *indexArray, int sizeReg);


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

int concatenateReg (contato reg, char *buffer, FILE* arq)
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
  buffer[offset+1] = '\0';

  fwrite(buffer, strlen(buffer), 1, arq);

  return length;
}

  void clearScreen()
  {
    system("clear");
  }

  int drawMenu()
  {
    clearScreen();
    int opcao = -1;
    printf("\n --===========================================--");
    printf("\n --==            AGENDA DOS AMIGOS          ==--");
    printf("\n --===========================================--");
    printf("\n --== 1: Insercao Registro                  ==--");
    printf("\n --== 2: Remocao Registro                   ==--");
    printf("\n --== 3: Compactacao do Arquivo             ==--");
    printf("\n --== 4: Debug: Created and Print IndexList ==--");
    printf("\n --== 0: Sair                               ==--");
    printf("\n --===========================================--");
    printf("\nDigite uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
  }

// a menu to switch through some options...
void menu(int opcao, contato reg, char *buffer, FILE *arq)
{
  int sizeReg, nextPositionAvailable;
  switch (opcao) {
    case 1: //insercao
    {
      printf("\ninsercao");

      reg = readContact();  // read from the user input

      sizeReg = concatenateReg(reg, buffer, arq);  //mount the register in order to be stored
      printf("\nDebug: Registro a ser escrito: %s", buffer);
      printf("\nDebug: Tamanho do Registro a ser escrito: %d \n", sizeReg);
      insertIntoIndexMap(sizeReg);
      printIndexMap(arq);
      nextPositionAvailable = nextAvailable(arq, indexMap, sizeReg);

      getchar();
      break;
    }
    case 2: //remocao
    {
      printf("\nremocao");
      getchar();
      break;
    }
    case 3: //compactacao
    {
      printf("\ncompactacao");
      getchar();
      break;
    }
    case 0: // exit
    {
      printf("\nSaindo do programa!\n");
      getchar();
      break;
    }
    default:  // invalid choices
    {
      printf("\nEscolha invalida!");
      getchar();
      break;
    }
  }
}

void insertIntoIndexMap(int offset) {

  

}

// Function that keeps the offsets for the registers in the file
void createIndexMap(FILE* arq) {

  int position = 1;
  int size;

  indexMap[0] = 1; // the first register is always at the start of the file after the first byte

  printf("\nCreating IndexMap...");

  // check if the file is empty
  if ((fscanf (arq, "%04x", &size)) == EOF) {
    indexMap[0] = -1;
    return;
  }

  while (size != EOF) {
    if((fscanf(arq, "%04x", &size)) != EOF) //Return NULL when reach EOF
    {
        indexMap[position] = size + 4; // add 4 to account for the next offset slot (int)
        printf("\nDEBUG: #%d - Value: %d - Size: %d", position, indexMap[position], size);  //Debug Only
        if (size != EOF) {
          fseek(arq, indexMap[position], 1); // we skip to next register
          position++;
        }
    }
    else
    {
        printf("\nDebug: EOF reached");
        size = -1;
        indexMap[position] = size;
    }
  }
  printf("\nIndexList created!\n");
}

// Debug to check the IndexMap
void printIndexMap() {
  int i = 0;

  printf("\nPrinting IndexMap");

  while (indexMap[i] != -1) {
    printf("\n #%d - Value: %d", i, indexMap[i]);
    i++;
  }

  printf("\nEnd of IndexMap");
}

int nextAvailable (FILE *arq, int *indexArray, int sizeReg)
{
  int offset = 0, i = 0;
  while (indexArray[i] != 0)
  {
    offset += indexArray[i];
    i++;
  }
  return offset;
}

int main()
{
  FILE *arq;
  contato reg;
  int sizeReg, opcao = -1;
  char buffer[256];

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

  // created and print a IndexList
  createIndexMap(arq);
  printIndexMap(indexMap);
  getchar();

  while (opcao != 0 ) // menu: 0 to exit
  {
    opcao = drawMenu();
    menu(opcao, reg, buffer, arq);
  }

  return 0;
}

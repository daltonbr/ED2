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
int indexMap[1000][4]; // 0 size of the register, 1 validation char, 2 Codigo, 3 offsetFromStart

//function pre Declarations
int sizeOfReg(contato reg);
contato readContact();
void clearScreen();
int drawMenu();
void menu(int opcao, contato reg, char *buffer, FILE *arq);
void createIndexMap(FILE* arq);
void printIndexMap();
int nextAvailable (FILE *arq, int sizeReg);
void insertIntoIndexMap(int offset);


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
  int sizeReg, nextPositionAvailable, remover, i;
  switch (opcao) {
    case 1: //insercao
    {
      printf("\ninsercao");

      reg = readContact();  // read from the user input

      sizeReg = concatenateReg(reg, buffer, arq);  //mount the register in order to be stored
      printf("\nDebug: Registro a ser escrito: %s", buffer);
      printf("\nDebug: Tamanho do Registro a ser escrito: %d \n", sizeReg);
      insertIntoIndexMap(sizeReg);
      printIndexMap();
      nextPositionAvailable = nextAvailable(arq, sizeReg);

      getchar();
      break;
    }
    case 2: //remocao
    {
      printf("\n -----====== REMOCAO de Registro =====----- ");
      createIndexMap(arq);
      printIndexMap();
      printf("\nDigite o Codigo do registro a ser removido:");
      fpurge(stdin);   // fflush(stdin)  // no windows
      scanf("%d", &remover);
      i = 1;
      while (indexMap[i][2] != remover && indexMap[i][0] != -1 )  //code not found AND not EOF
      {
        printf("indexMap[%d][2] = %d - ", i, indexMap[i][2]);
        i++;
      }
      if (indexMap[i][2] == remover )
      {
        indexMap[i][1] = 42; // set * to the desired register
        fseek(arq,indexMap[i][3],0);  //position the cursor at the register to be removed
        fseek(arq, 4, 1);   // move 4 bytes to move to the validation char (@ or *)
        fwrite("*" , 1 , sizeof(char) , arq );  // writes * to remove logically the register
        printf("\nRegistro apagado");
        printIndexMap();
      }
      if ( indexMap[i][0] == -1 ) // if reachs the EOF, so the register wasn't founded
      {
        printf("Registro nao encontrado!");
      }
      fpurge(stdin);   // fflush(stdin)  // no windows
      getchar();
      break;
    }
    case 3: //compactacao
    {
      printf("\ncompactacao");
      getchar();
      break;
    }
    case 4: // Debug Renew indexMap
    {
      //createIndexMap(arq);
      printIndexMap();
      fpurge(stdin);   // fflush(stdin)  // no windows
      getchar();
      break;
    }
    case 0: // exit
    {
      printf("\nSaindo do programa!");
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

//[wip]

}

// Function that keeps the offsets for the registers in the file
void createIndexMap(FILE* arq) {

  int position = 1;
  int size, codigo, offsetFromStart = 0;  // initial offset for the first reg
  char available;

  indexMap[0][0] = 0; // the first register is always at the start of the file after the first byte
  //indexMap[0][3] = 1;
  printf("\nCreating IndexMap...");

  // check if the file is empty
  if ((fscanf (arq, "%04x", &size)) == EOF) {
    indexMap[0][0] = -1;  // offset to next (or -1 to end of the indexMap)
    indexMap[0][1] = 42;  // 42 = *   - Validation char

    return;
  }

  while (size != EOF) {
    if((fscanf(arq, "%04x", &size)) != EOF) //Return NULL when reach EOF
    {
        indexMap[position][3] = offsetFromStart;
        offsetFromStart += size + 4;   // sums the current offset since the beggining of the file
        indexMap[position][0] = size + 4; // add 4 to account for the next offset slot (int)
        fscanf(arq, "%c", &available);  // read the validation character
        fscanf(arq, "%04x", &codigo);   // read the 'Codigo' (key index)
        indexMap[position][1] = available;
        indexMap[position][2] = codigo;

        printf("\nDEBUG: #%d - Value: %d - Size: %d - Available: %c - Codigo %d - OffsetFromStart: %d"
                  , position, indexMap[position][0], size, indexMap[position][1]
                  , indexMap[position][2], indexMap[position][3]);  //Debug Only
        if (size != EOF) {
          fseek(arq, indexMap[position][0]-4, 1); // we skip to next register (-4 from the Codigo )
          position++;
        }
    }
    else
    {
        printf("\nDebug: EOF reached");
        size = -1;
        indexMap[position][0] = size;  // -1 determines the end of the indexMap
    }
  }
  printf("\nIndexList created!\n");
}

// Debug to check the IndexMap
void printIndexMap() {
  int i = 0;

  printf("\nPrinting IndexMap");

  while (indexMap[i][0] != -1) {
    printf("\n #%d - Value: %d - Available: %c - Codigo %d - OffsetFromTheStart: %d"
            , i, indexMap[i][0], indexMap[i][1], indexMap[i][2], indexMap[i][3]);
    i++;
  }

  printf("\nEnd of IndexMap");
}

int nextAvailable (FILE *arq, int sizeReg)
{
  int offset = 0, i = 0;
  while (indexMap[i][0] != 0)
  {
    offset += indexMap[i][0];
    i++;
  }
  return offset;
}

int main()
{
  FILE *arq;
  contato reg;
  int opcao = -1;
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
  printIndexMap();
  getchar();

  while (opcao != 0 ) // menu: 0 to exit
  {
    opcao = drawMenu();
    menu(opcao, reg, buffer, arq);
  }

  return 0;
}

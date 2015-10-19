// Authors: Dalton Lima & Lucas Pinheiro - oct 2015
// Aula 3 - tarefa 3 - ED2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function headers
void createIndexMap(FILE* arq, int arr[]);
void printIndexMap(int arr[]);
int getRegisterOffset (int regNum, int *indexMap);
void fetchFields(char* buffer, char* name, char* surName, char* address, char *number);
int fetchField(char *buffer, char *dest, int offset);

int main() {

  int arr[15],  //must exceed the max number of registers
      choice, offset, regSize;
  FILE *arq;

  char name[100];
  char surName[100];
  char address[100];
  char number[100];
  char buffer[300];

  // opening the data file
  if((arq = fopen("campo_var_reg_var.dad", "r+")) == NULL) {
    puts("Arquivo nao encontrado!");
    return 0;
  } else {
    createIndexMap(arq, arr);
  }

  // Debug: print the IndexMap
  printIndexMap(arr);

  puts("\nInsert the desired struct number: ");
  scanf("%d", &choice);

  //Calculates the offset for the desired register
  offset = getRegisterOffset (choice, arr);
  regSize = arr[choice] - 1;   //minus 1 to account for the "slot info"

  printf("\nDebug: Register# %d - Offset (start of the register): %d bytes - Full Register Size: %d\n", choice, offset, regSize);

  // Go to the desired position on the file
  fseek(arq, offset, SEEK_SET);

  //read the entire register and put at the buffer
  fread(buffer, regSize, 1, arq);
  buffer[arr[choice]-1] = '\0';  //just putting terminator in buffer

  //Debug: checking the buffer
  puts(buffer);

  fetchFields(buffer, name, surName, address, number);

  printf("Name: %s\n", name);
  printf("SurName: %s\n", surName);
  printf("Address: %s\n", address);
  printf("Number: %s\n", number);
  return 0;
}

// Function that keeps the offsets for the registers in the file
void createIndexMap(FILE* arq, int arr[]) {

  int size = 0;
  int position = 1;

  arr[0] = 1; //the first register is always at the start of the file after the first byte

  printf("\nCreating IndexMap...");
  while (size != EOF) {
    if( fread(&size, sizeof(char), 1, arq) ) //Return NULL when reach EOF
    {
        arr[position] = ((int)size) +1; // add 1 to account for the "info slot"
        //printf("\nDEBUG: #%d - Value: %d", position, arr[position]);  //Debug Only
        position++;
        fseek(arq, (int)size, 1);  //parameter SET_CUR won't work. Why?  respositioning the file pointer
    }
    else
    {
        printf("\nDebug: EOF reached");
        size = -1;
    }
  }
}

// Debug to check the IndexMap
void printIndexMap(int arr[])
{
  int i;
  for (i = 0; i < 10; i++ )
  {
      printf("\n #%d - Value: %d", i, arr[i]);
  }
}

int getRegisterOffset (int regNum, int *indexMap)
{
  int offset, i;
  offset = 0;
  for (i = 0; i < regNum; i++)
  {
    offset += indexMap[i];
  }

  return offset;
}

int fetchField(char *buffer, char *dest, int offset) {

  int size = 0;
  int i = offset;

  while (buffer[i] != '|') {
    size++;
    i++;
  }

  strncpy(dest, buffer+offset, size);
  dest[size] = '\0';
  offset += size + 1; // we skip the | character

  return offset;
}

void fetchFields(char* buffer, char* name, char* surName, char* address, char *number) {

  int offset = 0;

  offset = fetchField(buffer, name, offset);
  offset = fetchField(buffer, surName, offset);
  offset = fetchField(buffer, address, offset);
  offset = fetchField(buffer, number, offset);

}

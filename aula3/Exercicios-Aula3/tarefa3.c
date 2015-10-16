#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createIndexMap(FILE* arq, int arr[]);

int main() {

  int arr[10];
  FILE *arq;

  if((arq = fopen("campo_var_reg_var.dad", "r+")) == NULL) {
    puts("Arquivo nao encontrado!");
  } else {
    createIndexMap(arq, arr);
  }

// Debug: print the IndexMap
int i;
for (i = 0; i < 10; i++ )
{
    printf("\n #%d - Value: %d", i, arr[i]);
}

  return 0;
}

// Function that keeps the offsets for the registers in the file
void createIndexMap(FILE* arq, int arr[]) {

  int size = 0;
  int position = 0;

  printf("\nCreating IndexMap...");
  while (size != EOF) {
    if( fread(&size, sizeof(char), 1, arq) ) //Return NULL when reach EOF
    {
        arr[position] = (int) size;
        printf("\nDEBUG: #%d - Value: %d", position, arr[position]);
        position++;
        fseek(arq, (int)size, 1);  //SET_CUR nao aceito como parametro. Why?
    }
    else
    {
        printf("\nDebug: EOF reached");
        size = -1;
    }
  }


}

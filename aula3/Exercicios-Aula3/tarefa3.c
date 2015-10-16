#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  int arr[10];

  FILE *arq;

  if((arq = fopen("campo_var_reg_var.dad", "r+") == NULL)) {
    puts("Fodeu");
  } else {
    createIndexMap(arq, arr);
  }


  return 0;
}

// Function that keeps the offsets for the registers in the file
void createIndexMap(FILE* arq, int arr[]) {

  int size = 0;
  int position = 0;

  while (size != EOF) {
    fread(size, sizeof(char), 1, arq);
    arr[position] = (int) size;
    printf("%d\n", arr[position]);
    position++;
    fseek(arq, (int) size, SET_CUR);
  }

}

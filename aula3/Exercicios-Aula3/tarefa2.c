#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Tarefa 2: Arquivo campo_var_reg_fixo.dad
  O arquivo campo_var_reg_fixo.dad possui 10 registros gravados em um formato de campos de tamanho variável e registros de tamanho fixo.
  Foi utilizado o caractere ‘|’ como separador de campos.
  Cada registro possui um tamanho fixo igual à soma dos tamanhos máximos de cada um dos campos (da mesma maneira que na Tarefa 1).
  Um exemplo de registro nesta organização é:
    João|Moreira|XV de Novembro|110|<== espaço não utilizado ==>Eduardo|...
  Para a leitura de todos os registros, pode-se ler blocos de dados cujo tamanho é igual a um registro.
  Entretanto, é necessário criar uma sub-rotina capaz de identificar cada um dos campos separados pelo caractere ‘|’.
  Para a leitura de um registro especificado pelo usuário, pode-se calcular o número de bytes existentes entre o início do arquivo e o registro de interesse,
  da mesma maneira que na Tarefa 1. Mas a sub-rotina para identificar os campos também é necessária.
*/

void fetchFields(char *buffer, char* name, char* surName, char* address, char* number);
int fetchField(char* buffer, char* dest, int offset);

int main() {

  char name[15];
  char surName[15];
  char address[26];
  char number[4];
  int choice, offset;
  char buffer[60];

  FILE *arq;

  if ((arq = fopen("campo_var_reg_fixo.dad", "r+")) == NULL) {
    puts("The file could not be open!");
    return 1;
  } else {

    puts("Insert the desired struct number: ");
    scanf("%d", &choice);

    // Go to the desired position on the file
    offset = (choice-1) * sizeof(buffer);

    fseek(arq, offset, SEEK_SET);

    // Read data and put it on the buffer
    fread(buffer, sizeof(buffer), 1, arq);

    fetchFields(buffer, name, surName, address, number);

    printf("Name: %s\n", name);
    printf("SurName: %s\n", surName);
    printf("Address: %s\n", address);
    printf("Number: %s\n", number);
  }

  fclose(arq);

  return 0;
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

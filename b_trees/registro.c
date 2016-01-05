#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define primo 31  // numero predefinido para criarmos a hash table
int pega_registro(FILE *p_out, char *p_reg);
int insereRegistro();
int buscaRegistro();
void imprimirHash();
void imprimirArquivo();
char registro[90];

typedef struct hash{
  int codigo;
  int rrn;
} field;

typedef struct reg{
  int code;
  char name[30];
  char phone[30];
} ficha;

field hashTable[primo];
ficha arquivo[primo];
int cod, tam_reg;
FILE *out, *hash;

int main(void)
{

  int i, opcao = 1;
  char *pch;

  if ((out = fopen("arq.bin","r+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo, criando um novo arquivo...");
		getchar();
    out = fopen("arq.bin","w+b");
	 }

   if ((hash = fopen("hash.bin","r+b")) == NULL)
 	 {
 		  printf("Nao foi possivel abrir a hash table, criando um novo arquivo...");
 		   getchar();
       hash = fopen("hash.bin","w+b"); //initializing the hashTable
       for (i = 0; i <= primo; i++)
       {
          hashTable[i].codigo = -1;
          hashTable[i].rrn = -1;
          arquivo[i].code = -1;
          //fprintf(hash, "|%d|%d|%d|" ,i ,&(hashTable[i].codigo), &(hashTable[i].rrn));
       }
 	 }

  //insertion
  while (opcao != 0)
  {
    printf("[1] - Inserir registro\n" );
    printf("[2] - Listar todos os registros\n" );
    printf("[3] - Listar registro por codigo\n" );
    printf("[0] - Sair\n" );
    printf("\nEscolha uma opcao: " );
    scanf("%d",&opcao);

    switch (opcao) {
      case 1:{  //insert a register
        insereRegistro();
        break;
      }
      case 2:{ // List all register

        for (i = 0; i <= primo; i++)
        {
          printf("posicao: %d: ", i);
          printf("%d - ", arquivo[i].code);
          printf("%s - ", arquivo[i].name);
          printf("%s * ", arquivo[i].phone);
          printf("hash: %d - ", hashTable[i].codigo);
          printf("%d \n ", hashTable[i].rrn);
        }
        break;
      }
      case 3:{  //List a specific register
          buscaRegistro();
        break;
      }
      case 0:{
        // exit
        break;
      }
       default:{
         printf("\nOpcao invalida!\n");
         break;
      }

      imprimirArquivo();
      imprimirHash();

    }
  }
/*
  fseek(out,0,0);
  tam_reg = pega_registro(out,registro);
  while (tam_reg > 0)
   {
    pch = strtok(registro,"|");
    while (pch != NULL)
      {
        printf("%s\n",pch);
        pch = strtok(NULL,"|");
      }
    printf("\n");
    tam_reg = pega_registro(out,registro);
    getchar();
   }

  fclose(out);

  getchar();
  */
}

int pega_registro(FILE *p_out, char *p_reg)
{
     int bytes;

     if (!fread(&bytes, sizeof(int), 1, p_out))
       return 0;
     else {
            fread(p_reg, bytes, 1, p_out);
            return bytes;
          }
}

int insereRegistro()
{
  char nome[30], fone[30], registro[90];
  int cod, tam_reg;
  int address,originalAddress,     // resultado do mod do Codigo pelo primo escolhido
  collision = 0;  // indica se houve colisao e qtas tentativas na insercao

  printf("cod: ");
  scanf("%d",&cod);
  fpurge(stdin);

  address = cod % primo;
  originalAddress = address;
  printf("[Debug]: hash: %d \n", address);
  //fprintf(hash,"%d|",address);  // escreve o endereco no hash table
  printf("nome: ");
  fpurge(stdin);
  gets(nome);
  printf("fone: ");
  fpurge(stdin);
  gets(fone);

  sprintf(registro,"%d|%s|%s|",cod,nome,fone);
  tam_reg = strlen(registro);
  tam_reg++;
  //fwrite(&tam_reg, sizeof(int), 1, out);
  //fwrite(registro, sizeof(char), tam_reg, out);

  do
  {
    if ( arquivo[address].code == -1 ) //achamos local pra inserir
    {
      arquivo[address].code = cod;
      strcpy(arquivo[address].name,nome);
      strcpy(arquivo[address].phone,fone);
      printf("[Debug]: Chave %d inserida com sucesso\n", cod);
      if (collision != 0) {   // TODO not working yet
        printf("[Debug]: Colisao\n");
        printf("Tentativa %d \n", collision);
      }
    return collision;
    }
    else
    {
      collision++;
      address++;
      if (address == primo) address = 0;  //reached the end of the hash and loop
    }
  }while (originalAddress != address);  //check if we loop through all hashTable

  printf("[Debug]: Chave NAO inserida! Hash cheia!\n");
  return -1;
}

int buscaRegistro()
{
  int cod, address, originalAddress, i;
  printf("cod: ");
  scanf("%d",&cod);
  fpurge(stdin);

  address = cod % primo;
  originalAddress = address;

  do
  {
    if ( arquivo[address].code == cod )
    {
      printf("%d\n", i);
      printf("%d - ", arquivo[address].code);
      printf("%s - ", arquivo[address].name);
      printf("%s \n", arquivo[address].phone);
      return address;
    }
    else
    {
      address++;
      if (address == primo) address = 0;  //closes the loop
    }

  } while (originalAddress != address);

  //if not found returns -1
  printf("Registro nao encontrado!\n");
  return -1;
}

void imprimirHash()
{
  fseek(hash,0,0);
  int i = 0;
  for (i = 0; i <= primo; i++ )
  {
    fprintf(hash, "%d|", hashTable[i].codigo);
    fprintf(hash, "%d\n", hashTable[i].rrn);
  }

}

void imprimirArquivo()
{
  fseek(out,0,0);
  int i = 0;
  for (i = 0; i <= primo; i++ )
  {
    fprintf(out, "%d|", arquivo[i].code);
    fprintf(out, "%s|", arquivo[i].name);
    fprintf(out, "%s\n", arquivo[i].phone);
  }
}

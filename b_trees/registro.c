#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO TAMANHO VARIAVEL COM INDICADOR DE TAMANHO
int pega_registro(FILE *p_out, char *p_reg);

int main(void)
{
  char nome[30], fone[30], registro[90];
  FILE *out;
  int cod, tam_reg;
  char *pch;

  if ((out = fopen("arq.bin","r+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo, criando um novo arquivo...");
		getchar();
    out = fopen("arq.bin","w+b");
	 }

  printf("cod: ");
  scanf("%d",&cod);
  fpurge(stdin);

  while (cod != 0)
   {
        printf("nome: ");
        fpurge(stdin);
        gets(nome);
        printf("fone: ");
        fpurge(stdin);
        gets(fone);

        sprintf(registro,"%d|%s|%s|",cod,nome,fone);
        tam_reg = strlen(registro);
        tam_reg++;
        fwrite(&tam_reg, sizeof(int), 1, out);
        fwrite(registro, sizeof(char), tam_reg, out);

        printf("\ncod: ");
        scanf("%d",&cod);
        fpurge(stdin);
   }

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

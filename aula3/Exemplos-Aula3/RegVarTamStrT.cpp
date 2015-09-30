#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO TAMANHO VARIAVEL COM INDICADOR DE TAMANHO
int pega_registro(FILE *p_out, char *p_reg);

int main(void)
{
  char nome[30], end[30], registro[90];
  char teste[30];
  FILE *out;
  int ra, tam_reg;
  char *pch;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getch();
		return 0;
	 }
	 
  printf("ra: ");
  scanf("%d",&ra);
  fflush(stdin);          
  
  while (ra != 0)	 
   {
        printf("nome: ");
        gets(nome);
        printf("endereco: ");
        gets(end);      
        
        sprintf(registro,"%d|%s|%s|",ra,nome,end);
        tam_reg = strlen(registro);
        tam_reg++;
        fwrite(&tam_reg, sizeof(int), 1, out);
        fwrite(registro, sizeof(char), tam_reg, out);
        
        printf("\nra: ");
        scanf("%d",&ra);        
        fflush(stdin);             	    
   }    

  fseek(out,0,0);
  tam_reg = pega_registro(out,registro);
  while (tam_reg > 0)
   {
    pch = strtok(registro,"|");
    while (pch != NULL)
      {
        printf("%s\n",pch);
        //strcpy(teste,pch);
        //printf("%s\n",teste);
        pch = strtok(NULL,"|");
      }
    printf("\n");
    tam_reg = pega_registro(out,registro);  
    getch();      
   } 

  fclose(out);

  getch();  
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

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO COM TAMANHO FIXO CAMPO VARIÁVEL
int main(void)
{
  char nome[30], sobrenome[30], end[30];
  char registro[90];
  FILE *out;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getche();
		return 0;
	 }
	 
  printf("nome: ");
  gets(nome);
  
  while (strlen(nome) > 0)	 
   {
        printf("sobrenome: ");
        gets(sobrenome);
        printf("endereco: ");
        gets(end);      
        
        sprintf(registro,"%s|%s|%s|",nome,sobrenome,end);
        fwrite(registro,sizeof(registro),1,out);                  
	            
        printf("nome: ");
        gets(nome);           	    
   }    

  fclose(out);

  getch();
}

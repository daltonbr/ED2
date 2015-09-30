#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO CAMPO COM TAMANHO FIXO
int main(void)
{
  char nome[30], sobrenome[30], end[30];
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
        
  	    fwrite(nome,sizeof(nome),1,out);                  
	    fwrite(sobrenome,sizeof(sobrenome),1,out);
	    fwrite(end,sizeof(end),1,out);    
        
        printf("nome: ");
        gets(nome);           	    
   }    

  fclose(out);

  getch();
}

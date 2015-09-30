#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO COM TAMANHO FIXO CAMPO FIXO
int main(void)
{
  struct estrutura
  {
    char nome[30], sobrenome[30], end[30];
  }ts;
  
  FILE *out;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getche();
		return 0;
	 }
	 
  printf("nome: ");
  gets(ts.nome);
  
  while (strlen(ts.nome) > 0)	 
   {
        printf("sobrenome: ");
        gets(ts.sobrenome);
        printf("endereco: ");
        gets(ts.end);      
        
  	    fwrite(&ts,sizeof(ts),1,out);                  
	            
        printf("nome: ");
        gets(ts.nome);           	    
   }    

  rewind(out);
  while (fread(&ts,sizeof(ts),1,out))
   {
        printf("\nnome: %s",ts.nome);
        printf("\nsobrenome: %s",ts.sobrenome);
        printf("\nendereco: %s",ts.end);
        getch();
   }
   
  fclose(out);

  getch();
}

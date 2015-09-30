#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO CAMPO COM INDICADOR DE COMPRIMENTO
int main(void)
{
  char nome[30], sobrenome[30], end[30];
  FILE *out;
  int tam;

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
        
  	    tam = strlen(nome);
  	    tam++;
  	    fwrite(&tam,sizeof(int),1,out);                 
        fwrite(nome,sizeof(char),tam,out); 
        
	    tam = strlen(sobrenome);
	    tam++;
  	    fwrite(&tam,sizeof(int),1,out);                 
        fwrite(sobrenome,sizeof(char),tam,out);
        
        tam = strlen(end);
        tam++;
  	    fwrite(&tam,sizeof(int),1,out);                         
	    fwrite(end,sizeof(char),tam,out);    
        
        printf("nome: ");
        gets(nome);           	    
   }   
    
  rewind(out);
  char buffer[255];
  while (fread(&tam,sizeof(int),1,out))
   {      
        fread(buffer,sizeof(char),tam,out);
        //buffer[tam]='\0';
        
        printf("\ncampo: %s",buffer);
        getch();
   }

  fclose(out);

  getch();
}

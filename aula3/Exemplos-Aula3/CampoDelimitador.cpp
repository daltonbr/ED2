#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO CAMPO COM DELIMITADORES
int pega_campo(FILE *p_out, char *p_campo);

int main(void)
{
  char nome[30], sobrenome[30], end[30], campo[30];
  char buffer[100];
  FILE *out;
  int tam_campo;

  if ((out = fopen("arq.bin","w+b")) == NULL)
	 {
		printf("Nao foi possivel abrir o arquivo");
		getch();
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
        
        sprintf(buffer,"%s|%s|%s|",nome,sobrenome,end);
        fwrite(buffer,sizeof(char),strlen(buffer),out);
        
        printf("nome: ");
        gets(nome);           	    
   }    

  fseek(out,0,0);
  tam_campo = pega_campo(out,campo);	 
  while (tam_campo > 0)
   {        
        printf("tamanho: %d\n",tam_campo);
        printf("campo: %s\n\n",campo);  
        tam_campo = pega_campo(out,campo);        
        getch();      
   } 
  
  fclose(out);

  getch();  
}

int pega_campo(FILE *p_out, char *p_campo)
{
     char ch;
     int i=0;

     p_campo[i] = '\0';
     
     /*ch = fgetc(p_out);     
     while ((ch != '|') && (ch != EOF))
      {                      
           p_campo[i] = ch;
           i++;
           ch = fgetc(p_out);           
      }     */
      
     while (fread(&ch,sizeof(char),1,p_out))
       {
           if (ch == '|')
             break;
           else p_campo[i] = ch;
           
           i++;
       }
     
     p_campo[i] = '\0';
     
     return strlen(p_campo);
}     

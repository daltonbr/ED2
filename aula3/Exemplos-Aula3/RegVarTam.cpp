#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
//EXEMPLO REGISTRO TAMANHO VARIAVEL COM INDICADOR DE TAMANHO
int pega_campo(char *p_registro, int *p_pos, char *p_campo);
int pega_registro(FILE *p_out, char *p_reg);

int main(void)
{
  char nome[30], end[30], campo[30], registro[90];
  FILE *out;
  int ra, tam_campo, tam_reg, pos;

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
        pos = 0;        
        tam_campo = pega_campo(registro,&pos,campo);        
        while (pos <= tam_reg)
          {            
            printf("tamanho: %d\n",tam_campo);
            printf("campo: %s\n\n",campo);            
            tam_campo = pega_campo(registro,&pos,campo);                                
          }  
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

int pega_campo(char *p_registro, int *p_pos, char *p_campo)
{
     char ch;
     int i=0;

     p_campo[i] = '\0';
     
     ch = p_registro[*p_pos];     
     while ((ch != '|') && (ch!=EOF))
      {                      
           p_campo[i] = ch;
           i++;
           ch = p_registro[++(*p_pos)];     
      }     
     ++(*p_pos); 
     p_campo[i] = '\0';
     
     return strlen(p_campo);
}     

#include <stdio.h>

void PrintToEOF();

void PrintToEOF(FILE *file)
{
    char ch;
    ch = fgetc(file);
    while ( ch != EOF )
    {
        printf("%c", ch);
        ch = fgetc(file);
    }
}

int main() {

    FILE *out;
    char ch;
    int numberOfLines = 1;
/*

    C string containing a file access mode. It can be:
"r"	read: Open file for input operations. The file must exist.
"w"	write: Create an empty file for output operations. If a file with the same name already exists, its contents are discarded and the file is treated as a new empty file.
"a"	append: Open file for output at the end of a file. Output operations always write data at the end of the file, expanding it. Repositioning operations (fseek, fsetpos, rewind) are ignored. The file is created if it does not exist.
"r+"	read/update: Open a file for update (both for input and output). The file must exist.
"w+"	write/update: Create an empty file and open it for update (both for input and output). If a file with the same name already exists its contents are discarded and the file is treated as a new empty file.
"a+"	append/update: Open a file for update (both for input and output) with all output operations writing data at the end of the file. Repositioning operations (fseek, fsetpos, rewind) affects the next input operations, but output operations move the position back to the end of file. The file is created if it does not exist.

*/
    //printf("Enter the name of the file that will be tailed: ");
    //print ("Enter the number of lines to be tailed: ");

    if ((out = fopen("output.txt", "r+")) == NULL) {
        puts("Arquivo nao pode ser aberto");
        return 0;
    }
    else
    {
        printf("Arquivo aberto com sucesso!\n");
        printf("Digite o numero de quebra de linhas: ");
        scanf("%d", &numberOfLines);
    }

    // jumps to the EOF, and move 2 positions back
    fseek(out, -2, 2);  //o ultimo parametro (2) se refere ao fim do arquivo
    ch = fgetc(out);    // reads the last char
    if (ch != '\n'){
        numberOfLines --; //decrements the count
        printf("\nDebug: fim de linha encontrado!\n");
    }

    if ( numberOfLines == 0 ) //se contagem chegou ao fim, imprime tudo ate EOF
    {
        PrintToEOF(out);
        return 0;
    }
        do
        {
            fseek(out, -3, 1);  //agora usa posica relativa pra retroceder 3 posicoes
            ch = fgetc(out);  // le uma posicao

            printf(" Debug: %c", ch);   //Debug only
            //if (ch == '\n') numberOfLines--;   // encontrou \n decrementa contador - linha mais enxuta sem o debug abaixo
            if (ch == '\n'){
                numberOfLines --; //decrements the count
                printf("\nDebug: fim de linha encontrado!\n");
            }

            if ( numberOfLines == 0 ) //se contagem chegou ao fim, imprime tudo ate EOF - encapsular esta parte?
            {
                PrintToEOF(out);
                return 0;   //fim do programa
            }
            ch = fgetc(out);
        } while (numberOfLines != 0);

    // TODO: implement a string input to enter the name of the file that will be used
    // TODO: [BUG] - se o numero entrado exceder o inicio do arquivo, entramos num loop infinito
    //                devemos checar se chegamos no inicio do arquivo?

    return 0;
}

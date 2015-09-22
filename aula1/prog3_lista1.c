#include <stdio.h>

int main() {

    FILE *out;
    char ch;
    int lineFeedCount;
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
    if ((out = fopen("output.txt", "r+")) == NULL) {
        puts("Arquivo nao pode ser aberto");
        return 0;
    }
    else
        printf("Arquivo aberto com sucesso!\n");

    fseek(out, -2, 2);  //o ultimo parametro (2) se refere ao fim do arquivo

    ch = fgetc(out);
    if (ch != EOF) {
        printf("Debug: %c", ch);
    }

    // while ((ch = fgetc(stdin)) != 0x1B) {
    //     fwrite(&ch, sizeof(char), 1, out);
    // }

    // TODO: implement a utility similar to UNIX command tail

    return 0;
}

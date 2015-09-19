#include <stdio.h>

int main() {

    FILE *out;
    char ch;
    int lineFeedCount;
    int numberOfLines = 1;

    if ((out = fopen("output.txt", "w+")) == NULL) {
        puts("Arquivo nao pode ser aberto");
        return 0;
    }

    while ((ch = fgetc(stdin)) != 0x1B) {
        fwrite(&ch, sizeof(char), 1, out);
    }

    // TODO: implement a utility similar to UNIX command tail

    return 0;
}

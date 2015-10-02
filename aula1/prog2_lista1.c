#include <stdio.h>
#include <ctype.h>

void printASCII(char *buffer);

int main() {

    FILE *out;
    char ch, ch2;
    char buffer[17];

    int i = 0;
    int format; // 0 -> HEX, 1 -> ASCII
    int offset;

    if((out = fopen("output.txt", "r+")) == NULL) {
        puts("Arquivo nao pode ser aberto");
        return 0;
    }

    while ((ch = fgetc(stdin)) != 0x1B) {
        fwrite(&ch, sizeof(char), 1, out);
    }

    rewind(out);
    do {
        ch2 = fgetc(out);
        if (ch2 != EOF) {
            printf("%X", ch2);
            buffer[i] = ch2;
        }
        i++;
        if (i == 16 || ch2 == EOF) {
            printf(" ");
            buffer[i] = '\0';
            printASCII(buffer);
            i = 0;
            printf("\n");
        }
    } while(ch2 != EOF);

    printf("\n");

    return 0;
}

void printASCII(char *buffer) {

    char ch;
    int i = 0;

    while(i < 16) {
        ch = buffer[i];
        if (ch == '\0') {
            return;
        }
        if (isprint(ch)) {
            printf("%c", ch);
        } else {
            printf(".");
        }
        i++;
    }

}

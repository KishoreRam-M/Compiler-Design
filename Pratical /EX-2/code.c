#include <stdio.h>
#include <ctype.h>
#include <string.h>

void main() {
    FILE *fi, *fo, *fop, *fk;
    char c, word[20], keyword[20], oper[20], filename[20];
    int line = 1, flag;

    printf("Enter the input filename: ");
    scanf("%s", filename);

    fi = fopen(filename, "r");
    fo = fopen("inter.c", "w");
    fop = fopen("oper.c", "r");
    fk = fopen("key.c", "r");

    // Tokenize input file and add $ at line breaks
    while ((c = fgetc(fi)) != EOF) {
        if (c == '\n')
            fprintf(fo, " $\n");
        else
            fprintf(fo, "%c", c);
    }

    fclose(fi);
    fclose(fo);

    // Read inter.c and perform lexical analysis
    fi = fopen("inter.c", "r");
    printf("\nLexical Analysis\nLine: %d\n", line++);

    while (fscanf(fi, "%s", word) != EOF) {
        flag = 0;

        if (strcmp(word, "$") == 0) {
            printf("\nLine: %d\n", line++);
            continue;
        }

        // Check in operator file
        rewind(fop);
        while (fscanf(fop, "%s", oper) != EOF) {
            if (strcmp(word, oper) == 0) {
                fscanf(fop, "%s", oper);
                printf("\t%s\t:\t%s\n", word, oper);
                flag = 1;
                break;
            }
        }

        // Check in keyword file
        rewind(fk);
        while (fscanf(fk, "%s", keyword) != EOF) {
            if (strcmp(word, keyword) == 0) {
                printf("\t%s\t:\tKeyword\n", word);
                flag = 1;
                break;
            }
        }

        // If not keyword or operator
        if (!flag) {
            if (isdigit(word[0]))
                printf("\t%s\t:\tConstant\n", word);
            else
                printf("\t%s\t:\tIdentifier\n", word);
        }
    }

    fclose(fi);
    fclose(fop);
    fclose(fk);
}


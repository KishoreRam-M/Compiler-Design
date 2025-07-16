#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void main() {
    char expr[100], symbols[20];
    int *addr[20], count = 0;
    char ch = 'y', search;
    int found = 0;

    printf("Enter an expression ending with $: ");
    int i = 0;
    char c;
    while ((c = getchar()) != '$') {
        if (isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '(' || c == ')') {
            symbols[count] = c;
            addr[count] = (int*)malloc(sizeof(int));
            count++;
        }
    }

    printf("\nSymbol Table\n");
    printf("Symbol\tAddress\t\tType\n");
    for (i = 0; i < count; i++) {
        printf("  %c\t%p\t%s\n", symbols[i], addr[i],
               isalpha(symbols[i]) ? "Identifier" : "Operator");
    }

    while (ch == 'y') {
        printf("\nEnter symbol to search: ");
        scanf(" %c", &search);
        found = 0;

        for (i = 0; i < count; i++) {
            if (symbols[i] == search) {
                printf("Symbol found: %c at address %p\n", search, addr[i]);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Symbol not found.\n");
        }

        printf("Do you want to search again? (y/n): ");
        scanf(" %c", &ch);
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char non_terminals[50];
char terminals[50];
char start_symbol;
int num_prods = 0;
char target[100];

int found = 0;
char path[100][100];

typedef struct {
    char lhs;
    char rhs[50];
} Production;

Production prods[50];

int is_non_terminal(char c) {
    return strchr(non_terminals, c) != NULL;
}

void replace_leftmost(char *src, char target_nt, const char *replacement, char *dest) {
    int i = 0;
    while (src[i] != '\0' && src[i] != target_nt) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    if (src[i] == target_nt) {
        strcat(dest, replacement);
        strcat(dest, src + i + 1);
    }
}

void derive(char *current, int depth, int max_depth) {
    if (found) return;

    strcpy(path[depth], current);

    char leftmost_nt = '\0';
    for (int i = 0; current[i] != '\0'; i++) {
        if (is_non_terminal(current[i])) {
            leftmost_nt = current[i];
            break;
        }
    }

    if (leftmost_nt == '\0') {
        if (strcmp(current, target) == 0) {
            found = 1;
            printf("\nShortest Leftmost Derivation found for '%s':\n", target);
            for (int i = 0; i <= depth; i++) {
                if (strlen(path[i]) == 0) {
                    printf("E"); 
                } else {
                    printf("%s", path[i]);
                }
                if (i < depth) printf(" -> ");
            }
            printf("\n");
        }
        return;
    }

    if (depth >= max_depth) return;

    if (strlen(current) > strlen(target) + 10) return;

    char next_form[200];
    for (int p = 0; p < num_prods; p++) {
        if (prods[p].lhs == leftmost_nt) {
            if (strcmp(prods[p].rhs, "e") == 0 || strcmp(prods[p].rhs, "E") == 0) {
                replace_leftmost(current, leftmost_nt, "", next_form);
            } else {
                replace_leftmost(current, leftmost_nt, prods[p].rhs, next_form);
            }
            derive(next_form, depth + 1, max_depth);
            if (found) return; 
        }
    }
}

int main() {
     printf("Kanak Waradkar 24B-0CO-030");
    printf("Enter non-terminals (e.g., SAB): ");
    scanf("%49s", non_terminals);

    printf("Enter terminals (e.g., ab): ");
    scanf("%49s", terminals);

    printf("Enter Start Symbol: ");
    scanf(" %c", &start_symbol);

    printf("Enter number of productions: ");
    scanf("%d", &num_prods);

    printf("Enter productions (Format: LHS RHS, use 'e' for epsilon):\n");
    for (int i = 0; i < num_prods; i++) {
        scanf(" %c %s", &prods[i].lhs, prods[i].rhs);
    }
    
    printf("Enter string to derive: ");
    scanf("%99s", target);

    int max_search_depth = strlen(target) * 3 + 5;
    char start_str[2] = {start_symbol, '\0'};

    for (int limit = 1; limit <= max_search_depth; limit++) {
        derive(start_str, 0, limit);
        if (found) break;
    }

    if (!found) {
        printf("\nString '%s' cannot be derived by this grammar, or exceeds search limits.\n", target);
    }

    return 0;
}
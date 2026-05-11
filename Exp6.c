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
printf("$\nShortest$ Leftmost Derivation found for '%s':\n", strlen(target) == 0 ? "epsilon" : target);
for (int i = 0; i <= depth; i++) {
if (strlen(path[i]) == 0) {
printf("e");
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
strcpy(non_terminals, "S");
strcpy(terminals, "ab");
start_symbol = 'S';
num_prods = 5;
prods[0].lhs = 'S'; prods[1].lhs = 'S'; prods[2].lhs = 'S'; prods[3].lhs = 'S'; prods[4].lhs = 'S';
strcpy(prods[0].rhs, "e");
strcpy(prods[1].rhs, "a");
strcpy(prods[2].rhs, "b");
strcpy(prods[3].rhs, "aSa");
strcpy(prods[4].rhs, "bSb");
printf("\nS->e");
printf("\nS->a|b");
printf("\nS->aSa|bSb");
printf("\nEnter string to derive (type 'e' for empty): ");
scanf("%99s", target);
if (strcmp(target, "e") == 0) {
target[0] = '\0';
}
int max_search_depth = strlen(target) * 3 + 5;
char start_str[2] = {start_symbol, '\0'};
for (int limit = 1; limit <= max_search_depth; limit++) {
derive(start_str, 0, limit);
if (found) break;
}
if (!found) {
printf("\nString 's' cannot be derived.\n", strlen(target) == 0 ? "epsilon" : target);
}
return 0;
}



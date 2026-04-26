//Convwrsion from nfa to dfa using subset Conversion method print accordingly
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_states, n_sym;
char sym[20];
int nfa[50][20][51];
int start_st;
int n_fin;
int fin[50];

int dfa_st[100][50];
int dfa_tr[100][20];
int n_dfa = 0;

int get_dfa_state(int *set) {
    for (int i = 0; i < n_dfa; i++) {
        int match = 1;
        for (int j = 0; j < n_states; j++) {
            if (dfa_st[i][j] != set[j]) {
                match = 0;
                break;
            }
        }
        if (match) return i;
    }
    for (int j = 0; j < n_states; j++) {
        dfa_st[n_dfa][j] = set[j];
    }
    return n_dfa++;
}

void print_set(int *set) {
    printf("{");
    int first = 1;
    for (int i = 0; i < n_states; i++) {
        if (set[i]) {
            if (!first) printf(", ");
            printf("q%d", i);
            first = 0;
        }
    }
    printf("}");
}

int main() {
     printf("24B-0CO-030 Kanak Waradkar\n");
    printf("Enter number of states: ");
    scanf("%d", &n_states);
    printf("Enter number of input symbols: ");
    scanf("%d", &n_sym);
    printf("Enter input symbols: ");
    for (int i = 0; i < n_sym; i++) {
        scanf(" %c", &sym[i]);
    }
    printf("Enter start state: ");
    scanf("%d", &start_st);
    printf("Enter number of final states: ");
    scanf("%d", &n_fin);
    if (n_fin > 0) {
        printf("Enter final states: ");
        for (int i = 0; i < n_fin; i++) {
            scanf("%d", &fin[i]);
        }
    }

    for (int i = 0; i < n_states; i++) {
        for (int j = 0; j < n_sym; j++) {
            printf("Transitions from q%d on '%c' (count followed by destination states): ", i, sym[j]);
            scanf("%d", &nfa[i][j][0]);
            for (int k = 1; k <= nfa[i][j][0]; k++) {
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }

    int init_set[50] = {0};
    init_set[start_st] = 1;

    int q[100], head = 0, tail = 0;
    q[tail++] = get_dfa_state(init_set);

    while (head < tail) {
        int curr_dfa = q[head++];
        for (int i = 0; i < n_sym; i++) {
            int next_set[50] = {0};
            int is_empty = 1;
            for (int j = 0; j < n_states; j++) {
                if (dfa_st[curr_dfa][j]) {
                    for (int k = 1; k <= nfa[j][i][0]; k++) {
                        int dest = nfa[j][i][k];
                        next_set[dest] = 1;
                        is_empty = 0;
                    }
                }
            }

            if (!is_empty) {
                int prev_n = n_dfa;
                int next_dfa = get_dfa_state(next_set);
                dfa_tr[curr_dfa][i] = next_dfa;
                if (next_dfa == prev_n) {
                    q[tail++] = next_dfa;
                }
            } else {
                dfa_tr[curr_dfa][i] = -1; 
            }
        }
    }

    printf("\n--- DFA Transitions ---\n");
    for (int i = 0; i < n_dfa; i++) {
        for (int j = 0; j < n_sym; j++) {
            printf("DFA State %d ", i);
            print_set(dfa_st[i]);
            printf(" -- %c --> ", sym[j]);
            if (dfa_tr[i][j] != -1) {
                printf("DFA State %d ", dfa_tr[i][j]);
                print_set(dfa_st[dfa_tr[i][j]]);
            } else {
                printf("Dead State {Phi}");
            }
            printf("\n");
        }
    }

    printf("\n--- DFA Final States ---\n");
    for (int i = 0; i < n_dfa; i++) {
        int is_final = 0;
        for (int j = 0; j < n_states; j++) {
            if (dfa_st[i][j]) {
                for (int k = 0; k < n_fin; k++) {
                    if (j == fin[k]) {
                        is_final = 1;
                        break;
                    }
                }
            }
            if (is_final) break;
        }
        if (is_final) {
            printf("DFA State %d ", i);
            print_set(dfa_st[i]);
            printf("\n");
        }
    }

    return 0;
}
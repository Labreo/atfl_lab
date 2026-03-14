#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 50
#define MAX_SYMBOLS 20
#define MAX_STRING 100
#define MAX_TRANSITIONS 10

int num_states, num_symbols;
char alphabet[MAX_SYMBOLS];
int transition_table[MAX_STATES][MAX_SYMBOLS][MAX_TRANSITIONS];
int transition_count[MAX_STATES][MAX_SYMBOLS];

int get_symbol_index(char c) {
    for (int i = 0; i < num_symbols; i++) {
        if (alphabet[i] == c) return i;
    }
    return -1;
}

void epsilon_closure(bool states[], bool result[]) {
    for (int i = 0; i < num_states; i++) result[i] = states[i];
    bool changed = true;
    int eps_index = get_symbol_index('*');
    if (eps_index == -1) return;
    while (changed) {
        changed = false;
        for (int i = 0; i < num_states; i++) {
            if (result[i]) {
                for (int j = 0; j < transition_count[i][eps_index]; j++) {
                    int next = transition_table[i][eps_index][j];
                    if (!result[next]) {
                        result[next] = true;
                        changed = true;
                    }
                }
            }
        }
    }
}

void move(bool current[], int symbol_index, bool result[]) {
    for (int i = 0; i < num_states; i++) result[i] = false;
    for (int i = 0; i < num_states; i++) {
        if (current[i]) {
            for (int j = 0; j < transition_count[i][symbol_index]; j++) {
                int next = transition_table[i][symbol_index][j];
                result[next] = true;
            }
        }
    }
}

void print_state_set(bool states[]) {
    printf("{");
    bool first = true;
    for (int i = 0; i < num_states; i++) {
        if (states[i]) {
            if (!first) printf(", ");
            printf("q%d", i);
            first = false;
        }
    }
    printf("}");
}

int main() {
    printf("Kanak Waradkar 24B-0CO-030");
    int initial_state;
    printf("Enter number of states: ");
    scanf("%d", &num_states);
    printf("Enter number of alphabet symbols: ");
    scanf("%d", &num_symbols);
    printf("Enter the alphabet symbols (use * for epsilon): ");
    scanf("%s", alphabet);
    printf("Enter initial state: ");
    scanf("%d", &initial_state);

    memset(transition_count, 0, sizeof(transition_count));

    printf("Enter transition table:\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            printf("Number of transitions for q%d on '%c': ", i, alphabet[j]);
            scanf("%d", &transition_count[i][j]);
            for (int k = 0; k < transition_count[i][j]; k++) {
                printf("  Transition %d goes to state: ", k + 1);
                scanf("%d", &transition_table[i][j][k]);
            }
        }
    }

    int num_final_states;
    printf("Enter number of final states: ");
    scanf("%d", &num_final_states);
    int final_states[MAX_STATES];
    printf("Enter the final states: ");
    for (int i = 0; i < num_final_states; i++) {
        scanf("%d", &final_states[i]);
    }

    char input_string[MAX_STRING];
    while (1) {
        printf("\nEnter string to evaluate (-1 to exit): ");
        scanf("%s", input_string);
        if (strcmp(input_string, "-1") == 0) break;

        bool current[MAX_STATES] = {false};
        bool temp[MAX_STATES] = {false};
        bool after_closure[MAX_STATES] = {false};

        current[initial_state] = true;
        epsilon_closure(current, after_closure);
        memcpy(current, after_closure, sizeof(current));

        printf("\nExtended transition function:\n");
        printf("Initial set after epsilon closure: ");
        print_state_set(current);
        printf("\n");

        bool valid_string = true;
        int string_length = strlen(input_string);

        for (int i = 0; i < string_length; i++) {
            char c = input_string[i];
            if (c == '*') {
                printf("error: cannot use epsilon in input string.\n");
                valid_string = false;
                break;
            }
            int symbol_index = get_symbol_index(c);
            if (symbol_index == -1) {
                printf("error: symbol '%c' not in alphabet.\n", c);
                valid_string = false;
                break;
            }
            move(current, symbol_index, temp);
            epsilon_closure(temp, after_closure);
            memcpy(current, after_closure, sizeof(current));
            printf("d(");
            print_state_set(current);
            printf(", %c) -> ", c);
            print_state_set(current);
            printf("\n");
        }

        if (!valid_string) {
            printf("\nResult: Rejected\n");
            continue;
        }

        bool is_accepted = false;
        for (int i = 0; i < num_final_states; i++) {
            if (current[final_states[i]]) {
                is_accepted = true;
                break;
            }
        }
        printf("\nResult: %s\n", is_accepted ? "Accepted" : "Rejected");
    }
    return 0;
}
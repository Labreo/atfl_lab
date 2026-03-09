#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 50
#define MAX_SYMBOLS 20
#define MAX_STRING 100

int get_symbol_index(char c, char alphabet[], int num_symbols) {
    for (int i = 0; i < num_symbols; i++) {
        if (alphabet[i] == c) { return i;}}
    return -1;}

int main() {
    int num_states, num_symbols,initial_state;
    
    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Enter the initial state:");
    scanf("%d", &initial_state);

    int num_transistion[num_states];
    char alphabet[MAX_SYMBOLS];
    char a[100];
    printf("Enter the alphabet symbols(Enter * to represent lambda): ");
    scanf("%s", alphabet);


    for (int i = 0; i < num_states; i++) {
        printf("Enter what is the amount of transistions of for the given state q%d:\n",i);
        scanf("%d",&num_transistion[i]);
    }
     
     int transition_table[MAX_STATES][MAX_SYMBOLS];
    printf("Enter the transition table (use -1 to route to the trap state).\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_transistion[i]; j++) {
            printf("Enter the No:%d input for q%d:",j+1,i);
            scanf("%s",a);
            printf("State q%d on input '%s' goes to state q: ", i, a);
            scanf("%d", &transition_table[i][j]);
        }
    }

    int trap_state = num_states;
    num_states++;

    for (int i = 0; i < num_symbols; i++) {
        transition_table[trap_state][i] = trap_state;
    }

    for (int i = 0; i < num_states - 1; i++) {
        for (int j = 0; j < num_symbols; j++) {
            if (transition_table[i][j] == -1) {
                transition_table[i][j] = trap_state;
            }
        }
    }
    int start_state;
    printf("Enter the start state: ");
    scanf("%d", &start_state);
    int num_final_states;
    printf("Enter number of final states: ");
    scanf("%d", &num_final_states);
    int final_states[MAX_STATES];
    printf("Enter the final states: ");
    for (int i = 0; i < num_final_states; i++) {
    scanf("%d", &final_states[i]); }
    char input_string[MAX_STRING];
     while (1) {printf("\nEnter string to evaluate (-1 to exit): ");
        scanf("%s", input_string);
        if (strcmp(input_string, "-1") == 0) {
            break;}

        printf("\nextended transition function\n");
        int current_state = start_state;
        int string_length = strlen(input_string);
        bool valid_string = true;

        for (int i = 0; i < string_length; i++) {
            char current_symbol = input_string[i];
            int symbol_index = get_symbol_index(current_symbol, alphabet, num_symbols);

            if (symbol_index == -1) {
                printf("error: symbol not in alphabet.\n");
                valid_string = false;
                break;
            }

            int next_state = transition_table[current_state][symbol_index];
            printf("d(q%d, %c) -> q%d\n", current_state, current_symbol, next_state);
            current_state = next_state;

            if (current_state == trap_state) {
                printf("trap state reached.\n");
                break;
            }
        }

        if (!valid_string) {
 printf("\nresult: rejected\n");
     continue;}
        bool is_accepted = false;
        for (int i = 0; i < num_final_states; i++) {
            if (current_state == final_states[i]) {
                is_accepted = true;
                break;
            } }
        if (is_accepted) {
            printf("\nresult: accepted\n");
        } else { printf("\nresult: rejected\n");
        }}return 0;}
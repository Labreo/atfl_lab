/*make me a c program that takes this input at runtime for Push down automata and take string from user and tell wheateher we can accept that string or not into the given push down automata Just output code dont add comments or anything
		δ(q0, a, Z) = (q0, aZ)            
		δ(q0, a, a) = (q0, aa)            
		δ(q0, b, Z) = (q0, bZ)            
		δ(q0, b, b) = (q0, bb)
		δ(q0, a, b) = (q0, ab)            
		δ(q0, b, a) = (q0, ba)            
			
		// this is decision step	
		δ(q0, c, a) = (q1, a)
		δ(q0, c, b) = (q1, b)

		δ(q1, b, b) = (q1, ε)     
		δ(q1, a, a) = (q1, ε)     

		δ(q1, ε, Z) = (qf, Z)  sHOW stack content after every iteration of the string 
        Enter number of transitions: 11
0 a Z 0 aZ
0 a a 0 aa
0 b Z 0 bZ
0 b b 0 bb
0 a b 0 ab
0 b a 0 ba
0 c a 1 a
0 c b 1 b
1 b b 1 e
1 a a 1 e
1 e Z f Z  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100
#define MAX_TRANS 50
#define MAX_ACTION 10
#define MAX_STATE 10

typedef struct {
    char from_state[MAX_STATE];
    char input_sym;
    char stack_top;
    char to_state[MAX_STATE];
    char action[MAX_ACTION];
} Transition;

char stack[MAX_STACK];
int top = -1;

void push(char c) {
    if (top < MAX_STACK - 1) stack[++top] = c;
}

char pop() {
    if (top >= 0) return stack[top--];
    return '\0';
}

void print_stack() {
    printf(" Stack: ");
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("\n");
}

void print_id(const char* state, const char* str, int index) {
    printf("ID: (%s, ", state);
    if (index >= strlen(str)) {
        printf("e, ");
    } else {
        printf("%s, ", str + index);
    }
    for (int i = top; i >= 0; i--) {
        printf("%c", stack[i]);
    }
    printf(")\n");
}

int main() {
    printf("\nKanak Waradkar 24B-0CO-030");
    int n;
    char current_state[MAX_STATE] = "0";
    char input_str[100];
    Transition delta[MAX_TRANS];

    printf("Enter number of transitions: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s %c %c %s %s", delta[i].from_state, &delta[i].input_sym, &delta[i].stack_top, delta[i].to_state, delta[i].action);
    }

    printf("Enter string: ");
    scanf("%s", input_str);

    push('Z');
    int i = 0;
    int len = strlen(input_str);

    printf("\nInitial ID:\n");
    print_id(current_state, input_str, i);

    while (1) {
        int found = 0;
        char current_char = (i < len) ? input_str[i] : 'e';

        for (int j = 0; j < n; j++) {
            if (strcmp(delta[j].from_state, current_state) == 0 && delta[j].input_sym == current_char && delta[j].stack_top == stack[top]) {
                strcpy(current_state, delta[j].to_state);
                pop();
                if (strcmp(delta[j].action, "e") != 0) {
                    for (int k = strlen(delta[j].action) - 1; k >= 0; k--) push(delta[j].action[k]);
                }
                if (current_char != 'e') i++;
                found = 1;
                printf("Step %d: char '%c' -> State %s", i, current_char, current_state);
                print_stack();
                print_id(current_state, input_str, i);
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < n; j++) {
                if (strcmp(delta[j].from_state, current_state) == 0 && delta[j].input_sym == 'e' && delta[j].stack_top == stack[top]) {
                    strcpy(current_state, delta[j].to_state);
                    pop();
                    if (strcmp(delta[j].action, "e") != 0) {
                        for (int k = strlen(delta[j].action) - 1; k >= 0; k--) push(delta[j].action[k]);
                    }
                    found = 1;
                    printf("Step (ε): State %s", current_state);
                    print_stack();
                    print_id(current_state, input_str, i);
                    break;
                }
            }
        }
        
        if (!found || (strcmp(current_state, "f") == 0 && i >= len)) break;
    }

    if (strcmp(current_state, "f") == 0) printf("\nAccepted\n");
    else printf("\nRejected\n");

    return 0;
}
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

		δ(q1, ε, Z) = (qf, Z)     */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 100
#define MAX_TRANS 50
#define MAX_ACTION 10

typedef struct {
    char from_state[5];
    char input_sym;
    char stack_top;
    char to_state[5];
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

int main() {
printf("Kanak Waradkar 24B-0CO-030");
    int n;
    char current_state[5] = "0";
    char input_str[100];
    Transition delta[MAX_TRANS];

    printf("\nEnter number of transitions: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s %c %c %s %s", delta[i].from_state, &delta[i].input_sym, &delta[i].stack_top, delta[i].to_state, delta[i].action);
    }

    printf("Enter string: ");
    scanf("%s", input_str);

    push('Z');
    int i = 0;
    int len = strlen(input_str);

    while (1) {
        int found = 0;
        char current_char = (i < len) ? input_str[i] : 'e';

        for (int j = 0; j < n; j++) {
            if (strcmp(delta[j].from_state, current_state) == 0 && delta[j].input_sym == current_char && delta[j].stack_top == stack[top]) {
                strcpy(current_state, delta[j].to_state);
                pop();
                if (strcmp(delta[j].action, "e") != 0) {
                    for (int k = strlen(delta[j].action) - 1; k >= 0; k--) {
                        push(delta[j].action[k]);
                    }
                }
                if (current_char != 'e') i++;
                found = 1;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < n; j++) {
                if (strcmp(delta[j].from_state, current_state) == 0 && delta[j].input_sym == 'e' && delta[j].stack_top == stack[top]) {
                    strcpy(current_state, delta[j].to_state);
                    pop();
                    if (strcmp(delta[j].action, "e") != 0) {
                        for (int k = strlen(delta[j].action) - 1; k >= 0; k--) {
                            push(delta[j].action[k]);
                        }
                    }
                    found = 1;
                    break;
                }
            }
        }
        
        if (!found) break;
        if (strcmp(current_state, "f") == 0 && i >= len) break;
    }

    if (strcmp(current_state, "f") == 0) printf("Accepted\n");
    else printf("Rejected\n");

    return 0;
}

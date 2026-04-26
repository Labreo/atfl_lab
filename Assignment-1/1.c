#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 // Conversion of reg exp to enfa. 
typedef struct State {
    int id;
    char c1;
    struct State* out1;
    char c2;
    struct State* out2;
} State;

typedef struct Frag {
    State* start;
    State* accept;
} Frag;

int state_cnt = 0;
Frag stack[200];
int top = -1;

State* create_state() {
    State* s = (State*)malloc(sizeof(State));
    s->id = state_cnt++;
    s->c1 = 0;
    s->out1 = NULL;
    s->c2 = 0;
    s->out2 = NULL;
    return s;
}

void push(Frag f) {
    stack[++top] = f;
}

Frag pop() {
    return stack[top--];
}

void print_transitions(State* s, int* visited) {
    if (!s || visited[s->id]) return;
    visited[s->id] = 1;
    if (s->out1) {
        printf("q%d -- %c --> q%d\n", s->id, s->c1 ? s->c1 : 'E', s->out1->id);
        print_transitions(s->out1, visited);
    }
    if (s->out2) {
        printf("q%d -- %c --> q%d\n", s->id, s->c2 ? s->c2 : 'E', s->out2->id);
        print_transitions(s->out2, visited);
    }
}

void insert_concat(char* infix, char* res) {
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        res[j++] = infix[i];
        if (infix[i + 1]) {
            char c1 = infix[i];
            char c2 = infix[i + 1];
            int is_c1_op = (c1 == '*' || c1 == ')' || (c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z') || (c1 >= '0' && c1 <= '9'));
            int is_c2_op = (c2 == '(' || (c2 >= 'a' && c2 <= 'z') || (c2 >= 'A' && c2 <= 'Z') || (c2 >= '0' && c2 <= '9'));
            if (is_c1_op && is_c2_op) {
                res[j++] = '.';
            }
        }
    }
    res[j] = '\0';
}

int prec(char c) {
    if (c == '*') return 3;
    if (c == '.') return 2;
    if (c == '|' || c == '+') return 1;
    return 0;
}

void infix_to_postfix(char* infix, char* postfix) {
    char op_stack[200];
    int op_top = -1;
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        char c = infix[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            postfix[j++] = c;
        } else if (c == '(') {
            op_stack[++op_top] = c;
        } else if (c == ')') {
            while (op_top != -1 && op_stack[op_top] != '(') {
                postfix[j++] = op_stack[op_top--];
            }
            if (op_top != -1) op_top--;
        } else {
            while (op_top != -1 && prec(op_stack[op_top]) >= prec(c)) {
                postfix[j++] = op_stack[op_top--];
            }
            op_stack[++op_top] = c;
        }
    }
    while (op_top != -1) {
        postfix[j++] = op_stack[op_top--];
    }
    postfix[j] = '\0';
}

int main() {
    char infix[100];
    char explicit_infix[200];
    char postfix[200];
     printf("24B-0CO-030 Kanak Waradkar\n");

    printf("Enter infix regular expression: ");
    scanf("%99s", infix);

    insert_concat(infix, explicit_infix);
    infix_to_postfix(explicit_infix, postfix);

    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];
        if (c == '.') {
            Frag f2 = pop();
            Frag f1 = pop();
            f1.accept->c1 = 0;
            f1.accept->out1 = f2.start;
            Frag new_frag = {f1.start, f2.accept};
            push(new_frag);
        } else if (c == '|' || c == '+') {
            Frag f2 = pop();
            Frag f1 = pop();
            State* start = create_state();
            State* accept = create_state();
            start->c1 = 0;
            start->out1 = f1.start;
            start->c2 = 0;
            start->out2 = f2.start;
            f1.accept->c1 = 0;
            f1.accept->out1 = accept;
            f2.accept->c1 = 0;
            f2.accept->out1 = accept;
            Frag new_frag = {start, accept};
            push(new_frag);
        } else if (c == '*') {
            Frag f = pop();
            State* start = create_state();
            State* accept = create_state();
            start->c1 = 0;
            start->out1 = f.start;
            start->c2 = 0;
            start->out2 = accept;
            f.accept->c1 = 0;
            f.accept->out1 = f.start;
            f.accept->c2 = 0;
            f.accept->out2 = accept;
            Frag new_frag = {start, accept};
            push(new_frag);
        } else {
            State* start = create_state();
            State* accept = create_state();
            start->c1 = c;
            start->out1 = accept;
            Frag new_frag = {start, accept};
            push(new_frag);
        }
    }

    if (top != 0) {
        printf("Invalid input expression.\n");
        return 1;
    }

    Frag final = pop();
    int visited[1000] = {0};

    printf("\nStart State: q%d\n", final.start->id);
    printf("Accept State: q%d\n", final.accept->id);
    printf("\nTransitions (E = Epsilon):\n");
    print_transitions(final.start, visited);

    return 0;
}
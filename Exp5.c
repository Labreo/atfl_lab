#include <stdio.h>
#include <string.h>

#define MAX 20

struct Mealy
{
    int next[2];
    char out[2][3];
};

int main()
{
    printf("24B-0CO-030 Kanak Waradkar\n");
    struct Mealy state[MAX];
    int n, i;
    char str[100];
    int current = 0;

    printf("Enter number of states: ");
    scanf("%d",&n);

    printf("\nEnter Mealy Machine (use -1 for no transition)\n");

    for(i=0;i<n;i++)
    {
        printf("\nState q%d\n",i);

        printf("Next state for input 0: ");
        scanf("%d",&state[i].next[0]);

        if(state[i].next[0] != -1)
        {
            printf("Output for input 0: ");
            scanf("%s",state[i].out[0]);
        }

        printf("Next state for input 1: ");
        scanf("%d",&state[i].next[1]);

        if(state[i].next[1] != -1)
        {
            printf("Output for input 1: ");
            scanf("%s",state[i].out[1]);
        }
    }

    printf("\nEnter input string (0,1): ");
    scanf("%s",str);

    int tempState = current;

    printf("\nState Transitions:\n");
    printf("q%d", tempState);

    for(i=0;i<strlen(str);i++)
    {
        int input;

        if(str[i]=='0') input = 0;
        else if(str[i]=='1') input = 1;
        else
        {
            printf("\nInvalid input\n");
            return 0;
        }

        if(state[tempState].next[input] == -1)
        {
            printf("\nNo transition → REJECTED\n");
            return 0;
        }

        tempState = state[tempState].next[input];
        printf(" -> q%d", tempState);
    }

    printf("\n\nOutput String:\n");

    tempState = current;

    for(i=0;i<strlen(str);i++)
    {
        int input = (str[i]=='0') ? 0 : 1;

        printf("%s ", state[tempState].out[input]);

        tempState = state[tempState].next[input];
    }

    printf("\n");

    return 0;
}
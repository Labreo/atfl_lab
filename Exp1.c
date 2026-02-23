// Kanak Waradkar 24B-CO-030
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 

bool isKeyword(char s[]) {
    char* keywords[] = {
        "auto","break","case","char","const","continue","default","do","double",
        "else","enum","extern","float","for","goto","if","int","long",
        "register","return","short","signed","sizeof","static","struct",
        "switch","typedef","union","unsigned","void","volatile","while"
    };
    int n = sizeof(keywords)/sizeof(keywords[0]);
    for(int i=0; i<n; i++) {
        if(strcmp(s, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool isIdentifier(char s[]) {
    // Check if first character is a letter or underscore
    if (!(isalpha(s[0]) || s[0] == '_')) {
        return false;
    }
    // Check remaining characters
    for (int i = 1; s[i] != '\0'; i++) {
        if (!(isalnum(s[i]) || s[i] == '_')) {
            return false;
        }
    }
    return true;
}

int main() {
    char input[50];
    printf("Enter word to be checked: ");

    scanf("%s", input);

    if (isKeyword(input)) {
        printf("\n%s is a keyword\n", input);
    }
    else {
        if (isIdentifier(input)) {
            printf("\n%s is a valid identifier\n", input);
        }
        else {
            printf("\n%s is neither a keyword nor a valid identifier\n", input);
        }
    }
    return 0;
}
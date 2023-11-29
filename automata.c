#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define alphabet_size 10
#define max_states 9
void removeSpaces(char *str) {
    char *i = str;
    char *j = str;

    while (*j != '\0') {
        *i = *j++;
        if (!isspace(*i)) {
            i++;
        }
    }
    *i = '\0';
}
bool sigma_alphabet_check(const char *arr1, const char *arr2) {
    while (*arr1 != '\0') {
        bool found = false;
        const char *temp = arr2;

        while (*temp != '\0') {
            if (*temp == *arr1) {
                found = true;
                break;
            }
            temp++;
        }

        if (!found) {
            return false;
        }
        arr1++;
    }

    return true;
}
int main()
{
    //Parsing the file

    FILE* file = fopen("DFA1.txt", "r");

    if (file == NULL) {
        printf("File cannot be opened.\n");
        return 1;
    }
    char buffer[50];
    char sigma[alphabet_size];
    char initial_state = '0';
    char current_state;
    int q;
    char accept_state[max_states];
    int valid_string=0;

    //Reading the alphabet

    fgets(buffer, sizeof(buffer), file);
    int i = strlen(buffer) - 1;
    buffer[strcspn(buffer, "\t")] = '\0';
    strcpy(sigma, buffer);
    printf("sigma: %s\n", sigma);

    //Reading the number of states
    printf("\n");
    fgets(buffer, sizeof(buffer), file);
    i = strlen(buffer) - 1;
    buffer[strcspn(buffer, "\t")] = '\0';
    q = buffer[0] - '0';
    printf("total_states: %d\n", q);

    //Reading the transition table
    printf("\n");
    char transition_table[q][strlen(sigma)];
    for (int j = 0; j < q; j++)
    {
        fgets(buffer, sizeof(buffer), file);
        i = strlen(buffer) - 1;
        buffer[strcspn(buffer, "\t")] = '\0';
        // printf("%s", buffer);
        removeSpaces(buffer);
        // printf("%s", buffer);
        for (int k = 0; k < strlen(sigma); k++)
        {
            transition_table[j][k] = buffer[k];
        }
        }printf("""Transition TABLE\n""");
        for (int j = 0; j < q;j++){
            for(int k = 0; k < strlen(sigma);k++){
                printf("%c\t",transition_table[j][k]); //You did not follow a homogenous data type definitions. Look into it
            }printf("\n");
        }

        //Reading the Final State
        printf("\n");
        fgets(buffer, sizeof(buffer), file);
            i = strlen(buffer) - 1;
            buffer[strcspn(buffer, "\t")] = '\0';  
            strcpy(accept_state, buffer);
            printf("Accept State: %s\n", accept_state);

            fclose(file);

            // End of Parsing the file

            // PsuedoCode implementation:
             char input[100];
             printf("\n");
             printf("Enter the input string within the valid Sigma to be processed: ");
             fgets(input,sizeof(input),stdin);
             while (strcmp(input,"Done")){
                removeSpaces(input); //Removing unwanted space from the input
                 for (int i = 0;i<strlen(input);i++){
                    //checking if alphabet is a subset of sigma or not

                    if (sigma_alphabet_check(input,sigma) == false) {
                        printf("\nInvalid alphabet detected, Not found in sigma\n");
                    }else{
                        valid_string = 1;
                    }
                 }if(valid_string==1){
                 current_state = initial_state;
                 printf("%c", current_state);
                 for (int i = 0; i < strlen(input); i++)
                 {
                     printf("\nCurrent State: %c Current Input Character: %c\n", (char)i, input[i]);
                     int alpha_index = strchr(sigma, input[i]) - sigma;
                     current_state = transition_table[current_state - '0'][alpha_index];
                     printf("%c\n",current_state);
                 }
                if (current_state == *accept_state){
                    printf("String %s is accepted\n", input);
                }else{
                    printf("String %s is rejected\n", input);
                } printf("\nPlease Enter the next input string: ");
                fgets(input,sizeof(input),stdin);
                 }else{
                     break;
                 }
             }
             return 1;
}
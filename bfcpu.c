#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum InstructionSet {
    MOVE_LEFT = '<',
    MOVE_RIGHT = '>',
    INCREMENT = '+',
    DECREMENT = '-',
    OUTPUT = '.',
    INPUT = ',',
    LOOP_START = '[',
    LOOP_END = ']'
} InstructionSet;

void execute();
void eval(InstructionSet instruction, int* i);

int memory[30000] = {0};
int* ptr = &memory[0];
int loops = 0;
int startindex[62];


int main(void) {
    
    execute(ptr, memory);
    printf("\n");
    // free(ptr); ???
    return 0;
}


void execute() {
    char* code = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."; // Output Input + 10
    unsigned long code_length = strlen(code);
    for (int i = 0; i < code_length; i++) {
        char instruction = code[i];
        eval(instruction, &i);
    }
}

void eval(InstructionSet instruction, int* i) {
    switch (instruction) {
        case MOVE_LEFT:
            ptr--;
            break;
        case MOVE_RIGHT:
            ptr++;
            break;
        case INCREMENT:
            (*ptr)++;
            break;
        case DECREMENT:
            (*ptr)--;
            break;
        case OUTPUT:
            printf("%c", ((*ptr)));
            break;
        case INPUT:
            scanf("%d", (*(&ptr)));
            break;
        case LOOP_START:
            if (++loops > 62) {
                printf("Error: Too many nested loops");
                exit(1);
            }
            startindex[loops] = *i;
            break;
        case LOOP_END:
            if ((*ptr) != 0) {
                i = startindex[loops] + 1;
            } else {
                loops--;
            }
            break;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_SIZE 255

// Mnemonics
// stop program
#define HLT 240
// Store in byte
#define STA 16
// Load byte
#define LDA 32
// Add
#define ADD 48
#define OR 64
#define AND 80
#define NOT 96
#define JMP 128
#define JN 144
#define JZ 160

void print(uint8_t buffer[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%u ", buffer[i]);
    }
}

void checkByte(uint8_t buffer[], uint8_t *Ac, int *size) {
    uint8_t currentIdx = *size;
    uint8_t nextIdx = (++currentIdx);
    switch (buffer[*size]) {
        case HLT:
            printf("Final result:\n");
            printf("AC: %d\n", *Ac);
            printf("PC: %d\n", buffer[2]);
            printf("Flag B: %d\n", buffer[3]);
            printf("Flag Z: %d\n", buffer[4]);
            printf("Complete memory map:\n");
            for (int i = 0; i < MAX_SIZE; i++) {
                printf("Mem[%d]: %d\n", i, buffer[i]);
            }
            exit(0);
            break;
        case STA:
            printf("STA");
            buffer[buffer[nextIdx]] = *Ac;
            (*size)++;
            break;
        case LDA:
            printf("LDA");
            *Ac = buffer[buffer[nextIdx]];
            (*size)++;
            break;
        case ADD:
            printf("ADD");
            *Ac += buffer[buffer[nextIdx]];
            (*size)++;
            break;
        case OR:
            printf("OR");
            *Ac |= buffer[buffer[nextIdx]];
            (*size)++;
            break;
        case AND:
            printf("AND");
            *Ac &= buffer[buffer[nextIdx]];
            (*size)++;
            break;
        case NOT:
            printf("NOT");
            *Ac = ~*Ac;
            (*size)++;
            break;
        case JMP:
            printf("JMP");
            (*size) = buffer[nextIdx];
            break;
        case JN:
            printf("JN");
            if (*Ac == 0) {
                (*size) = buffer[nextIdx];
            }
            break;
        case JZ:
            printf("JZ");
            if (*Ac == 0) {
                (*size) = buffer[nextIdx];
            }
            break;
    }
    (++(*size));
    printf("\n");
}

int binary(FILE *file) {
    uint8_t buffer[MAX_SIZE];
    uint8_t AC = 0;
    int i = 0;
    fseek(file, 0, SEEK_SET);
    fread(&buffer, MAX_SIZE, 1, file);

    print(buffer);
    if (buffer[0] != 42) {
        printf("Invalid binary\n");
        return 1;
    } else {
        AC = buffer[1];
        while (buffer[i] != 0 && i < MAX_SIZE) {
            buffer[2] = i;
            checkByte(buffer, &AC, &i);
            printf("Mem[%d]: %d\n", i, buffer[i]);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

 if(argc != 2){
		printf("Favor inserir 2 argumentos:\nEx.: main entrada.nar\n");
		return 1;
	}    
    FILE *file;
    if (file = fopen(argv[1], "rb")) {
        binary(file);
        fclose(file);
    } else {
        printf("Error open %s!\n", argv[1]);
        return 1;
    }
    return 0;
}
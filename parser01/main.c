#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_SIZE 1000

typedef enum Token
{
    NumeroInteiro,
    NumeroReal,U
    Soma,
    Indeterminado,
} Token;

struct Tokens
{
    enum Token token;
    union
    {
        char op;
        double num;
    } value;
};

/* void tokenizar(char *caracteres, int length, struct Tokens *vetorTokens, int *numTokens): função que recebe um vetor de caracteres, seu comprimento, um vetor de Tokens e um ponteiro para o número de tokens encontrados no vetor de caracteres. Esta função realiza a tokenização dos caracteres, identificando números e operadores, e preenche o vetor de Tokens.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    MAIS,
    MENOS,
    MULTIPLICACAO,
    DIVISAO,
    POTENCIA,
    INDETERMINADO,
} Token;

Token obter_token(char c) {
    switch (c) {
        case '+':
            return MAIS;
        case '-':
            return MENOS;
        case '*':
            return MULTIPLICACAO;
        case '/':
            return DIVISAO;
        case '**':
            return POTENCIA;
        default:
            return INDETERMINADO;
    }
}

int main(void) {
    FILE *arquivo;
    char nome_arquivo[100];
    char linha[100];
    Token tokens[100];
    int i = 0;

    // lê o nome do arquivo
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);

    // abre o arquivo
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // lê as linhas do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // percorre a linha e obtém os tokens
        for (char *p = linha; *p; p++) {
            if (*p == ' ') {
                continue;
            }
            tokens[i++] = obter_token(*p);
        }
    }

    // fecha o arquivo
    fclose(arquivo);

    // imprime os tokens
    printf("TOKENS: ");
    for (int j = 0; j < i; j++) {
        switch (tokens[j]) {
            case MAIS:
                printf("Mais ");
                break;
            case MENOS:
                printf("Menos ");
                break;
            case MULTIPLICACAO:
                printf("Multiplica ");
                break;
            case DIVISAO:
                printf("Divide ");
                break;
            case POTENCIA:
                printf("Potencia ");
                break;
            case INDETERMINADO:
                printf("Indeterminado ");
                break;
        }
    }
    printf("\n");

    return 0;
}

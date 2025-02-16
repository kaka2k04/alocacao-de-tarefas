#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int identificacao;
    int tarefa;
    int tempo;
} funcionario;

void limpar_Lista_Com_Inexistentes(int* lista, int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = -1;
    }
}

void limpar_Lista_Com_Zeros(int* lista, int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = 0;
    }
}

int** criaMatriz(const int n) {
    int **matriz = (int**)malloc(n * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro ao alocar memória para a matriz\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d\n", i);
            exit(1);
        }
    }
    return matriz;
}

void liberaMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int* cria_Lista_int(const int n) {
    int* lista = (int*)malloc(n * sizeof(int));
    if (lista == NULL) {
        printf("Erro ao alocar memória para a lista de inteiros\n");
        exit(1);
    }
    return lista;
}

funcionario* cria_Lista_funcionarios(const int n) {
    funcionario* lista = (funcionario*)malloc(n * sizeof(funcionario));
    if (lista == NULL) {
        printf("Erro ao alocar memória para a lista de funcionários\n");
        exit(1);
    }
    return lista;
}

void ler_quant_funcionarios(FILE* arquivo, int* quantidadeFuncionarios) {
    if (fscanf(arquivo, "%d", quantidadeFuncionarios) != 1) {
        printf("Erro ao ler a quantidade de funcionários\n");
        exit(1);
    }
}

void copia_Matriz_Do_Arquivo(int** matriz, FILE* arquivo, int tamanhoMatriz) {
    for (int i = 0; i < tamanhoMatriz; i++) {
        for (int j = 0; j < tamanhoMatriz; j++) {
            if (fscanf(arquivo, "%d", &matriz[i][j]) != 1) {
                printf("Erro ao ler o valor da matriz na posição [%d][%d]\n", i, j);
                exit(1);
            }
        }
    }
}

int main() {
    int quantidade_Funcionarios;
    int n;
    int menor_tempo_tarefa;
    int indice_funcionario_menor_tempo;
    long int tempo_Total = 0;

    FILE *arquivo = fopen("assignp1500.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    ler_quant_funcionarios(arquivo, &quantidade_Funcionarios);
    n = quantidade_Funcionarios;

    int** matriz = criaMatriz(n);
    int* atribuicoes = cria_Lista_int(n);
    limpar_Lista_Com_Inexistentes(atribuicoes, n);
    int* funcionarios_Atribuidos = cria_Lista_int(n);
    limpar_Lista_Com_Zeros(funcionarios_Atribuidos, n);
    funcionario* lista_funcionarios = cria_Lista_funcionarios(n);

    copia_Matriz_Do_Arquivo(matriz, arquivo, n);
    fclose(arquivo);

    for (int j = 0; j < n; j++) {
        menor_tempo_tarefa = INT_MAX;
        indice_funcionario_menor_tempo = -1; // Inicializa com valor inválido
        for (int i = 0; i < n; i++) {
            if (funcionarios_Atribuidos[i] == 0 && matriz[i][j] < menor_tempo_tarefa) {
                menor_tempo_tarefa = matriz[i][j];
                indice_funcionario_menor_tempo = i;
            }
        }
        if (indice_funcionario_menor_tempo == -1) {
            printf("Erro: Nenhum funcionário disponível para a tarefa %d\n", j);
            exit(1);
        }
        atribuicoes[indice_funcionario_menor_tempo] = j;
        funcionarios_Atribuidos[indice_funcionario_menor_tempo] = 1;
    }

    for (int i = 0; i < n; i++) {
        lista_funcionarios[i].identificacao = i + 1;
        lista_funcionarios[i].tarefa = atribuicoes[i] + 1;
        lista_funcionarios[i].tempo = matriz[i][atribuicoes[i]];
        tempo_Total += lista_funcionarios[i].tempo;
    }

    for (int i = 0; i < n; i++) {
        printf("Funcionário %d --> Tarefa %d\n", lista_funcionarios[i].identificacao, lista_funcionarios[i].tarefa);
    }

    printf("Tempo Total = %ld\n", tempo_Total);

    // Liberar memória alocada
    liberaMatriz(matriz, n);
    free(atribuicoes);
    free(funcionarios_Atribuidos);
    free(lista_funcionarios);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct{
    int identificacao;
    int tarefa;
    int tempo;
}funcionario;                                       

void limpar_Lista_Com_Inexistentes(int* lista, int n){
    for(int i = 0; i < n; i++){
        lista[i] = -1;
    }
}

void limpar_Lista_Com_Zeros(int* lista, int n){
    for(int i = 0; i < n; i++){
        lista[i] = 0;
    }
}

int** criaMatriz(const int n){
    int **matriz = (int**)malloc(n * sizeof(int *));        //criando matriz de tamanho n
    if (matriz == NULL){
        printf("Erro ao alocar memória para a matriz\n");
        exit(1);
    }
    for(int i = 0; i < n; i++){
        matriz[i] = (int *)malloc(n * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d\n", i);
            exit(1);
        }
    }
    return matriz;
}

int* cria_Lista_int(const int n){
    int* lista = (int*)malloc(n * sizeof(int));
    if( lista == NULL){
        printf("Erro ao alocar memória para a lista de inteiros\n");
        exit(1);
    }
    return lista;
}

funcionario* cria_Lista_funcionarios(const int n){
    funcionario* lista = (funcionario*)malloc(n * sizeof(funcionario));             //cria uma variavel chamada lista, vetor tamanho n
    if( lista == NULL){
        printf("Erro ao alocar memória para a lista de funcionarios\n");
        exit(1);
    }
    return lista;
}

void ler_quant_funcionarios(FILE* arquivo,int* quantidadeFuncionarios){                                    //lendo a quantidade de funcionarios e tarefas
    if (fscanf(arquivo, "%d", quantidadeFuncionarios) != 1) {                                  //equivalente a &(*quantidadeFuncionarios)
        printf("Erro ao ler a quantidade de funcionários\n");
        exit(1);
    }
}

void copia_Matriz_Do_Arquivo(int** matriz, FILE* arquivo, int tamanhoMatriz){
    for(int i = 0; i < tamanhoMatriz; i++){                                                         //copiando matriz do arquivo para a variavel matriz
        for(int j = 0; j < tamanhoMatriz; j++){
            if(fscanf(arquivo,"%d", &matriz[i][j]) == NULL){
                printf("ERRO\n nao foi possivel copiar matriz do arquivo");
                exit(1);
            }
        }
    }
}


int main(){

    int quantidade_Funcionarios;
    int n;
    int menor_tempo_tarefa;
    int indice_funcionario_menor_tempo;
    long int tempo_Total = 0;
    
    FILE *arquivo = fopen("assignp3000.txt", "r");            //abrindo o arquivo
    if( arquivo == NULL){                                   //verificando se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo");
        exit(1);    
    }
    
    ler_quant_funcionarios(arquivo,&quantidade_Funcionarios);           //lendo quantidade de funcionários
    n = quantidade_Funcionarios;

    int** matriz = criaMatriz(n);                                        //criando matriz de tamanho n x n
    int* atribuicoes = cria_Lista_int(n);                                    //criando lista de tamanho n para guardar as atribuições( indice = funcionario; valor = tarefa)
    limpar_Lista_Com_Inexistentes(atribuicoes, n);                                        //limpando lista atribuições
    int* funcionarios_Atribuidos = cria_Lista_int(n);            //cria lista de funcionarios atribuidos inicializada com false em todas as posições (nenhum funcionario atribuido)
    limpar_Lista_Com_Zeros(funcionarios_Atribuidos, n);
    funcionario* lista_funcionarios = cria_Lista_funcionarios(n);                 //cria lista funcionarios
    
    copia_Matriz_Do_Arquivo(matriz, arquivo, n);                        //copia matriz do arquivo para a variavel matriz
    fclose(arquivo);                                                    //fecha o arquivo


    for(int j = 0; j < n; j++){                                                                                     //percorre as tarefas
        menor_tempo_tarefa = INT_MAX;
        for(int i = 0; i < n; i++){                                                                             //em cada tarefa percorre os funcionarios
            if(funcionarios_Atribuidos[i] == 0 && matriz[i][j] < menor_tempo_tarefa){                    //se o funcionario ainda não estiver atribuido
                menor_tempo_tarefa = matriz[i][j];                                                              //novo menor tempo será o dele
                indice_funcionario_menor_tempo = i;                                                          //guarda o indice do funcionario
                }      
        }
       atribuicoes[indice_funcionario_menor_tempo] = j;
       funcionarios_Atribuidos[indice_funcionario_menor_tempo] = 1;
    }


    for(int i = 0; i < n; i++){                                         //para cada indice da lista de atribuições
        lista_funcionarios[i].identificacao = i + 1;
        lista_funcionarios[i].tarefa = atribuicoes[i] + 1;
        lista_funcionarios[i].tempo = matriz[i][atribuicoes[i]];

        tempo_Total += lista_funcionarios[i].tempo;
    }


    for(int i = 0; i < n; i++){
        printf("funcionario %d --> job %d\n", lista_funcionarios[i].identificacao, lista_funcionarios[i].tarefa);
    }

    printf("Tempo Total = %ld\n", tempo_Total);


    for(int i = 0; i < n; i++){
        free(matriz[i]);
    }
    
    free(atribuicoes);
    free(funcionarios_Atribuidos);
    free(lista_funcionarios);

    return 0;
}

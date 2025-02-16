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
            if(fscanf(arquivo,"%d", &matriz[i][j]) != 1){
                printf("ERRO\n Nao foi possivel copiar matriz do arquivo em matriz[%d][%d]", i, j);
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
    char nomeArquivo[100];
    char nomeArquivoResposta[100];

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);
    
    FILE *arquivo = fopen(nomeArquivo, "r");            //abrindo o arquivo
    if( arquivo == NULL){                                   //verificando se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo");
        exit(1);    
    }
    
    printf("Processando dados. Aguarde.\n\n");
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

    for(int j = 0; j < n; j++){                                                                                    //percorre as tarefas
        
        menor_tempo_tarefa = INT_MAX;
        indice_funcionario_menor_tempo = -1;
        for(int i = 0; i < n; i++){                                                                             //em cada tarefa percorre os funcionarios
            if(funcionarios_Atribuidos[i] == 0 && matriz[i][j] < menor_tempo_tarefa){                    //se o funcionario ainda não estiver atribuido
                menor_tempo_tarefa = matriz[i][j];                                                              //novo menor tempo será o dele
                indice_funcionario_menor_tempo = i;                                                          //guarda o indice do funcionario
                }      
        }
    if(indice_funcionario_menor_tempo != -1){
        atribuicoes[indice_funcionario_menor_tempo] = j;
        funcionarios_Atribuidos[indice_funcionario_menor_tempo] = 1;
    }
    }

    for(int i = 0; i < n; i++){                                         //para cada indice da lista de atribuições
        lista_funcionarios[i].identificacao = i + 1;
        lista_funcionarios[i].tarefa = atribuicoes[i] + 1;
        lista_funcionarios[i].tempo = matriz[i][atribuicoes[i]];

        tempo_Total += lista_funcionarios[i].tempo;
    }

    printf("Tempo Total = %ld\n\n", tempo_Total);

    int opcao = 0;

    printf("O que voce deseja fazer?\n");
    printf("1 - salvar arquivo apenas tempo total\n");
    printf("2 - salvar arquivo com tempo total e atribuicoes\n");
    printf("3 - imprimir atribuicoes no terminal\n");
    printf("4 - nao salvar arquivo\n");
    scanf("%d", &opcao);

    if(opcao == 1 || opcao == 2){
        printf("Digite o nome do Arquivo com as respostas:\n");
        scanf("%s", nomeArquivoResposta);
        printf("\n");
    }

    switch (opcao){
    case 1:
        printf("Voce escolheu a opcao 1!\n");
        printf("Arquivos salvos!\n\n");
        FILE *arquivoRespostas_opcao1 = fopen(nomeArquivoResposta, "w");
        if (arquivoRespostas_opcao1 == NULL) {
            printf("Erro ao criar o arquivo respostas!\n");
            return 1;
        }
        fprintf(arquivoRespostas_opcao1, "Resposta do Arquivo %s:\n\n", nomeArquivo);
        fprintf(arquivoRespostas_opcao1, "Tempo Total: %ld\n", tempo_Total);
        fclose(arquivoRespostas_opcao1);
        break;

    case 2:
        printf("Voce escolheu a opcao 2!\n");
        printf("Arquivos Salvos!\n\n");

        FILE *arquivoRespostas_opcao2 = fopen(nomeArquivoResposta, "w");
        if (arquivoRespostas_opcao2 == NULL) {
            printf("Erro ao criar o arquivo respostas!\n");
            return 1;
        }
        fprintf(arquivoRespostas_opcao2, "Resposta do Arquivo %s:\n\n", nomeArquivo);
        fprintf(arquivoRespostas_opcao2, "Tempo Total: %ld\n\n", tempo_Total);
        fprintf(arquivoRespostas_opcao2,"Atribuicoes:\n\n");
        for(int i = 0; i < n;i++){
            fprintf(arquivoRespostas_opcao2, "funcionario %d --> tarefa %d\n", lista_funcionarios[i].identificacao, lista_funcionarios[i].tarefa);
        }
        fclose(arquivoRespostas_opcao2);
        break;

        break;

    case 3:
        printf("Voce escolheu a opcao 3!\n");
        printf("Atribuicoes:\n\n");
        for(int i = 0; i < n; i++){
            printf("funcionario %d --> tarefa %d\n", lista_funcionarios[i].identificacao, lista_funcionarios[i].tarefa);
        }
        break;

    case 4:
        printf("Voce escollheu a opcao 4!\n");
        printf("Arquivo nao sera salvo\n");
        break;
    
    default:
        printf("Opcao invalida!\n");
        break;
    }
    
    //liberando memoria alocada
    for(int i = 0; i < n; i++){
        free(matriz[i]);
    }

    free(atribuicoes);
    free(funcionarios_Atribuidos);
    free(lista_funcionarios);

    printf("Fim de programa\nAte mais! :)\n");
    return 0;
}
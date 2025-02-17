#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct{                                             //cria struct funcionario para armazenar três inteiros
    int identificacao;
    int tarefa;
    int tempo;
}funcionario;                                       

void limpar_Lista_Com_Inexistentes(int* lista, int n){       //substitui o valor de todas as posições de uma lista por -1
    for(int i = 0; i < n; i++){
        lista[i] = -1;
    }
}

void limpar_Lista_Com_Zeros(int* lista, int n){              //sustitui o valor  de todas as posições de uma lista por 0
    for(int i = 0; i < n; i++){
        lista[i] = 0;
    }
}

int** criaMatriz(const int n){                              //cria matriz de inteiros de tamanho NxN com alocação dinâmica
    int **matriz = (int**)malloc(n * sizeof(int *));        
    if (matriz == NULL){                                        //verifica se foi possivel alocar memória
        printf("Erro ao alocar memória para a matriz\n");   
        exit(1);
    }
    for(int i = 0; i < n; i++){
        matriz[i] = (int *)malloc(n * sizeof(int));
        if (matriz[i] == NULL) {                                      //verifica se foi possivel alocar memória
            printf("Erro ao alocar memória para a linha %d\n", i);
            exit(1);
        }
    }
    return matriz;
}

int* cria_Lista_int(const int n){                       //cria lista de inteiros de tamanho N utilizando alocação dinâmica
    int* lista = (int*)malloc(n * sizeof(int));
    if( lista == NULL){                                 //verifica se foi possivel alocar memória para a lista
        printf("Erro ao alocar memória para a lista de inteiros\n");
        exit(1);
    }
    return lista;
}

funcionario* cria_Lista_funcionarios(const int n){                                  //cria uma lista do tipo funcionario de tamanho N usando alocação dinamica        
    funcionario* lista = (funcionario*)malloc(n * sizeof(funcionario));             //cria uma variavel chamada lista, vetor tamanho n
    if( lista == NULL){
        printf("Erro ao alocar memória para a lista de funcionarios\n");
        exit(1);
    }
    return lista;
}

void ler_quant_funcionarios(FILE* arquivo,int* quantidadeFuncionarios){                         //ler a quantidade de funcionarios e armazena na variavel quantidadeFuncionarios
    if (fscanf(arquivo, "%d", quantidadeFuncionarios) != 1) {                                  //terceiro argumento equivalente a &(*quantidadeFuncionarios)
        printf("Erro ao ler a quantidade de funcionários\n");
        exit(1);
    }
}

void copia_Matriz_Do_Arquivo(int** matriz, FILE* arquivo, int tamanhoMatriz){                 //copia matriz do arquivo para a variavel matriz
    for(int i = 0; i < tamanhoMatriz; i++){                                                         
        for(int j = 0; j < tamanhoMatriz; j++){
            if(fscanf(arquivo,"%d", &matriz[i][j]) != 1){                                       //verifica se foi possivel copiar cada elemento da matriz
                printf("ERRO\n Nao foi possivel copiar matriz do arquivo em matriz[%d][%d]", i, j);    //em caso de erro na leitura informa a posição do erro e encerra o programa
                exit(1);
            }
        }
    }
}

void escrever_linhas_recursivamente(FILE *arquivo, funcionario *lista, int n) {             //escreve as atribuições funcionário --> tarefa utilizando recursão
    if (n <= 0) {
        return;
    }
    fprintf(arquivo, "funcionario %d --> tarefa %d\n", (*lista).identificacao, (*lista).tarefa);
    escrever_linhas_recursivamente(arquivo, lista + 1, n - 1);
}


int main(){

    int quantidade_Funcionarios;
    int n;
    int menor_tempo_tarefa;
    int indice_funcionario_menor_tempo;
    long int tempo_Total = 0;
    char nomeArquivo[100];
    char nomeArquivoResposta[100];

    printf("Digite o nome do arquivo: ");                   //pedi para o usuario informar o nome do arquivo a ser processado
    scanf("%s", nomeArquivo);
    
    FILE *arquivo = fopen(nomeArquivo, "r");                //abrindo o arquivo
    if( arquivo == NULL){                                   //verificando se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo");
        exit(1);    
    }
    
    printf("Processando dados. Aguarde.\n\n");
    ler_quant_funcionarios(arquivo,&quantidade_Funcionarios);           //lendo quantidade de funcionários
    n = quantidade_Funcionarios;

    int** matriz = criaMatriz(n);                                        //criando matriz de tamanho n x n
    int* atribuicoes = cria_Lista_int(n);                                //criando lista de tamanho n para guardar as atribuições( indice = funcionario; valor = tarefa)
    limpar_Lista_Com_Inexistentes(atribuicoes, n);                       //limpando lista atribuições
    int* funcionarios_Atribuidos = cria_Lista_int(n);                    //cria lista de funcionarios atribuidos
    limpar_Lista_Com_Zeros(funcionarios_Atribuidos, n);                  //substitui todos os elementos da lista por zero (nenhum funcionario atribuido)
    funcionario* lista_funcionarios = cria_Lista_funcionarios(n);        //cria lista funcionarios
    
    copia_Matriz_Do_Arquivo(matriz, arquivo, n);                        //copia matriz do arquivo para a variavel matriz
    fclose(arquivo);                                                    //fecha o arquivo

    for(int j = 0; j < n; j++){                                                                //percorre as tarefas
        menor_tempo_tarefa = INT_MAX;                                                          //em cada tarefa o primeiro menor tempo será INT_MAX
        indice_funcionario_menor_tempo = -1;                                                   //limpa a variavel que guarda a posição do melhor tempo
        for(int i = 0; i < n; i++){                                                                 //em cada tarefa percorre os funcionarios
            if(funcionarios_Atribuidos[i] == 0 && matriz[i][j] < menor_tempo_tarefa){               //se o funcionario ainda não estiver atribuido e o tempo for menor que o menor tempo anterior
                menor_tempo_tarefa = matriz[i][j];                                                  //novo menor tempo será o dele
                indice_funcionario_menor_tempo = i;                                                 //guarda o indice do funcionario
                }      
        }
        if(indice_funcionario_menor_tempo != -1){                                   //depois de percorrer todos os funcionarios da tarefa, se a melhor tarefa foi atribuida       
            atribuicoes[indice_funcionario_menor_tempo] = j;                        //atribui o funcionario com o melhor tempo para a tarefa
            funcionarios_Atribuidos[indice_funcionario_menor_tempo] = 1;            //marca o fuuncionario como atribuido
         }
    }

    for(int i = 0; i < n; i++){                                         //percorre a lista de funcionarios
        lista_funcionarios[i].identificacao = i + 1;                    //identifica o funcionario com a respectiva linha
        lista_funcionarios[i].tarefa = atribuicoes[i] + 1;              //guarda o id da tarefa 
        lista_funcionarios[i].tempo = matriz[i][atribuicoes[i]];        //guarda o tempo do funcionario na tarefa atribuida

        tempo_Total += lista_funcionarios[i].tempo;
    }

    printf("Tempo Total = %ld\n\n", tempo_Total);                       //imprime no terminal o tempo total

    int opcao = 0;

    printf("O que voce deseja fazer?\n");
    printf("1 - salvar arquivo apenas tempo total\n");
    printf("2 - salvar arquivo com tempo total e atribuicoes\n");
    printf("3 - imprimir atribuicoes no terminal\n");
    printf("4 - nao salvar arquivo\n");
    scanf("%d", &opcao);

    if(opcao == 1 || opcao == 2){                                   //caso o usuário escolha a primeira ou segunda opção pede para informar o nome do arquivo que será salvo
        printf("Digite o nome do Arquivo com as respostas:\n");
        scanf("%s", nomeArquivoResposta);
        printf("\n");
    }

    switch (opcao){
    case 1:                                                         //salva o arquivo apenas com o tempo total
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

    case 2:                                                    //salva o arquivo com tempo total e todas as atribuições
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
        escrever_linhas_recursivamente(arquivoRespostas_opcao2, lista_funcionarios, n);
        fclose(arquivoRespostas_opcao2);
        break;

    case 3:                                         //imprime no terminal todas as atribuições
        printf("Voce escolheu a opcao 3!\n");
        printf("Atribuicoes:\n\n");
        for(int i = 0; i < n; i++){
            printf("funcionario %d --> tarefa %d\n", lista_funcionarios[i].identificacao, lista_funcionarios[i].tarefa);
        }
        break;

    case 4:                                     //informa o usuário que o arquivo não será salvo
        printf("Voce escolheu a opcao 4!\n");
        printf("Arquivo nao sera salvo\n");
        break;
    
    default:                                   //caso o usuário digite uma entrada invalida, informa o usuário e segue o programa normalmente
        printf("Opcao invalida!\n");
        break;
    }
    
    for(int i = 0; i < n; i++){         //libera a memória alocada para cada coluna da matriz
        free(matriz[i]);
    }

    free(matriz);                   //libera a memória alocada para a matriz
    free(atribuicoes);              //libera a memória alocada para a lista atribuições
    free(funcionarios_Atribuidos);  //libera a memória alocada para a lista funcionarios_Atribuidos
    free(lista_funcionarios);       //libera a memória alocada para lista funcionarios

    printf("Fim de programa\nAte mais!\n");
    return 0;
}

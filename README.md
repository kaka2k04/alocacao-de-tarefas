# Atribuição de Tarefas
Trabalho de Linguagem de programação 1
## INTEGRANTES DO TRABALHO:
Carlos Eduardo de Sousa Gomes<br>
Kelvin Vinicius Vieira Santos<br>
Thiago Henrique Garcia da Paz<br>
## Um pouco sobre o trabalho e seu objetivo <b>:

O algoritmo busca resolver o problema de atribuição , que consiste em encontrar a melhor maneira de atribuir um conjunto de tarefas a um conjunto de funcionarios, minimizando os custos.

# Propósito e Aplicação

O principal propósito do algoritimo é encontrar uma correspondência ótima entre duas partes de um problema, garantindo que a soma dos custos (ou a soma dos lucros, dependendo do contexto) seja minimizada (ou maximizada).

Ele é amplamente usado em diversas áreas, como:

Gerenciamento de tarefas (designação de funcionários para tarefas específicas)
Otimização em logística (atribuição de entregas a veículos)
Visão computacional (rastreamento de objetos em vídeos)
Emparelhamento em machine learning (associação de previsões a dados reais)
O algoritmo é conhecido por sua eficiência e roda em tempo polinomial, tornando-o adequado para problemas de grande escala
### Implemetntação 
Este programa em C atribui tarefas a funcionários de forma a minimizar o tempo total de execução. Ele lê uma matriz de tempos de um arquivo e utiliza um método guloso para designar cada funcionário à tarefa mais rápida disponível. O código aloca dinamicamente listas e matrizes para armazenar os dados, garantindo que cada funcionário receba exatamente uma tarefa. Após a atribuição, exibe quais funcionários executam quais tarefas e calcula o tempo total gasto. O programa gerencia a memória corretamente, evitando vazamentos, e fornece uma solução eficiente para o problema de alocação de tarefas.

# Exemplo matematico em questão e sua aplicação

Problema de Atribuição de Tarefas em uma Fábrica<br>

Uma fábrica moderna deseja melhorar a alocação de suas tarefas aos funcionários, otimizando o desempenho operacional. Cada funcionário possui um nível de habilidade para executar diferentes tarefas, e o objetivo é atribuir as tarefas disponíveis de forma a minimizar o tempo gasto para realizar todas as atividades, respeitando as seguintes condições:

Cada funcionário deve ser alocado para exatamente uma tarefa.

Cada tarefa deve ser atribuída a exatamente um funcionário


Ex.:

N = 4 (Funcionários)

M = 4 (Tarefas)

Matriz de Tempos:

66 41 98 67
63 80 4 43
44 63 93 75
22 5 81 18


Cada valor na matriz representa o tempo que um funcionário leva para completar uma tarefa.

## Requisitos para o codigo
#### Algoritimo testado em:
- Windows 11<b>
### Compilador 
- Replit
- Visual Code Studio GCC 6.3.0







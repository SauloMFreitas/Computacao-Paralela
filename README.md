# Computao-Paralela
 Repositório para armazenar os códigos feitos para atividades de Computação Paralela na PUC-MINAS no semestre 2024/2

obs.: tarefas 1 e 5 foram quizzes online
obs2.: todas as tarefas foram realizadas em grupo de 3 ou 4 pessoas

## Tarefa 2
Modifique o seguinte código, utilizando o padrão MAP (e outros comandos do OpenMP),

#include <stdio.h>
#include <omp.h>

int main()
{
    int i;

    #pragma omp parallel num_threads(2) // seta o número de threads em 2 
    {
        int tid = omp_get_thread_num(); // lê o identificador da thread 
        for(i = 1; i <= 3; i++) 
        {
           printf("[PRINT1] T%d = %d \n",tid,i);
           printf("[PRINT2] T%d = %d \n",tid,i);
        }
    }
}

para que a saída do programa seja:

[PRINT1] T0 = 1 
[PRINT2] T0 = 1 
[PRINT1] T0 = 2 
[PRINT2] T0 = 2 
[PRINT1] T1 = 3 
[PRINT2] T1 = 3

## Tarefa 3
Implementar um código paralelo OpenMP em C (Linux utilizando o compilador GCC) usando também o padrão REDUCE e políticas de escalonamento para encontrar a quantidade de números primos entre 2 e n, onde n é um número inteiro <= 1000000000, usando o Crivo de Eratóstenes sequencial (sieve.c). Um exemplo de entrada e saída abaixo:

## Tarefa 4
Dado o seguinte código em MPI para um processo mestre distribuir um número entre os processos escravo (distribute_number.c), complete o código, substituindo os comentários, com as operações de send e receive para que ele funcione corretamente (não é permitido utilizar operações de comunicação coletiva).

## Tarefa 6
Dado o seguinte código em MPI para encontrar o maior elemento em um vetor de tamanho N (max_int.c), complete o código, substituindo os comentários, com as operações em MPI necessárias para que ele funcione corretamente.

## Tarefa 7
Paralelizar e avaliar o desempenho do código da multiplicação de matrizes (mm.c Download mm.c) para GPU usando o OpenMP. 

A entrega deve ser um arquivo .c. 

Ao postar o código, o grupo deve colocar como comentário no início do código os tempos de execução da versão sequencial, paralela para multicore, e paralela para GPU (com as diretivas "distribute", "distribute parallel for" e "distribute parallel for simd". Todas as versões (incluindo a sequencial) devem ser compiladas com -O3. Deixar comentado os pragmas para multicore e gpu comentados no arquivo .c submetido.

Importante: Os códigos devem ser compilados com o compilador gcc8 e a flag -fopenmp.
Escrever literalmente gcc8

## Tarefa 8

Paralelizar e avaliar o desempenho do código da multiplicação de matrizes (mm.c) para GPU usando CUDA. 

A entrega deve ser um arquivo .txt. 

Ao postar o código, o aluno deve colocar como comentário no início do código os tempos de execução da versão sequencial, paralela para multicore, e a melhor paralela para GPU com OpenMP e a versão em CUDA. Todas as versões (incluindo a sequencial) devem ser compiladas com -O3. 

Além do tempo, o aluno também deve postar o número de warps_launched e o warp_execution_efficiency para as versões em GPU. Estas métricas são obtidas executando-se o código com o nvprof.

nvprof --events warps_launched --metrics warp_execution_efficiency ./mm

Importante: Os códigos devem ser compilados com o compilador gcc8 e a flag -fopenmp para OpenMP e com o compilador nvcc para CUDA.

Importante: Caso ocorra algum erro para obtenção dos warps, primeiro, tente descobrir se algo foi feito errado. Depois de algumas tentativas, o erro permanecendo, explique o que foi feito para obter os resultados, mesmo que sem sucesso.

Dicas:

i) A multiplicação de matrizes utiliza-se de duas dimensões (x e y, ou "i" e "j", ou linha e coluna), portanto é necessário utilizar-se no kernel dois índices:

int row = blockIdx.y*blockDim.y+threadIdx.y;
int col = blockIdx.x*blockDim.x+threadIdx.x;

ii) Como a multiplicação de matrizes tem vários laços aninhados, a granularidade é por elemento de saída. Isso significa que apenas o laço do "k" (mais interno) será executado no kernel.

iii) O dimGrid e o dimBlock também utilizarão a segunda dimensão deles (basta repetir a primeira, no segundo argumento).

iv) No kernel é necessário agora conferir se as threads não estão acessando elementos inexistentes tanto pelo índice da linha, quanto pelo índice da coluna.

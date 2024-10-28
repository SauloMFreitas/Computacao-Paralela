/**
 * @file Tarefa2.c
 * @authors Bernardo Marques
 *          Marcos Antônio Lommez
 *          Saulo de Moura
 *          Vitória de Lourdes
 * @brief Modificar o código utilizando o padrão MAP (não alterar o código fonte, apenas incluir as diretivas necessárias).
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <omp.h>

int main()
{
    int i;

    #pragma omp parallel num_threads(2) // seta o número de threads em 2 
    {
        int tid = omp_get_thread_num(); // lê o identificador da thread 
        #pragma omp for ordered schedule(dynamic) // inicializa uma "ordered clause" para realizar "#pragma omp ordered"
        for(i = 1; i <= 3; i++) 
        {
           #pragma omp ordered // executa as regiões sequencialmente na ordem das iterações do loop
           {
                //OBS.: também é possível usar #pragma omp ordered threads que o efeito será o mesmo
                printf("[PRINT1] T%d = %d \n",tid,i);
                printf("[PRINT2] T%d = %d \n",tid,i);
           }
        }
    }
}
/**
 * @file Tarefa6.c
 * @authors Bernardo Marques
 *          Marcos Antônio Lommez
 *          Saulo de Moura
 *          
 * @brief complete o código, substituindo os comentários, com as 
 *        operações em MPI necessárias para que ele funcione corretamente.
 *        Para o caso foi usado Scatter(para distribuir o vetor) 
 *        e Reduce(para reduzir os maiores valores até um único valor)
 * 
 * @date 2024-10-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <time.h>
#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>
#define N 20
#define MAX 2000
#define NUMBER 3//Não entendemos a utilidade dessa definição(??)

void main(int argc, char* argv[]) {
  int p, rank, maior_parcial, maior_final, numProcs;
  int buffer[N];
  MPI_Status status;

  MPI_Init(&argc, &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);


  int chunk_size = N / numProcs; // Quantos elementos cada processo terá
  int chunk[chunk_size];         // Vetor para armazenar os valores nos processos

  if (rank == 0) {
    // preencher o buffer com N valores inteiros aleatórios
    srand(time(NULL));
    for(int i = 0; i < N; i++){
      buffer[i] = rand() % MAX;
      printf("buffer[%d] = %d\n", i, buffer[i]);
    }
  } 

  // distribuir o vetor para todos os outros processos
  MPI_Scatter(buffer, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

  // processar o maior dos valores dentro do seu intervalo
  maior_parcial = chunk[0];
  for(int i = 1; i < chunk_size; i++){

    if(chunk[i] > maior_parcial){
      maior_parcial = chunk[i];
    }

  }

  // reduzir os maiores no maior, enviando o resultado para o processo com rank = 0

  MPI_Reduce(&maior_parcial, &maior_final, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); 

  if (rank == 0) {
    // imprimir maior
    printf("o maior valor no vetor é: %d\n",maior_final);
  }
  
  MPI_Finalize();
}

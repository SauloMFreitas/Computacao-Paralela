/**
 * @file Tarefa4.c
 * @authors Bernardo Marques
 *          Marcos Antônio Lommez
 *          Saulo de Moura
 *
 * @brief Completar o código em MPI para uim processo mestre distribuir um número entre processos escravo
 *        com as operações de send e receive para que ele funcione corretamente
 *          -> Restrições: (não é permitido utilizar operações de comunicação coletiva).
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAG 1

void main(int argc, char* argv[]) {
  int i, rank, val, numProcs;
  MPI_Status status;

  // inicialização do MPI ---------------------------
  MPI_Init(&argc, &argv) ;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  //-------------------------------------------------
  if (rank == 0) {
    val = 51; // qual mensagem será enviada

    // enviar o valor para todos os processos
    for(i = 1; i < numProcs; i++){
      MPI_Send(&val, 1, MPI_DOUBLE, i, TAG, MPI_COMM_WORLD);// primitiva send envia a mensagem val do processo 0 para o processo i
      printf("Process %d sends a message to %d\n",rank,i);
    }
  } else {

    // receber o valor enviado
    MPI_Recv(&val, 1, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, &status); // primitiva receive faz com que cada processo possa receber a mensagem enviada pelo processo 0
    printf("Process %d receives a message from %d with value %d\n",rank,0,val);

  }
  MPI_Finalize();
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
 * @file Tarefa7.c
 * @authors Bernardo Marques
 *          Marcos Antônio Lommez
 *          Saulo de Moura
 *
 * @brief o grupo deve colocar como comentário no início do código os tempos de execução da versão sequencial,
 *        paralela para multicore, e paralela para GPU (com as diretivas "distribute", "distribute parallel for"
 *        e "distribute parallel for simd". Todas as versões (incluindo a sequencial) devem ser compiladas com -O3.
 *        Deixar comentado os pragmas para multicore e gpu comentados no arquivo .c submetido.
 *
 * gcc8 -fopenmp -O3 -o t7 mm.c && time ./t7
 *
 *                              |    real    |    user    |    sys    | Speed-Up Seq | Speed-Up Par |
 * sequencial                   | 1m  6.137s | 1m  6.018s | 0m 0.060s |    1.000x    |    ------    |
 * paralelo multicore           | 0m 17.873s | 1m 10.034s | 0m 0.088s |    3.700x    |    1.000x    |
 * distribute                   | 1m 50.129s | 1m 29.818s | 0m20.292s |    0.601x    |    0.162x    |
 * distribute parallel for      | 0m 23.832s | 0m 18.218s | 0m 5.591s |    2.775x    |    0.750x    |
 * distribute parallel for simd | 0m 15.654s | 0m 12.360s | 0m 3.270s |    4.225x    |    1.142x    |
 *
 * Speed-Up Seq = Speed-Up em relacao ao codigo sequencial
 * Speed-Up Par = Speed-Up em relacao do multicore aos de GPU
 *
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */

void mm(double* a, double* b, double* c, int width)
{
        // #pragma omp parallel for collapse(2) // MULTICORE
        // #pragma omp target teams distribute map(to: a[0:width*width], b[0:width*width]) map(from: c[0:width*width]) // DISTRIBUTE
        // #pragma omp target teams distribute parallel for collapse(2) map(to: a[0:width*width], b[0:width*width]) map(from: c[0:width*width]) // DISTRIBUTE PARALLEL FOR
        for (int i = 0; i < width; i++) {
                for (int j = 0; j < width; j++) {
                        double sum = 0;
                        // #pragma unroll
                        // #pragma omp simd // DISTRIBUTE PARALLEL FOR SIMD - obs: usar junto do pragma distribute parallel for
                        for (int k = 0; k < width; k++) {
                                double x = a[i * width + k];
                                double y = b[k * width + j];
                                sum += x * y;
                        }
                        c[i * width + j] = sum;
                }
        }
}

int main()
{
        int width = 2000;
        double *a = (double*) malloc (width * width * sizeof(double));
        double *b = (double*) malloc (width * width * sizeof(double));
        double *c = (double*) malloc (width * width * sizeof(double));

        for(int i = 0; i < width; i++) {
                for(int j = 0; j < width; j++) {
                        a[i*width+j] = i;
                        b[i*width+j] = j;
                        c[i*width+j] = 0;
                }
        }

        mm(a,b,c,width);

        //      for(int i = 0; i < width; i++) {
        //              for(int j = 0; j < width; j++) {
        //                       printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
        //              }
        //      }
}
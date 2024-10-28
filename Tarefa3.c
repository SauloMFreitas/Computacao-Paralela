/**
 * @file Tarefa3.c
 * @authors Bernardo Marques
 *          Marcos Antônio Lommez
 *          Saulo de Moura
 *          Vitória de Lourdes

 * @date 2024-09-11
 * 
 * obs: para cada teste foi realizado 10 compilações e execuções do código e feito a média dos tempos de execução
 * 
 * Como foi realizado:: primeiramente for realizado os testes com o código original sequencial e pego a média de tempos de execução
 *                      para os testes com o código em paralelo, foram adicionados 2 diretivas #pragma omp parallel for, uma para o primeiro loop e outra para o segundo loop
 *                      No primeiro loop foi adicionado a diretiva schedule, com os valores static, dynamic e guided, além do default nao adicionando nenhum schedule, para verificar qual o melhor desempenho
 *                      No segundo loop foi adicionado a diretiva reduction para somar a quantidade de números primos
 * 
 *                                              (seg) :: SpeedUp
 * tempo de execução sequencial               : 1,704 :: 1.0000
 * tempo de execução paralelo default         : 1,355 :: 1,2578
 * tempo de execução paralelo schedule static : 1,363 :: 1,2499
 * tempo de execução paralelo schedule dynamic: 0,678 :: 2,5178
 * tempo de execução paralelo schedule guided : 1,408 :: 1,2097
 * 
 * Após reaizar os testes é perciptível que o melhor desempenho foi com a diretiva schedule dynamic, com um speedup de 2,5178
 * 
 * Caso queira ver os 10 tempos de execução separadamente, está disponível em https://docs.google.com/spreadsheets/d/1KuTAe3jVtIjf9Y59sCkf9VwF3Kz0Srfj99oFqym5Vb8/edit?usp=sharing
 * 
 * Configuração da máquina testada:
 *    Processador: AMD Ryzen 5 5500U with Radeon Graphics
 *    memoria RAM: 8GB DDR4
 *    Sistema Operacional: Linux Mint 
 *    placa mãe: LNVNB161216
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/*
* Adapted from: http://w...content-available-to-author-only...s.org/sieve-of-eratosthenes
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <omp.h>

#include <time.h>

int sieveOfEratosthenes(int n)
{
   // Create a boolean array "prime[0..n]" and initialize
   // all entries it as true. A value in prime[i] will
   // finally be false if i is Not a prime, else true.
   int primes = 0; 
   bool *prime = (bool*) malloc((n+1)*sizeof(bool));
   int sqrt_n = sqrt(n);

   memset(prime, true,(n+1)*sizeof(bool));

   #pragma omp parallel for schedule(guided)
   for (int p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       if (prime[p] == true)
       {
           // Update all multiples of p
           for (int i=p*2; i<=n; i += p)
           prime[i] = false;
        }
    }

          // count prime numbers
   #pragma omp parallel for reduction (+: primes)
   for (int p=2; p<=n; p++)
      if (prime[p])
         primes++;

   return(primes);
}

int main()
{


   int n = 100000000;
   printf("%d\n",sieveOfEratosthenes(n));

   
   return 0;
} 
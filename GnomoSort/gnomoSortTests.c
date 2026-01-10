#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a quantidade de números no vetor para os testes
#define N 20000

/**
 * Enumeração para organizar os tipos de cenários de teste.
 */
typedef enum
{
    ALEATORIO,
    CRESCENTE,
    DECRESCENTE
} TipoTeste;

/**
 * Função Auxiliar: Troca de Valores
 * Recebe o endereço de dois inteiros e inverte seus conteúdos.
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Algoritmo Principal: Gnome Sort
 * - Se os elementos estão na ordem correta, o "gnomo" avança (index++).
 * - Se estão fora de ordem, ele troca os dois e volta uma posição (index--).
 * * Essa volta é necessária para garantir que o elemento que foi movido para trás
 * seja comparado novamente com seu novo antecessor.
 */
void gnomeSort(int arr[], int n)
{
    int index = 0;
    while (index < n)
    {
        if (index == 0)
            index++;

        if (arr[index] >= arr[index - 1])
        {
            index++;
        }
        else
        {
            swap(&arr[index], &arr[index - 1]);

            index--;
        }
    }
}

/**
 * Função de Geração de Dados:
 * Preenche o vetor dinamicamente conforme o cenário:
 * - ALEATORIO: Usa rand() para gerar valores sem ordem definida.
 * - CRESCENTE: Preenche em ordem crescente (Melhor Caso - O gnomo nunca recua).
 * - DECRESCENTE: Preenche em ordem decrescente (Pior Caso - O gnomo recua ao máximo).
 */
void prepararVetor(int v[], int n, TipoTeste tipo)
{
    for (int i = 0; i < n; i++)
    {
        if (tipo == ALEATORIO)
        {
            v[i] = rand() % 100000;
        }
        else if (tipo == CRESCENTE)
        {
            v[i] = i;
        }
        else if (tipo == DECRESCENTE)
        {
            v[i] = n - i;
        }
    }
}

/**
 * Função de Gerenciamento de Experimento:
 * Realiza todo o ciclo de teste: alocação, preenchimento, cronometragem e limpeza.
 */
void rodarExperimento(TipoTeste tipo, const char *nome)
{
    // Alocação do vetor
    int *v = (int *)malloc(N * sizeof(int));
    if (!v)
        return;

    // Prepara os dados iniciais
    prepararVetor(v, N, tipo);

    printf("Testando cenário %s: ", nome);

    // Captura o tempo de CPU inicial
    clock_t start = clock();

    // Executa a ordenação
    gnomeSort(v, N);

    // Captura o tempo de CPU final
    clock_t end = clock();

    // Calcula a diferença em segundos
    double tempo_segundos = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tempo: %.6f segundos\n", tempo_segundos);
    free(v);
}

int main()
{
    // Semente para o gerador aleatório baseada no relógio do sistema
    srand(time(NULL));

    // Execução dos três cenários
    rodarExperimento(ALEATORIO, "Aleatorio");
    rodarExperimento(CRESCENTE, "Crescente");
    rodarExperimento(DECRESCENTE, "Decrescente");

    return 0;
}
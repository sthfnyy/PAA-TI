#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// faz as trocas dos valores no vetor
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// garante que a subárvore com raiz no índice i obedeça a regra de max-heap (pai maior que os filhos)
void heapify(int arr[], int n, int i) {
    int maior = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[maior]) 
        maior = l;
    if (r < n && arr[r] > arr[maior]) 
        maior = r;

    if (maior != i) {
        swap(&arr[i], &arr[maior]);   // <-- corrigido (passa ponteiro)
        heapify(arr, n, maior);
    }
}

// ordena o vetor usando Heap Sort.
void heapSort(int arr[], int n) {
    // Vai chamando heapify para transformar o vetor em um max-heap
    for (int i = (n / 2) - 1; i >= 0; i--) 
        heapify(arr, n, i);

    // extração do maior repetidamente (ordenação)
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);       // <-- corrigido (passa ponteiro)
        heapify(arr, i, 0);
    }
}

// leitura dos dados do arquivo
void lerArquivo(int *vetor, int n, const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d", &vetor[i]) != 1) {
            printf("erro ao ler valor na linha %d\n", i + 1);
            fclose(file);
            exit(1);
        }
    }

    fclose(file);
}

int main() 
{
    int n, numTestes;
    printf("tamanho do vetor:  ");
    scanf("%d", &n);
    printf("número de testes:  ");
    scanf("%d", &numTestes);

    int *vetor = (int*)malloc(n * sizeof(int));

    srand(time(NULL));

    // crescente
    double somaCrescente = 0.0;
    for (int j = 0; j < numTestes; j++) {
        for(int i = 0; i < n; i++) vetor[i] = i;

        clock_t inicio = clock();
        heapSort(vetor, n);
        clock_t fim = clock();

        double tempoSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaCrescente += tempoSegundos;

        printf("tempo crescente rodada %d: %.10f s, %.2f us\n", j+1, tempoSegundos, tempoSegundos*1e6);
    }
    printf("media crescente: %.10f s, %.2f us\n\n", somaCrescente/numTestes, (somaCrescente*1e6)/numTestes);

    // decrescente
    double somaDecrescente = 0.0;
    for (int j = 0; j < numTestes; j++) {
        for(int i = 0; i < n; i++) vetor[i] = n - i;

        clock_t inicio = clock();
        heapSort(vetor, n);
        clock_t fim = clock();

        double tempoSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaDecrescente += tempoSegundos;

        printf("tempo decrescente rodada %d: %.10f s, %.2f us\n", j+1, tempoSegundos, tempoSegundos*1e6);
    }
    printf("media decrescente: %.10f s, %.2f us\n\n", somaDecrescente/numTestes, (somaDecrescente*1e6)/numTestes);

    // aleatório -> lê do arquivo
    double somaAleatorio = 0.0;
    for (int j = 0; j < numTestes; j++) {
        lerArquivo(vetor, n, "baseDeDados.txt");

        clock_t inicio = clock();
        heapSort(vetor, n);
        clock_t fim = clock();

        double tempoSegundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
        somaAleatorio += tempoSegundos;

        printf("tempo aleatorio rodada %d: %.10f s, %.2f us\n", j+1, tempoSegundos, tempoSegundos*1e6);
    }
    printf("media aleatorio: %.10f s, %.2f us\n\n", somaAleatorio/numTestes, (somaAleatorio*1e6)/numTestes);

    free(vetor);
    return 0;
}

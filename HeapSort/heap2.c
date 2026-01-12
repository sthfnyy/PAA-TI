#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// De acordo com o chat esta modularizado  
/* =========================
   Funções já existentes
   ========================= */

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
        swap(&arr[i], &arr[maior]);
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
        swap(&arr[0], &arr[i]);
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

/* =========================
   Novas funções (modularização)
   * Não altera a lógica
   ========================= */

static void preencherCrescente(int *vetor, int n) {
    for (int i = 0; i < n; i++) vetor[i] = i;
}

static void preencherDecrescente(int *vetor, int n) {
    // Mantendo a mesma lógica do seu código original (n, n-1, ..., 1)
    for (int i = 0; i < n; i++) vetor[i] = n - i;
}

static double medirTempoHeapSort(int *vetor, int n) {
    clock_t inicio = clock();
    heapSort(vetor, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

static void imprimirRodada(const char *rotulo, int rodada, double tempoSegundos) {
    printf("tempo %s rodada %d: %.10f s, %.2f us\n",
           rotulo, rodada, tempoSegundos, tempoSegundos * 1e6);
}

static void imprimirMedia(const char *rotulo, double somaTempos, int numTestes) {
    double media = somaTempos / numTestes;
    printf("media %s: %.10f s, %.2f us\n\n",
           rotulo, media, media * 1e6);
}

static double executarTesteCrescente(int *vetor, int n, int numTestes) {
    double soma = 0.0;
    for (int j = 0; j < numTestes; j++) {
        preencherCrescente(vetor, n);
        double t = medirTempoHeapSort(vetor, n);
        soma += t;
        imprimirRodada("crescente", j + 1, t);
    }
    imprimirMedia("crescente", soma, numTestes);
    return soma;
}

static double executarTesteDecrescente(int *vetor, int n, int numTestes) {
    double soma = 0.0;
    for (int j = 0; j < numTestes; j++) {
        preencherDecrescente(vetor, n);
        double t = medirTempoHeapSort(vetor, n);
        soma += t;
        imprimirRodada("decrescente", j + 1, t);
    }
    imprimirMedia("decrescente", soma, numTestes);
    return soma;
}

static double executarTesteAleatorioArquivo(int *vetor, int n, int numTestes, const char *arquivo) {
    double soma = 0.0;
    for (int j = 0; j < numTestes; j++) {
        lerArquivo(vetor, n, arquivo);
        double t = medirTempoHeapSort(vetor, n);
        soma += t;
        imprimirRodada("aleatorio", j + 1, t);
    }
    imprimirMedia("aleatorio", soma, numTestes);
    return soma;
}

/* =========================
   main
   ========================= */

int main() {
    int n, numTestes;

    printf("tamanho do vetor:  ");
    scanf("%d", &n);

    printf("número de testes:  ");
    scanf("%d", &numTestes);

    int *vetor = (int*)malloc((size_t)n * sizeof(int));
    if (!vetor) {
        printf("erro: falha ao alocar memoria para n=%d\n", n);
        return 1;
    }

    srand((unsigned)time(NULL));

    executarTesteCrescente(vetor, n, numTestes);
    executarTesteDecrescente(vetor, n, numTestes);
    executarTesteAleatorioArquivo(vetor, n, numTestes, "baseDeDados.txt");

    free(vetor);
    return 0;
}

#include <stdio.h>

void printArray(int arr[], int n, int atual)
{
    for (int i = 0; i < n; i++)
    {
        if (i == atual)
            printf("[%d] ", arr[i]);
        else
            printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void gnomeSort(int arr[], int n)
{
    int index = 0;
    int passo = 1;

    while (index < n)
    {
        printf("Passo %02d (Indice %d): ", passo++, index);
        printArray(arr, n, index);

        if (index == 0 || arr[index] >= arr[index - 1])
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

int main()
{
    int vetor[] = {34, 2, 10, 9, 0};
    int n = 5;

    printf("===== VETOR INICIAL ====\n");
    printArray(vetor, n, -1);
    printf("\n==== INICIANDO ORDENACAO ====\n");

    gnomeSort(vetor, n);

    printf("\n===== VETOR FINAL (ORDENADO) =====\n");
    printArray(vetor, n, -1);

    return 0;
}
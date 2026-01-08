import time
import random

# --- ALGORITMO HEAP SORT ---

def transformar_em_heap(vetor, tamanho_do_heap, indice_raiz):
    """
    Mantém a propriedade do heap máximo (o pai deve ser maior que os filhos).
    """
    maior = indice_raiz  
    esquerda = 2 * indice_raiz + 1
    direita = 2 * indice_raiz + 2

    # Verifica se o filho da esquerda existe e é maior que a raiz
    if esquerda < tamanho_do_heap and vetor[esquerda] > vetor[maior]:
        maior = esquerda

    # Verifica se o filho da direita existe e é maior que o maior atual
    if direita < tamanho_do_heap and vetor[direita] > vetor[maior]:
        maior = direita

    # Se o maior não for a raiz, realiza a troca e continua organizando
    if maior != indice_raiz:
        vetor[indice_raiz], vetor[maior] = vetor[maior], vetor[indice_raiz]
        
        # Chamada recursiva para garantir que a subárvore esteja correta
        transformar_em_heap(vetor, tamanho_do_heap, maior)


def heap_sort(vetor):
    """
    Função principal que executa a ordenação por Heap.
    Complexidade: O(n log n)
    """
    n = len(vetor)

    # 1. Constrói o Heap Máximo (Rearranja o vetor)
    # Começa do último nó que não é folha e vai até a raiz
    for i in range(n // 2 - 1, -1, -1):
        transformar_em_heap(vetor, n, i)

    # 2. Extrai os elementos um por um do heap
    for i in range(n - 1, 0, -1):
        # Move a raiz atual (maior elemento) para o final do vetor
        vetor[0], vetor[i] = vetor[i], vetor[0]
        
        # Chama transformar_em_heap no heap reduzido
        transformar_em_heap(vetor, i, 0)
    
    return vetor

# --- FUNÇÕES OBRIGATÓRIAS DO PROJETO ---

def gerar_vetor(tamanho, tipo='aleatorio'):
    """Gera vetores: 'aleatorio', 'ordenado' ou 'invertido'."""
    if tipo == 'aleatorio':
        return [random.randint(0, tamanho * 10) for _ in range(tamanho)]
    elif tipo == 'ordenado':
        return list(range(tamanho))
    elif tipo == 'invertido':
        return list(range(tamanho, 0, -1))

def medir_tempo_heap(tamanho, tipo):
    """Realiza a medição de tempo do algoritmo Heap Sort."""
    vetor = gerar_vetor(tamanho, tipo)
    
    inicio = time.perf_counter()
    heap_sort(vetor)
    fim = time.perf_counter()
    
    tempo_total = fim - inicio
    return tempo_total

# --- DEMONSTRAÇÃO DE USO ---

if __name__ == "__main__":
    # Exemplo simples de funcionamento
    exemplo = [35, 12, 43, 8, 51]
    print(f"Exemplo original: {exemplo}")
    heap_sort(exemplo)
    print(f"Exemplo ordenado: {exemplo}")
    print("-" * 30)

    # Teste de desempenho conforme solicitado no projeto
    n = 10000
    cenarios = ['aleatorio', 'ordenado', 'invertido']
    
    print(f"Desempenho Heap Sort (N={n}):")
    for c in cenarios:
        tempo = medir_tempo_heap(n, c)
        print(f"Cenário {c:10}: {tempo:.6f} segundos")
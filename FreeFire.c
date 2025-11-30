#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/* Mostra os componentes após a ordenação */
void mostrarComponentes(Componente v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-15s | prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

/* Bubble sort por nome */
long bubbleSortNome(Componente v[], int n) {
    long comp = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comp++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
    return comp;
}

/* Insertion sort por tipo */
long insertionSortTipo(Componente v[], int n) {
    long comp = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comp++;
            v[j + 1] = v[j];
            j--;
        }
        if (j >= 0) comp++;

        v[j + 1] = chave;
    }
    return comp;
}

/* Selection sort por prioridade */
long selectionSortPrioridade(Componente v[], int n) {
    long comp = 0;
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comp++;
            if (v[j].prioridade < v[menor].prioridade)
                menor = j;
        }
        if (menor != i) {
            Componente tmp = v[i];
            v[i] = v[menor];
            v[menor] = tmp;
        }
    }
    return comp;
}

/* Busca binária por nome (após bubble sort) */
int buscaBinariaPorNome(Componente v[], int n, char alvo[]) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(alvo, v[meio].nome);

        if (cmp == 0) return meio;
        if (cmp > 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* Mede tempo de execução de um algoritmo */
double medirTempo(long (*alg)(Componente[], int), Componente v[], int n, long *comparacoes) {
    clock_t ini = clock();
    *comparacoes = alg(v, n);
    clock_t fim = clock();
    return (double)(fim - ini) / CLOCKS_PER_SEC;
}

int main() {
    Componente itens[20];
    int qtd = 0;

    printf("Quantos componentes (max 20)? ");
    scanf("%d", &qtd);
    getchar();

    for (int i = 0; i < qtd; i++) {
        printf("\nComponente %d:\n", i + 1);

        printf("Nome: ");
        fgets(itens[i].nome, 30, stdin);
        itens[i].nome[strcspn(itens[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(itens[i].tipo, 20, stdin);
        itens[i].tipo[strcspn(itens[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &itens[i].prioridade);
        getchar();
    }

    printf("\n1 - Ordenar por nome (Bubble)\n");
    printf("2 - Ordenar por tipo (Insertion)\n");
    printf("3 - Ordenar por prioridade (Selection)\n");
    printf("Escolha: ");
    int op;
    scanf("%d", &op);
    getchar();

    Componente copia[20];
    memcpy(copia, itens, sizeof(itens));

    long comps = 0;
    double tempo = 0;

    if (op == 1) {
        tempo = medirTempo(bubbleSortNome, copia, qtd, &comps);
    } else if (op == 2) {
        tempo = medirTempo(insertionSortTipo, copia, qtd, &comps);
    } else if (op == 3) {
        tempo = medirTempo(selectionSortPrioridade, copia, qtd, &comps);
    }

    printf("\nComponentes ordenados:\n");
    mostrarComponentes(copia, qtd);

    printf("\nComparacoes: %ld\n", comps);
    printf("Tempo: %.6f segundos\n", tempo);

    if (op == 1) {
        char chave[30];
        printf("\nBuscar qual componente? ");
        getchar();
        fgets(chave, 30, stdin);
        chave[strcspn(chave, "\n")] = '\0';

        int idx = buscaBinariaPorNome(copia, qtd, chave);

        if (idx >= 0) {
            printf("Encontrado: %s (%s), prioridade %d\n",
                   copia[idx].nome, copia[idx].tipo, copia[idx].prioridade);
        } else {
            printf("Nao encontrado.\n");
        }
    }

    return 0;
}

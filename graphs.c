/*
Grupa: 161
Problema: Colorarea grafurilor (Greedy)
Nume: Rusănescu Gabriel
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    int id;
    int degree;
    int color;
    int *neighbors;
} Node;

Node* aloca_graf(int n) {
    Node* graf = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        graf[i].id = i + 1;
        graf[i].degree = 0;
        graf[i].color = -1;
        graf[i].neighbors = NULL;
    }
    return graf;
}

void elibereaza_graf(Node* graf, int n) {
    for (int i = 0; i < n; i++) {
        free(graf[i].neighbors);
    }
    free(graf);
}

void sorteaza_dupa_grad(Node** ordine, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ordine[i]->degree < ordine[j]->degree) {
                Node* temp = ordine[i];
                ordine[i] = ordine[j];
                ordine[j] = temp;
            }
        }
    }
}

int coloreaza_greedy(const char* filename) {
    FILE* f = fopen(filename, "r"); // 
    if (!f) return -1;

    int n;
    if (fscanf(f, "%d", &n) != 1) {
        fclose(f);
        return -1;
    }

    Node* graf = aloca_graf(n);
    Node** ordine = (Node**)malloc(n * sizeof(Node*));

    for (int i = 0; i < n; i++) {
        int current_id, deg;
        fscanf(f, "%d %d", &current_id, &deg);
        graf[i].degree = deg;
        graf[i].neighbors = (int*)malloc(deg * sizeof(int));
        for (int j = 0; j < deg; j++) {
            fscanf(f, "%d", &graf[i].neighbors[j]);
        }
        ordine[i] = &graf[i];
    }
    fclose(f);

    sorteaza_dupa_grad(ordine, n);

    int max_color = 0;
    for (int i = 0; i < n; i++) {
        Node* u = ordine[i];
        bool* culori_folosite = (bool*)calloc(n + 1, sizeof(bool));
        for (int j = 0; j < u->degree; j++) {
            int v_id = u->neighbors[j];
            if (graf[v_id - 1].color != -1) {
                culori_folosite[graf[v_id - 1].color] = true;
            }
        }
        int color = 1;
        while (culori_folosite[color]) color++;        
        u->color = color;
        if (color > max_color) max_color = color;
        free(culori_folosite);
    }
    elibereaza_graf(graf, n);
    free(ordine);
    return max_color;
}

int main(){
    assert(coloreaza_greedy("input1.txt") == 3); 
    assert(coloreaza_greedy("input2.txt") == 3);
    assert(coloreaza_greedy("input3.txt") == 2);
    printf("Toate testele (assert) au trecut cu succes!\n");
    return 0;
}
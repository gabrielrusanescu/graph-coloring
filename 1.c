/*
Grupa: 161
Problema: 6, culoarearea grafurilor (Greedy)
Nume: Rusănescu Gabriel
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct{
    int id;
    int grad;
    int culoare;
    int *vecini;
} nod;


int comparnoduri(const void* a, const void* b){
    nod* n1 = *(nod**)a;
    nod* n2 = *(nod**)b;
    if(n2->grad != n1->grad){
        return n2->grad - n1->grad;
    }
    // in caz ca au acelasi grad iau dupa ID crescator
    return n1->id - n2->id;
}

nod* aloca_graf(int n){
    nod* graf=(nod*)malloc(n*sizeof(nod));
    for(int i=0; i<n; i++){
        graf[i].id=i+1;
        graf[i].grad=0;
        graf[i].culoare=-1;
        graf[i].vecini=NULL;
    }
    return graf;
}

void elibereaza_graf(nod* graf, int n){
    for (int i=0; i<n; i++){
        free(graf[i].vecini);
    }
    free(graf);
}

int greedycolorare(const char* filename){
    FILE* f=fopen(filename, "r");
    if(!f) return -1;
    int n;
    if (fscanf(f, "%d", &n)!=1){
        fclose(f);
        return -1;
    }
    nod* graf = aloca_graf(n);
    nod** ordine = (nod**)malloc(n*sizeof(nod*));
    for(int i=0; i<n; i++){
        int id_curent, grad;
        fscanf(f, "%d %d", &id_curent, &grad);
        graf[i].grad=grad;
        graf[i].vecini=(int*)malloc(grad*sizeof(int));
        for(int j=0; j<grad; j++){
            fscanf(f, "%d", &graf[i].vecini[j]);
        }
        ordine[i] = &graf[i];
    }
    fclose(f);

    qsort(ordine, n, sizeof(nod*), comparnoduri);

    int maxculoare=0;
    for(int i=0; i<n; i++){
        nod* u = ordine[i];
        bool* culori_folosite = (bool*)calloc(n+1, sizeof(bool));
        for(int j=0; j < u->grad; j++){
            int v_id = u->vecini[j];
            if(graf[v_id - 1].culoare != -1){
                culori_folosite[graf[v_id - 1].culoare] = true;
            }
        }
        int culoare=1;
        while (culori_folosite[culoare]) culoare++;        
        u->culoare = culoare;
        if(culoare > maxculoare) maxculoare = culoare;
        free(culori_folosite);
    }
    elibereaza_graf(graf, n);
    free(ordine);
    return maxculoare;
}

int main(){
    assert(greedycolorare("input1.txt")==3); 
    assert(greedycolorare("input2.txt")==3);
    assert(greedycolorare("input3.txt")==2);
    printf("Toate testele au trecut cu succes!\n");
    return 0;
}

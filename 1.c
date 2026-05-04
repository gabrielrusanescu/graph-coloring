/*
Grupa: 161
Problema: 6, Colorarea grafurilor (Greedy)
Nume: Rusănescu Gabriel
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct{
    int id;
    int grad;
    int color;
    int *vecini;
} nod;

nod* aloca_graf(int n){
    nod* graf=(nod*)malloc(n*sizeof(nod));
    for(int i=0; i<n; i++){
        graf[i].id=i+1;
        graf[i].grad=0;
        graf[i].color=-1;
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

void sorteaza_dupa_grad(nod** ordine, int n){
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(ordine[i]->grad < ordine[j]->grad){
                nod* temp = ordine[i];
                ordine[i]=ordine[j];
                ordine[j]=temp;
            }
        }
    }
}

int greedycolor(const char* filename){
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
        int current_id, deg;
        fscanf(f, "%d %d", &current_id, &deg);
        graf[i].grad=deg;
        graf[i].vecini=(int*)malloc(deg*sizeof(int));
        for(int j=0; j<deg; j++){
            fscanf(f, "%d", &graf[i].vecini[j]);
        }
        ordine[i] = &graf[i];
    }
    fclose(f);

    sorteaza_dupa_grad(ordine, n);

    int maxcolor=0;
    for(int i=0; i<n; i++){
        nod* u = ordine[i];
        bool* culori_folosite = (bool*)calloc(n+1, sizeof(bool));
        for(int j=0; j < u->grad; j++){
            int v_id = u->vecini[j];
            if(graf[v_id - 1].color != -1){
                culori_folosite[graf[v_id - 1].color] = true;
            }
        }
        int color=1;
        while (culori_folosite[color]) color++;        
        u->color = color;
        if(color > maxcolor) maxcolor = color;
        free(culori_folosite);
    }
    elibereaza_graf(graf, n);
    free(ordine);
    return maxcolor;
}

int main(){
    assert(greedycolor("input1.txt")==3); 
    assert(greedycolor("input2.txt")==3);
    assert(greedycolor("input3.txt")==2);
    printf("Toate testele au trecut cu succes!\n");
    return 0;
}
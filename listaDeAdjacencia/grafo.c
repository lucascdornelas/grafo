#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

struct grafo {
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};

Grafo* cria_grafo(int nro_vertices, int grau_max, int eh_ponderado) {
    Grafo *gr = (Grafo*) malloc(sizeof(struct grafo));

    if(gr != NULL){
        int i;

        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
        gr->grau = (int*) calloc(nro_vertices, sizeof(int));
        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));

        for(i = 0; i < nro_vertices; i++){
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
            if(gr->eh_ponderado){
                gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));

                for(i = 0; i< nro_vertices; i++){
                    gr->pesos[i] = (float*) malloc(grau_max*sizeof(float)); 
                }
            }
        }
    }

    return gr;
}

void libera_grafo(Grafo *gr){
    if(gr != NULL){
        int i;
        for(i = 0; gr->nro_vertices; i++){
            free(gr->arestas[i]);
        }
        free(gr->arestas);

        if(gr->eh_ponderado){
            for(i = 0; i < gr->nro_vertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }

        free(gr->grau);
        free(gr);
    }
}

int insere_aresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL){
        return 0;
    }

    if(orig < 0 || orig >= gr->nro_vertices){
        gr->nro_vertices;
    }
    if(dest < 0 || dest >= gr->nro_vertices){
        return 0;
    }

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->eh_ponderado){
        gr->pesos[orig][gr->grau[orig]] = peso;
    }
    gr->grau[orig]++;

    if(eh_digrafo == 0){
        insere_aresta(gr, dest, orig, 1, peso);
    }

    return 1;
}

int remove_aresta(Grafo *gr, int orig, int dest, int eh_digrafo){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices)
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    int i = 0;
    while (i < gr->grau[orig] && gr->arestas[orig][i] != dest){
        i++;
    }
    if(i == gr->grau[orig])
        return 0;
    
    gr->grau[orig]--;
    gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];

    if(gr->eh_ponderado)
        gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];

    if(eh_digrafo == 0)
        remove_aresta(gr, dest, orig, 1);

    return 1;
}

// fun????o que faz a interface com o usu??rio
void busca_profundidade_grafo(Grafo *gr, int ini, int *visitado){
    int i, cont = 1;
    for(i = 0; i< gr->nro_vertices; i++){
        visitado[i] = 0;
    }

    busca_profundidade(gr, ini, visitado, cont);
}

// fun????o que faz o c??lculo
void busca_profundidade(Grafo *gr, int ini, int *visitado, int cont){
    int i;
    visitado[ini] = cont;

    for(i = 0; i < gr->grau[ini]; i++){
        if(!visitado[gr->arestas[ini][i]]){
            // chamada recursiva, assim cria a pilha de execu????o quando finalizar a busca em profundidade completa
            // ele vai chamar o ultimo no v??tice empilhado e verificar se seu pr??ximo vertice ja foi visitado.
            // caso ainda n??o for visitado: passa ele para execu????o, at?? todos seus filhos forem visitados...
            // caso j?? tiver sido visitado: ent??o passa para o vertice pai e assim por diante...

            busca_profundidade(gr, gr->arestas[ini][i], visitado, cont+1);
        }
    }
}

void busca_largura_grafo(Grafo *gr, int ini, int *visitado){
    int i, vert, NV, cont = 1, *fila, IF = 0, FF = 0;
    // marca os v??rtices como n??o visitados
    for(i = 0; i < gr->nro_vertices; i++)
        visitado[i] = 0;
    
    // cria fila.
    // visita e insere "ini" na fila
    NV = gr->nro_vertices;
    fila = (int*) malloc(NV * sizeof(int));
    FF++;
    fila[FF] = ini;
    visitado[ini] = cont;

    // pega primeiro da fila
    while(IF != FF){
        IF = (IF + 1) % NV;
        vert = fila[IF];
        cont++;
        
        // visita os visinhos ainda n??o visitados e coloca na fil
        for(i = 0; i < gr->grau[vert]; i++){
            if(!visitado[gr->arestas[vert][i]]){
                FF = (FF + 1) % NV;
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    }
    free(fila);
}


int main(int argc, char const *argv[]){
    Grafo *gr;
    gr = cria_grafo(9, 2, 0);

    insere_aresta(gr, 0, 1, 0, 0);
    insere_aresta(gr, 0, 5, 0, 0);
    insere_aresta(gr, 1, 2, 0, 0);
    insere_aresta(gr, 1, 3, 0, 0);
    insere_aresta(gr, 3, 4, 0, 0);
    insere_aresta(gr, 5, 6, 0, 0);

    insere_aresta(gr, 7, 8, 0, 0);

    int visitados_profundidade[9];
    int visitados_largura[9];

    busca_largura_grafo(gr, 0, visitados_largura);
    busca_profundidade_grafo(gr, 0, visitados_profundidade);

    for(int i = 0; i < 9; i++){
        printf("%d ", visitados_profundidade[i]);
    }
    printf("\n");
    for(int i = 0; i < 9; i++){
        printf("%d ", visitados_largura[i]);
    }

    libera_grafo(gr);

    return 0;
}

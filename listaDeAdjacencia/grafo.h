// TAD, "Grafo", usando a representação em lista de adjacência

typedef struct grafo Grafo;

Grafo *cria_grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_grafo(Grafo *gr);
int insere_aresta(Grafo *gr, int orig, int dest, int eh_digrafo, float peso);
int remove_aresta(Grafo *gr, int orig, int dest, int eh_digrafo);

// Busca em Grafos
void busca_profundidade_grafo(Grafo *gr, int ini, int *visitado);       //função interface com o usuário
void busca_profundidade(Grafo *gr, int ini, int *visitado, int cont);   //função que vai calcular e a busca



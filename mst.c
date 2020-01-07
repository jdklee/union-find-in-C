#include "mst.h"
#include "union_find.h"
#include "wu_graph.h"
#include <stdlib.h>
#include <stdio.h>
//source of comparator function and how built in sort works
//https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/

int comparator (const void* a, const void* b){
    struct wu_edge* e1= (struct wu_edge*)a;
    struct wu_edge* e2 = (struct wu_edge*)b;

    weight_t w1 = e1->w;
    weight_t w2= e2->w;
    if(w1>w2){
        return 1;
    }
    if (w2>w1){
        return -1;
    }
    else
        return 0;
}


wu_graph_t kruskal_mst(wu_graph_t g)
{
    union_find_t uf = NULL;
    wu_graph_t mst = NULL;
    uf=uf_create(wug_size(g));
    mst=wug_create(wug_size(g));
    size_t edge_count = wug_edge_count(g);
    //struct wu_edge mst_edges[wug_edge_count(g)];
    struct wu_edge edges[edge_count];
    wug_get_edges(g, edges, edge_count);

    if (!(uf = uf_create(wug_size(g))))
        goto finish;

    if (!(mst = wug_create(wug_size(g))))
        goto finish;



    qsort(edges, edge_count, sizeof(struct wu_edge), comparator);


    for (size_t i = 0; i < edge_count; i++) {
        if(uf_union(uf,edges[i].u,edges[i].v)){
            wug_set_edge(mst, edges[i].u, edges[i].v, edges[i].w); //added edges if no cycle...
        }
    }
    return mst;

    finish:
    uf_destroy(uf);
    wug_destroy(mst);

}
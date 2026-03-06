#include <stdio.h>
#include <stdlib.h>

struct dsu_node {
	struct dsu_node* parent;
	int rank;
	int num; 
	
}; typedef struct dsu_node dsu_node;

dsu_node* make_set(int num) {
	dsu_node *tmp = (dsu_node*) malloc(sizeof(dsu_node));
	tmp->num = num;
	tmp->rank = 1;
	tmp->parent = tmp;
	
	return tmp;
}

dsu_node* find_set(dsu_node* p) {
	if (p->parent == p) {
		return p;
	}
	
	return p->parent = find_set(p->parent);

}

dsu_node* union_set(dsu_node* p1, dsu_node* p2) {
	p1 = find_set(p1);
	p2 = find_set(p2);
	
	if (p1 != p2) {
		if (p1->rank > p2->rank) {
			p2->parent = p1;
			return p1;
		} else if (p1->rank < p2->rank) {
			p1->parent = p2;
			return p2;
		} else {
			p1->parent = p2;
			(p2->rank)++;
			return p2;
		}
	}
	
	return p1; 

}

void insert_edge(dsu_node **vertexes_dsus, int *component_weights, int from_vertex, int to_vertex, int weight) {

    int new_weight = 0;

    if (find_set(vertexes_dsus[from_vertex]) != find_set(vertexes_dsus[to_vertex])) {
        new_weight = weight + component_weights[find_set(vertexes_dsus[from_vertex])->num] + component_weights[find_set(vertexes_dsus[to_vertex])->num];

        union_set(vertexes_dsus[from_vertex], vertexes_dsus[to_vertex]);
    } else {
        new_weight = component_weights[find_set(vertexes_dsus[from_vertex])->num] + weight;
    }

    component_weights[find_set(vertexes_dsus[from_vertex])->num] = new_weight;

}


int main(void) {
    dsu_node **vertexes_dsus;
    int *component_weights;

    int count_of_vertexes, count_of_requests;
    int component_vertex, from_vertex, to_vertex, weight;
    int request_code;
    int i;

    scanf("%d %d", &count_of_vertexes, &count_of_requests);

    vertexes_dsus = (dsu_node**) calloc(count_of_vertexes, sizeof(dsu_node*));
    component_weights = (int*) calloc(count_of_vertexes, sizeof(int));

    for (i=0; i<count_of_vertexes; i++) vertexes_dsus[i] = make_set(i);

    for (i=0; i<count_of_requests; i++) {
        scanf("%d", &request_code);
        if (request_code == 1) {
            scanf("%d %d %d", &from_vertex, &to_vertex, &weight);
            insert_edge( vertexes_dsus, component_weights, from_vertex-1, to_vertex-1, weight);

        } else {
            scanf("%d", &component_vertex);
            printf("%d\n", component_weights[find_set(vertexes_dsus[component_vertex-1])->num]);
        }
    }


    for (i=0; i<count_of_vertexes; i++) free(vertexes_dsus[i]);
    free(vertexes_dsus);
    free(component_weights);



    return 0;
}
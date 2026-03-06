#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vertex {
    double x; 
    double y;
};


struct dsu_node {
	struct dsu_node* parent;
	int rank;
	int num; 
	
};

struct weight_and_vertexes {

    struct dsu_node* v1;
    struct dsu_node* v2;
    int visited;
    double weight;

};

struct dsu_node* make_set(int num) {
	struct dsu_node *tmp = (struct dsu_node*) malloc(sizeof(struct dsu_node));
	tmp->num = num;
	tmp->rank = 1;
	tmp->parent = tmp;
	
	return tmp;
}

struct dsu_node* find_set(struct dsu_node* p) {
	if (p->parent == p) {
		return p;
	}
	
	return p->parent = find_set(p->parent);

}

struct dsu_node* union_set(struct dsu_node* p1, struct dsu_node* p2) {
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

double calc_distance(struct vertex *point1, struct vertex *point2) {
    double x1, y1, x2, y2; 

    x1 = point1->x;
    y1 = point1->y;
    x2 = point2->x;
    y2 = point2->y;

    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}


 
int main(void) {
    struct vertex **vertexes;
    struct dsu_node **dsu_nodes;
    struct weight_and_vertexes **edges_from_to, *cur_smallest;
    
    int i, j, x, y;
    int count_of_vertexes, count_of_existing_pathes, total_count_of_ways, from_vertex, to_vertex, cur_count_of_good_edges=0, last_cell=0;
    
    double total_cost=0, cur_dist, max_dist;

    scanf("%d", &count_of_vertexes);

    for (i=1; i<count_of_vertexes+1; i++) total_count_of_ways += i;

    vertexes = (struct vertex**) malloc(sizeof(struct vertex*)*count_of_vertexes);
    dsu_nodes = (struct dsu_node**) malloc(sizeof(struct dsu_node*)*count_of_vertexes);
    edges_from_to = (struct weight_and_vertexes**) malloc(sizeof(struct weight_and_vertexes*)*total_count_of_ways);

    for (i=0; i<count_of_vertexes; i++) {
        scanf("%d %d", &x, &y);

        vertexes[i] = (struct vertex*) malloc(sizeof(struct vertex));
        vertexes[i]->x = x;
        vertexes[i]->y = y;
        
        dsu_nodes[i] = make_set(i);

    }

    scanf("%d", &count_of_existing_pathes);

    for (i=0; i<count_of_existing_pathes; i++) {
        scanf("%d %d", &from_vertex, &to_vertex);

        if (find_set(dsu_nodes[from_vertex-1]) != find_set(dsu_nodes[to_vertex-1])) {
            cur_count_of_good_edges++;
            union_set(dsu_nodes[from_vertex-1], dsu_nodes[to_vertex-1]);
        }

    }

    for (i=0; i<count_of_vertexes; i++) {
        for (j=i+1; j<count_of_vertexes; j++, last_cell++) {
            cur_dist = calc_distance(vertexes[i], vertexes[j]);
            edges_from_to[last_cell] = (struct weight_and_vertexes*) malloc(sizeof(struct weight_and_vertexes));
            edges_from_to[last_cell]->v1 = dsu_nodes[i];
            edges_from_to[last_cell]->v2 = dsu_nodes[j];
            edges_from_to[last_cell]->visited = 0;
            edges_from_to[last_cell]->weight = cur_dist;
            
            if (max_dist < cur_dist) {
                max_dist = cur_dist;
            }

        }
    }

    while (cur_count_of_good_edges < count_of_vertexes-1) {
        cur_dist = max_dist+1.0;
        for (i=0; i<last_cell; i++) {
            if ((edges_from_to[i]->visited == 0) && (edges_from_to[i]->weight < cur_dist) && (find_set((edges_from_to[i]->v1)) != find_set((edges_from_to[i]->v2)))) {
                cur_smallest = edges_from_to[i];
                cur_dist = cur_smallest->weight;
            }
        }

        cur_count_of_good_edges++;
        total_cost += cur_smallest->weight;
        cur_smallest->visited = 1;
        union_set((cur_smallest->v1), (cur_smallest->v2));
    }

    printf("%.5lf", total_cost);





    return 0;
}
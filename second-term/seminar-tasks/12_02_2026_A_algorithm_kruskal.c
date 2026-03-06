#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point_of_interest {
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

double calc_distance(struct point_of_interest *point1, struct point_of_interest *point2) {
    double x1, y1, x2, y2; 

    x1 = point1->x;
    y1 = point1->y;
    x2 = point2->x;
    y2 = point2->y;

    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

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

int main(void) {
    int width, height, num, count_of_ways=0, last_cell=0, i, j, mst_c_v=0;
    struct point_of_interest **p_o_is, *cur_point;
    struct weight_and_vertexes **edges_from_to, *cur_smallest;
    struct dsu_node **nodes;
    double cur_x, cur_y, cur_dist, mst_w=0.0, max_dist=0.0; 

    scanf("%d %d %d", &height, &width, &num);
    num++;

    for (i=1; i<num+1; i++) count_of_ways += i;
    p_o_is = (struct point_of_interest**) malloc(sizeof(struct point_of_interest*)*num);
    edges_from_to = (struct weight_and_vertexes**) malloc(sizeof(struct weight_and_vertexes*)*count_of_ways);
    nodes = (struct dsu_node**) malloc(sizeof(struct dsu_node*)*num);

    for (i=0; i<num-1; i++) { 
        scanf("%lf %lf", &cur_y, &cur_x);
        cur_point = (struct point_of_interest*) malloc(sizeof(struct point_of_interest*));
        cur_point->x = cur_x;
        cur_point->y = cur_y;

        p_o_is[i] = cur_point;
        nodes[i] = make_set(i);
    }

    cur_point = (struct point_of_interest*) malloc(sizeof(struct point_of_interest*));
    cur_point->x = width/2;
    cur_point->y = 0;

    p_o_is[i] = cur_point;
    nodes[i] = make_set(i);

    for (i=0; i<num; i++) {
        for (j=i+1; j<num; j++, last_cell++) {
            cur_dist = calc_distance(p_o_is[i], p_o_is[j]);
            edges_from_to[last_cell] = malloc(sizeof(struct weight_and_vertexes));
            edges_from_to[last_cell]->v1 = nodes[i];
            edges_from_to[last_cell]->v2 = nodes[j];
            edges_from_to[last_cell]->visited = 0;
            edges_from_to[last_cell]->weight = cur_dist;

            
            if (max_dist < cur_dist) {
                max_dist = cur_dist;
                cur_smallest = edges_from_to[last_cell];
            }

        }
    }

    
    
    while (mst_c_v < num-1) {
        cur_dist = max_dist+1.0;
        for (i=0; i<last_cell; i++) {
            if ((edges_from_to[i]->visited == 0) && (edges_from_to[i]->weight < cur_dist) && (find_set((edges_from_to[i]->v1)) != find_set((edges_from_to[i]->v2)))) {
                cur_smallest = edges_from_to[i];
                cur_dist = cur_smallest->weight;
            }
        }

        mst_c_v++;
        mst_w += cur_smallest->weight;
        cur_smallest->visited = 1;
        union_set((cur_smallest->v1), (cur_smallest->v2));
    }

    printf("%lf", mst_w);


    for (i=0; i<num; i++) { 
        free(p_o_is[i]);
        free(edges_from_to[i]);
        free(nodes[i]);
    }
    free(p_o_is);
    free(cur_point);
    free(edges_from_to);
    free(nodes);

    return 0;
}
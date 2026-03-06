#include <stdio.h>
#include <stdlib.h>

struct bridge {
    int coordinate_i;
    int coordinate_j;
    int direction;
};

struct dsu_node {
	struct dsu_node* parent;
	int rank;
	int num; 
	
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

void connect_two_nodes(struct dsu_node **nodes, int count_of_columns, int count_of_nodes, int from_i, int from_j, int to_i, int to_j) {
    int node_number_from = count_of_columns*from_i + from_j;
    int node_number_to = count_of_columns*to_i + to_j;
    if (node_number_to < count_of_nodes) union_set(nodes[node_number_from], nodes[node_number_to]);

}

void add_bridges(struct dsu_node **nodes, int count_of_columns, int count_of_nodes, int from_i, int from_j, int bridges_status) {
    switch (bridges_status) {
    case 1:
        connect_two_nodes(nodes, count_of_columns, count_of_nodes, from_i, from_j, from_i+1, from_j);
        break;

    case 2:
        connect_two_nodes(nodes, count_of_columns, count_of_nodes, from_i, from_j, from_i, from_j+1);
        break;

    case 3:
        connect_two_nodes(nodes, count_of_columns, count_of_nodes,from_i, from_j, from_i+1, from_j);
        connect_two_nodes(nodes, count_of_columns, count_of_nodes,from_i, from_j, from_i, from_j+1);
        break;
    
    default:
        break;
    }

}

int main(void) {
    struct dsu_node **nodes;
    struct bridge **new_bridges;

    int count_of_columns, count_of_rows;
    int total_count_of_new_bridges=0, total_cost_of_new_bridges=0;
    int current_node_bridges_status;
    int current_node_1_index, current_node_2_index;
    int i, j;

    scanf("%d %d", &count_of_rows, &count_of_columns);

    nodes = (struct dsu_node**) malloc(sizeof(struct dsu_node*)*count_of_columns*count_of_rows);
    new_bridges = (struct bridge**) calloc(((count_of_columns-1)*count_of_rows + (count_of_rows-1)*count_of_columns)*3, sizeof(struct bridge*));

    for (i=0; i<count_of_columns*count_of_rows; i++) nodes[i] = make_set(i);

    for (i=0; i<count_of_rows; i++) {
        for (j=0; j<count_of_columns; j++) {
            scanf("%d", &current_node_bridges_status);
            add_bridges(nodes, count_of_columns, count_of_columns*count_of_rows, i, j, current_node_bridges_status);
        }

    }

    for (i=0; i<count_of_rows-1; i++) {
        for (j=0; j<count_of_columns; j++) {
            current_node_1_index = count_of_columns*i + j;
            current_node_2_index = count_of_columns*(i+1) + j;
            if (current_node_2_index<count_of_columns*count_of_rows && find_set(nodes[current_node_1_index]) != find_set(nodes[current_node_2_index])) {
                union_set(nodes[current_node_1_index], nodes[current_node_2_index]);
                new_bridges[total_count_of_new_bridges] = (struct bridge*) malloc(sizeof(struct bridge));
                new_bridges[total_count_of_new_bridges]->direction = 1;
                new_bridges[total_count_of_new_bridges]->coordinate_i = i+1;
                new_bridges[total_count_of_new_bridges]->coordinate_j = j+1; 

                total_cost_of_new_bridges += 1;
                total_count_of_new_bridges++; 
            }
        }
    }

    for (i=0; i<count_of_rows; i++) {
        for (j=0; j<count_of_columns-1; j++) {
            current_node_1_index = count_of_columns*i + j;
            current_node_2_index = count_of_columns*i + j+1;
            if (current_node_2_index<count_of_columns*count_of_rows && find_set(nodes[current_node_1_index]) != find_set(nodes[current_node_2_index])) {
                union_set(nodes[current_node_1_index], nodes[current_node_2_index]);
                new_bridges[total_count_of_new_bridges] = (struct bridge*) malloc(sizeof(struct bridge));
                new_bridges[total_count_of_new_bridges]->direction = 2;
                new_bridges[total_count_of_new_bridges]->coordinate_i = i+1;
                new_bridges[total_count_of_new_bridges]->coordinate_j = j+1; 

                total_cost_of_new_bridges += 2;
                total_count_of_new_bridges++; 
            }
        }
    }

    printf("%d %d\n", total_count_of_new_bridges, total_cost_of_new_bridges);

    for (i=0; i<(count_of_columns-1)*count_of_rows + (count_of_rows-1)*count_of_columns && new_bridges[i]!=NULL; i++) {
        printf("%d %d %d\n", new_bridges[i]->coordinate_i, new_bridges[i]->coordinate_j, new_bridges[i]->direction);
    }

    for (i=0; i<count_of_columns*count_of_rows; i++) free(nodes[i]);
    for (i=0; i<(count_of_columns-1)*count_of_rows + (count_of_rows-1)*count_of_columns && new_bridges[i]!=NULL; i++) free(new_bridges[i]);
    free(nodes);
    free(new_bridges);


    


    return 0;
}
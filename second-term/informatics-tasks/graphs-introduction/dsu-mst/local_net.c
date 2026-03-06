#include <stdio.h>
#include <stdlib.h>

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

struct possible_way {
    struct dsu_node *from_computer;
    struct dsu_node *to_computer;
    int is_it_cheap_category;
    int length;
    int connection_number;
};

struct possible_cheap_way {
    int count_of_included_ways;
    struct possible_way **included_ways;
};

void merge(struct possible_way **all_available_connections, int left, int right, int middle) {
    int i, j, k = left;
    int left_size = middle - left + 1;
    int right_size = right - middle;

    struct possible_way **left_tmp_array, **right_tmp_array;

    left_tmp_array = (struct possible_way**) malloc(sizeof(struct possible_way*)*left_size);
    right_tmp_array = (struct possible_way**) malloc(sizeof(struct possible_way*)*right_size);

    for (i=0; i<left_size; i++) {
        left_tmp_array[i] = (struct possible_way*) malloc(sizeof(struct possible_way));

        left_tmp_array[i]->from_computer = all_available_connections[left+i]->from_computer;
        left_tmp_array[i]->to_computer = all_available_connections[left+i]->to_computer;
        left_tmp_array[i]->length = all_available_connections[left+i]->length;
        left_tmp_array[i]->connection_number = all_available_connections[left+i]->connection_number;

    }

    for (i=0; i<right_size; i++) {
        right_tmp_array[i] = (struct possible_way*) malloc(sizeof(struct possible_way));

        right_tmp_array[i]->from_computer = all_available_connections[middle+1+i]->from_computer;
        right_tmp_array[i]->to_computer = all_available_connections[middle+1+i]->to_computer;
        right_tmp_array[i]->length = all_available_connections[middle+1+i]->length;
        right_tmp_array[i]->connection_number = all_available_connections[middle+1+i]->connection_number;

    }

    i = j = 0;

    while (i < left_size && j < right_size) {
        if (left_tmp_array[i]->length <= right_tmp_array[j]->length) {
            all_available_connections[k]->from_computer = left_tmp_array[i]->from_computer;
            all_available_connections[k]->to_computer = left_tmp_array[i]->to_computer;
            all_available_connections[k]->length = left_tmp_array[i]->length;
            all_available_connections[k]->connection_number = left_tmp_array[i]->connection_number;

            i++;
        } else {
            all_available_connections[k]->from_computer = right_tmp_array[j]->from_computer;
            all_available_connections[k]->to_computer = right_tmp_array[j]->to_computer;
            all_available_connections[k]->length = right_tmp_array[j]->length;
            all_available_connections[k]->connection_number = right_tmp_array[j]->connection_number;
            
            j++;
        }

        k++;

    }

    while (i < left_size) {
        all_available_connections[k]->from_computer = left_tmp_array[i]->from_computer;
        all_available_connections[k]->to_computer = left_tmp_array[i]->to_computer;
        all_available_connections[k]->length = left_tmp_array[i]->length;
        all_available_connections[k]->connection_number = left_tmp_array[i]->connection_number;

        i++; 
        k++;

    }

    while (j < right_size) {
        all_available_connections[k]->from_computer = right_tmp_array[j]->from_computer;
        all_available_connections[k]->to_computer = right_tmp_array[j]->to_computer;
        all_available_connections[k]->length = right_tmp_array[j]->length;
        all_available_connections[k]->connection_number = right_tmp_array[j]->connection_number;

        j++;
        k++;
    }

    for(i=0; i<left_size; i++) free(left_tmp_array[i]);
    for(i=0; i<right_size; i++) free(right_tmp_array[i]);

    free(left_tmp_array);
    free(right_tmp_array);


}


void merge_sort(struct possible_way **all_available_connections, int left, int right) {
    int middle; 

    if (left < right) {
        middle = left + (right - left)/2;

        merge_sort(all_available_connections, left, middle);
        merge_sort(all_available_connections, middle+1, right);

        merge(all_available_connections, left, right, middle);
    }
}

void free_used_data(struct possible_way **all_available_connections, struct possible_cheap_way **possible_cheap_ways, struct possible_way **minimum_spanning_tree, struct dsu_node **nodes, int count_of_available_connections, int count_of_computers_in_net) {
    int i;

    for (i=0; i<count_of_available_connections; i++) free(all_available_connections[i]);
    for (i=0; i<count_of_computers_in_net; i++) free(nodes[i]);

    free(all_available_connections);
    free(possible_cheap_ways);
    free(minimum_spanning_tree);
    free(nodes);

}


int main(void) {
    struct possible_way **all_available_connections;
    struct possible_way **minimum_spanning_tree;
    struct possible_cheap_way **possible_cheap_ways;
    struct possible_cheap_way *highest_usage_of_cheap_wire = NULL;
    struct dsu_node **nodes;

    int count_of_computers_in_net, count_of_available_connections;
    int from_computer, to_computer, length, chosen_length;
    int flag_this_computer_already_used_in_this_sum=0, flag_found_computer_out_of_net=0;
    int p5, q5, p6, q6;
    int cool_wire_cant_cover;
    int count_of_ways_in_minimum_spannaing_tree=0;
    int cheap_wire_length, cool_wire_length, cheap_wire_price, cool_wire_price;
    int length_of_cheap_wire_we_gonna_use, total_wire_length_we_need=0, cheap_category;
    int i, j, l, k=0;

    scanf("%d %d", &count_of_computers_in_net, &count_of_available_connections);

    all_available_connections = (struct possible_way**) malloc(sizeof(struct possible_way*)*count_of_available_connections);
    minimum_spanning_tree = (struct possible_way**) malloc(sizeof(struct possible_way*)*(count_of_computers_in_net-1));
    nodes = (struct dsu_node**) malloc(sizeof(struct dsu_node*)*count_of_computers_in_net);

    for (i=0; i<count_of_computers_in_net; i++) nodes[i] = make_set(i);

    for (i=0; i<count_of_available_connections; i++) {
        scanf("%d %d %d", &from_computer, &to_computer, &length);

        all_available_connections[i] = (struct possible_way*) malloc(sizeof(struct possible_way));
        all_available_connections[i]->from_computer = nodes[from_computer-1];
        all_available_connections[i]->to_computer = nodes[to_computer-1];
        all_available_connections[i]->length = length;
        all_available_connections[i]->is_it_cheap_category = 0;
        all_available_connections[i]->connection_number = i+1;

    }

    scanf("%d %d %d %d", &p5, &q5, &p6, &q6);

    if (p5 < p6) {
        cheap_wire_price = p5;
        cheap_wire_length = q5;
        cool_wire_price = p6;
        cool_wire_length = q6; 
        cheap_category = 5;
    } else {
        cheap_wire_price = p6;
        cheap_wire_length = q6;
        cool_wire_price = p5;
        cool_wire_length = q5;
        cheap_category = 6;
    }

    possible_cheap_ways = (struct possible_cheap_way**) calloc(cheap_wire_length+1, sizeof(struct possible_cheap_way*));
    
    if (count_of_available_connections < count_of_computers_in_net-1) {
        printf("Impossible");
        free_used_data(all_available_connections, possible_cheap_ways, minimum_spanning_tree, nodes, count_of_available_connections, count_of_computers_in_net);
        return 0;
    }
    merge_sort(all_available_connections, 0, count_of_available_connections-1); // Worked at this point

    for (i=0; i < count_of_available_connections; i++) {
        if (find_set(all_available_connections[i]->from_computer) != find_set(all_available_connections[i]->to_computer)) {
            union_set(all_available_connections[i]->from_computer, all_available_connections[i]->to_computer);
            minimum_spanning_tree[k] = all_available_connections[i];
            total_wire_length_we_need += minimum_spanning_tree[k]->length;
            count_of_ways_in_minimum_spannaing_tree++;
            k++;
        }
    }

    for (i=0; i<count_of_computers_in_net; i++) {
        for (j=0; j<count_of_computers_in_net; j++) {
            flag_found_computer_out_of_net |= find_set(nodes[j]) != find_set(nodes[i]);
        }
    }

    cool_wire_cant_cover = total_wire_length_we_need - cool_wire_length;
    if (cool_wire_cant_cover < 0) cool_wire_cant_cover = 0;


    if ((total_wire_length_we_need > cool_wire_length+cheap_wire_length) || flag_found_computer_out_of_net || cool_wire_cant_cover > cheap_wire_length || count_of_ways_in_minimum_spannaing_tree != count_of_computers_in_net-1) {
        free_used_data(all_available_connections, possible_cheap_ways, minimum_spanning_tree, nodes, count_of_available_connections, count_of_computers_in_net);
        printf("Impossible");
        return 0;
    }
    possible_cheap_ways[0] = (struct possible_cheap_way*) malloc(sizeof(struct possible_cheap_way)); // We can get zero sum
    possible_cheap_ways[0]->count_of_included_ways = 0;
    possible_cheap_ways[0]->included_ways = NULL;

    for (i=0; i<count_of_computers_in_net-1; i++) {
        chosen_length = minimum_spanning_tree[i]->length;
        for (j=0; j<cheap_wire_length+1; j++) {
            if (possible_cheap_ways[j] != NULL && chosen_length+j <= cheap_wire_length && possible_cheap_ways[j+chosen_length]==NULL) {
                flag_this_computer_already_used_in_this_sum = 0;
                possible_cheap_ways[j+chosen_length] = (struct possible_cheap_way*) malloc(sizeof(struct possible_cheap_way));
                possible_cheap_ways[j+chosen_length]->count_of_included_ways = possible_cheap_ways[j]->count_of_included_ways + 1;
                possible_cheap_ways[j+chosen_length]->included_ways = (struct possible_way**) malloc(sizeof(struct possible_cheap_way*)*(possible_cheap_ways[j+chosen_length]->count_of_included_ways));

                (possible_cheap_ways[j+chosen_length]->included_ways)[0] = minimum_spanning_tree[i];

                if (possible_cheap_ways[j]->included_ways != NULL) {
                    for (l=1; l<possible_cheap_ways[j]->count_of_included_ways+1 && !flag_this_computer_already_used_in_this_sum; l++) {
                        if ((possible_cheap_ways[j]->included_ways)[l-1] != minimum_spanning_tree[i]) {
                            (possible_cheap_ways[j+chosen_length]->included_ways)[l] = (possible_cheap_ways[j]->included_ways)[l-1];
                        } else {
                            flag_this_computer_already_used_in_this_sum = 1;
                        }
                    }
                }

                if (flag_this_computer_already_used_in_this_sum) {
                    free(possible_cheap_ways[j+chosen_length]->included_ways);
                    free(possible_cheap_ways[j+chosen_length]);
                    possible_cheap_ways[j+chosen_length] = NULL;
                }

            }
        }
    }

    for (i=cheap_wire_length; i>=0 && highest_usage_of_cheap_wire==NULL; i--) {
        if (possible_cheap_ways[i] != NULL && total_wire_length_we_need-i <= cool_wire_length) {
            highest_usage_of_cheap_wire = possible_cheap_ways[i];
            length_of_cheap_wire_we_gonna_use = i;
            for (j=0; j<highest_usage_of_cheap_wire->count_of_included_ways; j++) {
                (highest_usage_of_cheap_wire->included_ways)[j]->is_it_cheap_category = 1;
            }
        }
    }

    if (highest_usage_of_cheap_wire == NULL) {
        free_used_data(all_available_connections, possible_cheap_ways, minimum_spanning_tree, nodes, count_of_available_connections, count_of_computers_in_net);
        printf("Impossible");
        return 0;
    }

    printf("%d\n", (length_of_cheap_wire_we_gonna_use*cheap_wire_price)+(total_wire_length_we_need-length_of_cheap_wire_we_gonna_use)*cool_wire_price);

    for (i=0; i<count_of_computers_in_net-1; i++) {
        printf("%d ", minimum_spanning_tree[i]->connection_number);
        if (minimum_spanning_tree[i]->is_it_cheap_category) {
            printf("%d\n", cheap_category);
        } else {
            printf("%d\n", 11-cheap_category);
        }
    }

    for (i=0; i<cheap_wire_length+1; i++) {
        if (possible_cheap_ways[i] != NULL) {
            if (possible_cheap_ways[i]->included_ways != NULL) free(possible_cheap_ways[i]->included_ways);

            free(possible_cheap_ways[i]);
        }

    }
    free_used_data(all_available_connections, possible_cheap_ways, minimum_spanning_tree, nodes, count_of_available_connections, count_of_computers_in_net);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define M 7

typedef int (*function_from_int_to_int)(int);

typedef struct hash_table_element {
    int key;
    double value;
    int deleted;

} hash_table_element;

typedef struct hash_table {

    int size;
    hash_table_element **table;
    function_from_int_to_int using_hash_function;

} hash_table;

int hash_function(int key) {
    return key%M;
}

int insert_to_hash(hash_table *hash, int key, double value) {
    
    int hash_result, base_hash_result;
    int error_code = 0;

    hash_table_element **tmp;

    base_hash_result = hash_result = hash->using_hash_function(key);

    while ((hash->table[hash_result] != NULL && (hash->table[hash_result] != NULL && hash->table[hash_result]->deleted != 1)) && !error_code) {
        hash_result += base_hash_result;

        if (hash_result > hash->size) {
            tmp = hash->table;
            hash->table = realloc(hash->table, (hash->size)*2);

            if (hash->table == NULL) {
                error_code = 1;
                hash->table = tmp;
            } else {
                if (tmp != hash->table) free(tmp);
                hash->size = (hash->size)*2;
            }

        }
    }

    if (!error_code) {
        if (hash->table[hash_result] == NULL) {
            hash->table[hash_result] = (hash_table_element*) malloc(sizeof(hash_table_element));
        } 
        
        hash->table[hash_result]->key = key;
        hash->table[hash_result]->value = value;
        hash->table[hash_result]->deleted = 0;
    }

    return error_code;

}

int find_by_key(hash_table *hash, int key, double *value) {
    int error_code = 0;
    int hash_result, base_hash_result;

    base_hash_result = hash_result = hash_function(key);

    while ((hash_result < hash->size) && ((hash->table[hash_result] != NULL) && hash->table[hash_result]->key != key)) {
        hash_result += base_hash_result;
    }

    if ((hash_result < hash->size) && ((hash->table[hash_result] != NULL) && hash->table[hash_result]->key == key && hash->table[hash_result]->deleted == 0)) {
        (*value) = hash->table[hash_result]->value;
    } else {
        error_code = 3;
    }

    return error_code;
    
}

int del_by_key(hash_table *hash, int key) {
    
    int error_code = 0;
    int hash_result, base_hash_result;

    base_hash_result = hash_result = hash_function(key);

    while ((hash_result < hash->size) && (hash->table[hash_result]->key != key)) {
        hash_result += base_hash_result;
    }

    if ((hash_result < hash->size) && hash->table[hash_result]->key == key && hash->table[hash_result]->deleted == 0) {
        hash->table[hash_result]->deleted = 1;
    } else {
        error_code = 3;
    }

    return error_code;

}

int clear_the_table(hash_table *hash) {
    int i;

    for (i=0; i<hash->size; i++) {
        free(hash->table[i]);
        hash->table[i] = NULL;
    }

    return 0;
}


int main(void) {

    hash_table *hash;

    int key;
    int command = 1;

    double value, tmp_value;

    hash = (hash_table*) malloc(sizeof(hash_table));
    hash->table = (hash_table_element**) calloc(30, sizeof(hash_table_element*));
    hash->using_hash_function = hash_function;
    hash->size = 30;

    while (command) {
        scanf("%d", &command);

        switch (command) {
        case 1:
            scanf("%d %lf", &key, &value);
            if (find_by_key(hash, key, &tmp_value) == 0) {
                printf("2\n");
            } else {
                printf("%d\n", insert_to_hash(hash, key, value));
            }
            
            break;

        case 2:
            scanf("%d", &key);
            if (find_by_key(hash, key, &value) == 0) {
                printf("%lf\n", value);
            } else {
                printf("Not found\n");
            }
            break;

        case 3:
            scanf("%d", &key);
            printf("%d\n", del_by_key(hash, key));
            break;

        case 4:
            printf("%d\n", clear_the_table(hash));
            break;
        
        default:
            break;
        } 
    }

    clear_the_table(hash);
    free(hash);


    return 0;
}
#include <stdio.h>

struct match {
    long long command1;
    long long command2;
};

void push_back(long long *deque, long long *front_index, long long *end_index, long long value) {
    if ((*end_index) + 1 < 600003) {
        (*end_index) = (*end_index) + 1;
        deque[(*end_index)] = value;
    }
}

void push_front(long long *deque, long long *front_index, long long *end_index, long long value) {
    if ((*front_index) - 1 >= 0) {
        deque[(*front_index)] = value;
        (*front_index) = (*front_index) - 1;
    }
}

void pop_front(long long *deque, long long *front_index, long long *end_index) {
    (*front_index) = (*front_index) + 1;

}

void pop_back(long long *deque, long long *front_index, long long *end_index) {
    (*end_index) = (*end_index) - 1;
}

long long view_back(long long *deque, long long *front_index, long long *end_index) {
    return deque[(*end_index)];
}


long long view_front(long long *deque, long long *front_index, long long *end_index) {
    return deque[(*front_index)+1];
}

long long main(void) {
    long long n, val, i, k, max_strength=0, times_to_strongest_turn=0;
    long long deque[600003];
    long long front_index=3, end_index=3;

    struct match m_array[600003];

    scanf("%lld", &n);

    for (i=0; i<n; i++) {
        scanf("%lld", &val);
        push_back(deque, &front_index, &end_index, val);
        max_strength = (val>max_strength)? val: max_strength;
    }
    
    for (i=0; i<n && view_front(deque, &front_index, &end_index)!=max_strength; i++) {
        m_array[i].command1 = view_front(deque, &front_index, &end_index);
        pop_front(deque, &front_index, &end_index);
        m_array[i].command2 = view_front(deque, &front_index, &end_index);
        pop_front(deque, &front_index, &end_index);
        times_to_strongest_turn++;
        if (m_array[i].command1 > m_array[i].command2) {
            push_front(deque, &front_index, &end_index, m_array[i].command1);
            push_back(deque, &front_index, &end_index, m_array[i].command2);
        } else {
            push_front(deque, &front_index, &end_index, m_array[i].command2);
            push_back(deque, &front_index, &end_index, m_array[i].command1);
        }
        

    }

    pop_front(deque, &front_index, &end_index);

    scanf("%lld", &k);

    for (i=0; i<k; i++) {
        scanf("%lld", &val);
        if (val <= times_to_strongest_turn) {
            printf("%lld %lld\n", m_array[val-1].command1, m_array[val-1].command2);
        } else {
            printf("%lld %lld\n", max_strength, deque[front_index+1 + (val - times_to_strongest_turn - 1)%(n-1)]);
        }
    }


    

    return 0;
}
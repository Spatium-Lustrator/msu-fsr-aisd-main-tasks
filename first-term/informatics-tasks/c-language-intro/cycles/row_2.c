#include <stdio.h>

int main() {
    int left_range, right_range;

    scanf("%d", &left_range);
    scanf("%d", &right_range);

    for (int i=left_range; i!=right_range + (left_range<right_range? 1: -1); left_range<right_range? i++: i--) {
        printf("%d ", i);
    }

    return 0;
}
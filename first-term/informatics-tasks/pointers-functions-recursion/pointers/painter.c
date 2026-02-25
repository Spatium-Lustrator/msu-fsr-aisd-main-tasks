#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int w=0, h=0, n=0, i=0, curr_x=0, curr_y=0, painted =0;
    int *wp=&w, *hp=&h, *np=&n, *ip=&i, *curr_xp=&curr_x, *curr_yp=&curr_y, *paintedp=&painted;


    scanf("%d", wp);
    scanf("%d", hp);
    scanf("%d", np);

    if ((*np < *hp) && (*np < *wp)) {
        printf("No");
    } else {
        char** canvas = (char**)malloc((*hp)*sizeof(char*));

        for (*ip = 0; *ip<*hp; *ip += 1) {
            *(canvas + *ip) = (char*)malloc((*wp)*sizeof(char));
        }

        for (*ip = 0; *ip<*np; *ip += 1) {
            scanf("%d %d", curr_xp, curr_yp);

            if (((1<=(*curr_xp)) && ((*curr_xp)<=(*wp))) && ((1<=(*curr_yp)) && ((*curr_yp)<=(*hp)))) {
                if (*(*(canvas + *curr_yp - 1) + *curr_xp - 1) != '1') {
                    *(*(canvas + *curr_yp - 1) + *curr_xp - 1) = '1';
                    *paintedp += 1;
                }

            }

            if (((1<=(*curr_xp)-1) && ((*curr_xp)-1<=(*wp))) && ((1<=(*curr_yp)) && ((*curr_yp)<=(*hp)))) {
                if (*(*(canvas + *curr_yp - 1) + *curr_xp - 2) != '1') {
                    *(*(canvas + *curr_yp - 1) + *curr_xp - 2) = '1';
                    *paintedp += 1;
                }
            }

            if (((1<=(*curr_xp)) && ((*curr_xp)<=(*wp))) && ((1<=(*curr_yp)-1) && ((*curr_yp)-1<=(*hp)))) {
                if (*(*(canvas + *curr_yp - 2) + *curr_xp - 1) != '1') {
                    *(*(canvas + *curr_yp - 2) + *curr_xp - 1) = '1';
                    *paintedp += 1;
                }
            }

            if (((1<=(*curr_xp)+1) && ((*curr_xp)+1<=(*wp))) && ((1<=(*curr_yp)) && ((*curr_yp)<=(*hp)))) {
                if (*(*(canvas + *curr_yp - 1) + *curr_xp) != '1') {
                    *(*(canvas + *curr_yp - 1) + *curr_xp) = '1';
                    *paintedp += 1;
                }
            }

            if (((1<=(*curr_xp)) && ((*curr_xp)<=(*wp))) && ((1<=(*curr_yp)+1) && ((*curr_yp)+1<=(*hp)))) {
                if (*(*(canvas + *curr_yp) + *curr_xp - 1) != '1') {
                    *(*(canvas + *curr_yp) + *curr_xp - 1) = '1';
                    *paintedp += 1;
                }
            }
        }

        if ((*paintedp) < (*hp)*(*wp)) {
            printf("No");
        } else {
            printf("Yes");
        }

        
        for (*ip=0; (*ip)<(*hp); (*ip) += 1) {
            free(*(canvas + *ip));
        } 

        free(canvas);

    }

    

    return 0;
}
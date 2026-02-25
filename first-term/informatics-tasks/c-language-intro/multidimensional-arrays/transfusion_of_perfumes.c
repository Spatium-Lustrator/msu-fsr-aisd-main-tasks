#include <stdio.h>

int main() {
    int n=0, m=0, l=0, k=0, s=0, t=0, ak=0, i=0, j=0;
    double total_volume = 0.0;
    double coco_chanel_data[100][100];

    scanf("%d %d", &n, &m);

    for(i=0; i<n; i++){
        for(j=0; j<m ;j++) {
            coco_chanel_data[i][j]=0.0;
        }
    }

    for(i=0; i<n; i++){
        scanf("%d", &l);
        scanf("%lf", &coco_chanel_data[i][l-1]);
    }


    scanf("%d", &k);
    for (i=0; i<k ; i++){
        scanf("%d %d %d", &s, &t, &ak);
        for (j=0; j<m; j++){
            coco_chanel_data[t-1][j] += coco_chanel_data[s-1][j]*(ak*0.01);
            coco_chanel_data[s-1][j] *= (100-ak)*0.01;
        }
    }

    for (i=0; i<m; i++) {
        total_volume+=coco_chanel_data[0][i];
    }

    for (i=0; i<m; i++){
        printf("%lf ", coco_chanel_data[0][i]/total_volume*100);
        
    }


    return 0;
}
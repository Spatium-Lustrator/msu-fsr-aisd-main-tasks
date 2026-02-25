#include <stdio.h>

int main() {
    int x=0,y=0,z=0,s=0, g=0, max=0, min=0;
    scanf("%d %d %d",&x,&y,&z);
    s=x+y+z; 

    if(s%2==1) {
        printf("NO");
    } else{
        g=s/2; 
        max = x;
        if (y>max) {
            max = y;
        }

        if (z>max) {
            max = z;
        }

        min = x;

        if (y<min) {
            min = y;
        }

        if (z<min) {
            min = z;
        }

        if (max>g || min<g/2) {
            printf("NO");
        } else {
            printf("YES");
        }



    }
    
}
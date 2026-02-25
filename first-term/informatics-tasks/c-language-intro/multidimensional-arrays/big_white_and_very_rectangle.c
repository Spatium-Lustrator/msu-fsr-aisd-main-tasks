#include <stdio.h>

int main(){
    int n=0, m=0, result=0, l=0, current=0, i=0, j=0, x=0, tua=0, w=0, cages=0;
    int h[5000], st[5000];

    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++){

        for(j=0;j<m;j++){
            scanf("%d",&x);
            if(x==0) {
                h[j]++;
            }  else {
                h[j]=0;
            }
        }


        int top=-1;
        for(j=0;j<=m;j++){

            if (j<m) {
                current = h[j];
            } else {
                current = 0;
            }

            while(top>=0 && h[st[top]]>current){
                tua=h[st[top--]];
                if (top>=0) {
                    l = st[top]+1;
                } else {
                    l = 0;
                }
                w = j - l;
                cages = tua*w;
                if(cages>result) {
                    result=cages;
                }
            }
            
            st[++top]=j;
        }
    }
    printf("%d",result);
    return 0;
}
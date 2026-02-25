#include <stdio.h>

int rook(char desk[8][9], int x, int y) {

    int cx = x, cy = y, count_of_bitten=0;

    for (cx = x+1, cy=y; cx<8 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cx++) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    for (cx = x-1, cy=y; cx>-1 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cx--) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    for (cy = y+1, cx=x; cy<8 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cy++) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    for (cy = y-1, cx=x; cy>-1 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cy--) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }
    return count_of_bitten;

}

int bishop(char desk[8][9], int x, int y) {

    int cx = x, cy = y, count_of_bitten=0;

    for (cx = x-1, cy=y+1; cx>-1 && cy<8 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cx--, cy++) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    for (cx = x+1, cy=y+1; cx<8 && cy<8 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cx++, cy++) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    for (cy = y-1, cx=x+1; cy>-1 && cx<8 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cy--, cx++) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    for (cy = y-1, cx=x-1; cy>-1 && cx>-1 && desk[cx][cy]!='B' && desk[cx][cy]!='R'; cy--, cx--) {
        if (desk[cx][cy] == '*'){
            desk[cx][cy] = 'x';
            count_of_bitten++;
        }
    }

    return count_of_bitten;



}
int main() {
    int i=0, j=0, count_of_bitten =0, cofnot=0;
    char desk[8][9];

    for (i=0; i<8; i++) {
        for (j=0; j<9; j++) {
            scanf("%c", &desk[i][j]);
        }
    }

    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            if (desk[i][j] == 'R') {
                count_of_bitten += rook(desk, i, j) + 1;
            } else if (desk[i][j] == 'B') {
                count_of_bitten += bishop(desk, i, j) + 1;
            }
        }
    }


    for (i=0; i<8; i++) {
        for (j=0; j<8; j++) {
            if (desk[i][j]=='*') {
                cofnot++;
            }
        }
    }
    

    

    printf("%d", cofnot);



    return 0;
}
#include <stdio.h>

int get_string_length(char *s) {
    int length=0;

    while (*s) {
        s++;
        length++;
    }
    return length;
}

void from_string_to_ratios_array(char* string, int polynom[]) {
    int i=0, length=0, sign=1, ratio=0, degree=0, was_there_any_num_for_ratio_flag=0;

    length = get_string_length(string);
    
    while (i<length) {

        if (string[i]=='+') {

            sign=1;
            i++;

        } else if (string[i]=='-') {

            sign=-1;
            i++;
        }
        
        ratio=was_there_any_num_for_ratio_flag=0;
        
        while ((i<length) && (string[i]>='0') && (string[i]<='9')) {
            ratio=ratio*10+(string[i]-'0');
            was_there_any_num_for_ratio_flag=1;
            i++;
        }
        
        if ((was_there_any_num_for_ratio_flag==0) && (i<length) && (string[i]=='x')) {
            ratio=1;
        }
        
        degree=0;

        if ((i<length) && (string[i]=='x')) {

            i++; 

            if ((i<length) && (string[i]=='^')) {

                i++; 

                while ((i<length) && (string[i]>= '0') && (string[i]<='9')) {
                    degree=degree*10+(string[i]-'0');
                    i++;
                }

            } else {
                degree=1;
            } 

        } else {
            degree=0;
        } 
        
        polynom[degree]=sign*ratio;
    }
}

void multiply_polynoms(int first_polynom_ratios[], int second_polynom_ratios[], int result_polynom_ratios[]) {

    int i=0, j=0;

    for (i=0; i<11; i++) {
        for (j=0; j<11; j++) {
            result_polynom_ratios[i+j] += first_polynom_ratios[i]*second_polynom_ratios[j];
        }
    
    }
}

void show_the_polynom(int polynom[]) {
    int first=1, i=100; 
    
    for (i=100; i>=0; i--) {

        if (polynom[i] != 0) {

            if (first==0) {
                if (polynom[i]>0) printf("+");
            }
            
            if (i==0) {
                printf("%d", polynom[i]);
            } else if (polynom[i]==1) {

                if (i==1) {
                    printf("x");
                } else {
                    printf("x^%d", i);
                }

            } else if (polynom[i]==-1) {

                if (i==1) {
                    printf("-x");
                } else {
                    printf("-x^%d", i);
                }

            } else {

                if (i==1) {
                    printf("%dx", polynom[i]);
                } else {
                    printf("%dx^%d", polynom[i], i);
                }
            }

            first=0;
        }
    }

    if (first==1) {
        printf("0");
    }
}


int main(void) {
    char first_polynom_string[1000], second_polynom_string[1000];
    int first_polynom_ratios[11]={0}, second_polynom_ratios[11]={0}, result_polynom_ratios[101]={0}; 
    
    scanf("%s %s", first_polynom_string, second_polynom_string);
    
    from_string_to_ratios_array(first_polynom_string, first_polynom_ratios);
    from_string_to_ratios_array(second_polynom_string, second_polynom_ratios);

    multiply_polynoms(first_polynom_ratios, second_polynom_ratios, result_polynom_ratios);
    
    show_the_polynom(result_polynom_ratios);
    
    return 0;
}
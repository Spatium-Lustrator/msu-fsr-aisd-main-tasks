#include <stdio.h>
#include <string.h>


int main(void) {
    char start_string[201], current_command;
    int x,y,position_of_returning,flag_if_robot_at_start_position,i,j,start_string_symbol_index,saved_substring_symbol_index;
    int count_of_commands = 0;

    while (scanf("%c", &current_command) == 1 && current_command != '\n') {
        if (current_command == 'E' || current_command == 'W' || current_command == 'N' || current_command == 'S') {
            start_string[count_of_commands] = current_command;
            count_of_commands++;
        }
    }

    start_string[count_of_commands] = '\0';

    for (i=0; i+1<count_of_commands; i++) {

        if (start_string[i] == start_string[i+1]) {
            x=0;
            y=0;
            position_of_returning=-1;
            flag_if_robot_at_start_position=0;

            for (j=i+1; j<count_of_commands && !flag_if_robot_at_start_position; j++) {

                switch (start_string[j]) {
                    case 'N':
                        y++;
                        break;

                    case 'S':
                        y--;
                        break;

                    case 'E':
                        x++;
                        break;

                    case 'W':
                        x--;
                        break;
                
                    default:
                        break;
                }

                if (x == 0 && y == 0) {
                    position_of_returning = j;
                    flag_if_robot_at_start_position = 1;
                }
            }

            char saved_substring[200];

            for (j=i+1; j<=position_of_returning; j++) {
                saved_substring[j] = start_string[j];
            }

            for (start_string_symbol_index=i+1, saved_substring_symbol_index=position_of_returning; start_string_symbol_index<=position_of_returning; start_string_symbol_index++, saved_substring_symbol_index--) {

                switch (saved_substring[saved_substring_symbol_index]) {
                    case 'N':
                        start_string[start_string_symbol_index] = 'S';
                        break;
                        
                    case 'S':
                        start_string[start_string_symbol_index] = 'N';
                        break;

                    case 'E':
                        start_string[start_string_symbol_index] = 'W';
                        break;


                    case 'W':
                        start_string[start_string_symbol_index] = 'E';
                        break;
                    
                    default:
                        break;
                }
            
            }
        }
    }

    printf("%s", start_string);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct section {
    
    double start_x;
    double start_y;
    double end_x;
    double end_y;

} section;


int main(void) {

    double current_section_start_x, current_section_start_y, current_section_end_x, current_section_end_y;
    int current_index_section;
    int count_of_sections, i;

    section **sections;

    scanf("%d", &count_of_sections);

    sections = (section**) malloc(sizeof(section*)*count_of_sections);
    
    for (i=0; i<count_of_sections; i++) {
        scanf("%d %lf %lf %lf %lf", &current_index_section, &current_section_start_x, &current_section_start_y, &current_section_end_x, &current_section_end_y);

        sections[current_index_section-1] = (section*) malloc(sizeof(section));

        sections[current_index_section-1]->start_x = current_section_start_x;
        sections[current_index_section-1]->start_y = current_section_start_y;
        sections[current_index_section-1]->end_x = current_section_end_x;
        sections[current_index_section-1]->end_y = current_section_end_y;
    }

    return 0;
}
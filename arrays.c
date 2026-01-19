#ifndef CARS_H
#define CARS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 5

typedef struct Car {
    char brand[20];        
    char manufacturer[30]; 
    char type[20];         
    int year;              
    int reg_year;          
} car_t;

void fill_array(car_t* c, int size);
void print_array(car_t* c, int size);
void print_one(car_t c);
car_t* search_material(car_t* c, int size, char* brand);
int compare(const void* a, const void* b);
int load_file(char* filename, car_t* c, int* size);
int save_file(char* filename, car_t* c, int size);
void edit_one(car_t* c, int index);

#endif

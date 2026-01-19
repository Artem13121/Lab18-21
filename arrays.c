#include "cars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BRAND_COUNT 10
#define MANUFACTURER_COUNT 10
#define TYPE_COUNT 8

const char* brands[] = { 
    "Ford", "Toyota", "BMW", "Mercedes", "Volkswagen", 
    "Audi", "Honda", "Hyundai", "Kia", "Chevrolet" 
};

const char* manufacturers[] = { 
    "USA", "Japan", "Germany", "South Korea", "France", 
    "Italy", "UK", "China", "Russia", "Sweden" 
};

const char* types[] = { 
    "Седан", "Внедорожник", "Хэтчбек", "Универсал", 
    "Купе", "Минивен", "Кабриолет", "Пикап" 
};

void fill_array(car_t* c, int size) {
    for (int i = 0; i < size; i++) {
        strcpy(c[i].brand, brands[rand() % BRAND_COUNT]);
        strcpy(c[i].manufacturer, manufacturers[rand() % MANUFACTURER_COUNT]);
        strcpy(c[i].type, types[rand() % TYPE_COUNT]);
        c[i].year = 1990 + rand() % 34;
        c[i].reg_year = c[i].year + rand() % 10;
        if (c[i].reg_year > 2023) c[i].reg_year = 2023;
    }
}

void print_array(car_t* c, int size) {
    printf("\n=== СПИСОК АВТОМОБИЛЕЙ ===\n");
    printf("Индекс Марка      Производитель Тип          Год_вып Год_рег\n");
    
    for (int i = 0; i < size; i++) {
        printf("%6d %-10s %-13s %-12s %7d %7d\n",
            i, c[i].brand, c[i].manufacturer, c[i].type, c[i].year, c[i].reg_year);
    }
    
    printf("\n=== FORD, ЗАРЕГИСТРИРОВАННЫЕ ДО 2000 ГОДА ===\n");
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        if (strcmp(c[i].brand, "Ford") == 0 && c[i].reg_year < 2000) {
            count++;
            printf("%d. %s (%s) - %s, выпуск: %d, регистрация: %d\n",
                count, c[i].brand, c[i].manufacturer, c[i].type, 
                c[i].year, c[i].reg_year);
        }
    }
    
    printf("Всего: %d автомобилей Ford зарегистрированных до 2000 года\n", count);
}

void print_one(car_t c) {
    printf("Марка автомобиля: %s\n", c.brand);
    printf("Производитель: %s\n", c.manufacturer);
    printf("Тип: %s\n", c.type);
    printf("Год выпуска: %d\n", c.year);
    printf("Год регистрации: %d\n", c.reg_year);
}

car_t* search_material(car_t* c, int size, char* brand) {
    for (int i = 0; i < size; i++) {
        if (strcmp(c[i].brand, brand) == 0) {
            return &c[i];
        }
    }
    return NULL;
}

int compare(const void* a, const void* b) {
    const car_t* ca = (const car_t*)a;
    const car_t* cb = (const car_t*)b;
    
    if (ca->year < cb->year) return -1;
    if (ca->year > cb->year) return 1;
    return 0;
}

int load_file(char* filename, car_t* c, int* size) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    
    *size = 0;
    
    while (*size < SIZE &&
        fscanf(f, "%s %s %s %d %d",
            c[*size].brand, c[*size].manufacturer, c[*size].type,
            &c[*size].year, &c[*size].reg_year) == 5) {
        (*size)++;
    }
    
    fclose(f);
    return 1;
}

int save_file(char* filename, car_t* c, int size) {
    FILE* f = fopen(filename, "w");
    if (!f) return 0;
    
    for (int i = 0; i < size; i++) {
        fprintf(f, "%s %s %s %d %d\n",
            c[i].brand, c[i].manufacturer, c[i].type, 
            c[i].year, c[i].reg_year);
    }
    
    fclose(f);
    return 1;
}

void edit_one(car_t* c, int index) {
    printf("Новые данные для автомобиля:\n");
    printf("Марка автомобиля: ");
    scanf("%s", c[index].brand);
    printf("Производитель: ");
    scanf("%s", c[index].manufacturer);
    printf("Тип: ");
    scanf("%s", c[index].type);
    printf("Год выпуска: ");
    scanf("%d", &c[index].year);
    printf("Год регистрации: ");
    scanf("%d", &c[index].reg_year);
}

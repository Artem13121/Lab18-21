```
#define _CRT_SECURE_NO_WARNINGS
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

int main() {
    car_t cars[SIZE];
    int current_size = SIZE;
    int loaded = 0;
    int choice;

    srand(time(NULL));

    do {
        printf("\n1. Загрузить\n2. Заполнить\n3. Показать\n4. Изменить\n5. Найти\n6. Сортировать\n7. Сохранить\n0. Выход\nВыбор: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            char name[100];
            printf("Имя файла: ");
            scanf("%s", name);
            if (load_file(name, cars, &current_size)) {
                loaded = 1;
                printf("Загружено %d\n", current_size);
            }
            else printf("Ошибка\n");
            break;
        }
        case 2: {
            fill_array(cars, SIZE);
            loaded = 1;
            printf("Заполнено\n");
            break;
        }
        case 3: {
            if (loaded) print_array(cars, current_size);
            else printf("Сначала загрузите\n");
            break;
        }
        case 4: {
            if (loaded) {
                int idx;
                printf("Индекс: ");
                scanf("%d", &idx);
                if (idx >= 0 && idx < current_size) edit_one(cars, idx);
                else printf("Неверно\n");
            }
            else printf("Сначала загрузите\n");
            break;
        }
        case 5: {
            if (loaded) {
                char brand[20];
                printf("Марка автомобиля: ");
                scanf("%s", brand);
                car_t* found = search_material(cars, current_size, brand);
                if (found) {
                    printf("\nНайден автомобиль:\n");
                    print_one(*found);
                }
                else printf("Не найдено\n");
            }
            else printf("Сначала загрузите\n");
            break;
        }
        case 6: {
            if (loaded) {
                qsort(cars, current_size, sizeof(car_t), compare);
                printf("Отсортировано\n");
            }
            else printf("Сначала загрузите\n");
            break;
        }
        case 7: {
            if (loaded) {
                char name[100];
                printf("Имя файла: ");
                scanf("%s", name);
                if (save_file(name, cars, current_size)) printf("Сохранено\n");
                else printf("Ошибка\n");
            }
            else printf("Сначала загрузите\n");
            break;
        }
        case 0: printf("Выход\n"); break;
        default: printf("Неверно\n");
        }
    } while (choice != 0);

    return 0;
}
void fill_array(car_t* c, int size) {
    char* brands[] = { "Ford", "Toyota", "BMW", "Mercedes", "Volkswagen", "Audi", "Honda", "Hyundai", "Kia", "Chevrolet" };
    char* manufacturers[] = { "USA", "Japan", "Germany", "South Korea", "France", "Italy", "UK", "China", "Russia", "Sweden" };
    char* types[] = { "Седан", "Внедорожник", "Хэтчбек", "Универсал", "Купе", "Минивен", "Кабриолет", "Пикап" };

    for (int i = 0; i < size; i++) {
        strcpy(c[i].manufacturer, manufacturers[rand() % 10]);
        strcpy(c[i].type, types[rand() % 8]);
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
            i,
            c[i].brand,
            c[i].manufacturer,
            c[i].type,
            c[i].year,
            c[i].reg_year);
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
        if (strcmp(c[i].brand, brand) == 0) return &c[i];
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
            c[*size].brand,
            c[*size].manufacturer,
            c[*size].type,
            &c[*size].year,
            &c[*size].reg_year) == 5) {
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
            c[i].brand,
            c[i].manufacturer,
            c[i].type,
            c[i].year,
            c[i].reg_year);
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
```

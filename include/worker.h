#ifndef WORKER_H
#define WORKER_H

// Структура для хранения данных о рабочем
typedef struct {
    char surname[50];
    char name[50];
    char patronymic[50];
    
    // Адрес
    char postal_code[20];
    char country[50];
    char region[50];
    char district[50];
    char city[50];
    char street[50];
    char house[20];
    char apartment[20];
    
    // Другие данные
    char nationality[50];
    int birth_year;
    int birth_month;
    int birth_day;
    int workshop_number;
    int employee_id;
    char education[50];
    int start_year;
} Worker;

// Прототипы функций
void createInputFile(const char *filename);
void viewFile(const char *filename);
void processAndSaveResults(const char *inputFile, const char *outputFile);
void parseWorkerFromString(char *buffer, Worker *worker);
void printWorkerToFile(FILE *file, Worker *worker);

#endif

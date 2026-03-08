#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/worker.h"

void createInputFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка создания файла %s!\n", filename);
        return;
    }

    fprintf(file, "Иванов;Иван;Иванович;123456;Россия;Московская;Раменский;Москва;Ленина;10;25;Русский;1985;5;15;3;1001;Высшее;2020\n");
    fprintf(file, "Петров;Петр;Петрович;654321;Россия;Ленинградская;Всеволожский;СПб;Невский;20;5;Русский;1990;3;10;2;1002;Среднее;2019\n");
    fprintf(file, "Сидоров;Сидор;Сидорович;111222;Россия;Новосибирская;Новосибирский;Новосибирск;Гагарина;15;7;Русский;1988;8;22;1;1003;Высшее;2020\n");
    fprintf(file, "Козлов;Антон;Павлович;333444;Россия;Свердловская;Октябрьский;Екатеринбург;Мира;5;12;Русский;1992;11;3;3;1004;Среднее;2021\n");
    fprintf(file, "Смирнова;Анна;Сергеевна;555666;Россия;Татарстан;Приволжский;Казань;Пушкина;8;3;Татарка;1987;7;18;2;1005;Высшее;2020\n");
    fprintf(file, "Васильев;Алексей;Петрович;777888;Россия;Ростовская;Аксайский;Ростов;Советская;12;4;Русский;1991;9;25;1;1006;Среднее;2020\n");

    fclose(file);
    printf("Файл %s успешно создан!\n", filename);
}

void viewFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла %s!\n", filename);
        return;
    }

    printf("\nСодержимое файла %s:\n", filename);
    printf("====================================\n");
    
    char line[1024];
    int lineNum = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("%d: %s", lineNum++, line);
    }
    
    printf("====================================\n");
    fclose(file);
}

void parseWorkerFromString(char *buffer, Worker *worker) {
    char *token = strtok(buffer, ";");
    if (token) strcpy(worker->surname, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->name, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->patronymic, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->postal_code, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->country, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->region, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->district, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->city, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->street, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->house, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->apartment, token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->nationality, token);
    
    token = strtok(NULL, ";");
    if (token) worker->birth_year = atoi(token);
    
    token = strtok(NULL, ";");
    if (token) worker->birth_month = atoi(token);
    
    token = strtok(NULL, ";");
    if (token) worker->birth_day = atoi(token);
    
    token = strtok(NULL, ";");
    if (token) worker->workshop_number = atoi(token);
    
    token = strtok(NULL, ";");
    if (token) worker->employee_id = atoi(token);
    
    token = strtok(NULL, ";");
    if (token) strcpy(worker->education, token);
    
    token = strtok(NULL, ";");
    if (token) worker->start_year = atoi(token);
}

void printWorkerToFile(FILE *file, Worker *worker) {
    fprintf(file, "ФИО: %s %s %s\n", worker->surname, worker->name, worker->patronymic);
    fprintf(file, "Адрес: %s, %s, %s обл., %s р-н, г.%s, ул.%s, д.%s, кв.%s\n",
           worker->postal_code, worker->country, worker->region, 
           worker->district, worker->city, worker->street, 
           worker->house, worker->apartment);
    fprintf(file, "Национальность: %s\n", worker->nationality);
    fprintf(file, "Дата рождения: %02d.%02d.%04d\n", 
           worker->birth_day, worker->birth_month, worker->birth_year);
    fprintf(file, "№ цеха: %d\n", worker->workshop_number);
    fprintf(file, "Табельный номер: %d\n", worker->employee_id);
    fprintf(file, "Образование: %s\n", worker->education);
    fprintf(file, "Год поступления: %d\n", worker->start_year);
    fprintf(file, "--------------------------------------------\n");
}

void processAndSaveResults(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Ошибка открытия файла %s!\n", inputFile);
        return;
    }

    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        printf("Ошибка создания файла %s!\n", outputFile);
        fclose(input);
        return;
    }

    Worker worker;
    int found = 0;
    int totalWorkers = 0;
    char buffer[1024];

    fprintf(output, "============================================\n");
    fprintf(output, "   РАБОЧИЕ, ПОСТУПИВШИЕ НА РАБОТУ В 2020 ГОДУ\n");
    fprintf(output, "============================================\n\n");

    while (fgets(buffer, sizeof(buffer), input)) {
        // Убираем символ новой строки
        buffer[strcspn(buffer, "\n")] = 0;
        
        // Пропускаем пустые строки
        if (strlen(buffer) == 0) continue;
        
        totalWorkers++;
        
        // Создаем копию строки для парсинга
        char tempBuffer[1024];
        strcpy(tempBuffer, buffer);
        
        parseWorkerFromString(tempBuffer, &worker);

        // Проверка, поступил ли рабочий в 2020 году
        if (worker.start_year == 2020) {
            found++;
            fprintf(output, "Рабочий #%d:\n", found);
            printWorkerToFile(output, &worker);
        }
    }

    fprintf(output, "\n============================================\n");
    fprintf(output, "Всего обработано записей: %d\n", totalWorkers);
    fprintf(output, "Найдено рабочих 2020 года: %d\n", found);
    fprintf(output, "============================================\n");

    fclose(input);
    fclose(output);
    
    printf("Обработка завершена. Результат сохранен в файл %s\n", outputFile);
    printf("Всего записей: %d, найдено: %d\n", totalWorkers, found);
}

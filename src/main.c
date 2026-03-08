#include <stdio.h>
#include <stdlib.h>
#include "../include/worker.h"

int main() {
    const char *inputFile = "data/workers.txt";
    const char *outputFile = "data/workers_2020.txt";
    
    int choice;
    
    printf("====================================\n");
    printf("   ПРОГРАММА ДЛЯ ОБРАБОТКИ ДАННЫХ\n");
    printf("        о рабочих предприятия\n");
    printf("====================================\n");
    
    while (1) {
        printf("\nМеню:\n");
        printf("1. Создать файл с данными\n");
        printf("2. Просмотреть содержимое файла\n");
        printf("3. Обработать данные (найти рабочих 2020 года)\n");
        printf("4. Просмотреть результат обработки\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        
        scanf("%d", &choice);
        getchar(); // Очистка буфера ввода
        
        switch(choice) {
            case 1:
                createInputFile(inputFile);
                break;
                
            case 2:
                viewFile(inputFile);
                break;
                
            case 3:
                processAndSaveResults(inputFile, outputFile);
                break;
                
            case 4:
                viewFile(outputFile);
                break;
                
            case 0:
                printf("Программа завершена.\n");
                return 0;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    
    return 0;
}

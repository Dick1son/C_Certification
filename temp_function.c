#include "temp_function.h"

sensorData *allMonthsDataArray[MONTHS] = {NULL};

void help(void);
char* getMonthName(int);

double getMonthAverageTemp(sensorData **allMonthsData, int month) {
    double monthAvgTemp = 0;
    float totalTemp = 0;

        for (uint16_t i = 0; i < QUANTITY_OF_RECORDS; i++) {
            totalTemp += allMonthsData[month][i].temperature;
        }

        monthAvgTemp = totalTemp / QUANTITY_OF_RECORDS;

    return monthAvgTemp;
}

int8_t getMonthMaxTemp(sensorData **allMonthsData, int month) {
    int8_t maxTemperature = allMonthsData[month][0].temperature;

    for (uint16_t i = 0; i < QUANTITY_OF_RECORDS; i++) {
        if (maxTemperature < allMonthsData[month][i].temperature) {
            maxTemperature = allMonthsData[month][i].temperature;
        }
    }

    return maxTemperature;
}

int8_t getMonthMinTemp(sensorData **allMonthsData, int month) {
    int8_t minTemperature = allMonthsData[month][0].temperature;

    for (uint16_t i = 0; i < QUANTITY_OF_RECORDS; i++) {
        if (minTemperature > allMonthsData[month][i].temperature) {
            minTemperature = allMonthsData[month][i].temperature;
        }
    }

    return minTemperature;
}



double getYearAverageTemp() {
    double yearAvgTemp = 0;
    float totalAvgTemp = 0;

    for(uint8_t month = JANUARY; month <= DECEMBER; month++){
        totalAvgTemp += getMonthAverageTemp(allMonthsDataArray, month);
    }

    yearAvgTemp = totalAvgTemp / MONTHS;

    return yearAvgTemp;
}

int8_t getYearMaxTemp() {
    int8_t maxYearTemp = 0;

    for(uint8_t month = JANUARY; month <= DECEMBER; month++){
        int8_t monthMaxTemp = getMonthMaxTemp(allMonthsDataArray, month);

        if(maxYearTemp < monthMaxTemp){
            maxYearTemp = monthMaxTemp;
        }
    }

    return maxYearTemp;
}

int8_t getYearMinTemp() {
    int8_t minYearTemp = 0;

    for(uint8_t month = JANUARY; month <= DECEMBER; month++){
        int8_t monthMinTemp = getMonthMinTemp(allMonthsDataArray, month);

        if(minYearTemp < monthMinTemp){
            minYearTemp = monthMinTemp;
        }
    }
    return minYearTemp;
}

void fileReader(char *path) {
    FILE *file;
    uint16_t year;
    uint8_t day, month, hour, min;
    int8_t temperature, readLine;
    uint32_t errorStringNumber = 0;
    uint16_t counter = 0;
    static int old_month;

    if (access(path, F_OK) == 0) 
        file = fopen(path, "r");
    else 
        printf("File %s is not exist!\n", path);

    do {
        readLine = fscanf(file, "%" SCNu16 ";%" SCNu8 ";%" SCNu8 ";%" SCNu8 ";%" SCNu8 ";%" SCNd8, &year, &month, &day, &hour, &min, &temperature);
        if (readLine > 0){
            if (readLine < QUANTITY_OF_PARAMETERS) {
                        char errorString[50];
                        readLine = fscanf(file, "%[^\n]", errorString);
                        printf("ERROR on string (%d), number of parsing arguments (%d), error string: (%s)\n", errorStringNumber, readLine, errorString);
                    } else if (month != old_month) {
                            if(counter != 0) {
                                allMonthsDataArray[month - 2][0].quantityOfRecords = counter;
                            }
                            old_month = month;
                            counter = 0;
                            allMonthsDataArray[month - 1] = (sensorData*) malloc(BUFFER_SIZE * sizeof(sensorData));
                        }
                    allMonthsDataArray[month - 1][counter].year = year;
                    allMonthsDataArray[month - 1][counter].month = month;
                    allMonthsDataArray[month - 1][counter].day = day;
                    allMonthsDataArray[month - 1][counter].hour = hour;
                    allMonthsDataArray[month - 1][counter].min = min;
                    allMonthsDataArray[month - 1][counter].temperature = temperature;
                    counter++;
                    errorStringNumber++;
        } else
            allMonthsDataArray[month - 1][0].quantityOfRecords = counter;
        

    } while ( (readLine = fscanf(file, "%" SCNu16 ";%" SCNu8 ";%" SCNu8 ";%" SCNu8 ";%" SCNu8 ";%" SCNd8, &year, &month, &day, &hour, &min, &temperature)) != EOF);
    
    fclose(file);
}

void printMonthStat(char *arg) {
    uint8_t month = atoi(arg) - 1;
    if(allMonthsDataArray[0] == NULL)
    {
        printf("Error, specify the path to the file");
        help();
    }    
    else
        printf("Month | Average Temperature | Max Temperature | Min Temperature |\n %s\t   %.2f C\t\t   %d C\t\t   %d C",  getMonthName(month), 
                                                                                                                    getMonthAverageTemp(allMonthsDataArray, month),
                                                                                                                    getMonthMaxTemp(allMonthsDataArray, month),
                                                                                                                    getMonthMinTemp(allMonthsDataArray, month));
}

void printYearStat() {
    if(allMonthsDataArray[0] == NULL)
    {
        printf("Error, specify the path to the file");
        help();
    }    
    else
        printf(" Average Temperature | Max Temperature | Min Temperature |\n\t   %.2f C\t\t   %d C\t\t   %d C",     getYearAverageTemp(),
                                                                                                                    getYearMaxTemp(),
                                                                                                                    getYearMinTemp());
}

char* getMonthName(int monthNumber) {
    switch (monthNumber) {
        case JANUARY: return "JAN"; break;
        case FEBRUARY: return "FEB"; break;
        case MARCH: return "MAR"; break;
        case APRIL: return "APR"; break;
        case MAY: return "MAY"; break;
        case JUNE: return "JUN"; break;
        case JULY: return "JUL"; break;
        case AUGUST: return "AUG"; break;
        case SEPTEMBER: return "SEP"; break;
        case OCTOBER: return "OCT"; break;
        case NOVEMBER: return "NOV"; break;
        case DECEMBER: return "DEC"; break;
        default: return "ERROR"; break;
    }
}

void help() {
    printf("[-h]                 to show help\n");
    printf("[-f <path to csv>]   path to csv file\n");
    printf("[-m <month number>]  to show statistics by this month\n");
    printf("[-y]                 to show statistics by year\n\n");
}

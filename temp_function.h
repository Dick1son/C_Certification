#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>

#define MONTHS 12
#define DAYS 30
#define QUANTITY_OF_PARAMETERS 6
#define BUFFER_SIZE 50000
#define QUANTITY_OF_RECORDS allMonthsDataArray[month][0].quantityOfRecords

typedef struct sensorData {
    uint16_t quantityOfRecords;
    uint16_t year;
    uint8_t day;
    uint8_t month;
    uint8_t hour;
    uint8_t min;
    int8_t temperature;
} sensorData;

enum Months {
    JANUARY = 0,
    FEBRUARY = 1,
    MARCH = 2,
    APRIL = 3,
    MAY = 4,
    JUNE = 5,
    JULY = 6,
    AUGUST = 7,
    SEPTEMBER = 8,
    OCTOBER = 9,
    NOVEMBER = 10,
    DECEMBER = 11
};

void    printMonthStat(char *);
void    printYearStat(void);
void    fileReader(char*);
void    help(void);
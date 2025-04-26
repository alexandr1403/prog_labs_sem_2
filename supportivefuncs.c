#include "aCash.h"

/*Функция строкового представления месяца*/
void month(DATA dats, char *str)
{
    switch (dats.mon)
    {
    case 1:
    {
        strcpy(str, "января");
        break;
    }
    case 2:
    {
        strcpy(str, "февраля");
        break;
    }
    case 3:
    {
        strcpy(str, "марта");
        break;
    }
    case 4:
    {
        strcpy(str, "апреля");
        break;
    }
    case 5:
    {
        strcpy(str, "мая");
        break;
    }
    case 6:
    {
        strcpy(str, "июня");
        break;
    }
    case 7:
    {
        strcpy(str, "июля");
        break;
    }
    case 8:
    {
        strcpy(str, "августа");
        break;
    }
    case 9:
    {
        strcpy(str, "сентября");
        break;
    }
    case 10:
    {
        strcpy(str, "октября");
        break;
    }
    case 11:
    {
        strcpy(str, "ноября");
        break;
    }
    default:
    {
        strcpy(str, "декабря");
        break;
    }
    }
}

/*Функция для перевода значений типа карты и валюты в значения enum*/
int translatetoint(char *str)
{
    if (strcmp(str, "дебетовая") == 0)
        return debit;
    else if (strcmp(str, "кредитная") == 0)
        return credit;
    else if (strcmp(str, "эскроу") == 0)
        return eskrow;
    else if (strcmp(str, "доллар") == 0)
        return dollar;
    else if (strcmp(str, "евро") == 0)
        return euro;
    else if (strcmp(str, "рубль") == 0)
        return rubl;
    else if (strcmp(str, "фунт") == 0)
        return funt;
    else if (strcmp(str, "юань") == 0)
        return yuan;
    else
        return -1;
}

/*Контроль выделения памяти*/
bool control_of_NULL(void *ptr)
{
    return (ptr == NULL) ? false : true;
}
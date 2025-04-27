#ifndef INFO_H
#define INFO_H
#include "aCash.h"

/*Данные для заполнения информации о счетах*/

/*Данные о счёте A-Bank*/
char id_bank[] = "1234123456785678";
char num_bank[] = "12345123455678956789";
CARD type_bank = debit;
VAL val_bank = rubl;
double bal_bank = 12000;
uint open_year_bank = 2020;
int open_month_bank = 3;
int open_day_bank = 2;
uint bonus_bank = 0;

/*Данные о банковской ячейке счёта A-Bank*/
ulg id_acell = 2739141525;
uint cost_acell = 2600;
uint size_acell = large;
uint period_acell = 9;
uint safety_acell = highlvl;
bool video_acell = true;
bool access_acell = false;

/*Данные о счёте B-Bank */
char id_acc[] = "1234123456785678";
char num_acc[] = "12345123455678956789";
CARD type_acc = eskrow;
VAL val_acc = dollar;
double bal_acc = 50;
uint open_year_acc = 2023;
int open_month_acc = 4;
int open_day_acc = 22;
uint bonus_acc = 216;

/*Данные о банковской ячейке счёта B-Bank*/
ulg id_bcell = 1364698019;
uint cost_bcell = 2000;
uint size_bcell = low;
uint period_bcell = 9;
uint safety_bcell = veryhighlvl;
bool video_bcell = true;
bool access_bcell = true;

/*Общие данные для счетов*/
int bonpay = 50;  // в % от суммы операции
int bonpadd = 10; // в % от суммы операции

#endif
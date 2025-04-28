#ifndef ACASH_H
#define ACASH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdalign.h>
#include <time.h>
#include "bitcellB.h"

/*Константы*/
#define PIN_BANK 1235
#define PIN_ACC 7132
#define MINUS 5000
#define COMISS 300
#define LENID 16
#define LENNUM 20
#define LENSTRS strlen("дебетовая") + 1
#define MAXBONUS 3000

typedef unsigned int uint;

/*Типы карт*/
typedef enum type
{
    debit,
    credit,
    eskrow
} CARD;

/*Курс валют отталкивается от рубля*/
typedef enum valute
{
    dollar = 90,
    euro = 95,
    rubl = 1,
    funt = 113,
    yuan = 12
} VAL;

typedef struct data
{
    uint day;
    uint mon;
    uint year;
} DATA;

typedef struct bonus
{
    uint bonuses;
    int bon_to_pay;
    int bon_to_add;
} BNS;

typedef struct aCash
{
    double balance;
    char *id, *num, *type, *val;
    DATA *data_open, *data_close;
    BNS *bonus;
    ulg bank_cell;
    CELL *cellB;
} CASH;

/*Прототипы функций*/
int construct_data(DATA *, uint, int, int);
void copydatas(DATA *, DATA *);
DATA *def_data_construct();
CASH *def_aCash_construct();
void construct(CASH *, char *, char *, int, int, double, uint, int, int, uint, int, int, ulg, uint, uint, uint, uint, bool, bool);
void destroy_aCash(CASH *);
BNS *def_bonus_construct();
void bonus_construct(BNS *, uint, int, int);
int isowner(char, int);
int if_not_owner(CASH *);
int ifowner(CASH *, CASH *);
void month(DATA, char *);
int translatetoint(char *);
void show_info(const CASH *, bool);
void show_str(const CASH *);
void show_balance(const CASH *, bool);
int comparison_accs(CASH *, CASH *);
int isclose(CASH *, uint, uint, uint);
double addition(CASH *, double);
double payment(CASH *, double, int);
void division(double, double, char *);
double transfer(CASH *, CASH *, double);
double usebons(CASH *, double);
void destroy_bons(BNS *);
int choose(CASH *, CASH *);
void copy_dt(DATA *, DATA *);
void copy_aCash(CASH *, CASH *);
void copy_bon(BNS *, BNS *);
int isopen(CASH *, uint, uint, uint);
int input_info_bons(BNS *);
int input_info(CASH *);
bool control_of_NULL(void *);
void demo_align(CASH *bank);
void support_user(CASH *bank, int user);

#endif
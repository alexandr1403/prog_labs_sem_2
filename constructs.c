#include "aCash.h"

/*Функция "пустой" конструктор для структуры DATA*/
DATA *def_data_construct()
{
    DATA *data = (DATA *)malloc(sizeof(DATA));
    if (!control_of_NULL(data))
        return NULL;

    data->day = 0;
    data->mon = 0;
    data->year = 0;
    return data;
}

/*Функция конструктор для структуры data*/
int construct_data(DATA *open, uint year, int mon, int day)
{
    if (!control_of_NULL(open))
        return 0;
    open->year = year;
    open->mon = mon;
    open->day = day;
    return 1;
}

/*Функция для создания структуры даты закрытия карты*/
void copydatas(DATA *strop, DATA *strcl)
{
    if (!control_of_NULL(strop) || !control_of_NULL(strcl))
        printf("Не удалось скопировать структуру.\n");
    else
    {
        strcl->year = strop->year + 6;
        strcl->mon = strop->mon;
        strcl->day = strop->day;
    }
}

/*Функция "пустой" конструктор для структуры aCash */
CASH *def_aCash_construct()
{
    CASH *bank = (CASH *)malloc(sizeof(CASH));
    if (!control_of_NULL(bank))
        return NULL;

    bank->id = (char *)malloc((LENID + 1) * sizeof(char));
    bank->num = (char *)malloc((LENNUM + 1) * sizeof(char));
    bank->balance = 0.0;
    bank->type = (char *)malloc(20 * sizeof(char));
    bank->val = (char *)malloc(20 * sizeof(char));
    bank->bank_cell = 0;
    bank->data_open = def_data_construct();
    bank->data_close = def_data_construct();
    bank->bonus = def_bonus_construct();
    bank->cellB = def_cell_struct_construct();
    if (!control_of_NULL(bank->data_open) || !control_of_NULL(bank->data_close) || !control_of_NULL(bank->data_close) || !control_of_NULL(bank->cellB))
        return NULL;

    return bank;
}

/*Функция - конструктор для банковского счёта*/
void construct(CASH *bank, char *id, char *num, int val, int type, double balance, uint year_open, int day, int month, uint bonuses, int bonpay, int bonadd, ulg cellid, uint cost, uint size, uint period, uint s_lvl, bool video, bool ac_type)
{
    strcpy(bank->id, id);
    strcpy(bank->num, num);

    construct_data(bank->data_open, year_open, month, day);
    copydatas(bank->data_open, bank->data_close);

    switch (val)
    {
    case dollar:
    {
        strcpy(bank->val, "доллар");
        break;
    }
    case euro:
    {
        strcpy(bank->val, "евро");
        break;
    }
    case rubl:
    {
        strcpy(bank->val, "рубль");
        break;
    }
    case funt:
    {
        strcpy(bank->val, "фунт");
        break;
    }
    default:
    {
        strcpy(bank->val, "юань");
        break;
    }
    }

    switch (type)
    {
    case 0:
    {
        strcpy(bank->type, "дебетовая");
        break;
    }
    case 1:
    {
        strcpy(bank->type, "кредитная");
        break;
    }

    default:
    {
        strcpy(bank->type, "эскроу");
        break;
    }
    }

    bank->balance = balance;
    bonus_construct(bank->bonus, bonuses, bonpay, bonadd);
    cellB_construct(&(bank->bank_cell), cellid, cost, size, period, s_lvl, video, ac_type);
    cell_struct_construct(bank->cellB, cellid, cost, size, period, s_lvl, video, ac_type);
}

/*Функция деструктор для структуры DATA*/
void destroy_dat(DATA *dat)
{
    construct_data(dat, 0, 0, 0);
    free(dat);
    dat = NULL;
}

/*Функция деструктор для структуры aCash*/
void destroy_aCash(CASH *bank)
{
    if (bank)
    {
        free(bank->id);
        free(bank->num);
        free(bank->val);
        free(bank->type);

        bank->balance = 0.0;

        free(bank->data_open);
        free(bank->data_close);

        destroy_bons(bank->bonus);
        bank->bank_cell = 0;
        destroy_cell(bank->cellB);
        free(bank);
    }
    bank = NULL;
}

/*Функция "пустой" конструктор для структуры bonus*/
BNS *def_bonus_construct()
{
    BNS *bonus = (BNS *)malloc(sizeof(BNS));
    if (!control_of_NULL(bonus))
        return NULL;

    bonus->bonuses = 0;
    bonus->bon_to_add = 0;
    bonus->bon_to_pay = 0;
    return bonus;
}

/*Функция конструктор для структуры bonus*/
void bonus_construct(BNS *bonus, uint bonuses, int bonpay, int bonadd)
{
    bonus->bonuses = bonuses;
    bonus->bon_to_add = bonadd;
    bonus->bon_to_pay = bonpay;
}

/*Функция деструктор для структуры bonus*/
void destroy_bons(BNS *bonus)
{
    bonus->bonuses = 0;
    bonus->bon_to_add = 0;
    bonus->bon_to_pay = 0;
    free(bonus);
    bonus = NULL;
}

/*Функция копирующий конструктор для структуры data*/
void copy_dt(DATA *one, DATA *two)
{
    if (control_of_NULL(one) && (control_of_NULL(two)))
    {
        two->year = one->year;
        two->mon = one->mon;
        two->day = one->day;
    }
    else
        printf("Не удалось скопировать структуру.\n");
}

/*Копирующий конструктор для структуры cellB*/
void copy_cellB(CELL *bank, CELL *acc)
{
    if (!control_of_NULL(bank) || !control_of_NULL(acc))
        puts("Не удалось выделить память.");
    else
    {
        acc->access_type = bank->access_type;
        acc->cost = bank->cost;
        acc->id = bank->id;
        acc->period = bank->period;
        acc->safety_lvl = bank->safety_lvl;
        acc->size = bank->size;
        acc->video = bank->video;
    }
}

/*Функция копирующий конструктор для структуры aCash*/
void copy_aCash(CASH *bank, CASH *acc)
{
    if (control_of_NULL(bank) && (control_of_NULL(acc)))
    {
        strcpy(bank->id, acc->id);
        strcpy(bank->num, acc->num);
        strcpy(bank->type, acc->type);
        strcpy(bank->val, acc->val);
        bank->balance = acc->balance;
        copy_dt(acc->data_open, bank->data_open);
        copydatas(bank->data_open, bank->data_close);
        copy_bon(acc->bonus, bank->bonus);
        bank->bank_cell = acc->bank_cell;
        copy_cellB(bank->cellB, acc->cellB);
    }
    else
        printf("Не удалось скопировать структуру.\n");
}

/*Функция копирующий конструктор для структуры bonus*/
void copy_bon(BNS *bank, BNS *acc)
{
    if (control_of_NULL(bank) && (control_of_NULL(acc)))
    {
        acc->bonuses = bank->bonuses;
        acc->bon_to_add = bank->bon_to_add;
        acc->bon_to_pay = bank->bon_to_pay;
    }
    else
        printf("Не удалось скопировать структуру.\n");
}

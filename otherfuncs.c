#include "aCash.h"

/*Функция для вывода данных о счёте*/
void show_info(const CASH *bank, bool x)
{
    if (bank == NULL)
        puts("Нечего показывать.");
    else
    {
        if (x == true)
        {
            printf("Номер карты: %s\nНомер счёта: %s\nВид карты: %s\nВалюта: %s\nБаланс: %.2f\nДата открытия счёта: %d.%d.%d\nДата закрытия счёта: %d.%d.%d\nБонусов накоплено: %d\nКаждый бонус - 1 рубль\nТариф на пополнение счёта: начисление + %d%% от суммы пополнения бонусами\nТариф на оплату покупок бонусами: не более %d%% от стоимости покупки\nКомиссия за перевод на карту другого типа: %d рублей\n", bank->id, bank->num, bank->type, bank->val, bank->balance, bank->data_open->day, bank->data_open->mon, bank->data_open->year, bank->data_close->day, bank->data_close->mon, bank->data_close->year, bank->bonus->bonuses, bank->bonus->bon_to_add, bank->bonus->bon_to_pay, COMISS);
            printf("Информация о банковской ячейке: \n");
            show_cellB(bank->bank_cell);
        }
        else
        {
            printf("Номер карты: %s\nНомер счёта: %s\nВид карты: %s\nВалюта: %s\n", bank->id, bank->num, bank->type, bank->val);
            show_balance(bank, false);
        }
    }
}

/*Функция для строкового представления объекта*/
void show_str(const CASH *bank)
{
    char *str = (char *)malloc(10 * sizeof(char));
    month(*(bank->data_open), str);
    printf("%s карта с номером %s привязана к расчётному счёту номер %s. На счету сейчас лежит %.2f %s. Счёт открыт %d %s %d года и будет закрыт в %d году. На счету накоплено %d бонусов, каждый бонус = 1 рубль. Тариф на пополнение счёта: + %d%% от суммы пополнения бонусами. Тариф на оплату покупок бонусами: не более %d%% от стоимости покупки. Комиссия за перевод на карту другого типа: %d рублей\n", bank->type, bank->id, bank->num, bank->balance, bank->val, bank->data_open->day, str, bank->data_open->year, bank->data_close->year, bank->bonus->bonuses, bank->bonus->bon_to_add, bank->bonus->bon_to_pay, COMISS);
    printf("Информация о банковской ячейке: ");
    strshow_cellB(bank->bank_cell);
    free(str);
}

/*Функция просмотра баланса*/
void show_balance(const CASH *bank, bool is)
{
    CARD x = translatetoint(bank->type);
    if (x == 2)
    {
        printf("Баланс карты: %.2f %s\n", bank->balance, bank->val);
    }
    else
    {
        if (is == true)
        {
            printf("Баланс карты: %.2f %s\n", bank->balance, bank->val);
        }
        else
            printf("Просмотр баланса разрешён только владельцу карты.\n");
    }
}

/*Функция для сравнения двух счетов*/
int comparison_accs(CASH *bank, CASH *acc)
{
    uint year_bank = bank->data_open->year;
    int day_bank = bank->data_open->day;
    int month_bank = bank->data_open->mon;
    uint year_acc = acc->data_close->year;
    int day_acc = acc->data_close->day;
    int month_acc = acc->data_close->mon;
    uint a_bon = bank->bonus->bonuses;
    uint b_bon = acc->bonus->bonuses;
    int x = bank->balance * (translatetoint(bank->val));
    int y = acc->balance * (translatetoint(acc->val));
    if (acc != NULL && bank != NULL)
    {
        int cmp;
        printf("По какому показателю сравнивать карты? (1 - баланс, 2 - по дате открытия счёта, 3 - по типу карты, 4 - по кол-ву бонусов): ");
        if (scanf("\n%d", &cmp) == EOF)
            return 0;
        while (cmp < 1 || cmp > 4)
        {
            printf("Ошибка ввода, попробуйте ещё раз: ");
            if (scanf("\n%d", &cmp) == EOF)
                return 0;
        }
        switch (cmp)
        {
        case 1:
        {
            if (x != y)
            {
                if (x > y)
                {
                    printf("На карте, с которой Вы работаете, больше средств, чем на параллельном счету.\n");
                }
                else
                {
                    printf("На карте, с которой Вы работаете, меньше средств, чем на параллельном счету.\n");
                }
            }
            else
            {
                printf("На счетах лежит поровну средств.\n");
            }
            break;
        }
        case 3:
        {
            if (strcmp(bank->type, acc->type) == 0)
            {
                printf("Карты одного типа.\n");
            }
            else
            {
                printf("Карты имеют разный тип.\n");
            }
            break;
        }
        case 2:
        {
            if (year_bank == year_acc)
            {
                if (month_bank == month_acc)
                {
                    if (day_bank == day_acc)
                    {
                        printf("Счета открыты в один день.\n");
                    }
                    else
                    {
                        if (day_bank > day_acc)
                        {
                            printf("Счёт, с которым Вы работаете, был открыт позже, чем параллельный счёт.\n");
                        }
                        else
                        {
                            printf("Счёт, с которым Вы работаете, был открыт раньше, чем параллельный счёт.\n");
                        }
                    }
                }
                else
                {
                    if (month_bank > month_acc)
                    {
                        printf("Счёт, с которым Вы работаете, был открыт позже, чем параллельный счёт.\n");
                    }
                    else
                    {
                        printf("Счёт, с которым Вы работаете, был открыт раньше, чем параллельный счёт.\n");
                    }
                }
            }
            else
            {
                if (year_bank > year_acc)
                {
                    printf("Счёт, с которым Вы работаете, был открыт позже, чем параллельный счёт.\n");
                }
                else
                {
                    printf("Счёт, с которым Вы работаете, был открыт раньше, чем параллельный счёт.\n");
                }
            }
            break;
        }
        case 4:
        {
            if (a_bon == b_bon)
                printf("На счету поровну бонусов.\n");
            else if (a_bon > b_bon)
                printf("На счёте, с которым Вы работаете, накоплено больше бонусов, чем на параллельном.\n");
            else
                printf("На счёте, с которым Вы работаете, накоплено меньше бонусов, чем на параллельном.\n");
        }
        }
    }
    else
    {
        printf("Нечего сравнивать\n");
    }
    return 1;
}

/*Функция проверки открытия счёта*/
int isopen(CASH *bank, uint year, uint mon, uint day)
{
    if (bank->data_open->year == year)
    {
        if (bank->data_open->mon == mon)
        {
            if (bank->data_open->day < day)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (bank->data_open->mon < mon)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        if (bank->data_open->year > year)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/*Функция проверки закрытия счёта*/
int isclose(CASH *bank, uint year, uint mon, uint day)
{
    if (bank->data_close->year == year)
    {
        if (bank->data_close->mon == mon)
        {
            if (bank->data_close->day < day)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (bank->data_close->mon < mon)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    else
    {
        if (bank->data_close->year > year)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/*Функция пополнения карты*/
double addition(CASH *bank, double sum)
{
    bank->balance += sum;
    bank->bonus->bonuses += ((sum * (bank->bonus->bon_to_add) / 100) * translatetoint(bank->val));
    return sum;
}

/*Функция для снятия наличных/оплаты товара*/
double payment(CASH *bank, double sum, int isvalute)
{
    if (strcmp(bank->type, "кредитная") == 0)
    {
        if ((bank->balance * translatetoint(bank->val) + MINUS) < sum)
        {
            printf("Невозможно произвести операцию. Недостаточно средств\n");
            return 0;
        }
        else
        {
            if (isvalute == 0)
            {
                bank->balance -= sum / translatetoint(bank->val);
                return sum;
            }
            else
            {
                if ((bank->balance * translatetoint(bank->val) + MINUS) < (sum + COMISS))
                {
                    printf("Невозможно произвести операцию. Недостаточно средств\n");
                    return 0;
                }
                else
                {
                    bank->balance -= (sum / translatetoint(bank->val) + COMISS / translatetoint(bank->val));
                    printf("Комиссия за перевод: %.2f %s\n", (double)COMISS / translatetoint(bank->val), bank->val);
                    return (sum + COMISS);
                }
            }
        }
    }
    else
    {
        if ((bank->balance) * translatetoint(bank->val) < sum)
        {
            printf("Невозможно произвести операцию. Недостаточно средств\n");
            return 0;
        }
        else
        {
            if (isvalute == 0)
            {
                bank->balance -= sum / translatetoint(bank->val);
                return sum;
            }
            else
            {
                if (bank->balance * translatetoint(bank->val) < (sum + COMISS))
                {
                    printf("Невозможно произвести операцию. Недостаточно средств\n");
                    return 0;
                }
                else
                {
                    bank->balance -= (sum / translatetoint(bank->val) + COMISS / translatetoint(bank->val));
                    printf("Комиссия за перевод: %.2f %s\n", (double)COMISS / translatetoint(bank->val), bank->val);
                    return (sum + COMISS);
                }
            }
        }
    }
}

/*Функция для подсчёта отношения пополнений и списаний*/
void division(double x, double y, char *str)
{
    if ((x + y) != 0)
    {
        double div_xy = x - y;
        // double div_y = (x + y) / y;
        double perc_x = x * 100 / (x + y);
        double perc_y = y * 100 / (x + y);
        if (div_xy < 0)
        {
            printf("Списаний по счёту было больше на %.2f %s, чем пополнений.\n", (div_xy * (-1)) / translatetoint(str), str);
        }
        else
        {
            printf("Пополнений по счёту было больше на %.2f %s, чем списаний.\n", div_xy / translatetoint(str), str);
        }
        printf("Пополнения от общего движения средств по счёту составили %.2f%%, а списания - %.2f%%.\n", perc_x, perc_y);
    }
    else
    {
        printf("По счёту не было пополнений и списаний.\n");
    }
}

/*Функция для перевода средств*/
double transfer(CASH *bank, CASH *acc, double sum)
{
    double down;
    down = payment(bank, sum, strcmp(bank->val, acc->val));
    if (down != 0)
        addition(acc, sum / translatetoint(acc->val));
    return down;
}

/*Функция для пользования бонусами*/
double usebons(CASH *bank, double sum)
{
    if (bank->bonus->bonuses < (sum * bank->bonus->bon_to_pay / 100) && bank->bonus->bonuses < MAXBONUS)
    {
        int a = sum - bank->bonus->bonuses;
        payment(bank, (sum - (bank->bonus->bonuses)), 0);
        bank->bonus->bonuses = 0;
        return a;
    }
    else
    {
        if ((sum * bank->bonus->bon_to_pay / 100) < MAXBONUS)
        {
            payment(bank, (sum * bank->bonus->bon_to_pay / 100), 0);
            bank->bonus->bonuses -= (sum * bank->bonus->bon_to_pay / 100); // подразумевается отнятие кол-ва использованных бонусов
            return (sum - (sum * bank->bonus->bon_to_pay / 100));
        }
        else
        {
            payment(bank, (sum - MAXBONUS), 0);
            bank->bonus->bonuses -= MAXBONUS; // подразумевается отнятие кол-ва использованных бонусов
            return (sum - MAXBONUS);
        }
    }
}

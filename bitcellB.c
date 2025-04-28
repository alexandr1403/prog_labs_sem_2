#include "aCash.h"

/*Ввод значения размера ячейки*/
ulg cellB_size(char user)
{
    switch (user)
    {
    case 'l':
        return low;
    case 'm':
        return mid;
    case 'h':
        return high;
    case 'v':
        return large;
    default:
        printf("Неверный ввод. Повторите: ");
        int att;
        scanf("\n%d", &att);
        return cellB_size(att);
    }
}

/*Уровень безопасности*/
ulg safety_level(char user)
{
    switch (user)
    {
    case 'l':
        return lowlvl;
    case 'm':
        return middlvl;
    case 'h':
        return highlvl;
    case 'v':
        return veryhighlvl;
    default:
        printf("Неверный ввод. Повторите: ");
        char att;
        scanf("\n%c", &att);
        return safety_level(att);
    }
}

/*Видеонаблюдение и тип доступа*/
ulg yesno()
{
    char yesno;
    if (scanf("\n%c", &yesno) == EOF)
        return 0;
    while (yesno != 'y' && yesno != 'n')
    {
        printf("Неверный ввод. Попробуйте ещё: ");
        scanf("\n%c", &yesno);
    }
    return (yesno == 'y') ? 1 : 0;
}

/*Конструктор банковской ячейки*/
void cellB_construct(ulg *cell, uint id, uint cost, uint size, uint period, uint s_lvl, bool video, bool ac_type)
{
    ulg user;
    for (int n = 32, i = 0, copy = 0; i < INP; n >>= 1, i++)
    {
        switch (i)
        {
        case 0: // идентификатор
        {
            user = id;
            break;
        }
        case 1:
        {
            user = (ulg)cost;
            break;
        }
        case 2:
        {
            user = (ulg)size;
            break;
        }
        case 3:
        {
            user = (ulg)period;
            break;
        }
        case 4:
        {
            user = (ulg)s_lvl;
            break;
        }
        case 5:
        {
            user = (ulg)video;
            break;
        }
        case 6:
        {
            user = (ulg)ac_type;
            break;
        }
        }
        (*cell) |= (user << copy);
        copy += n;
    }
}

/*Заполнение информации о ячейке*/
void cellB_init(ulg *cell, CELL *cellB)
{
    srand(time(0));
    ulg user;
    char ch;
    ulg a = 0;
    int copy = 0;
    for (int n = 32, i = 0; i < INP; n >>= 1, i++)
    {
        switch (i)
        {
        case 0: // идентификатор
        {
            a = getrand(1000000000, UINT_MAX);
            cellB->id = a;
            break;
        }
        case 1:
        {
            printf("Стоимость аренды в месяц: ");
            scanf("\n%lu", &user);
            a = user;
            cellB->cost = a;
            break;
        }
        case 2:
        {
            printf("Размер ячейки (l/m/h/v): ");
            scanf("\n%c", &ch);
            a = cellB_size(ch);
            cellB->size = a;
            break;
        }
        case 3:
        {
            printf("На сколько месяцев аренда? ");
            scanf("\n%lu", &user);
            a = user;
            cellB->period = a;
            break;
        }
        case 4:
        {
            printf("Уровень безопасности? l/m/h/v ");
            scanf("\n%c", &ch);
            a = safety_level(ch);
            cellB->safety_lvl = a;
            break;
        }
        case 5:
        {
            printf("Есть видеонаблюдение? (y/n)");
            a = yesno();
            cellB->video = a;
            break;
        }
        case 6:
        {
            printf("Тип доступа механический? (y/n)");
            a = yesno();
            cellB->access_type = a;
            break;
        }
        }
        (*cell) |= (a << copy);
        copy += n;
    }
}

/*Вывод информации о ячейке*/
void show_cellB(const ulg cell)
{
    char *safety[4] = {"Низкий", "Средний", "Высокий", "Очень высокий"};
    char *str[large + 1] = {[low] = "маленький", [mid] = "средний", [high] = "большой", [large] = "очень большой"};
    putchar('\n');
    for (int i = 0, n = 32, copy = 0; i < INP; copy += n, n >>= 1, i++)
        switch (i)
        {
        case 0:
            printf("Идентификатор: %lu\n", (cell >> copy) & INTMASK);
            break;
        case 1:
            printf("Стоимость аренды за месяц: %lu рублей\n", (cell >> copy) & HEXBITMASK);
            break;
        case 2:
            printf("Размер ячейки: %s - %lu см^3\n", str[(cell >> copy) & DEF_MASK], (cell >> copy) & DEF_MASK);
            break;
        case 3:
            printf("Срок аренды: %ld месяцев\n", (cell >> copy) & FOURBIT_MASK);
            break;
        case 4:
            printf("Уровень безопасности: %s\n", safety[(cell >> copy) & TWOBIT_MASK]);
            break;
        case 5:
            printf("Видеонаблюдение: %s\n", (((cell >> copy) & ONEBIT_MASK) == ONEBIT_MASK) ? "Есть" : "Отсутствует");
            break;
        case 6:
            printf("Тип доступа: %s\n", (((cell >> copy) & ONEBIT_MASK) == ONEBIT_MASK) ? "Механический" : "Биомеханический");
            break;
        }
}

/*Строковое представление банковской ячейки*/
void strshow_cellB(const ulg cell)
{
    char *safety[4] = {"Низкий", "Средний", "Высокий", "Очень высокий"};
    char *str[large + 1] = {[low] = "маленький", [mid] = "средний", [high] = "большой", [large] = "очень большой"};
    putchar('\n');
    for (int i = 0, n = 32, copy = 0; i < INP; copy += n, n >>= 1, i++)
        switch (i)
        {
        case 0:
            printf("Идентификатор ячейки %lu. ", (cell >> copy) & INTMASK);
            break;
        case 1:
            printf("Стоимость аренды за месяц составляет %lu рублей, ", (cell >> copy) & HEXBITMASK);
            break;
        case 2:
            printf("Размер ячейки %s: %lu см^3.", str[(cell >> copy) & DEF_MASK], (cell >> copy) & DEF_MASK);
            break;
        case 3:
            printf("Ячейка арендована на %ld месяцев.", (cell >> copy) & FOURBIT_MASK);
            break;
        case 4:
            printf("Безопасность ячейки -  %s уровень.", safety[(cell >> copy) & TWOBIT_MASK]);
            break;
        case 5:
            printf("Видеонаблюдение %s, ", (((cell >> copy) & ONEBIT_MASK) == ONEBIT_MASK) ? "Есть" : "Отсутствует");
            break;
        case 6:
            printf("Тип доступа к ячейке - %s.\n", (((cell >> copy) & ONEBIT_MASK) == ONEBIT_MASK) ? "Механический" : "Биомеханический");
            break;
        }
}

/*Демонстрация комбинации битов в переменной*/
char *longtobits(ulg n, char *bitstr)
{
    int size = CHAR_BIT * sizeof(ulg);
    for (int i = size - 1; i >= 0; i--, n >>= 1)
        bitstr[i] = (01 & n) + '0';
    bitstr[size] = '\0';
    return bitstr;
}

/*Демонстрация комбинации битов в структуре*/
char *structobits(CELL n, char *bitstr)
{
    int size = CHAR_BIT * sizeof(ulg);
    int i = size - 1;
    for (int j = 32, d = 0; d < INP; d++, j >>= 1)
        switch (d)
        {
        case 0:
            for (; i >= j; i--, n.id >>= 1)
                bitstr[i] = (01 & n.id) + '0';
            break;
        case 1:
            for (; i >= j; i--, n.cost >>= 1)
                bitstr[i] = (01 & n.cost) + '0';
        case 2:
            for (; i >= j; i--, n.size >>= 1)
                bitstr[i] = (01 & n.size) + '0';
        case 3:
            for (; i >= j; i--, n.period >>= 1)
                bitstr[i] = (01 & n.period) + '0';
        case 4:
            for (; i >= j; i--, n.safety_lvl >>= 1)
                bitstr[i] = (01 & n.safety_lvl) + '0';
        case 5:
            for (; i >= j; i--, n.video >>= 1)
                bitstr[i] = (01 & n.video) + '0';
        case 6:
            for (; i >= j; i--, n.access_type >>= 1)
                bitstr[i] = (01 & n.access_type) + '0';
        }
    bitstr[size] = '\0';
    return bitstr;
}

/*Смена настроек однобитовых полей*/
void set_onebit(ulg *cell, int remove)
{
    (*cell) ^= ((ulg)ONEBIT_MASK << remove);
}

/*Смена настроек остальных полей*/
void set_otherfields(ulg *cell, ulg mask, int remove, uint user)
{
    (*cell) &= ~((ulg)mask << remove);
    (*cell) |= ((ulg)user << remove);
}

void change_sets(ulg *cellB, CELL *cell, char *binstr, char *structstr, int field)
{
    ulg user;

    /*i - счётчик поля, n - вспомогалка, copy - смещение по переменной, remove - смещение по маске*/
    for (int i = 0, n = 16, copy = 32, remove = 16; i < field; copy += n, remove += (n >> 1), n >>= 1, i++)
    {
        if (i < field - 1)
            continue; // пока не добрались до нужного поля, не производим изменения
        switch (i)
        {
        case 0:
            puts("Переключим значение поля \"Стоимость\" на 1500: ");
            user = 1500;
            cell->cost = user;
            break;
        case 1:
            puts("Переключим значение поля \"Размер ячейки\" на \"Очень большую\": ");
            user = cellB_size('v');
            cell->size = user;
            break;
        case 2:
            puts("Переключим значение поля \"Срок аренды\" на \"5 месяцев\": ");
            user = 5;
            cell->period = user;
            break;
        case 3:
            puts("Переключим значение поля \"Уровень безопасности\" на \"Очень высокий\": ");
            user = safety_level('v');
            cell->safety_lvl = user;
            break;
        case 4:
            puts("Переключим значение поля \"видеонаблюдение\": ");
            cell->video = !(cell->video);
            break;
        case 5:
            puts("Переключим значение поля \"Тип доступа\": ");
            cell->access_type = !(cell->access_type);
            break;
        }
        (i > 3) ? (set_onebit(cellB, copy)) : (set_otherfields(cellB, (ulg)INTMASK >> remove, copy, user));

        printf("Комбинация битов при изменении в переменной cellB: %s\n", longtobits(*cellB, binstr));
        printf("Комбинация битов при изменении в структуре cellB: %s\n", structobits(*cell, structstr));
        show_cellB(*cellB);
    }
}

/*Для генерации идентификатора в случае смены ячейки*/
uint getrand(uint min, uint max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

/*Демонстрация выравнивания*/
void demo_align(CASH *bank)
{
    puts("Адреса элементов структуры:");
    printf("id: %p\nnum: %p\ntype: %p\nval: %p\nbalance: %p\nbonuses: %p\nbon to add: %p\nbon to pay: %p\nopen-day: %p\nopen-mon: %p\nopen-year: %p\nclose-day: %p\nclose-mon: %p\nclose-year: %p\nulg cellB: %p\ndata-open ptr: %p\ndata-close ptr: %p\nbonus ptr: %p\ncellB struct ptr: %p\n", &(bank->id), &(bank->num), &(bank->type), &(bank->val), &(bank->balance), &(bank->bonus->bonuses), &(bank->bonus->bon_to_pay), &(bank->bonus->bon_to_add), &(bank->data_open->day), &(bank->data_open->mon), &(bank->data_open->year), &(bank->data_close->day), &(bank->data_close->mon), &(bank->data_close->year), &(bank->bank_cell), &(bank->data_open), &(bank->data_close), &(bank->bonus), &(bank->cellB));
    putchar('\n');
    printf("Размер структуры aCash: %zu байт, Выравнивание структуры aCash: %zu байт\nРазмер структуры DATA: %zu байт, Выравнивание структуры DATA: %zu байт\nРазмер структуры BNS: %zu байт, Выравнивание структуры BNS: %zu байт\nРазмер структуры cellB: %zu байт, Выравнивание структуры cellB: %zu байт\n", sizeof(*bank), alignof(CASH), sizeof(*(bank->data_open)), alignof(DATA), sizeof(*(bank->bonus)), alignof(BNS), sizeof(*(bank->cellB)), alignof(CELL));
}

/*Пустой Конструктор новой структуры*/
CELL *def_cell_struct_construct()
{
    CELL *cell = (CELL *)malloc(sizeof(CELL));

    cell->id = 0;
    cell->cost = 0;
    cell->period = 0;
    cell->safety_lvl = 0;
    cell->size = 0;
    cell->video = 0;
    cell->access_type = 0;
    return cell;
}

/*Конструктор для новой структуры*/
void cell_struct_construct(CELL *cell, uint id, uint cost, SIZ size, uint period, uint safety_lvl, bool video, bool access_type)
{
    cell->id = id;
    cell->cost = cost;
    cell->period = period;
    cell->safety_lvl = safety_lvl;
    cell->size = size;
    cell->video = (ulg)video;
    cell->access_type = (ulg)access_type;
}

/*Деструктор для новой структуры*/
void destroy_cell(CELL *cell)
{
    free(cell);
    cell = NULL;
}

void show_cellstruct(const CELL *cell)
{
    printf("\nДемонстрация в формате побитовой структуры:\n");
    char *safety[4] = {"Низкий", "Средний", "Высокий", "Очень высокий"};
    char *str[large + 1] = {[low] = "Маленький", [mid] = "средний", [high] = "большой", [large] = "очень большой"};

    printf("Идентификатор ячейки: %u\n", cell->id);
    printf("Стоимость аренды за месяц: %u рублей\n", cell->cost);
    printf("Размер ячейки %s: %u см^3\n", str[cell->size], cell->size);
    printf("Ячейка арендована на %d месяцев\n", cell->period);
    printf("Уровень безопасности ячейки -  %s\n", safety[cell->safety_lvl]);
    printf("Видеонаблюдение: %s\n", (cell->video == true) ? "Есть" : "Отсутствует");
    printf("Тип доступа к ячейке: %s\n", (cell->access_type == true) ? "Механический" : "Биомеханический");
}

#include "fiolist.h"

void control_of_memory(void *ptr)
{
    if (ptr == NULL)
    {
        puts("Ошибка выделения памяти.");
        exit(EXIT_FAILURE);
    }
}

void control_of_open(FILE *fp)
{
    if (fp == NULL)
    {
        puts("Ошибка открытия файла.");
        exit(EXIT_FAILURE);
    }
}

/*Генерация одной структуры DATA (open)*/
DATA *gen_data()
{
    uint day;
    uint year = getrand(2000, 2025);
    uint month = getrand(1, 12);
    if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
        day = getrand(1, 30);
    else if (month == 2)
        day = getrand(1, 28);
    else
        day = getrand(1, 31);

    DATA *open = def_data_construct();
    control_of_memory(open);

    construct_data(open, year, month, day);
    return open;
}

/*Генерация одной структуры BNS*/
BNS *gen_bonus()
{
    BNS *bonus = def_bonus_construct();
    control_of_memory(bonus);
    bonus_construct(bonus, getrand(0, 1000), getrand(5, 50), getrand(5, 50));
    return bonus;
}

/*Генерация одной структуры cellB*/
void gen_cellB(ulg *cell_1, CELL *cell_2)
{
    SIZ mass_siz[] = {low, mid, high, large};
    LVL mass_lvl[] = {lowlvl, middlvl, highlvl, veryhighlvl};
    bool bool_mass[] = {0, 0, 0, 1, 1, 1};

    uint id = getrand(1000000000, UINT_MAX);
    uint cost = getrand(1000, 4000);
    uint size = mass_siz[getrand(0, 3)];
    uint period = getrand(1, 12);
    uint s_lvl = mass_lvl[getrand(0, 3)];
    bool video = bool_mass[getrand(0, 5)];
    bool acc_type = bool_mass[getrand(0, 5)];
    cellB_construct(cell_1, id, cost, size, period, s_lvl, video, acc_type);
    cell_struct_construct(cell_2, id, cost, size, period, s_lvl, acc_type, video);
}

/*Генерация строки из len цифр*/
char *gen_string(size_t len)
{
    char *res = (char *)calloc(len, sizeof(char));
    control_of_memory(res);
    *res = getrand(1, 9) + '0'; // номера карты и счёта не могут начинаться с нуля
    for (size_t i = 1; i < len - 1; i++)
    {
        *(res + i) = getrand(0, 9) + '0';
    }
    *(res + len) = '\0';
    return res;
}

/*Генерация значения баланса*/
double gen_balance()
{
    return ((double)getrand(0, 1000000) + (double)getrand(0, 100000) / 100000.0);
}

/*Генерация одной структуры aCash*/
CASH *gen_aCash()
{
    char *mass_types[] = {"дебетовая", "кредитная", "эскроу"};
    char *mass_valutes[] = {"доллар", "евро", "рубль", "фунт", "юань"};
    // CASH *bank = def_aCash_construct();
    CASH *bank = (CASH *)malloc(sizeof(CASH));
    control_of_memory(bank);
    bank->type = (char *)malloc(20 * sizeof(char));
    bank->val = (char *)malloc(20 * sizeof(char));
    control_of_memory(bank->type);
    control_of_memory(bank->val);

    bank->balance = gen_balance();
    bank->bank_cell = 0;
    bank->cellB = def_cell_struct_construct();
    gen_cellB(&(bank->bank_cell), bank->cellB);
    bank->bonus = gen_bonus();
    bank->id = gen_string(LENID + 1);
    bank->num = gen_string(LENNUM + 1);
    strcpy(bank->type, mass_types[getrand(0, 2)]);
    strcpy(bank->val, mass_valutes[getrand(0, 4)]);
    bank->data_open = gen_data();
    bank->data_close = def_data_construct();
    copydatas(bank->data_open, bank->data_close);

    return bank;
}

/*возвращает массив указателей на n сгенерированных структур*/
CASH **rand_gen_aCash_mass(size_t n)
{
    CASH **mass_structs = (CASH **)malloc(sizeof(CASH *) * n);
    control_of_memory(mass_structs);
    srand(time(0));

    for (size_t i = 0; i < n; i++)
    {
        mass_structs[i] = gen_aCash();
    }
    return mass_structs;
}

/*Очистка массива указателей на структуры aCash*/
void free_mass_structs(CASH **mass, size_t n)
{
    if (mass)
    {
        for (size_t i = 0; i < n; i++)
            destroy_aCash(mass[i]);
        free(mass);
    }
}

/*Запись одной структуры BNS в текстовый файл*/
void save_bonus_in_text(CASH *bank, FILE *fp)
{
    fprintf(fp, "%u ", bank->bonus->bon_to_add);
    fprintf(fp, "%u ", bank->bonus->bon_to_pay);
    fprintf(fp, "%u ", bank->bonus->bonuses);
}

/*Запись одной пары структур DATA в текстовый файл*/
void save_datas_in_text(CASH *bank, FILE *fp)
{
    fprintf(fp, "%u ", bank->data_open->day);
    fprintf(fp, "%u ", bank->data_open->mon);
    fprintf(fp, "%u ", bank->data_open->year);
    fprintf(fp, "%u ", bank->data_close->day);
    fprintf(fp, "%u ", bank->data_close->mon);
    fprintf(fp, "%u ", bank->data_close->year);
}

/*Запись одной структуры CellB в текстовый файл*/
void save_cellstruct_in_text(CASH *bank, FILE *fp)
{
    fprintf(fp, "%u ", bank->cellB->id);
    fprintf(fp, "%u ", bank->cellB->period);
    fprintf(fp, "%u ", bank->cellB->size);
    fprintf(fp, "%u ", bank->cellB->safety_lvl);
    fprintf(fp, "%u ", bank->cellB->cost);
    fprintf(fp, "%u ", bank->cellB->video);
    fprintf(fp, "%u ", bank->cellB->access_type);
}

/*Запись одной структуры в текстовый файл*/
void save_one_struct_in_file(CASH *bank, FILE *fp)
{
    fprintf(fp, "%s ", bank->id);
    fprintf(fp, "%s ", bank->num);
    fprintf(fp, "%s ", bank->type);
    fprintf(fp, "%s ", bank->val);
    fprintf(fp, "%lf ", bank->balance);
    fprintf(fp, "%lu ", bank->bank_cell);

    save_cellstruct_in_text(bank, fp);
    save_datas_in_text(bank, fp);
    save_bonus_in_text(bank, fp);

    fputc('\n', fp);
}

/*Запись массива структур в текстовый файл*/
size_t save_in_textfile(const char *filename, size_t n_mass, CASH **mass_structs)
{
    FILE *fp = fopen(filename, "w");
    control_of_open(fp);
    fprintf(fp, "%zd\n", n_mass);
    for (size_t i = 0; i < n_mass; i++)
        save_one_struct_in_file(mass_structs[i], fp);

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
    return n_mass;
}

void load_cellstruct_from_file(CASH *bank, FILE *fp)
{
    uint supp = 0;
    int count = 0;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->id = supp;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->period = supp;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->size = supp;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->safety_lvl = supp;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->cost = supp;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->video = (bool)supp;
    count += fscanf(fp, " %u", &supp);
    bank->cellB->access_type = (bool)supp;
    printf("count cell:%d\n", count);
    if (count != INP)
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }
}

void load_datas_from_file(CASH *bank, FILE *fp)
{
    int count = 0;
    count += fscanf(fp, " %u", &bank->data_open->day);
    count += fscanf(fp, " %u", &bank->data_open->mon);
    count += fscanf(fp, " %u", &bank->data_open->year);

    count += fscanf(fp, " %u", &bank->data_close->day);
    count += fscanf(fp, " %u", &bank->data_close->mon);
    count += fscanf(fp, " %u", &bank->data_close->year);
    if (count != 6)
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }
}

void load_bonus_from_file(CASH *bank, FILE *fp)
{
    int count = 0;
    count += fscanf(fp, " %d", &bank->bonus->bon_to_add);
    count += fscanf(fp, " %d", &bank->bonus->bon_to_pay);
    count += fscanf(fp, " %u", &bank->bonus->bonuses);
    if (count != 3)
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }
}

/*Загрузка из текстового файла*/
CASH *load_from_file(FILE *fp)
{
    char ch = 0;
    int i = 0, count = 0;
    CASH *bank = def_aCash_construct();
    control_of_memory(bank);

    while ((ch = getc(fp)) != '\n')
    {
        ungetc(ch, fp);
        while ((ch = getc(fp)) != ' ')
        {
            bank->id[i] = ch;
            i++;
        }
        bank->id[i] = '\0';
        i = 0;
        while ((ch = getc(fp)) != ' ')
        {
            bank->num[i] = ch;
            i++;
        }
        bank->num[i] = '\0';
        i = 0;
        while ((ch = getc(fp)) != ' ')
        {
            bank->type[i] = ch;
            i++;
        }
        bank->type[i] = '\0';
        i = 0;
        while ((ch = getc(fp)) != ' ')
        {
            bank->val[i] = ch;
            i++;
        }
        bank->val[i] = '\0';
        i = 0;
        count += fscanf(fp, " %lf", &bank->balance);
        count += fscanf(fp, " %lu", &bank->bank_cell);
        if (count != 2)
        {
            puts("Ошибка считывания данных.");
            exit(EXIT_FAILURE);
        }

        load_cellstruct_from_file(bank, fp);
        load_datas_from_file(bank, fp);
        load_bonus_from_file(bank, fp);

        fseek(fp, 1, SEEK_CUR);
    }

    return bank;
}

/*Загрузка массива структур aCash из текстового файла*/
CASH **load_mass_structs_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    control_of_open(fp);
    size_t n_mass;
    if (fscanf(fp, "%zd\n", &n_mass) != 1)
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }
    CASH **banks = (CASH **)malloc(sizeof(CASH *) * n_mass);
    control_of_memory(banks);
    for (size_t i = 0; i < n_mass; i++)
    {
        banks[i] = load_from_file(fp);
    }

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
    return banks;
}

/*Получение элемента из текстового файла по индексу*/
CASH *get_element_from_text_file(const char *filename, int index)
{
    FILE *fp = fopen(filename, "r");
    control_of_open(fp);

    char ch = 0;
    int count = 0;
    CASH *bank = NULL;
    while ((ch = getc(fp)) != EOF)
    {
        ungetc(ch, fp);
        bank = load_from_file(fp);
        if (count == index)
        {
            if (fclose(fp) == EOF)
            {
                puts("Ошибка закрытия файла.");
                exit(EXIT_FAILURE);
            }
            return bank;
        }
        count++;
        destroy_aCash(bank);
    }

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

/*Сохранение одной структуры aCash в бинарный файл*/
void save_one_struct_in_binaryfile(FILE *fp, CASH *bank)
{
    size_t type = strlen(bank->type) + 1, val = strlen(bank->val) + 1;
    size_t padding_type = LENSTRS - type, padding_val = LENSTRS - val;
    char *padd_1 = (char *)calloc(padding_type, sizeof(char));
    char *padd_2 = (char *)calloc(padding_val, sizeof(char));
    control_of_memory(padd_1);
    control_of_memory(padd_2);

    fwrite(&bank->balance, sizeof(double), 1, fp);
    // fwrite(&id, sizeof(size_t), 1, fp);
    fwrite(bank->id, sizeof(char), LENID + 1, fp);
    // fwrite(&num, sizeof(size_t), 1, fp);
    fwrite((bank->num), sizeof(char), LENNUM + 1, fp);
    fwrite(&type, sizeof(size_t), 1, fp);
    fwrite((bank->type), sizeof(char), type, fp);
    fwrite(padd_1, sizeof(char), padding_type, fp);
    fwrite(&val, sizeof(size_t), 1, fp);
    fwrite((bank->val), sizeof(char), val, fp);
    fwrite(padd_2, sizeof(char), padding_val, fp);
    fwrite(&(bank->bank_cell), sizeof(ulg), 1, fp);
    fwrite(bank->cellB, sizeof(CELL), 1, fp);
    fwrite(bank->bonus, sizeof(BNS), 1, fp);
    fwrite(bank->data_open, sizeof(DATA), 1, fp);
    fwrite(bank->data_close, sizeof(DATA), 1, fp);

    free(padd_1);
    free(padd_2);
}

/*Запись массива структур в бинарный файл*/
void save_in_binaryfile(const char *filename, size_t n_mass, CASH **mass_structs)
{
    FILE *fp = fopen(filename, "wb");
    control_of_open(fp);
    fwrite(&n_mass, sizeof(size_t), 1, fp);
    for (size_t i = 0; i < n_mass; i++)
        save_one_struct_in_binaryfile(fp, mass_structs[i]);

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
}

/*Заргрузка одной структуры aCash из бинарного файла*/
CASH *load_from_binfile(FILE *fp)
{
    CASH *bank = def_aCash_construct();
    control_of_memory(bank);

    size_t type, val, count = 0;

    count += fread(&bank->balance, sizeof(double), 1, fp);
    // fread(&id, sizeof(size_t), 1, fp);
    count += fread(bank->id, sizeof(char), LENID + 1, fp);
    // fread(&num, sizeof(size_t), 1, fp);
    count += fread((bank->num), sizeof(char), LENNUM + 1, fp);
    count += fread(&type, sizeof(size_t), 1, fp);
    count += fread((bank->type), sizeof(char), type, fp);
    size_t padding_type = LENSTRS - type; // padd
    char *padd_1 = (char *)calloc(padding_type, sizeof(char));
    control_of_memory(padd_1);
    count += fread(padd_1, sizeof(char), padding_type, fp);
    count += fread(&val, sizeof(size_t), 1, fp);
    count += fread((bank->val), sizeof(char), val, fp);
    size_t padding_val = LENSTRS - val; // padd
    char *padd_2 = (char *)calloc(padding_val, sizeof(char));
    control_of_memory(padd_2);
    count += fread(padd_2, sizeof(char), padding_val, fp);
    count += fread(&(bank->bank_cell), sizeof(ulg), 1, fp);
    count += fread(bank->cellB, sizeof(CELL), 1, fp);
    count += fread(bank->bonus, sizeof(BNS), 1, fp);
    count += fread(bank->data_open, sizeof(DATA), 1, fp);
    count += fread(bank->data_close, sizeof(DATA), 1, fp);

    // printf("count:%zd\n%zd\n", count, 10 + LENID + LENNUM + LENSTRS + LENSTRS);
    if (count != (10 + LENID + LENNUM + LENSTRS + LENSTRS))
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }

    return bank;
}

CASH **load_mass_structs_from_binfile(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    control_of_open(fp);
    size_t n_mass;
    if (fread(&n_mass, sizeof(size_t), 1, fp) != 1)
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }
    CASH **banks = (CASH **)malloc(sizeof(CASH *) * n_mass);
    control_of_memory(banks);

    for (size_t i = 0; i < n_mass; i++)
        banks[i] = load_from_binfile(fp);

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
    return banks;
}

/*Загрузка по индексу из бинарного файла*/
CASH *get_element_from_binary_file(const char *filename, int index, size_t element_size)
{
    FILE *fp = fopen(filename, "rb");
    control_of_open(fp);
    fseek(fp, index * (element_size + 2 * sizeof(size_t)) + sizeof(size_t), SEEK_SET);
    CASH *bank = load_from_binfile(fp);
    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
    return bank;
}

/*Генерация n структур aCash и возврат их, помещённых в двусвязный список*/
LIST rand_gen_struct_in_list(size_t n)
{
    srand(time(0));
    LIST a = def_list_construct();
    control_of_memory(a);
    CASH *bank;
    for (size_t i = 0; i < n; i++)
    {
        bank = gen_aCash();
        // insert_in_list(a, bank, i);
        bpush(a, bank);
    }
    // printf("count list: %d\ns", a->count);
    return a;
}

/*Сохранение сгенерированных в список структур в файл*/
void save_list_in_file(const char *filename, LIST a)
{
    FILE *fp = fopen(filename, "w");
    control_of_open(fp);
    fprintf(fp, "%d\n", a->count);
    for (ONE *i = a->root; i != NULL; i = i->next)
    {
        save_one_struct_in_file(i->bank, fp);
    }
    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
}

/*Загрузка списка структур из файла*/
LIST load_list_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    control_of_open(fp);
    LIST a = def_list_construct();
    control_of_memory(a);
    size_t n;
    if (fscanf(fp, "%zd\n", &n) != 1)
    {
        puts("Ошибка считывания данных0.");
        exit(EXIT_FAILURE);
    }

    CASH *bank;

    for (size_t i = 0; i < n; i++)
    {
        bank = load_from_file(fp);
        bpush(a, bank);
    }

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
    return a;
}

size_t aCash_size()
{
    return (sizeof(double) + sizeof(char) * (LENID + 1) + sizeof(char) * (LENNUM + 1) + sizeof(char) * (LENSTRS) + sizeof(char) * (LENSTRS) + sizeof(ulg) + sizeof(CELL) + sizeof(BNS) + sizeof(DATA) + sizeof(DATA));
}

/*Загрузка структур из списка в бинарный файл*/
void save_list_to_binfile(const char *filename, LIST a)
{
    FILE *fp = fopen(filename, "wb");
    fwrite(&(a->count), sizeof(size_t), 1, fp);
    for (ONE *curr = a->root; curr != NULL; curr = curr->next)
        save_one_struct_in_binaryfile(fp, curr->bank);

    if (fclose(fp) == EOF)
    {
        puts("Ошибка закрытия файла.");
        exit(EXIT_FAILURE);
    }
}

/*Загрузка структур из бинарного файла в список*/
LIST load_list_from_binfile(const char *filename)
{
    LIST a = def_list_construct();
    control_of_memory(a);
    FILE *fp = fopen(filename, "rb");
    control_of_open(fp);
    size_t n;
    if (fread(&n, sizeof(size_t), 1, fp) != 1)
    {
        puts("Ошибка считывания данных.");
        exit(EXIT_FAILURE);
    }
    CASH *bank;

    for (size_t i = 0; i < n; i++)
    {
        bank = load_from_binfile(fp);
        bpush(a, bank);
    }
    return a;
}

/*Демонстрация i-го элемента структуры, загруженной из текстововго файла*/
void demo_elem_from_list_from_file(const char *filename, int index, int mode)
{
    LIST a = (mode == 0) ? load_list_from_file(filename) : load_list_from_binfile(filename);
    control_of_memory(a);
    CASH *bank = gbind_list(a, index);
    show_info(bank, true);
    destroy_list(a);
}

void list_of_reading_elements(const char *filename, int mode)
{
    if ((mode != 1) && (mode != 0))
    {
        puts("Выбран неверный режим чтения.");
        exit(EXIT_FAILURE);
    }
    LIST banks = (mode == TEXT) ? load_list_from_file(filename) : load_list_from_binfile(filename);
    control_of_memory(banks);
    printf("Прочитано %d элементов:\n", banks->count);

    int index = 0;
    for (ONE *curr = banks->root; curr != NULL; curr = curr->next)
    {
        printf("index: %d\t element: %p\t(id: %s)\n", index, curr->bank, curr->bank->id);
        index++;
    }
    destroy_list(banks);
}

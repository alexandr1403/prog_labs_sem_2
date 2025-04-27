#include "fiolist.h"

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
    construct_data(open, year, month, day);
    return open;
}

/*Генерация одной структуры BNS*/
BNS *gen_bonus()
{
    BNS *bonus = def_bonus_construct();
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
    cell_construct(cell_2, id, cost, size, period, s_lvl, acc_type, video);
}

/*Генерация строки из len цифр*/
char *gen_string(size_t len)
{
    char *res = (char *)calloc(len, sizeof(char));
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
    // CASH *bank = default_construct();
    CASH *bank = (CASH *)malloc(sizeof(CASH));
    bank->type = (char *)malloc(20 * sizeof(char));
    bank->val = (char *)malloc(20 * sizeof(char));

    // time_t a = (time_t)rand();
    bank->balance = gen_balance();
    bank->bank_cell = 0;
    bank->cellB = def_cell_construct();
    gen_cellB(&(bank->bank_cell), bank->cellB);
    bank->bonus = gen_bonus();
    bank->id = gen_string(LENID + 1);
    strcpy(bank->type, mass_types[getrand(0, 2)]);
    strcpy(bank->val, mass_valutes[getrand(0, 4)]);
    bank->data_open = gen_data();
    bank->data_close = def_data_construct();
    copydatas(bank->data_open, bank->data_close);
    bank->num = gen_string(LENNUM + 1);

    return bank;
}

/*возвращает массив указателей на n сгенерированных структур*/
CASH **rand_gen_aCash_mass(size_t n)
{
    // time_t sidde = (time_t)rand() % (RAND_MAX - 1000);
    CASH **mass_structs = (CASH **)malloc(sizeof(CASH *) * n);
    srand(56);

    for (size_t i = 0; i < n; i++)
    {
        mass_structs[i] = gen_aCash();
        // printf("seed: %zd\n", );
        // u -= i * 1000;
    }
    return mass_structs;
}

/*Очистка массива указателей на структуры aCash*/
void free_mass_structs(CASH **mass, size_t n)
{
    for (size_t i = 0; i < n; i++)
        destructor(mass[i]);
    free(mass);
}

/*Запись одной структуры в файл текстовый*/
void save_one_struct_in_file(CASH *bank, FILE *fp)
{
    fprintf(fp, "%s ", bank->id);
    fprintf(fp, "%s ", bank->num);
    fprintf(fp, "%s ", bank->type);
    fprintf(fp, "%s ", bank->val);
    fprintf(fp, "%lf ", bank->balance);
    fprintf(fp, "%lu ", bank->bank_cell);
    fprintf(fp, "%u ", bank->cellB->id);
    fprintf(fp, "%u ", bank->cellB->period);
    fprintf(fp, "%u ", bank->cellB->size);
    fprintf(fp, "%u ", bank->cellB->safety_lvl);
    fprintf(fp, "%u ", bank->cellB->cost);
    fprintf(fp, "%u ", bank->cellB->video);
    fprintf(fp, "%u ", bank->cellB->access_type);
    fprintf(fp, "%u ", bank->data_open->day);
    fprintf(fp, "%u ", bank->data_open->mon);
    fprintf(fp, "%u ", bank->data_open->year);
    fprintf(fp, "%u ", bank->data_close->day);
    fprintf(fp, "%u ", bank->data_close->mon);
    fprintf(fp, "%u ", bank->data_close->year);
    fprintf(fp, "%u ", bank->bonus->bon_to_add);
    fprintf(fp, "%u ", bank->bonus->bon_to_pay);
    fprintf(fp, "%u ", bank->bonus->bonuses);
    fputc('\n', fp);
}

/*Запись массива структур в текстовый файл*/
size_t save_in_textfile(const char *filename, size_t n_mass, CASH **mass_structs)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%zd\n", n_mass);
    for (size_t i = 0; i < n_mass; i++)
        save_one_struct_in_file(mass_structs[i], fp);

    fclose(fp);
    return n_mass;
}

/*Загрузка из текстового файла*/
CASH *load_from_file(FILE *fp)
{
    // FILE *fp = fopen(filename, "r");
    // fpos_t position;
    char ch = 0;
    int i = 0;
    uint supp = 0;
    CASH *bank = default_construct();
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
        fscanf(fp, " %lf", &bank->balance);
        fscanf(fp, " %lu", &bank->bank_cell);

        fscanf(fp, " %u", &supp);
        bank->cellB->id = supp;
        fscanf(fp, " %u", &supp);
        bank->cellB->period = supp;
        fscanf(fp, " %u", &supp);
        bank->cellB->size = supp;
        fscanf(fp, " %u", &supp);
        bank->cellB->safety_lvl = supp;
        fscanf(fp, " %u", &supp);
        bank->cellB->cost = supp;
        fscanf(fp, " %u", &supp);
        bank->cellB->video = (bool)supp;
        fscanf(fp, " %u", &supp);
        bank->cellB->access_type = (bool)supp;

        fscanf(fp, " %u", &bank->data_open->day);
        fscanf(fp, " %u", &bank->data_open->mon);
        fscanf(fp, " %u", &bank->data_open->year);

        fscanf(fp, " %u", &bank->data_close->day);
        fscanf(fp, " %u", &bank->data_close->mon);
        fscanf(fp, " %u", &bank->data_close->year);

        fscanf(fp, " %d", &bank->bonus->bon_to_add);
        fscanf(fp, " %d", &bank->bonus->bon_to_pay);
        fscanf(fp, " %u", &bank->bonus->bonuses);
        fseek(fp, 1, SEEK_CUR);
        // printf("ch: %d\n", ch);
    }

    return bank;
}

/*Загрузка массива структур aCash из текстового файла*/
CASH **load_mass_structs_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    size_t n_mass;
    fscanf(fp, "%zd\n", &n_mass);
    CASH **banks = (CASH **)malloc(sizeof(CASH *) * n_mass);

    for (size_t i = 0; i < n_mass; i++)
    {
        banks[i] = load_from_file(fp);
    }
    fclose(fp);
    return banks;
}

/*Получение элемента из текстового файла по индексу*/
CASH *get_element_from_text_file(const char *filename, int index)
{
    FILE *fp = fopen(filename, "r");
    char ch = 0;
    int count = 0;
    CASH *bank = NULL;
    while ((ch = getc(fp)) != EOF)
    {
        ungetc(ch, fp);
        bank = load_from_file(fp);
        if (count == index)
        {
            fclose(fp);
            return bank;
        }
        count++;
        destructor(bank);
    }

    fclose(fp);
    return NULL;
}

/*Сохранение одной структуры aCash в бинарный файл*/
void save_one_struct_in_binaryfile(FILE *fp, CASH *bank)
{
    size_t id = LENID + 1, num = LENNUM + 1, type = strlen(bank->type) + 1, val = strlen(bank->val) + 1;

    fwrite(&bank->balance, sizeof(double), 1, fp);
    fwrite(&id, sizeof(size_t), 1, fp);
    fwrite(bank->id, sizeof(char), LENID + 1, fp);
    fwrite(&num, sizeof(size_t), 1, fp);
    fwrite((bank->num), sizeof(char), LENNUM + 1, fp);
    fwrite(&type, sizeof(size_t), 1, fp);
    fwrite((bank->type), sizeof(char), strlen(bank->type) + 1, fp);
    fwrite(&val, sizeof(size_t), 1, fp);
    fwrite((bank->val), sizeof(char), strlen(bank->val) + 1, fp);
    fwrite(&(bank->bank_cell), sizeof(ulg), 1, fp);
    fwrite(bank->cellB, sizeof(CELL), 1, fp);
    fwrite(bank->bonus, sizeof(BNS), 1, fp);
    fwrite(bank->data_open, sizeof(DATA), 1, fp);
    fwrite(bank->data_close, sizeof(DATA), 1, fp);
}

/*Запись массива структур в бинарный файл*/
void save_in_binaryfile(const char *filename, size_t n_mass, CASH **mass_structs)
{
    FILE *fp = fopen(filename, "wb");
    fwrite(&n_mass, sizeof(size_t), 1, fp);
    for (size_t i = 0; i < n_mass; i++)
        save_one_struct_in_binaryfile(fp, mass_structs[i]);
    fclose(fp);
}

/*Заргрузка одной структуры aCash из бинарного файла*/
CASH *load_from_binfile(FILE *fp)
{
    CASH *bank = default_construct();

    size_t id, num, type, val;

    fread(&bank->balance, sizeof(double), 1, fp);
    fread(&id, sizeof(size_t), 1, fp);
    fread(bank->id, sizeof(char), id, fp);
    fread(&num, sizeof(size_t), 1, fp);
    fread((bank->num), sizeof(char), num, fp);
    fread(&type, sizeof(size_t), 1, fp);
    fread((bank->type), sizeof(char), type, fp);
    fread(&val, sizeof(size_t), 1, fp);
    fread((bank->val), sizeof(char), val, fp);
    fread(&(bank->bank_cell), sizeof(ulg), 1, fp);
    fread(bank->cellB, sizeof(CELL), 1, fp);
    fread(bank->bonus, sizeof(BNS), 1, fp);
    fread(bank->data_open, sizeof(DATA), 1, fp);
    fread(bank->data_close, sizeof(DATA), 1, fp);

    return bank;
}

CASH **load_mass_structs_from_binfile(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    size_t n_mass;
    fread(&n_mass, sizeof(size_t), 1, fp);
    CASH **banks = (CASH **)malloc(sizeof(CASH *) * n_mass);

    for (size_t i = 0; i < n_mass; i++)
        banks[i] = load_from_binfile(fp);

    fclose(fp);
    return banks;
}

/*Загрузка по индексу из бинарного файла*/
CASH *get_element_from_binary_file(const char *filename, int index, size_t element_size)
{
    FILE *fp = fopen(filename, "rb");
    fseek(fp, index * (element_size + 4 * sizeof(size_t)) + sizeof(size_t), SEEK_SET);
    CASH *bank = load_from_binfile(fp);
    show_info(bank, true);
    fclose(fp);
    return bank;
}

/*Генерация n структур aCash и возврат их, помещённых в двусвязный список*/
LIST rand_gen_struct_in_list(size_t n)
{
    time_t seed = time(0);
    LIST a = def_list_construct();
    CASH *bank;
    for (size_t i = 0; i < n; i++)
    {
        bank = gen_aCash(&seed);
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
    // LIST a = rand_gen_struct_in_container(n);
    fprintf(fp, "%d\n", a->count);
    for (ONE *i = a->root; i != NULL; i = i->next)
    {
        save_one_struct_in_file(i->bank, fp);
    }
    fclose(fp);
}

/*Загрузка списка структур из файла*/
LIST load_list_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    LIST a = def_list_construct();
    size_t n;
    fscanf(fp, "%zd\n", &n);

    CASH *bank;

    for (size_t i = 0; i < n; i++)
    {
        bank = load_from_file(fp);
        // fseek(fp, 1, SEEK_CUR);
        bpush(a, bank);
    }
    fclose(fp);
    return a;
}

size_t aCash_size(CASH *bank)
{
    return (sizeof(bank->balance) + sizeof(*(bank->id)) * (strlen(bank->id) + 1) + sizeof(*(bank->num)) * (strlen(bank->num) + 1) + sizeof(*(bank->type)) * (strlen(bank->type) + 1) + sizeof(*(bank->val)) * (strlen(bank->val) + 1) + sizeof(bank->bank_cell) + sizeof(*(bank->cellB)) + sizeof(*(bank->bonus)) + sizeof(*(bank->data_open)) + sizeof(*(bank->data_close)));
}

/*Демонстрация i-го элемента структуры, загруженной из текстововго файла*/
void demo_elem_from_list_from_file(const char *filename, int index, int mode)
{
    LIST a = (mode == 0) ? load_list_from_file(filename) : load_list_from_binfile(filename);
    CASH *bank = gbind_list(a, index);
    show_info(bank, true);
    destroy_list(a);
}

/*Загрузка структур из списка в бинарный файл*/
void save_list_to_binfile(const char *filename, LIST a)
{
    FILE *fp = fopen(filename, "wb");
    fwrite(&(a->count), sizeof(size_t), 1, fp);
    for (ONE *curr = a->root; curr != NULL; curr = curr->next)
        save_one_struct_in_binaryfile(fp, curr->bank);

    fclose(fp);
}

LIST load_list_from_binfile(const char *filename)
{
    LIST a = def_list_construct();
    FILE *fp = fopen(filename, "rb");
    int n;
    fread(&n, sizeof(size_t), 1, fp);
    CASH *bank;

    for (int i = 0; i < n; i++)
    {
        bank = load_from_binfile(fp);
        bpush(a, bank);
    }
    return a;
}

void list_of_reading_elements(const char *filename, int mode)
{
    if ((mode != 1) && (mode != 0))
    {
        puts("Выбран неверный режим чтения.");
        exit(EXIT_FAILURE);
    }
    LIST banks = (mode == 0) ? load_list_from_file(filename) : load_list_from_binfile(filename);
    printf("Прочитано %d элементов:\n", banks->count);

    int index = 0;
    for (ONE *curr = banks->root; curr != NULL; curr = curr->next)
    {
        printf("index: %d\t element: %p\t(id: %s)\n", index, curr->bank, curr->bank->id);
        index++;
    }
    destroy_list(banks);
}

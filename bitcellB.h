#ifndef BIT_H
#define BIT_H

#define SIZE 0x4628190f // размер всех значений size (размер банковской ячейки), в каждом байте одно значение
#define MAXLVL 0x3      // максимальный уровень безопасности
#define REMOVE_CONST 8
#define INP 7 // количество полей структуры

typedef unsigned long ulg;

typedef enum masks
{
    ONEBIT_MASK = 0x1,
    TWOBIT_MASK = 0x3,
    FOURBIT_MASK = 0xf,
    DEF_MASK = 0xff,
    HEXBITMASK = 0xffff,
    INTMASK = 0xffffffff
} MASK;

typedef enum size
{
    low = SIZE & DEF_MASK,
    mid = (SIZE >> REMOVE_CONST) & DEF_MASK,
    high = (SIZE >> 2 * REMOVE_CONST) & DEF_MASK,
    large = (SIZE >> 3 * REMOVE_CONST) & DEF_MASK
} SIZ;

typedef enum safety
{
    veryhighlvl = MAXLVL & TWOBIT_MASK,
    highlvl = (MAXLVL >> 1) ^ TWOBIT_MASK,
    middlvl = (MAXLVL >> 1) & TWOBIT_MASK,
    lowlvl = (MAXLVL >> 2) & TWOBIT_MASK
} LVL;

typedef struct cellB
{
    uint id : 32;
    uint cost : 16;
    SIZ size : 8;
    uint period : 4;
    uint safety_lvl : 2;
    bool access_type : 1;
    bool video : 1;
} CELL;

/*Прототипы функций*/
void cellB_construct(ulg *cell, uint id, uint cost, uint size, uint period, uint s_lvl, bool video, bool ac_type);
void show_cellB(const ulg cell);
uint getrand(uint min, uint max);
ulg cellB_size(char user);
ulg safety_level(char user);
ulg yesno(void);
void cellB_init(ulg *cell, CELL *);
char *longtobits(ulg n, char *ps);
void set_onebit(ulg *cell, int remove);
void set_otherfields(ulg *cell, ulg mask, int remove, uint user);
void change_sets(ulg *, CELL *, char *, char *, int);
void strshow_cellB(const ulg cell);
void destroy_cell(CELL *cell);
CELL *def_cell_construct();
void cell_construct(CELL *cell, uint id, uint cost, SIZ size, uint period, uint safety_lvl, bool access_type, bool video);
void show_cellstruct(const CELL *cell);
char *structobits(CELL n, char *bitstr);

#endif
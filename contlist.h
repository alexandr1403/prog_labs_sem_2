#ifndef CONT_H_
#define CONT_H_
#include "aCash.h"

/*Узел*/
typedef struct one
{
    CASH *bank;
    struct one *prev, *next;
} ONE;

/*Список*/
typedef struct list
{
    ONE *root, *last;
    int count;
} SPIS;

typedef SPIS *LIST;

/*Итератор*/
typedef struct iterate
{
    LIST list;
    ONE *data;
} ITER;

/*Прототипы функций*/
LIST def_list_construct();
bool is_empty(LIST a);
void fpush(LIST a, CASH *bank);
void bpush(LIST a, CASH *bank);
CASH *fpop(LIST a);
CASH *bpop(LIST a);
void destroy_list(LIST a);
ONE *gbind_node(const LIST a, int index);
CASH *gbind_list(const LIST a, int index);
void insert_in_list(LIST a, CASH *bank, int index);
CASH *remove_from_list(LIST a, int index);
void clear_list(LIST a);
int size_list(LIST a);
void copy_list(const LIST a, LIST b);
LIST merge_list(LIST a, const LIST b);
int lookup_list(const LIST a, CASH *bank);
LIST reverse_list(LIST a);
void feach_list(LIST b, LIST a, int func);
void splice_list(LIST a, LIST b, int index);
ITER *iter_construct(LIST a);
void iter_destruct(ITER *a);
CASH *iter_root(ITER *a);
CASH *iter_last(ITER *a);
CASH *iter_next(ITER *a);
void show_list(LIST a);
void free_banks(LIST list);

#endif
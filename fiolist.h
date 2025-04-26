#ifndef FIO_H_
#define FIO_H_
#include "aCash.h"
#include "contlist.h"
#define COUNT 5

/*Прототипы функций*/
DATA *gen_data(time_t *i);
BNS *gen_bonus(time_t *i);
void gen_cellB(ulg *cell_1, CELL *cell_2, time_t *i);
char *gen_string(size_t len, time_t *seed);
double gen_balance(time_t *i);
CASH *gen_aCash(time_t *i);
CASH **rand_gen_aCash_mass(size_t n, time_t *seed);                                // возвращает массив указателей на n сгенерированных структур
size_t save_in_textfile(const char *filename, size_t n_mass, CASH **mass_structs); // сохраняет структуры в файл в обычном режиме
void free_mass_structs(CASH **mass, size_t n);
void save_one_struct_in_file(CASH *bank, FILE *fp);
CASH *load_from_file(FILE *p);
CASH **load_mass_structs_from_file(const char *filename);
CASH *get_element_from_text_file(const char *filename, int index);
void save_one_struct_in_binaryfile(FILE *fp, CASH *bank);
void save_in_binaryfile(const char *filename, size_t n_mass, CASH **mass_structs);
CASH *load_from_binfile(FILE *fp);
CASH **load_mass_structs_from_binfile(const char *filename);
CASH *get_element_from_binary_file(const char *filename, int index, size_t element_size);
LIST rand_gen_struct_in_container(size_t n);
void save_list_in_file(const char *filename, LIST a);
LIST load_list_from_file(const char *filename);
void demo_elem_from_list_from_file(const char *filename, int index);
void save_list_to_binfile(const char *filename, LIST a);
LIST load_list_from_binfile(const char *filename);

#endif
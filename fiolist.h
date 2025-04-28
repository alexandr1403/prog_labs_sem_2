#ifndef FIO_H_
#define FIO_H_
#include "aCash.h"
#include "contlist.h"
#define COUNT 5
#define TEXT 0
#define BIN 1

/*Прототипы функций*/
DATA *gen_data();
BNS *gen_bonus();
void gen_cellB(ulg *cell_1, CELL *cell_2);
char *gen_string(size_t len);
double gen_balance();
CASH *gen_aCash();
CASH **rand_gen_aCash_mass(size_t n);                                              // возвращает массив указателей на n сгенерированных структур
size_t save_in_textfile(const char *filename, size_t n_mass, CASH **mass_structs); // сохраняет структуры в файл в обычном режиме
void free_mass_structs(CASH **mass, size_t n);
void save_bonus_in_text(CASH *bank, FILE *fp);
void save_datas_in_text(CASH *bank, FILE *fp);
void save_cellstruct_in_text(CASH *bank, FILE *fp);
void save_one_struct_in_file(CASH *bank, FILE *fp);
void load_cellstruct_from_file(CASH *bank, FILE *fp);
void load_datas_from_file(CASH *bank, FILE *fp);
CASH *load_from_file(FILE *p);
CASH **load_mass_structs_from_file(const char *filename);
CASH *get_element_from_text_file(const char *filename, int index);
void save_one_struct_in_binaryfile(FILE *fp, CASH *bank);
void save_in_binaryfile(const char *filename, size_t n_mass, CASH **mass_structs);
CASH *load_from_binfile(FILE *fp);
CASH **load_mass_structs_from_binfile(const char *filename);
size_t aCash_size();
CASH *get_element_from_binary_file(const char *filename, int index, size_t element_size);
LIST rand_gen_struct_in_list(size_t n);
void save_list_in_file(const char *filename, LIST a);
LIST load_list_from_file(const char *filename);
void demo_elem_from_list_from_file(const char *filename, int index, int mode);
void save_list_to_binfile(const char *filename, LIST a);
LIST load_list_from_binfile(const char *filename);
void list_of_reading_elements(const char *filename, int mode);
void control_of_memory(void *ptr);

#endif
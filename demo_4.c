#include "fiolist.h"

int main(int argc, char const *argv[])
{
    if ((argc < 4) || (argc > 5))
    {
        puts("Неверный запуск программы. Ожидалось 3 либо 4 аргумента командной строки.");
        exit(EXIT_FAILURE);
    }
    if ((argc == 5) && (strcmp(argv[1], "get") == 0))
    {
        CASH *acc = NULL;
        if ((strcmp(argv[4], "-t") == 0))
        {
            acc = get_element_from_text_file(argv[3], atoi(argv[2]));
            show_info(acc, true);
            destroy_aCash(acc);
        }
        else if ((strcmp(argv[4], "-b") == 0))
        {
            acc = get_element_from_binary_file(argv[3], atoi(argv[2]), aCash_size());
            show_info(acc, true);
            destroy_aCash(acc);
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp("save", argv[1]) == 0)
    {
        CASH **banks = rand_gen_aCash_mass(COUNT);
        // for (int i = 0; i < COUNT; i++)
        // {
        //     show_info(banks[i], true);
        //     putchar('\n');
        // }
        if ((strcmp(argv[3], "-t") == 0))
        {
            save_in_textfile(argv[2], COUNT, banks);
            free_mass_structs(banks, COUNT);
        }
        else if ((strcmp(argv[3], "-b") == 0))
        {
            save_in_binaryfile(argv[2], COUNT, banks);
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp("load", argv[1]) == 0)
    {
        CASH **cash = NULL;
        if (strncmp("-t", argv[3], 2) == 0)
        {
            cash = load_mass_structs_from_file(argv[2]);
            show_info(cash[COUNT - 1], true);
            free_mass_structs(cash, COUNT);
        }
        else if (strncmp("-b", argv[3], 2) == 0)
        {
            cash = load_mass_structs_from_binfile(argv[2]);
            show_info(cash[COUNT - 1], true);
            free_mass_structs(cash, COUNT);
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp("list", argv[1]) == 0)
    {
        int text_mode;
        if (strcmp("-t", argv[3]) == 0)
            text_mode = 0;
        else if (strcmp("-b", argv[3]) == 0)
            text_mode = 1;
        else
            text_mode = -1;
        list_of_reading_elements(argv[2], text_mode);
    }
    else if (strcmp(argv[1], "cont") == 0)
    {
        if (strcmp(argv[3], "-t") == 0)
        {
            demo_elem_from_list_from_file(argv[2], 2, TEXT); // индекс передаётся через командную строку
        }
        else if (strcmp(argv[3], "-b") == 0)
        {
            demo_elem_from_list_from_file(argv[2], 2, BIN);
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Неверный запуск программы. Ожидался один из аргументов: save, load, list, get; получено: %s\n.", argv[2]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
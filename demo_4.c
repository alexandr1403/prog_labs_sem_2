#include "fiolist.h"

int main(int argc, char const *argv[])
{
    if ((argc < 4) && (argc > 6))
    {
        printf("Неверный запуск программы. Ожидалось от 3 до 5 аргументов командной строки, получено: %d\n", argc - 1);
        exit(EXIT_FAILURE);
    }
    if ((argc == 6) && (strcmp(argv[1], "get") == 0))
    {

        if ((strcmp(argv[5], "-t") == 0))
        {
            CASH *acc = NULL;
            if (strcmp(argv[3], "-m") == 0)
            {
                acc = get_element_from_text_file(argv[4], atoi(argv[2]));
                show_info(acc, true);
                destroy_aCash(acc);
            }
            else if (strcmp(argv[3], "-l") == 0)
            {
                demo_elem_from_list_from_file(argv[4], atoi(argv[2]), TEXT);
            }
            else
            {
                printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-m\" или \"-l\"?");
                exit(EXIT_FAILURE);
            }
        }
        else if ((strcmp(argv[5], "-b") == 0))
        {
            CASH *acc = NULL;
            if (strcmp(argv[3], "-m") == 0)
            {
                acc = get_element_from_binary_file(argv[4], atoi(argv[2]), aCash_size());
                show_info(acc, true);
                destroy_aCash(acc);
            }
            else if (strcmp(argv[3], "-l") == 0)
            {
                demo_elem_from_list_from_file(argv[4], atoi(argv[2]), BIN);
            }
            else
            {
                printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-m\" или \"-l\"?");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
    }
    else if ((argc == 5) && (strcmp("save", argv[1]) == 0))
    {
        LIST banks = rand_gen_struct_in_list(COUNT);
        CASH **mass_structs = rand_gen_aCash_mass(COUNT);
        // for (int i = 0; i < COUNT; i++)
        // {
        //     show_info(banks[i], true);
        //     putchar('\n');
        // }
        if ((strcmp(argv[4], "-t") == 0))
        {
            if (strcmp("-l", argv[2]) == 0)
            {
                save_list_in_file(argv[3], banks);
            }
            else if (strcmp("-m", argv[2]) == 0)
            {
                save_in_textfile(argv[3], COUNT, mass_structs);
            }
            else
            {
                printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-m\" или \"-l\"?");
                exit(EXIT_FAILURE);
            }
        }
        else if ((strcmp(argv[4], "-b") == 0))
        {
            if (strcmp("-l", argv[2]) == 0)
            {
                save_list_to_binfile(argv[3], banks);
            }
            else if (strcmp("-m", argv[2]) == 0)
            {
                save_in_binaryfile(argv[3], COUNT, mass_structs);
            }
            else
            {
                printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-m\" или \"-l\"?");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
        destroy_list(banks);
        free_mass_structs(mass_structs, COUNT);
    }
    else if ((argc == 5) && (strcmp("load", argv[1])) == 0)
    {
        LIST cash = NULL;
        CASH **mass = NULL;
        if (strcmp("-t", argv[4]) == 0)
        {
            if (strcmp("-l", argv[2]) == 0)
            {
                cash = load_list_from_file(argv[3]);
                show_info(cash->root->bank, true);
                destroy_list(cash);
            }
            else if (strcmp("-m", argv[2]) == 0)
            {
                mass = load_mass_structs_from_file(argv[3]);
                show_info(mass[0], true);
                free_mass_structs(mass, COUNT);
            }
            else
            {
                printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-m\" или \"-l\"?");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp("-b", argv[4]) == 0)
        {
            if (strcmp("-l", argv[2]) == 0)
            {
                cash = load_list_from_binfile(argv[3]);
                show_info(cash->root->bank, true);
                destroy_list(cash);
            }
            else if (strcmp("-m", argv[2]) == 0)
            {
                mass = load_mass_structs_from_binfile(argv[3]);
                show_info(mass[0], true);
                free_mass_structs(mass, COUNT);
            }
            else
            {
                printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-m\" или \"-l\"?");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Недопустимый запуск программы. Вероятно, Вы хотели ввести \"-b\" или \"-t\"?");
            exit(EXIT_FAILURE);
        }
    }
    else if ((argc == 4) && (strcmp("list", argv[1])) == 0)
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
    else
    {
        printf("Неверный запуск программы. Ожидался один из аргументов: save, load, list, get; получено: %s\n.", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
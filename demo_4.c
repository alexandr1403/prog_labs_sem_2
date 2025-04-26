#include "fiolist.h"

int main(int argc, char const *argv[])
{
    if (argc < 3)
        exit(EXIT_FAILURE);
    if ((argc == 4) && (strcmp(argv[1], "get") == 0))
    {
        CASH *acc = get_element_from_text_file(argv[3], atoi(argv[2]));
        show_info(acc, true);
        destructor(acc);
    }
    if (strcmp("save", argv[1]) == 0)
    {
        time_t seed = 123;

        CASH **banks = rand_gen_aCash_mass(COUNT, &seed);
        for (int i = 0; i < COUNT; i++)
        {
            show_info(banks[i], true);
            putchar('\n');
        }
        save_in_textfile(argv[2], COUNT, banks);
        free_mass_structs(banks, COUNT);
    }
    else if (strcmp("load", argv[1]) == 0)
    {
        CASH **cash = load_mass_structs_from_file(argv[2]);
        show_info(cash[COUNT - 1], true);
        free_mass_structs(cash, COUNT);
    }

    return 0;
}
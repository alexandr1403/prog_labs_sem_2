#include "contlist.h"

/*Создание пустого списка*/
LIST def_list_construct()
{
    LIST a = (LIST)malloc(sizeof(SPIS));
    if (control_of_NULL(a))
    {
        a->count = 0;
        a->root = NULL;
        a->last = NULL;
        return a;
    }
    else
        return NULL;
}

/*Проверка на пустоту*/
bool is_empty(LIST a)
{
    if (!control_of_NULL(a))
        return true;
    return ((a->count == 0)) ? true : false;
}

/*Добавление элемента в начало*/
void fpush(LIST a, CASH *bank)
{
    if (control_of_NULL(a) && control_of_NULL(bank))
    {
        ONE *new = (ONE *)malloc(sizeof(ONE));

        if (control_of_NULL(new))
        {
            new->bank = bank;
            new->prev = NULL;
            new->next = a->root;
            if (a->count == 0)
                a->last = new;
            else
                a->root->prev = new;
            a->root = new;

            a->count++;
        }
        else
            puts("Не удалось выделить память для добавления элемента.");
    }
    else
        puts("В функцию передан неверный аргумент.");
}

/*Добавление элемента в конец списка*/
void bpush(LIST a, CASH *bank)
{
    if (control_of_NULL(a) && control_of_NULL(bank))
    {
        ONE *current = a->last;
        ONE *new = (ONE *)malloc(sizeof(ONE));

        if (control_of_NULL(new))
        {
            new->bank = bank;
            new->prev = current;
            new->next = NULL;
            if (a->count == 0)
            {
                a->root = new;
                a->last = new;
            }
            else
            {
                a->last->next = new;
                a->last = new;
            }
            a->count++;
        }
        else
            puts("Не удалось выделить память для добавления элемента.");
    }
    else
        puts("В функцию передан неверный аргумент.");
}

/*Извлечение и удаление первого элемента списка*/
CASH *fpop(LIST a)
{
    if (!is_empty(a))
    {
        ONE *current = a->root;
        CASH *bank = current->bank;
        a->root = a->root->next;
        if (a->root == NULL)
            a->last = NULL;
        free(current);
        current = NULL;
        a->count--;
        return bank;
    }
    else
        puts("Не удалось удалить элемент.");
    return NULL;
}

/*Извлечение и удаление последнего элемента списка*/
CASH *bpop(LIST a)
{
    if (!is_empty(a))
    {
        ONE *current = a->root;
        ONE *prev = NULL;
        while (current && current->next)
        {
            prev = current;
            current = current->next;
        }
        CASH *bank = current->bank;
        if (prev)
        {
            prev->next = NULL;
            prev->prev = a->last->prev;
            a->last = prev;
        }
        else
        {
            a->root = NULL;
            a->last = NULL;
        }
        free(current);
        current = NULL;
        a->count--;
        return bank;
    }
    else
        puts("В списке нет элементов для удаления.");
    return NULL;
}

/*Освобождение памяти*/
void destroy_list(LIST a)
{
    if (!is_empty(a))
    {
        ONE *current = a->root;

        while (current)
        {
            ONE *temp = current;
            CASH *cbank = current->bank;
            current = current->next;
            destructor(cbank);
            free(temp);
        }
        a->count = 0;
    }
    free(a);
}

/*Доступ по индексу к узлу*/
ONE *gbind_node(LIST a, int index)
{

    if (is_empty(a) || index >= a->count)
        return NULL;
    else
    {
        ONE *current = a->root;

        for (int i = 0; i < (a->count) && current != NULL; i++)
        {
            if (i == index)
                return current;
            current = current->next;
        }
        return NULL;
    }
}

/*Доступ по индексу к элементу*/
CASH *gbind_list(LIST a, int index)
{
    if (index >= a->count || is_empty(a))
    {
        puts("В списке нет элемента по этому индексу.");
        return NULL;
    }
    else
    {
        ONE *current = gbind_node(a, index);
        return (current == NULL) ? NULL : (current->bank);
    }
}

/*Добавление элемента в список по индексу*/
void insert_in_list(LIST a, CASH *bank, int index)
{
    if (control_of_NULL(a) && control_of_NULL(bank))
    {
        if (index > a->count)
            puts("Нельзя добавить элемент по этому индексу.");

        else if (index != 0 && index != a->count)
        {
            ONE *insert = (ONE *)malloc(sizeof(ONE));

            insert->bank = bank;
            insert->prev = gbind_node(a, index - 1);
            insert->next = gbind_node(a, index);
            gbind_node(a, index)->prev = insert;
            gbind_node(a, index - 1)->next = insert;
            a->count++;
        }
        else
            (index == 0) ? fpush(a, bank) : bpush(a, bank);
    }
    else
        puts("В функцию передан неверный аргумент.");
}

/*Удаление элемента из списка по индексу*/
CASH *remove_from_list(LIST a, int index)
{
    if (index >= a->count || is_empty(a))
        puts("Нельзя удалить элемент по этому индексу.");
    else if (index != 0 && index != (a->count - 1))
    {
        ONE *remove = gbind_node(a, index);
        ONE *prev = gbind_node(a, index - 1);
        CASH *temp = remove->bank;
        if (prev)
            prev->next = gbind_node(a, index + 1);
        else
        {
            a->root = NULL;
            a->last = NULL;
        }
        free(remove);
        remove = NULL;

        a->count--;
        return temp;
    }
    else
        return (index == 0) ? fpop(a) : bpop(a);
    return NULL;
}

/*Очистка списка*/
void clear_list(LIST a)
{
    if (!is_empty(a))
    {
        for (ONE *current = a->root; current != NULL; current = current->next)
            free(current);
        a->count = 0;
        a->root = NULL;
        a->last = NULL;
        puts("Список очищен.");
    }
    else
        puts("Нечего очищать: список пуст.");
}

/*Возврат текущего размера списка*/
int size_list(LIST a)
{
    if (control_of_NULL(a))
        return a->count;
    else
        return 0;
}

/*Демонстрация списка*/
void show_list(LIST a)
{
    if (control_of_NULL(a))
        if (!is_empty(a))
        {
            printf("Размер списка: %d\n", size_list(a));
            for (int i = 0; i < a->count; i++)
            {
                show_balance(gbind_list(a, i), true);
                // show_info(gbind_list(a, i), true);
                // putchar('\n');
            }
            putchar('\n');
        }
        else
            puts("Список пуст.");
    else
        puts("Списка не существует.");
}

/*Копирование списка*/
void copy_list(LIST a, LIST b)
{
    if (control_of_NULL(a) && control_of_NULL(b))
    {
        if (!is_empty(b))
        {
            clear_list(b);
        }
        ONE *curr = a->root;

        for (int i = 0; curr != NULL; curr = curr->next, i++)
        {
            CASH *temp = curr->bank;
            insert_in_list(b, temp, i);
        }
    }
}

/*Слияние списков*/
LIST merge_list(const LIST a, const LIST b)
{
    if (control_of_NULL(a) && control_of_NULL(b))
    {
        LIST c = def_list_construct();
        if (control_of_NULL(c))
        {
            copy_list(a, c);
            ONE *curr = b->root;

            for (int i = c->count; curr != NULL; curr = curr->next, i++)
            {
                CASH *temp = curr->bank;
                insert_in_list(c, temp, i);
            }
            return c;
        }
        else
        {
            puts("Не удалось произвести слияние списков.");
            return NULL;
        }
    }
    else
        return NULL;
}

/*Возврат позиции в списке (поиск по значению)*/
int lookup_list(LIST a, CASH *bank)
{
    if (control_of_NULL(a))
    {
        ONE *current = a->root;
        for (int i = 0; i < a->count; i++)
        {
            if (current->bank == bank)
                return i;
            current = current->next;
        }
    }
    puts("В списке нет такого элемента.");
    return -1;
}

/*Создание итератора списка*/
ITER *iter_construct(LIST a)
{
    if (!is_empty(a))
    {
        ITER *iter = malloc(sizeof(ITER));
        if (iter == NULL)
            return NULL;
        iter->list = a;
        iter->data = a->root;
        return iter;
    }
    else
        return NULL;
}

/*Очистка итератора*/
void iter_destruct(ITER *a)
{
    if (control_of_NULL(a))
    {
        a->data = NULL;
        a->list = NULL;
        free(a);
    }
}

/*Возврат первой позиции в списке*/
CASH *iter_root(ITER *a)
{
    if (control_of_NULL(a))
        if (!is_empty(a->list))
        {
            a->data = a->list->root;
            return a->data->bank;
        }

    return NULL;
}

/*Возврат заключительной позиции в списке*/
CASH *iter_last(ITER *a)
{
    if (control_of_NULL(a))
        if (!is_empty(a->list))
        {
            a->data = a->list->last;
            return a->data->bank;
        }
    return NULL;
}

/*Возврат следующей позиции в списке*/
CASH *iter_next(ITER *iter)
{
    if (iter == NULL || iter->data == NULL)
    {
        puts("Список закончился.");
        return NULL;
    }
    iter->data = iter->data->next;
    if (iter->data == NULL)
    {
        puts("Список закончился");
        return NULL;
    }
    return iter->data->bank;
}

/*Перебор с применением функции*/
void feach_list(LIST supp, LIST a, int func)
{
    if (!is_empty(a))
    {
        ONE *current = a->root;
        int i = 0;
        while (current)
        {
            CASH *bank = default_construct();
            copy_aCash(bank, current->bank);

            support_user(bank, func);
            fpush(supp, bank);
            insert_in_list(a, bank, i);
            remove_from_list(a, i + 1);

            current = current->next;
            i++;

            putchar('\n');
        }
    }
    else
        puts("Перебор невозможен.");
}

/*Реверсирование списка*/
LIST reverse_list(const LIST a)
{
    if (!is_empty(a))
    {
        LIST b = def_list_construct();

        ONE *temp = a->last;
        CASH *bank;

        while (temp != NULL)
        {
            bank = temp->bank;
            bpush(b, bank);
            temp = temp->prev;
        }
        return b;
    }
    else
        return NULL;
}

/*Вставка списка в список по индексу*/
void splice_list(LIST a, LIST b, int index) // вставляем b в a
{
    if (!is_empty(a) && !is_empty(b))
    {
        if (index > a->count)
            puts("Не удалось вставить список.");
        else if (index != a->count && index != 0)
        {
            ONE *insert = b->root;
            for (int i = index; insert != NULL; insert = insert->next, i++)
            {
                CASH *bank = insert->bank;
                insert_in_list(a, bank, i);
            }
        }
        else
        {
            LIST c = (index == 0) ? (merge_list(b, a)) : (merge_list(a, b));
            // show_list(c);
            copy_list(c, a);
            destroy_list(c);
        }
    }
    else
        puts("Вставка невозможна.");
}

/*Очистка всех элементов списка*/
void free_banks(LIST list)
{
    if (!is_empty(list))
    {
        CASH *bank = list->root->bank;
        for (int i = 1; bank != NULL && i < list->count; i++)
        {
            destructor(bank);
            bank = gbind_list(list, i);
        }
        bank = list->last->bank;
        destructor(bank);
    }
}

#include "infoaccs.h"

/*Функция, определяющая, является ли пользователь владельцем счёта*/
int isowner(char x, int pin)
{
    uint user;
    char att;

    if (x == 'y')
    {
        printf("Введите ПИН-код: ");
        if (scanf("%d", &user) == EOF)
            return -1;
        if (user == (uint)pin)
        {
            return 1;
        }
        else
        {
            printf("Вы ввели неверный ПИН-код. Доступ к карте заблокирован. Программа завершена.\n");
            return -1;
        }
    }
    else if (x == 'n')
    {
        printf("\nХорошо, выберите нужную опцию из списка.\n");
        return 0;
    }
    else
    {
        printf("Нажмите \"y\", если Вы владелец карты, и \"n\", если нет: ");
        if (scanf("\n%c", &att) == EOF)
            return -1;
        return (isowner(att, pin));
    }
}

/*Функция для действий не владельца карты*/
int if_not_owner(CASH *bank)
{
    int user;

    printf("Вы можете:\n1. Посмотреть баланс\n2. Показать информацию по счёту\n3. Выход\nВыберите действие: ");
    if (scanf("%d", &user) == EOF)
        return -1;

    while (user > 0 && user < 3)
    {

        switch (user)
        {
        case 1:
        {
            show_balance(bank, false);
            break;
        }
        case 2:
        {
            show_info(bank, false);
            break;
        }
        }

        printf("\nЕсли Вы хотите продолжить работу с программой, выберите пункт из меню.\nВы можете:\n1. Посмотреть баланс\n2. Показать информацию по счёту\n3. Выход\nВыберите действие: ");
        if (scanf("%d", &user) == EOF)
            return 0;
    }
    if (user > 3)
    {
        printf("Ошибка выбора\n");
        return 1;
    }
    else
    {
        printf("Работа с картой завершена.\n");
        return 1;
    }
}

/* Функция для операций владельцу счёта*/
int ifowner(CASH *bank, CASH *acc)
{
    // CARD x = translatetoint(strlen(bank->type), bank->type);
    int user;
    double up_bank = 0;
    double down_bank = 0;
    double up_acc = 0;
    printf("Вы можете:\n1. Пополнить карту\n2. Снять наличные\n3. Посмотреть баланс\n4. Перевести деньги\n5. Совершить покупку\n6. Показать информацию по счёту\n7. Сравнить счета\n8. Расчёт списаний и накоплений\n9. Проверка закрытия счёта\n10. Выход\nВыберите действие: ");
    if (scanf("%d", &user) == EOF)
        return 0;

    while (user < 10 && user > 0)
    {
        switch (user)
        {
        case 1:
        {
            double sum;
            printf("Введите сумму пополнения (в рублях): ");

            if (scanf("\n%lf", &sum) == EOF)
                return 0;
            if (sum < 0)
                sum *= (-1);

            up_bank += addition(bank, (sum / (translatetoint(bank->val))));
            printf("Теперь на счету лежит %.2f %s\n", bank->balance, bank->val);
            break;
        }
        case 2:
        {
            double sum;
            printf("Сколько денег Вы хотите снять? (введите сумму в рублях): ");
            if (scanf("\n%lf", &sum) == EOF)
                return 0;
            if (sum < 0)
                sum *= (-1);
            down_bank += payment(bank, sum, 0);
            show_balance(bank, true);
            break;
        }
        case 3:
        {
            show_balance(bank, true);
            break;
        }
        case 4:
        {
            if (bank != NULL && acc != NULL)
            {
                double sum;
                printf("Введите сумму перевода (в рублях): ");
                if (scanf("\n%lf", &sum) == EOF)
                    return 0;

                down_bank += transfer(bank, acc, sum);
                up_acc += (sum * translatetoint(acc->val));
                show_balance(bank, true);
            }
            else
            {
                printf("Перевод невозможен - недостаточно информации о счетах.\n");
            }
            break;
        }
        case 5:
        {
            double sum;
            char quest;

            printf("Хотите потратить бонусы на покупку?(y/n) ");
            if (scanf("\n%c", &quest) == EOF)
                return 0;

            printf("Введите стоимость покупки (в рублях): ");
            if (scanf("\n%lf", &sum) == EOF)
                return 0;
            if (sum < 0)
                sum *= (-1);

            if (quest == 'n')
            {
                down_bank += payment(bank, sum, 0);
            }
            else if (quest == 'y')
            {
                if (bank->bonus->bonuses > 0)
                {
                    // функция оплаты бонусами
                    down_bank += usebons(bank, sum);
                }
                else
                {
                    printf("Нет бонусов\n");
                    down_bank += payment(bank, sum, 0);
                }
            }
            else
            {
                printf("Неверный выбор.\n");
            }
            show_balance(bank, true);
            break;
        }
        case 6:
        {
            int x;
            printf("Выберите формат представления данных. 1 - в строку, 2 - в стоблец: ");
            if (scanf("\n%d", &x) == EOF)
                return 0;
            while (x < 1 || x > 2)
            {
                printf("Ошибка выбора. Попробуйте ещё раз: ");
                if (scanf("\n%d", &x) == EOF)
                    return 0;
            }

            if (x == 1)
                show_str(bank);
            else
                show_info(bank, true);
            break;
        }
        case 7:
        {
            if (!comparison_accs(bank, acc))
                return 0;
            break;
        }
        case 8:
        {
            division(up_bank * translatetoint(bank->val), down_bank, bank->val); // так как addition возвращает значение в валюте счёта (up_bank), а функции списания - в рублях (down_bank)
            break;
        }
        case 9:
        {
            int mon, day;
            uint year;
            printf("Введите дату, в которой хотели бы посмотреть, закрыт ли счёт (в формате ДД.ММ.ГГГГ): ");
            if (scanf("\n%d.%d.%d", &day, &mon, &year) == EOF)
                return 0;

            if (!isopen(bank, year, mon, day))
            {
                printf("Счёт в указанной дате ещё не был открыт\n");
            }
            else
            {
                if (isclose(bank, year, mon, day))
                {
                    printf("Счёт закрыт\n");
                }
                else
                {
                    printf("Счёт не закрыт\n");
                }
            }
            break;
        }
        }

        printf("\nЕсли Вы хотите продолжить работу с программой, выберите пункт из меню.\nВы можете:\n1. Пополнить карту\n2. Снять наличные\n3. Посмотреть баланс\n4. Перевести деньги\n5. Совершить покупку\n6. Показать информацию по счёту\n7. Сравнить счета\n8. Расчёт списаний и накоплений\n9. Проверка закрытия счёта\n10. Выход\nВыберите действие: ");
        if (scanf("%d", &user) == EOF)
            return 0;
    }
    if (user > 10)
    {
        printf("Ошибка выбора\n");
        return 1;
    }
    else
    {
        printf("Работа с картой завершена.\n");
        return 1;
    }
}

/*Функция для выбора опций*/
int choose(CASH *bank, CASH *acc)
{
    char account;
    printf("Внесение в базу данных информации по счетам. Необходимо согласие на обработку персональных данных.\nЯ согласен(-cна) (y/n): ");
    if (scanf("%c", &account) == EOF)
        return 0;

    while (account != 'y' && account != 'n')
    {
        printf("Ошибка выбора. Попробуйте ещё раз: ");
        if (scanf("\n%c", &account) == EOF)
            return 0;
    }

    switch (account)
    {
    case 'y':
    {
        // input_info(bank);
        // input_info(acc);
        construct(bank, id_bank, num_bank, val_bank, type_bank, bal_bank, open_year_bank, open_day_bank, open_month_bank, bonus_bank, bonpay, bonpadd, id_acell, cost_acell, size_acell, period_acell, safety_acell, video_acell, access_acell);

        construct(acc, id_acc, num_acc, val_acc, type_acc, bal_acc, open_year_acc, open_day_acc, open_month_acc, bonus_acc, bonpay, bonpadd, id_bcell, cost_bcell, size_bcell, period_bcell, safety_bcell, video_bcell, access_bcell);

        break;
    }
    case 'n':
    {
        printf("Программа завершена.\n");
        return 0;
    }
    }

    int wichcard;
    bool contin = true;
    while (contin == true)
    {
        printf("Выберите карту для продолжения работы: 1 - A_Bank, 2 - B_Bank: ");
        if (scanf("\n%d", &wichcard) == EOF)
            return 0;

        while (wichcard < 1 || wichcard > 2)
        {
            printf("Вы не выбрали карту.\nПопробуйте ещё раз: ");
            if (scanf("\n%d", &wichcard) == EOF)
                return 0;
        }

        printf("Вы владелец этой карты? (y/n): ");
        char user;
        // user = getchar();
        if (scanf("\n%c", &user) == EOF)
            return 0;

        switch (wichcard)
        {
        case 1:
        {
            int owner = isowner(user, PIN_BANK);
            if (owner == -1)
                return 0;
            else if (owner == 1)
            {
                if (!ifowner(bank, acc))
                    return 0;
            }
            else if (owner == 0)
            {
                if (!if_not_owner(bank))
                    return 0;
            }
            break;
        }
        case 2:
        {
            int owner = isowner(user, PIN_ACC);
            if (owner == -1)
                return 0;
            else if (owner == 1)
            {
                if (!ifowner(acc, bank))
                    return 0;
            }
            else if (owner == 0)
            {
                if (!if_not_owner(acc))
                    return 0;
            }
            break;
        }
        default:
        {
            printf("Вы не выбрали карту.\n");
            break;
        }
        }
        printf("\nВы хотите продолжить работу? (y/n) ");
        char yesno;
        if (scanf("\n%c", &yesno) == EOF)
            return 0;

        while (yesno != 'y' && yesno != 'n')
        {
            printf("Ошибка ввода. Попробуйте ещё раз: ");
            if (scanf("\n%c", &yesno) == EOF)
                return 0;
        }

        if (yesno == 'y')
            contin = true;
        else
            contin = false;
    }
    printf("Программа завершена.\n");
    return 1;
}

void support_user(CASH *bank, int user)
{
    double up_bank = 0;
    double down_bank = 0;
    switch (user)
    {
    case 1:
    {
        double sum = 1000.0;
        show_balance(bank, true);
        printf("Пополнение на %.2lf рублей (%.2lf %s)\n", sum, sum / translatetoint(bank->val), bank->val);
        up_bank += addition(bank, (sum / (translatetoint(bank->val))));
        printf("Теперь на счету лежит %.2lf %s\n", bank->balance, bank->val);
        break;
    }
    case 2:
    {
        show_balance(bank, true);
        double sum = 100.0;
        down_bank += payment(bank, sum, 0);
        printf("Снято %.2lf рублей (%.2lf %s)\n", sum, sum / (translatetoint(bank->val)), bank->val);
        show_balance(bank, true);
        break;
    }
    case 3:
    {
        show_balance(bank, true);
        break;
    }
    case 4:
    {
        show_balance(bank, true);
        double sum = 1500.0;
        char quest = 'y';

        printf("Покупка на сумму: %.2lf рублей (%.2lf %s)\n", sum, sum / translatetoint(bank->val), bank->val);
        if (quest == 'n')
        {
            down_bank += payment(bank, sum, 0);
        }
        else if (quest == 'y')
        {
            if (bank->bonus->bonuses > 0)
            {
                int temp = bank->bonus->bonuses;
                down_bank += usebons(bank, sum);
                printf("Бонусов использовано: %d\n", temp - bank->bonus->bonuses);
            }
            else
            {
                printf("Нет бонусов\n");
                down_bank += payment(bank, sum, 0);
            }
        }
        else
        {
            printf("Неверный выбор.\n");
        }
        show_balance(bank, true);
        break;
    }
    case 5:
    {
        show_info(bank, true);
        break;
    }
    case 6:
    {
        int mon = 3;
        int day = 22;
        uint year = 2025;

        if (!isopen(bank, year, mon, day))
        {
            printf("Счёт в указанной дате ещё не был открыт\n");
        }
        else
        {
            if (isclose(bank, year, mon, day))
            {
                printf("Счёт закрыт\n");
            }
            else
            {
                printf("Счёт не закрыт\n");
            }
        }
        break;
    }
    }

    if (user > 6 || user < 1)
    {
        printf("Ошибка выбора\n");
    }
}

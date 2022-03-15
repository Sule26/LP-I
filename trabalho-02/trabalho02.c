#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct order
{
    char name[50];
    int code;
    unsigned short quantity;
    double price;
    struct order *next;
} order;

typedef struct order_list
{
    struct order *head;
    unsigned short size;
} order_list;

typedef struct table
{
    unsigned short number;
    int waiter_code;
    struct table *next;
    struct table *prev;
    struct order_list *requests;
    double requests_price;
} table;

typedef struct table_list
{
    struct table *head;
    unsigned short size;
} table_list;

typedef struct foods
{
    char name[50];
    int code;
    double price;
} foods;

typedef struct waiter
{
    char name[50];
    int code;
} waiter;

// começar a lista
void start_table_list(table_list *list)
{
    list->head = NULL;
    list->size = 0;
}

void start_order_list(order_list *list)
{
    list->head = NULL;
    list->size = 0;
}

// começar os nós
void start_table(table *node)
{
    node->number = 0;
    node->waiter_code = 0;
    node->requests_price = 0;
    node->requests = NULL;
    node->next = NULL;
    node->prev = NULL;
}

void start_order(order *node)
{
    node->code = 0;
    node->quantity = 0;
    node->price = 0;
    node->next = NULL;
}

// inserir
void insert_table_sorted(table_list *list, table *node)
{
    table *aux, *new = malloc(sizeof(table));
    if (new){
        memcpy(new, node, sizeof(table));
        if (list->head == NULL)
        {
            new->next = NULL;
            new->prev = NULL;
            list->head = new;
        }
        else if (new->number < list->head->number)
        {
            new->next = list->head;
            new->prev = NULL;
            list->head->prev = NULL;
            list->head = new;
        }
        else
        {
            aux = list->head;
            while (aux->next != NULL && new->number > aux->next->number)
                aux = aux->next;
            new->next = aux->next;
            if (aux->next != NULL)
                aux->next->prev = new;
            new->prev = aux;
            aux->next = new;
        }
        list->size++;
    }
    else
        printf("\nErro ao alocar memoria!");
}

void insert_order(order_list *list, order *node)
{

    order *aux = malloc(sizeof(order));

    node->next = NULL;
    // é o primeiro?
    if (list->head == NULL)
        list->head = node;
    else
    {
        aux = list->head;
        while (aux->next)
            aux = aux->next;
        aux->next = node;
    }
    list->size++;
}

// mostrar
void show_table(table_list list)
{

    table *current_table = list.head;
    order_list *aux;
    printf("\n-------------------------------------------------------\n");
    printf("Todas as %hu mesas: ", list.size);
    printf("\n-------------------------------------------------------\n");
    while (current_table)
    {
        printf("\nMesa: %hu\nCodigo do garcom: %d\nPreco a pagar: R$%.2lf\n", current_table->number, current_table->waiter_code, current_table->requests_price);
        printf("\nTodos os pedidos da mesa %hu:", current_table->number);
        aux = current_table->requests->head;
        show_order(&current_table->requests);
        current_table = current_table->next;
        printf("\n-------------------------------------------------------\n");
    }
}

void show_order(order_list *list)
{
    order *current_order = list->head;
    while (current_order)
    {
        printf("\n\tNome: %s\n\tCodigo: %d\n\tQuantidade: %hu\n\tPreco total: R$%.2lf\n", current_order->name, current_order->code, current_order->quantity, current_order->price);
        current_order = current_order->next;
    }
}

void show_table_number(table_list list)
{
    table *node = list.head;
    printf("\nNumero das %d mesas disponiveis: ", list.size);
    while (node)
    {
        printf("%d ", node->number);
        node = node->next;
    }
}

void show_specific_table(table_list list, int number)
{
    table *current_table = list.head;
    order_list *aux;
    while (current_table->number != number)
        current_table = current_table->next;
    printf("\n-------------------------------------------------------\n");
    printf("\nMesa: %hu\nCodigo do garcom: %d\nPreco a pagar: R$%.2lf\n", current_table->number, current_table->waiter_code, current_table->requests_price);
    printf("\nTodos os pedidos da mesa %hu", current_table->number);
    aux = current_table->requests->head;
    show_order(&current_table->requests);
    printf("\n-------------------------------------------------------\n");
}

// buscar
int search_number_table(table_list *list, int number)
{

    table *aux, *node = NULL;
    aux = list->head;
    while (aux && aux->number != number)
        aux = aux->next;
    if (aux)
        return 0;

    return 1;
}

// remover
void remove_table(table_list *list, int number)
{
    table *aux, *remove = NULL;
    if (list->head)
    {
        if (list->head->number == number)
        {
            remove = list->head;
            list->head = remove->next;
            if (list->head)
                list->head->prev = NULL;
        }
        else
        {
            aux = list->head;
            while (aux->next && aux->next->number != number)
                aux = aux->next;
            if (aux->next)
            {
                remove = aux->next;
                aux->next = remove->next;
                if (aux->next)
                    aux->next->prev = aux;
            }
        }
        list->size--;
    }
    free(remove);
}

// remover e inserir novamente
void remove_table_and_insert_again(table_list *list, int number, int new_number)
{

    table *aux, *new = NULL;
    if (list->head)
    {
        if (list->head->number == number)
        {
            new = list->head;
            list->head = new->next;
            if (list->head)
                list->head->prev = NULL;
        }
        else
        {
            aux = list->head;
            while (aux->next && aux->next->number != number)
                aux = aux->next;
            if (aux->next)
            {
                new = aux->next;
                aux->next = new->next;
                if (aux->next)
                    aux->next->prev = aux;
            }
        }
    }

    new->number = new_number;

    if (list->head == NULL)
    {
        new->next = NULL;
        new->prev = NULL;
        list->head = new;
    }
    else if (new->number < list->head->number)
    {
        new->next = list->head;
        new->prev = NULL;
        list->head->prev = NULL;
        list->head = new;
    }
    else
    {
        aux = list->head;
        while (aux->next != NULL && new->number > aux->next->number)
            aux = aux->next;
        new->next = aux->next;
        if (aux->next != NULL)
            aux->next->prev = new;
        new->prev = aux;
        aux->next = new;
    }
}

// pegar
table *get_table(table_list *list, int number)
{
    table *aux = list->head;
    while (aux && aux->number != number)
        aux = aux->next;
    if (aux)
        return aux;
}

order *get_order(order_list *list, int number)
{

    order *aux = list->head;
    if (number == 1)
        return aux;
    else
    {
        for (int i = 0; i < number - 1; i++)
            aux = aux->next;
        return aux;
    }
}
int main()
{

    char *menuFile = "Menu.bin";
    char *waiterFile = "Waiter.bin";

    foods menu[100] = {{
                           "Contra file",
                           1,
                           17,
                       },
                       {
                           "Contra file com queijo branco",
                           2,
                           21,
                       },
                       {
                           "Contra file empanado",
                           3,
                           19,
                       },
                       {
                           "Bife a cavalo",
                           4,
                           19,
                       },
                       {
                           "Chuleta",
                           5,
                           20,
                       },
                       {
                           "File mignon a parmegiana",
                           6,
                           27,
                       },
                       {
                           "File mignon grelhado",
                           7,
                           24,
                       },
                       {
                           "File mignon com queijo branco",
                           8,
                           26,
                       },
                       {
                           "File mignon a cavalo",
                           9,
                           26,
                       },
                       {
                           "Picanha a brasileira",
                           10,
                           27,
                       },
                       {
                           "File de frango",
                           11,
                           16,
                       },
                       {
                           "File de frango a cavalo",
                           12,
                           18,
                       },
                       {
                           "File de frango com queijo branco",
                           13,
                           20,
                       },
                       {
                           "File de frango empanado",
                           14,
                           18,
                       },
                       {
                           "File de frango a parmegiana",
                           15,
                           25,
                       },
                       {
                           "Bisteca de porco",
                           16,
                           16,
                       },
                       {
                           "Costelinha de porco",
                           17,
                           18,
                       },
                       {
                           "Costelinha de porco frita com molho barbecue",
                           18,
                           21,
                       },
                       {
                           "Omelete",
                           19,
                           18,
                       },
                       {
                           "Omelete recheado com batata",
                           20,
                           20,
                       },
                       {
                           "Calabresa acebolada",
                           21,
                           16,
                       },
                       {
                           "Salada",
                           22,
                           10,
                       },
                       {
                           "Agua mineral sem gas",
                           101,
                           4.5,
                       },
                       {
                           "Agua mineral com gas",
                           102,
                           4.5,
                       },
                       {
                           "Agua tonica",
                           103,
                           5,
                       },
                       {
                           "Suco integral (Laranja/Uva/Morango/Limao)",
                           104,
                           7.5,
                       },
                       {
                           "Refrigerante",
                           105,
                           7.5,
                       },
                       {
                           "Jack  Daniel's",
                           106,
                           20.5,
                       },
                       {
                           "Johnnie Walker Black",
                           107,
                           23,
                       },
                       {
                           "Johnnie Walker Red Label",
                           108,
                           19.5,
                       },
                       {
                           "Vodka Smirnoff",
                           109,
                           11.5,
                       },
                       {
                           "Dose Cachaca",
                           110,
                           4.5,
                       },
                       {
                           "Margarita",
                           111,
                           17.5,
                       },
                       {"Whiskey Sour", 112, 26}};

    waiter waiters[100] = {{
                               "Lucas",
                               101,
                           },
                           {
                               "Marcos",
                               102,
                           },
                           {
                               "Daniel",
                               103,
                           },
                           {
                               "Leonardo",
                               104,
                           },
                           {
                               "Bruno",
                               105,
                           },
                           {
                               "Leticia",
                               106,
                           },
                           {
                               "Jhonathan",
                               107,
                           },
                           {
                               "Agatha",
                               108,
                           },
                           {
                               "Paulo",
                               109,
                           },
                           {"Fellipe", 110}};

    unsigned short menu_index = 34;
    unsigned short waiters_index = 10;
    unsigned short position_chosen, waiter_chosen, food_chosen, quantity, c, number_to_test, code_equal, number_equal;
    unsigned short current;
    int code_to_test, option, option2, option3, option4, option5;

    foods menuReader[100];
    waiter waitersReader[100];

    table *current_table;
    order *current_order;
    table *table_chosen;
    order *order_chosen;

    table_list list_of_tables;

    start_table_list(&list_of_tables);

    FILE *fwaiter, *fmenu;

    fmenu = fopen(menuFile, "wb");
    if (fmenu == NULL)
    {
        printf("Erro na abertura!\n");
        system("Pause");
        return 1;
    }

    fwrite(&menu, sizeof(foods), menu_index, fmenu);
    fclose(fmenu);

    fwaiter = fopen(waiterFile, "wb");
    if (fwaiter == NULL)
    {
        printf("Erro na abertura!\n");
        system("Pause");
        return 1;
    }

    fwrite(&waiters, sizeof(waiter), waiters_index, fwaiter);
    fclose(fwaiter);

    do
    {

        printf("\nO que voce deseja fazer?");
        printf("\n[1] Adicionar uma mesa");
        printf("\n[2] Alterar informacoes de uma mesa");
        printf("\n[3] Fechar a conta de uma mesa");
        printf("\n[4] Consultar todas as mesas");
        printf("\n[5] Inserir algo no cardapio");
        printf("\n[6] Apagar algo do cardapio");
        printf("\n[7] Alterar algo no cardapio");
        printf("\n[8] Mostrar o cardapio");
        printf("\n[9] Adicionar um garcom");
        printf("\n[10] Excluir um garcom");
        printf("\n[11] Alterar informacoes sobre um garcom");
        printf("\n[12] Mostrar todos os garcons");
        printf("\n[13] Finalizar");
        printf("\nEscolha: ");
        scanf("%d", &option);
        switch (option)
        {

        case 1:

            current_table = malloc(sizeof(table));
            start_table(&current_table);
            start_order(&current_order);

            start_order_list(&current_table->requests);

            do
            {
                printf("\nNumero da mesa: ");
                scanf("%hu", &number_to_test);
                number_equal = 0;
                if (search_number_table(&list_of_tables, number_to_test) == 1)
                {
                    printf("\nNumero disponivel!");
                }
                else
                {
                    printf("Numero indisponivel! Tente novamente...\n");
                    number_equal++;
                }
            } while (number_equal);

            current_table->number = number_to_test;

            fwaiter = fopen(waiterFile, "rb");
            if (fwaiter == NULL)
            {
                printf("Erro na abertura!\n");
                system("Pause");
                return 1;
            }
            do
            {
                printf("\nGarcom: ");
                for (int i = 0; i < waiters_index; i++)
                {
                    fseek(fwaiter, i * sizeof(struct waiter), SEEK_SET);
                    fread(&waitersReader, sizeof(struct waiter), waiters_index, fwaiter);
                    printf("\n[%d] %s", i + 1, waitersReader->name);
                }
                printf("\nEscolha: ");
                scanf("%d", &option2);
                option2--;
                if (option2 < 0 || option2 > waiters_index - 1)
                    printf("Opcao invalida! Tente novamente...\n");
            } while (option2 < 0 || option2 > waiters_index - 1);

            rewind(fwaiter);
            fseek(fwaiter, (option2) * sizeof(waiter), SEEK_SET);
            fread(&waitersReader, sizeof(waiter), waiters_index, fwaiter);
            current_table->waiter_code = waitersReader->code;
            fclose(fwaiter);

            fmenu = fopen(menuFile, "rb");
            if (fmenu == NULL)
            {
                printf("Erro na abertura!\n");
                system("Pause");
                return 1;
            }
            current_table->requests_price = 0;
            do
            {
                option3 = 0;
                do
                {
                    current_order = malloc(sizeof(order));
                    printf("\nO que voce deseja?");
                    printf("\nMenu: ");
                    for (int i = 0; i < menu_index; i++)
                    {
                        fseek(fmenu, i * sizeof(struct foods), SEEK_SET);
                        fread(&menuReader, sizeof(struct foods), waiters_index, fwaiter);
                        printf("\n[%d]\t%s - R$%.lf", i + 1, menuReader->name, menuReader->price);
                    }
                    printf("\nEscolha: ");
                    scanf("%d", &option2);
                    option2--;
                    if (option2 < 0 || option2 > menu_index - 1)
                        printf("Opcao invalida! Tente novamente...\n");
                } while (option2 < 0 || option2 > menu_index - 1);
                rewind(fmenu);
                fseek(fmenu, (option2) * sizeof(struct foods), SEEK_SET);
                fread(&menuReader, sizeof(struct foods), menu_index, fmenu);
                strcpy(current_order->name, menuReader->name);
                current_order->code = menuReader->code;
                printf("\nPreco: %.2lf", menuReader->price);
                printf("\nQuantidade: ");
                scanf("%hu", &current_order->quantity);
                current_order->price = menuReader->price * current_order->quantity;
                current_table->requests_price += current_order->price;
                printf("\nPreco total: %.2lf", current_order->price);

                insert_order(&current_table->requests, current_order);

                printf("\nVoce deseja acrescentar mais pedidos?");
                printf("\n[1] Sim!");
                printf("\n[2] Nao!");
                printf("\nEscolha: ");
                scanf("%d", &option3);

            } while (option3 != 2);
            fclose(fmenu);

            insert_table_sorted(&list_of_tables, current_table);

            break;

        case 2:

            if (list_of_tables.size != 0)
            {

                show_table_number(list_of_tables);
                do
                {
                    printf("\nVoce quer alterar qual mesa? ");
                    scanf("%hu", &number_to_test);
                    number_equal = 0;
                    if (search_number_table(&list_of_tables, number_to_test) == 0)
                    {
                        printf("\nNumero disponivel!");
                    }
                    else
                    {
                        printf("Numero indisponivel! Tente novamente...\n");
                        number_equal++;
                    }
                } while (number_equal);

                show_specific_table(list_of_tables, number_to_test);
                table_chosen = get_table(&list_of_tables, number_to_test);

                printf("\nO que voce deseja alterar na mesa %d", number_to_test);
                printf("\n[1] Numero da mesa");
                printf("\n[2] Codigo do garcom");
                printf("\n[3] Modificar lista de pedidos");
                printf("\n[4] Acrescentar pratos na lista de pedidos");
                printf("\n[5] Finalizar");
                printf("\nEscolha: ");
                scanf("%d", &option2);
                switch (option2)
                {
                case 1:
                    do
                    {
                        printf("\nNovo numero da mesa: ");
                        scanf("%hu", &number_to_test);
                        number_equal = 0;
                        if (search_number_table(&list_of_tables, number_to_test) == 1)
                        {
                            printf("\nNumero disponivel!");
                        }
                        else
                        {
                            printf("\nNumero indisponivel! Tente novamente...\n");
                            number_equal++;
                        }
                    } while (number_equal);
                    remove_table_and_insert_again(&list_of_tables, table_chosen->number, number_to_test);

                    printf("\nMudanca feita com sucesso!\n");
                    break;

                case 2:
                    printf("\nNovo codigo do garcom: ");
                    fwaiter = fopen(waiterFile, "rb");
                    if (fwaiter == NULL)
                    {
                        printf("Erro na abertura!\n");
                        system("Pause");
                        return 1;
                    }
                    do
                    {
                        printf("\nGarcom: ");
                        for (int i = 0; i < waiters_index; i++)
                        {
                            fseek(fwaiter, i * sizeof(struct waiter), SEEK_SET);
                            fread(&waitersReader, sizeof(struct waiter), waiters_index, fwaiter);
                            printf("\n[%d] %s", i + 1, waitersReader->name);
                        }
                        printf("\nEscolha: ");
                        scanf("%d", &option2);
                        option2--;
                        if (option2 < 0 || option2 > waiters_index - 1)
                            printf("Opcao invalida! Tente novamente...\n");
                    } while (option2 < 0 || option2 > waiters_index - 1);

                    rewind(fwaiter);
                    fseek(fwaiter, (option2) * sizeof(waiter), SEEK_SET);
                    fread(&waitersReader, sizeof(waiter), waiters_index, fwaiter);
                    table_chosen->waiter_code = waitersReader->code;
                    fclose(fwaiter);

                    printf("\nMudanca feita com sucesso!\n");

                    break;
                case 3:

                    show_order(&table_chosen->requests);
                    order *aux = table_chosen->requests;
                    printf("\nQual pedido voce deseja alterar?");
                    int i = 0;
                    while (aux)
                    {
                        printf("\n[%d] %d pedido", i + 1, i + 1);
                        aux = aux->next;
                        i++;
                    }
                    printf("\nEscolha: ");
                    scanf("%d", &option2);
                    order_chosen = get_order(&table_chosen->requests, option2);

                    printf("\nO que vc deseja alterar?");
                    printf("\n[1] Prato");
                    printf("\n[2] Quantidade");
                    printf("\nEscolha: ");
                    scanf("%d", &option3);
                    switch (option3)
                    {
                    case 1:
                        table_chosen->requests_price -= order_chosen->price;
                        fmenu = fopen(menuFile, "rb");
                        if (fmenu == NULL)
                        {
                            printf("Erro na abertura!\n");
                            system("Pause");
                            return 1;
                        }
                        do
                        {
                            printf("\nO que voce deseja?");
                            printf("\nMenu: ");
                            for (int i = 0; i < menu_index; i++)
                            {
                                fseek(fmenu, i * sizeof(struct foods), SEEK_SET);
                                fread(&menuReader, sizeof(struct foods), menu_index, fmenu);
                                printf("\n[%d]\t%s - R$%.lf", i + 1, menuReader->name, menuReader->price);
                            }
                            printf("\nEscolha: ");
                            scanf("%d", &option4);
                            option4--;
                            if (option4 < 0 || option4 > menu_index - 1)
                                printf("\nOpcao invalida! Tente novamente...\n");
                        } while (option4 < 0 || option4 > menu_index - 1);
                        rewind(fmenu);
                        fseek(fmenu, (option4) * sizeof(struct foods), SEEK_SET);
                        fread(&menuReader, sizeof(struct foods), menu_index, fmenu);
                        strcpy(order_chosen->name, menuReader->name);
                        order_chosen->code = menuReader->code;
                        printf("\nVoce quer mudar a quantidade tambem?");
                        printf("\n[1] Sim!");
                        printf("\n[2] Nao!");
                        printf("\nEscolha: ");
                        scanf("%d", &option5);
                        if (option5 == 1)
                        {

                            printf("\nNova quantidade: ");
                            scanf("%hu", &order_chosen->quantity);
                        }

                        order_chosen->price = menuReader->price * order_chosen->quantity;
                        table_chosen->requests_price += order_chosen->price;

                        printf("\nMudanca feita com sucesso!\n");

                        break;

                    case 2:
                        table_chosen->requests_price -= order_chosen->price;

                        printf("\nNova quantidade: ");
                        scanf("%hu", &order_chosen->quantity);

                        order_chosen->price = menuReader->price * order_chosen->quantity;
                        table_chosen->requests_price += order_chosen->price;
                        printf("\nMudanca feita com sucesso!\n");

                        break;

                    default:

                        printf("\nOpcao invalida!");
                        break;
                    }
                    break;

                case 4:

                    fmenu = fopen(menuFile, "rb");
                    if (fmenu == NULL)
                    {
                        printf("Erro na abertura!\n");
                        system("Pause");
                        return 1;
                    }
                    do
                    {
                        option3 = 0;
                        do
                        {
                            current_order = malloc(sizeof(order));
                            printf("\nO que voce deseja?");
                            printf("\nMenu: ");
                            for (int i = 0; i < menu_index; i++)
                            {
                                fseek(fmenu, i * sizeof(struct foods), SEEK_SET);
                                fread(&menuReader, sizeof(struct foods), menu_index, fmenu);
                                printf("\n[%d]\t%s - R$%.2lf", i + 1, menuReader->name, menuReader->price);
                            }
                            printf("\nEscolha: ");
                            scanf("%d", &option2);
                            option2--;
                            if (option2 < 0 || option2 > menu_index - 1)
                                printf("\nOpcao invalida! Tente novamente...\n");
                        } while (option2 < 0 || option2 > menu_index - 1);
                        rewind(fmenu);
                        fseek(fmenu, (option2) * sizeof(struct foods), SEEK_SET);
                        fread(&menuReader, sizeof(struct foods), menu_index, fmenu);
                        strcpy(current_order->name, menuReader->name);
                        current_order->code = menuReader->code;
                        printf("\nPreco: %.2lf", menuReader->price);
                        printf("\nQuantidade: ");
                        scanf("%hu", &current_order->quantity);
                        current_order->price = menuReader->price * current_order->quantity;
                        table_chosen->requests_price += current_order->price;
                        printf("\nPreco total: %.2lf", current_order->price);

                        insert_order(&table_chosen->requests, current_order);

                        printf("\nVoce deseja acrescentar mais pedidos?");
                        printf("\n[1] Sim!");
                        printf("\n[2] Nao!");
                        printf("\nEscolha: ");
                        scanf("%d", &option3);

                    } while (option3 != 2);
                    fclose(fmenu);
                    printf("\nMudanca feita com sucesso!\n");
                    break;
                default:

                    if (option2 != 4)
                        printf("\nOpcao invalida!");
                    break;
                }
            }
            else
                printf("\nNao ha mesas disponiveis!\n");

            break;
        case 3:
            if (list_of_tables.size != 0)
            {
                show_table_number(list_of_tables);
                do
                {
                    printf("\nVoce quer fechar a conta de qual mesa? ");
                    scanf("%hu", &number_to_test);
                    number_equal = 0;
                    if (search_number_table(&list_of_tables, number_to_test) == 0)
                    {
                        printf("\nNumero disponivel!\n");
                    }
                    else
                    {
                        printf("\nNumero indisponivel! Tente novamente...\n");
                        number_equal++;
                    }
                } while (number_equal);

                show_specific_table(list_of_tables, number_to_test);

                remove_table(&list_of_tables, number_to_test);
            }
            else
                printf("\nNao ha mesas disponiveis!\n");
            break;

        case 4:
            if (list_of_tables.size != 0)
                show_table(list_of_tables);
            else
                printf("\nNao ha mesas disponiveis!\n");
            break;

        case 5:

            current = menu_index++;
            fmenu = fopen(menuFile, "wb");
            if (fmenu == NULL)
            {
                printf("Erro na abertura!\n");
                system("Pause");
                return 1;
            }
            printf("\nNome: ");
            fflush(stdin);
            fgets(menu[current].name,100, stdin);
            do
            {
                code_equal = 0;
                printf("Codigo: ");
                scanf("%d", &code_to_test);

                for (int i = 0; i < menu_index; i++)
                {
                    if (menu[i].code == code_to_test)
                    {
                        code_equal++;
                        break;
                    }
                }
                if (code_equal != 0)
                    printf("Codigo em uso! Tente novamente...\n");
            } while (code_equal);
            menu[current].code = code_to_test;

            printf("Preco: R$");
            scanf("%lf", &menu[current].price);

            printf("\nAdicionado com sucesso!\n");
            for (int i = 0; i < menu_index; i++)
            {
                printf("\nPos: %hu\nNome: %s\nCodigo: %d\nPreco: %.2lf", i + 1, menu[i].name, menu[i].code, menu[i].price);
            }
            fwrite(&menu, sizeof(struct foods), menu_index, fmenu);
            fclose(fmenu);
            break;

        case 6:
            fmenu = fopen(menuFile, "wb");
            if (fmenu == NULL)
            {
                printf("\nErro na abertura!\n");
                system("Pause");
                return 1;
            }
            printf("\n-------------------------------------------------------\n");
            printf("Qual posicao voce deseja deletar? No momento, possuimos %hu posicoes: ", menu_index);
            scanf("%hu", &position_chosen);
            printf("\n-------------------------------------------------------\n");

            for (int i = position_chosen - 1; i < menu_index - 1; i++)
            {
                menu[i] = menu[i + 1];
            }
            menu_index--;
            fwrite(&menu, sizeof(struct foods), menu_index, fmenu);
            printf("\nPosicao %hu removida!\n", position_chosen);
            fclose(fmenu);
            break;

        case 7:
            fmenu = fopen(menuFile, "wb");
            if (fmenu == NULL)
            {
                printf("Erro na abertura!\n");
                system("Pause");
                return 1;
            }
            printf("\n-------------------------------------------------------\n");
            printf("Qual posicao voce deseja alterar? No momento, possuimos %hu posicoes: ", menu_index);
            scanf("%hu", &position_chosen);
            position_chosen--;
            printf("\n-------------------------------------------------------\n");

            printf("\nO que voce deseja alterar?");
            printf("\n[1] Nome");
            printf("\n[2] Codigo");
            printf("\n[3] Preco");
            printf("\nEscolha: ");
            scanf("%d", &option2);
            printf("\n-------------------------------------------------------\n");
            switch (option2)
            {
            case 1:
                printf("Novo nome: ");
                fflush(stdin);
                fgets(menu[position_chosen].name, 100, stdin);
                break;

            case 2:
                do
                {
                    code_equal = 0;
                    printf("Codigo: ");
                    scanf("%d", &code_to_test);

                    for (int i = 0; i < menu_index; i++)
                    {
                        if (menu[i].code == code_to_test)
                        {
                            code_equal++;
                            break;
                        }
                    }
                    if (code_equal != 0)
                        printf("\nCodigo em uso! Tente novamente...\n");
                } while (code_equal);
                menu[position_chosen].code = code_to_test;

                break;

            case 3:
                printf("Novo preco: ");
                scanf("%lf", &menu[position_chosen].price);
                break;

            default:
                printf("Opcao invalida");
            }

            fwrite(&menu, sizeof(struct foods), menu_index, fmenu);
            printf("Posicao %hu modificada!", position_chosen + 1);
            fclose(fmenu);
            break;
        case 8:
            fmenu = fopen(menuFile, "rb");
            if (fmenu == NULL)
            {
                printf("Erro na abertura!\n");
                system("Pause");
                return 1;
            }
            printf("\n-------------------------------------------------------\n");
            for (int i = 0; i < menu_index; i++)
            {
                fseek(fmenu, i * sizeof(struct foods), SEEK_SET);
                fread(&menuReader, sizeof(struct foods), menu_index, fmenu);
                printf("\nPosicao: %d\nNome: %s\nCodigo: %d\nPreco R$%.2lf", i + 1, menuReader->name, menuReader->code, menuReader->price);
                printf("\n-------------------------------------------------------\n");
            }
            fclose(fmenu);
            break;

        case 9:
            current = waiters_index++;
            fwaiter = fopen(waiterFile, "wb");
            if (fwaiter == NULL)
            {
                printf("\nErro na abertura!\n");
                system("Pause");
                return 1;
            }

            printf("\nNome: ");
            fflush(stdin);
            fgets(waiters[current].name, 100, stdin);

            do
            {
                code_equal = 0;
                printf("Codigo do garcom: ");
                scanf("%d", &code_to_test);

                for (int i = 0; i < menu_index; i++)
                {
                    if (waiters[i].code == code_to_test)
                    {
                        code_equal++;
                        break;
                    }
                }
                if (code_equal != 0)
                    printf("Codigo em uso! Tente novamente...\n");
            } while (code_equal);
            waiters[current].code = code_to_test;

            fwrite(&waiters, sizeof(struct waiter), waiters_index, fwaiter);
            printf("\nAdicionado com sucesso!\n");
            fclose(fwaiter);
            break;

        case 10:
            fwaiter = fopen(waiterFile, "wb");
            if (fwaiter == NULL)
            {
                printf("\nErro na abertura!\n");
                system("Pause");
                return 1;
            }
            printf("\n-------------------------------------------------------\n");
            printf("Qual posicao voce deseja deletar? No momento, possuimos %hu posicoes: ", waiters_index);
            scanf("%hu", &position_chosen);
            printf("\n-------------------------------------------------------\n");

            for (int i = position_chosen - 1; i < waiters_index - 1; i++)
            {
                waiters[i] = waiters[i + 1];
            }
            waiters_index--;

            fwrite(&waiters, sizeof(struct waiter), waiters_index, fwaiter);
            printf("\nPosicao %hu removida!\n", position_chosen);

            fclose(fwaiter);

            break;

        case 11:
            fwaiter = fopen(waiterFile, "wb");
            if (fwaiter == NULL)
            {
                printf("\nErro na abertura!\n");
                system("Pause");
                return 1;
            }
            printf("\n-------------------------------------------------------\n");
            printf("Qual posicao voce deseja alterar? No momento, possuimos %hu posicoes: ", waiters_index);
            scanf("%hu", &position_chosen);
            position_chosen--;
            printf("\n-------------------------------------------------------\n");

            printf("\nO que voce deseja alterar?");
            printf("\n[1] Nome");
            printf("\n[2] Codigo");
            printf("\nEscolha: ");
            scanf("%d", &option2);
            printf("\n-------------------------------------------------------\n");
            switch (option2)
            {
            case 1:
                printf("Novo nome: ");
                fflush(stdin);
                fgets(waiters[position_chosen].name, 100, stdin);
                break;

            case 2:
                do
                {
                    code_equal = 0;
                    printf("Codigo do garcom: ");
                    scanf("%d", &code_to_test);

                    for (int i = 0; i < menu_index; i++)
                    {
                        if (waiters[i].code == code_to_test)
                        {
                            code_equal++;
                            break;
                        }
                    }
                    if (code_equal != 0)
                        printf("Codigo em uso! Tente novamente...\n");
                } while (code_equal);
                waiters[position_chosen].code = code_to_test;
                break;

            default:
                printf("\nOpcao invalida!\n");
            }

            fwrite(&waiters, sizeof(struct waiter), waiters_index, fwaiter);
            fclose(fwaiter);

            printf("\nPosicao %hu alterada!\n", position_chosen + 1);
            break;

        case 12:
            fwaiter = fopen(waiterFile, "rb");
            if (fmenu == NULL)
            {
                printf("\nErro na abertura\n");
                system("Pause");
                return 1;
            }
            printf("\n-------------------------------------------------------\n");
            for (int i = 0; i < waiters_index; i++)
            {
                fseek(fwaiter, i * sizeof(struct waiter), SEEK_SET);
                fread(&waitersReader, sizeof(struct waiter), waiters_index, fwaiter);
                printf("\nPosicao: %d\nNome: %s\nCodigo: %d", i + 1, waitersReader->name, waitersReader->code);
                printf("\n-------------------------------------------------------\n");
            }
            fclose(fwaiter);
            break;

        default:
            if (option != 13)
                printf("Opcao invalida!");
        }
    } while (option != 13);

    system("Pause");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct place
{
    char nome[100];
    char location[20];
    char type[20];
    char quality[20];
    char review[1024];
} place;

typedef struct states
{
    char states[10][25];
} states;

int main()
{
    FILE *f;
    states state_choices[5][20] = {{"Acre", "Amapa", "Amazonas", "Para", "Rondonia", "Roraima", "Tocantis"},
                                   {"Alagoas", "Bahia", "Ceara", "Maranhao", "Paraiba", "Pernambuco", "Piaui", "Rio Grande do Norte", "Sergipe"},
                                   {"Distrito Federal", "Goias", "Mato Grosso", "Mato Grosso do Sul"},
                                   {"Rio de Janeiro", "Sao Paulo", "Minas Gerais", "Espirito Santo"},
                                   {"Parana", "Santa Catarina", "Rio Grande do Sul"}};

    char region_choices[5][20] = {"Norte", "Nordeste", "Centro-Oeste", "Sudeste", "Sul"};
    char quality_choices[6][20] = {"Restaurante", "Praia", "Show", "Teatro", "Parques", "Museus"};
    char type_choices[8][20] = {"Otimo", "Bom", "Regular", "Ruim", "Pessimo", "Caro", "Barato", "Gratis"};

    unsigned state_choices_index[5] = {7, 9, 4, 4, 3};
    unsigned short option, option2, position_chosen, region_chosen, region_chosen_index;
    int acc = 0;

    f = fopen("Trabalho 01.bin", "wb");
    if (f == NULL)
    {
        printf("Erro na abertura!\n");
        system("pause");
        return 1;
    }

    struct place places[5][100] = {{"Parque do Jalapao", "Tocantis", "Parque", "Otimo", "O Jalapao era para mim um daqueles lugares que sempre quis conhecer mas nao fazia ideia do que tinha la.Pois bem... foi uma experiencia incrivel!",
                                    "Teatro Amazonas", "Amazonas", "Teatro", "Gratis", "Conta com varios guias, que explicam todo o processo de construcao, assim como as curiosidades.",
                                    "Teatro da Paz", "Para", "Teatro", "Barato", "Com inspiracao no Teatro Scalla de Milao, o Teatro da Paz possui estilo neoclassivo. Atualmente, o Teatro esta em pleno funcionamento, com apresentacoes quase todos os dias.",
                                    "Ilha de Marajo", "Para", "Praia", "Bom", "A ilha de marajo possui muitas caracteristicas unicas, que atraem os visitantes que gostam da natureza. Com diversas praias boas, passeios pela mata, compra de artesanato e comida boa nao falta."},

                                   {"Lencois Maranhenses", "Maranhao", "Praia", "Otimo", "Os Lencois Maranhenses e um passeio imperdivel, ficamos encantados com cada paisagens incrivel que nossos olhos puderam contemplar. Lugar e indescritivel.",
                                    "Marques da Varjota", "Ceara", "Restaurantes", "Caro", "Comida maravilha como esperado, mas o preco nao e nada convidativo",
                                    "Jericoacoara", "Ceara", "Praia", "Otimo", "Paisagem natural que inclui dunas, coqueirais, aguas azuis e cristalinas, e ate redes e mesas montadas.",
                                    "Serra da capivara", "Piaui", "Parques", "Pessimo", "Um lugar muito bonito pela sua paisagem natural, mas o acesso e extremamente precario, fazendo com que a dificuldade passada não valha a pena."},

                                   {"Museu das Culturas Dom Bosco", "Mato Grosso do Sul", "Museu", "Gratis", "Maravilhoso lugar para conhecer todos os tipos de cultura. E pra melhorar, e tudo gratutito",
                                    "Parque Nacional Chapada dos Guimaraes", "Mato Grosso", "Parque", "Regular", "Embora seja um lugar bonito a falta de estrutura pode decepcionar",
                                    "Exponop", "Mato Grosso", "Show", "Bom", "Um bom lugar para passar um tempo com os amigos e conhecer pessoas novas, enquanto desfruta de boas musicas",
                                    "Parque Nacional da Chapada dos Veadeiros", "Goias", "Parque", "Regular", "Um lugar legal, mas, devido a distancia e a falta de rede de celular, acaba fazendo com que perda seu brilho"},

                                   {"Praia de Copacabana", "Rio de Janeiro", "Praia", "Pessimo", "A TV te apresenta como um lugar maravilhoso, mas nao te conta dos perigos que e estar ali",
                                    "Rock in Rio", "Rio de Janeiro", "Show", "Bom", "Perfeito para apreciar boas musicas, conhecer pessoas e sair da rotina",
                                    "Museu de Artes de Sao Paulo Assis", "Sao Paulo", "Museu", "Regular", "Tem algumas coisas interessantes, mas não o suficiente para valer o preco pago.",
                                    "Parrillada Fuego Celeste", "Sao Paulo", "Restaurante", "Otimo", "Carne maravilhosa. Voce consegue comer varias e varias vezes sem se quer enjoar. Melhor restaurante que ja frequentei"},

                                   {"Beto Carrero World", "Santa Catarina", "Parque", "Pessimo", "Nao chega perto dos parques famosos internacionalmente, como a Disney",
                                    "Foz do Iguacu", "Parana", "Parque", "Bom", "Um bom lugar para passar o tempo e poder apreciar a paisagem",
                                    "Museu Oscar Niemeyer", "Parana", "Museu", "gratis", "Um dos lugares que você tem que dar uma olhada. O trabalho de Oscar Niemeyer e apreciada por muitos e odiada por poucos. Faca uma visita e tire suas conclusoes",
                                    "Garopaba", "Santa Catarina", "Praia", "pessimo", "Embora seja um lugar muito lindo devido a sua beleza natural, o preco para chegar la e mt salgado"}};

    struct place placesReader[5][100];
    unsigned short places_index[5] = {4, 4, 4, 4, 4};

    for (int i = 0; i < 5; i++)
    {
        fwrite(&places[i], sizeof(struct place), places_index[i], f);
    }

    fclose(f);

    f = fopen("Trabalho 01.bin", "rb");
    if (f == NULL)
    {
        printf("Erro na abertura!\n");
        system("pause");
        return 1;
    }

    printf("Qual regiao voce deseja se conectar?\n");
    printf("[1] Norte\n");
    printf("[2] Nordeste\n");
    printf("[3] Centro-Oeste\n");
    printf("[4] Sudeste\n");
    printf("[5] Sul\n");
    printf("Escolha: ");
    scanf("%hu%*c", &region_chosen);
    region_chosen--;

    for (int i = 0; i < region_chosen; i++)
    {
        acc += places_index[i];
    }

    printf("\n-------------------------------------------------------\n");
    for (int i = 0; i < places_index[region_chosen]; i++)
    {
        fseek(f, (acc + i) * sizeof(struct place), SEEK_SET);
        fread(&placesReader[region_chosen], sizeof(struct place), places_index[region_chosen], f);
        printf("Posicao: %d\nNome: %s\nRegiao: %s\nTipo: %s\nQualidade: %s\nReview: %s\n", i + 1, placesReader[region_chosen]->nome, placesReader[region_chosen]->location, placesReader[region_chosen]->type, placesReader[region_chosen]->quality, placesReader[region_chosen]->review);
        printf("\n-------------------------------------------------------\n");
    }
    fclose(f);

    while (option2 != 6)
    {
        printf("O que voce deseja fazer?\n");
        printf("[1] Incluir uma descricao\n");
        printf("[2] Alterar uma descricao\n");
        printf("[3] Excluir uma descricao\n");
        printf("[4] Mostrar uma descricao\n");
        printf("[5] Mostrar todas as descricoes da regiao\n");
        printf("[6] Finalizar\n");
        printf("Escolha: ");
        scanf("%hu%*c", &option2);
        printf("\n-------------------------------------------------------\n");
        switch (option2)
        {
        case 1:
            region_chosen_index = places_index[region_chosen]++;

            f = fopen("Trabalho 01.bin", "wb");
            if (f == NULL)
            {
                printf("Erro na abertura!\n");
                system("pause");
                return 1;
            }

            printf("\nNome: ");

            fgets(places[region_chosen][region_chosen_index].nome, 100, stdin);
            places[region_chosen][region_chosen_index].nome[strlen(places[region_chosen][region_chosen_index].nome) - 1] = '\0';

            printf("\nEstado:");
            for (unsigned short i = 0; i < state_choices_index[region_chosen]; i++)
            {
                printf("\n[%d] %s", i + 1, state_choices[region_chosen]->states[i]);
            }
            printf("\nEscolha: ");
            scanf("%hu%*c", &option);
            strcpy(places[region_chosen][region_chosen_index].location, state_choices[region_chosen]->states[option - 1]);

            printf("\nTipo:\n");
            printf("[1] Restaurantes\n");
            printf("[2] Praia\n");
            printf("[3] Show\n");
            printf("[4] Teatro\n");
            printf("[5] Parques\n");
            printf("[6] Museus\n");
            printf("Escolha: ");
            scanf("%hu%*c", &option);
            strcpy(places[region_chosen][region_chosen_index].type, type_choices[option - 1]);

            printf("\nQualidade:\n");
            printf("[1] Otimo\n");
            printf("[2] Bom\n");
            printf("[3] Regular\n");
            printf("[4] Ruim\n");
            printf("[5] Pessimo\n");
            printf("[6] Caro\n");
            printf("[7] Barato\n");
            printf("[8] Gratis\n");
            printf("Escolha: ");
            scanf("%hu%*c", &option);
            strcpy(places[region_chosen][region_chosen_index].quality, quality_choices[option - 1]);

            printf("\nReview: ");

            fgets(places[region_chosen][region_chosen_index].review, 1024, stdin);
            places[region_chosen][region_chosen_index].review[strlen(places[region_chosen][region_chosen_index].review) - 1] = '\0';

            for (int i = 0; i < 5; i++)
            {
                fwrite(&places[i], sizeof(struct place), places_index[i], f);
            }

            fclose(f);

            printf("\nAdicionado com sucesso!\n");

            break;

        case 2:

            f = fopen("Trabalho 01.bin", "wb");
            if (f == NULL)
            {
                printf("Erro na abertura!\n");
                system("pause");
                return 1;
            }
            printf("Qual a posicao da que vc deseja alterar? No momento, temos %hu posicoes: ", places_index[region_chosen]);
            printf("\n-------------------------------------------------------\n");
            scanf("%hu%*c", &position_chosen);
            position_chosen--;
            printf("Qual voce deseja alterar?\n");
            printf("[1] Nome\n");
            printf("[2] Regiao\n");
            printf("[3] Tipo\n");
            printf("[4] Qualidade\n");
            printf("[5] Review\n");
            scanf("%hu%*c", &option);
            switch (option)
            {
            case 1:
                printf("Novo nome: ");
                fgets(places[region_chosen][position_chosen].nome, 100, stdin);
                places[region_chosen][region_chosen_index].nome[strlen(places[region_chosen][region_chosen_index].nome) - 1] = '\0';

                break;

            case 2:
                printf("\nEstado:");
                for (unsigned short i = 0; i < state_choices_index[region_chosen]; i++)
                {
                    printf("\n[%d] %s", i + 1, state_choices[region_chosen]->states[i]);
                }
                printf("\nEscolha: ");
                scanf("%hu%*c", &option);
                strcpy(places[region_chosen][position_chosen].location, state_choices[region_chosen]->states[option - 1]);
                break;

            case 3:
                printf("Tipo:\n");
                printf("[1] Restaurantes\n");
                printf("[2] Praia\n");
                printf("[3] Show\n");
                printf("[4] Teatro\n");
                printf("[5] Parques\n");
                printf("[6] Museus");
                printf("Escolha: ");
                scanf("%hu%*c", &option);
                strcpy(places[region_chosen][position_chosen].type, type_choices[option - 1]);
                break;

            case 4:
                printf("Qualidade:\n");
                printf("[1] Otimo\n");
                printf("[2] Bom\n");
                printf("[3] Regular\n");
                printf("[4] Ruim\n");
                printf("[5] Pessimo\n");
                printf("[6] Caro");
                printf("[7] Barato\n");
                printf("[8] Gratis");
                printf("Escolha: ");
                printf("Review: ");
                scanf("%hu%*c", &option);
                strcpy(places[region_chosen][position_chosen].quality, quality_choices[option - 1]);
                break;

            case 5:
                printf("Novo review: ");
                fgets(places[region_chosen][position_chosen].review, 1024, stdin);
                places[region_chosen][region_chosen_index].review[strlen(places[region_chosen][region_chosen_index].review) - 1] = '\0';

            default:
                printf("\nopcao invalida!\n");
                break;
            }

            for (int i = 0; i < 5; i++)
            {
                fwrite(&places[i], sizeof(struct place), places_index[i], f);
            }
            fclose(f);
            break;

        case 3:
            f = fopen("Trabalho 01.bin", "wb");
            if (f == NULL)
            {
                printf("Erro na abertura!\n");
                system("pause");
                return 1;
            }

            printf("Qual posicao deseja excluir? No momento, temos %hu posicoes: ", places_index[region_chosen]);
            printf("\n-------------------------------------------------------\n");
            scanf("%hu%*c", &position_chosen);

            for (int i = position_chosen - 1; i < places_index[region_chosen] - 1; i++)
            {
                places[region_chosen][i] = places[region_chosen][i + 1];
            }
            places_index[region_chosen]--;

            for (int i = 0; i < 5; i++)
            {
                fwrite(&places[i], sizeof(struct place), places_index[i], f);
            }

            fclose(f);

            printf("\nPosicao %hu removida com sucesso!", position_chosen);
            printf("\n-------------------------------------------------------\n");

            break;

        case 4:
            f = fopen("Trabalho 01.bin", "rb");
            if (f == NULL)
            {
                printf("Erro na abertura!\n");
                system("pause");
                return 1;
            }

            printf("Qual posicao deseja ver? No momento, temos %hu posicoes: ", places_index[region_chosen]);
            printf("\n-------------------------------------------------------\n");
            scanf("%hu%*c", &position_chosen);
            fseek(f, (acc + position_chosen - 1) * sizeof(struct place), SEEK_SET);
            fread(&placesReader[region_chosen], sizeof(struct place), places_index[region_chosen], f);
            printf("-------------------------------------------------------\n");
            printf("Posicao: %d\nNome: %s\nRegiao: %s\nTipo: %s\nQualidade: %s\nReview: %s\n", position_chosen, placesReader[region_chosen]->nome, placesReader[region_chosen]->location, placesReader[region_chosen]->type, placesReader[region_chosen]->quality, placesReader[region_chosen]->review);
            printf("-------------------------------------------------------\n");
            fclose(f);
            break;

        case 5:
            f = fopen("Trabalho 01.bin", "rb");
            if (f == NULL)
            {
                printf("Erro na abertura!\n");
                system("pause");
                return 1;
            }

            printf("\n-------------------------------------------------------\n");
            for (int i = 0; i < places_index[region_chosen]; i++)
            {
                fseek(f, (acc + i) * sizeof(struct place), SEEK_SET);
                fread(&placesReader[region_chosen], sizeof(struct place), places_index[region_chosen], f);
                printf("Posicao: %d\nNome: %s\nRegiao: %s\nTipo: %s\nQualidade: %s\nReview: %s", i + 1, placesReader[region_chosen]->nome, placesReader[region_chosen]->location, placesReader[region_chosen]->type, placesReader[region_chosen]->quality, placesReader[region_chosen]->review);
                printf("\n-------------------------------------------------------\n");
            }
            fclose(f);
            break;

        default:
            if (option2 != 6)
                printf("\nPosicao invalida!\n");
            break;
        }
    }

    system("pause");
    return 0;
}

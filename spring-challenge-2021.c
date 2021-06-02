#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Cell
{
    int id;
    int richness;
    int have_tree;
    int tree_owner;
    int tree_size;
    int neigh[6];
    bool is_dormant;
};

int main()
{
    // 37
    int number_of_cells;
    scanf("%d", &number_of_cells);
    struct Cell cell[number_of_cells];
    for (int i = 0; i < number_of_cells; i++)
    {
        // 0 is the center cell, the next cells spiral outwards
        int index;
        // 0 if the cell is unusable, 1-3 for usable cells
        int richness;
        // the index of the neighbouring cell for each direction
        int neigh_0;
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        scanf("%d%d%d%d%d%d%d%d", &index, &richness, &neigh_0, &neigh_1, &neigh_2, &neigh_3, &neigh_4, &neigh_5);

        cell[i].id = index;
        cell[i].richness = richness;
        cell[i].have_tree = 0;
        cell[i].neigh[0] = neigh_0;
        cell[i].neigh[1] = neigh_1;
        cell[i].neigh[2] = neigh_2;
        cell[i].neigh[3] = neigh_3;
        cell[i].neigh[4] = neigh_4;
        cell[i].neigh[5] = neigh_5;
    }

    int nbr_tree_lvl_0 = 0;
    int nbr_tree_lvl_1 = 2;
    int nbr_tree_lvl_2 = 0;
    int nbr_tree_lvl_3 = 0;

    int nbr_of_growing = 0;
    int nbr_of_seeding = 1;

    // game loop
    while (1)
    {
        // the game lasts 24 days: 0-23
        int day;
        scanf("%d", &day);
        // the base score you gain from the next COMPLETE action
        int nutrients;
        scanf("%d", &nutrients);
        // your sun points
        int sun;
        // your current score
        int score;
        scanf("%d%d", &sun, &score);
        // opponent's sun points
        int opp_sun;
        // opponent's score
        int opp_score;
        // whether your opponent is asleep until the next day
        bool opp_is_waiting;
        int _opp_is_waiting;
        scanf("%d%d%d", &opp_sun, &opp_score, &_opp_is_waiting);
        opp_is_waiting = _opp_is_waiting;
        // the current amount of trees
        int number_of_trees;
        scanf("%d", &number_of_trees);
        for (int i = 0; i < number_of_trees; i++)
        {
            // location of this tree
            int cell_index;
            // size of this tree: 0-3
            int size;
            // 1 if this is your tree
            bool is_mine;
            // 1 if this tree is dormant
            bool is_dormant;
            int _is_mine;
            int _is_dormant;
            scanf("%d%d%d%d", &cell_index, &size, &_is_mine, &_is_dormant);
            is_mine = _is_mine;
            is_dormant = _is_dormant;

            cell[cell_index].have_tree = 1;
            cell[cell_index].tree_owner = is_mine;
            cell[cell_index].tree_size = size;
            cell[cell_index].is_dormant = is_dormant;
        }
        int number_of_possible_moves;
        scanf("%d", &number_of_possible_moves);
        fgetc(stdin);
        for (int i = 0; i < number_of_possible_moves; i++)
        {
            char possible_move[32];
            scanf("%[^\n]", possible_move);
            fgetc(stdin);
        }

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");

        // GROW cellIdx | SEED sourceIdx targetIdx | COMPLETE cellIdx | WAIT <message>

        // test nbr_of_growing pour tout recup avant la fin
        int test = 11;

        int completed = 0;
        if (nbr_of_growing > test)
            for (int i = 0; i < number_of_cells; i++)
            {
                if (cell[i].have_tree == 1 && cell[i].tree_owner == 1 && cell[i].tree_size == 3 && completed != 1 && !cell[i].is_dormant)
                {
                    printf("COMPLETE %d COMPLETE %d\n", i, i);
                    completed = 1;
                    nbr_tree_lvl_3--;
                    cell[i].have_tree = 0;
                }
            }

        int growed = 0;
        int best_tree = 100;
        if (completed == 0 && (nbr_of_seeding > nbr_of_growing || nbr_tree_lvl_0 >= 2 || nbr_of_growing >= test))
        {
            for (int i = 0; i < number_of_cells; i++)
            {
                if (cell[i].have_tree == 1 && cell[i].tree_owner == 1 && i < best_tree && !cell[i].is_dormant)
                {
                    if (cell[i].tree_size == 0)
                        if (sun > 1 + nbr_tree_lvl_1)
                        {
                            best_tree = i;
                        }
                    if (cell[i].tree_size == 1)
                        if (sun > 3 + nbr_tree_lvl_2)
                        {
                            best_tree = i;
                        }
                    if (cell[i].tree_size == 2)
                        if (sun > 7 + nbr_tree_lvl_3)
                        {
                            best_tree = i;
                        }
                }
            }
            if (best_tree != 100)
            {
                if (cell[best_tree].tree_size == 0)
                {
                    nbr_tree_lvl_0--;
                    nbr_tree_lvl_1++;
                }
                else if (cell[best_tree].tree_size == 1)
                {
                    nbr_tree_lvl_1--;
                    nbr_tree_lvl_2++;
                }
                else if (cell[best_tree].tree_size == 2)
                {
                    nbr_tree_lvl_2--;
                    nbr_tree_lvl_3++;
                }

                printf("GROW %d GROW in %d\n", best_tree, best_tree);
                growed = 1;
                nbr_of_growing++;
            }
        }

        int seeded = 0;
        int best_cell = -1;
        int source = 100;
        if (nbr_of_growing < test)
            if (completed == 0 && growed == 0 && (nbr_of_seeding <= nbr_of_growing))
            {
                for (int i = 0; i < number_of_cells; i++)
                {
                    if (cell[i].have_tree == 1 && cell[i].tree_owner == 1 && i < source && cell[i].tree_size > 1 && !cell[i].is_dormant)
                    {
                        int min = 100;
                        for (int j = 0; j < 6; j++)
                            if (cell[i].neigh[j] < min && cell[i].neigh[j] > -1)
                            {
                                min = cell[i].neigh[j];
                            }
                        int targ2 = -1;
                        int targ2_richness = -1;
                        for (int j = 0; j < 6; j++)
                            if (cell[cell[min].neigh[j]].richness > targ2_richness && cell[min].neigh[j] > -1 && cell[cell[min].neigh[j]].have_tree == 0)
                            {
                                targ2_richness = cell[cell[min].neigh[j]].richness;
                                targ2 = cell[min].neigh[j];
                            }
                        fprintf(stderr, "min = %d\ntarg2 = %d\nbest_cell = %d\n", min, targ2, best_cell);
                        if (targ2 == -1 || (targ2 > min && cell[min].have_tree == 0))
                            best_cell = min;
                        else
                            best_cell = targ2;
                        source = i;
                    }
                }
                if (best_cell != -1 && cell[best_cell].richness != 0)
                {
                    nbr_tree_lvl_0++;
                    printf("SEED %d %d SEED in %d\n", source, best_cell, best_cell);
                    seeded = 1;
                }
                nbr_of_seeding++;
            }

        if (completed == 0 && growed == 0 && seeded == 0)
            printf("WAIT Zzz\n");

        fprintf(stderr, "nbr_tree_lvl_0 = %d\nnbr_tree_lvl_1 = %d\nnbr_tree_lvl_2 = %d\nnbr_tree_lvl_3 = %d\nnbr_of_growing = %d\nnbr_of_seeding = %d\n", nbr_tree_lvl_0, nbr_tree_lvl_1, nbr_tree_lvl_2, nbr_tree_lvl_3, nbr_of_growing, nbr_of_seeding);
    }

    return 0;
}
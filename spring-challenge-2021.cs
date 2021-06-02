using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;


class Cell {
    public int index;
    public int richness;
    public int size;
    public bool isDormant;
    public bool isMine;

    public Cell (int index, int richness, int size, bool isDormant, bool isMine) {
        this.index = index;
        this.richness = richness;
        this.size = size;
        this.isDormant = isDormant;
        this.isMine = isMine;
    }
}

class Player
{
    static void Main(string[] args)
    {
        List<Cell> board = new List<Cell> ();

        string[] inputs;
        int numberOfCells = int.Parse(Console.ReadLine()); // 37
        for (int i = 0; i < numberOfCells; i++)
        {
            inputs = Console.ReadLine().Split(' ');
            int index = int.Parse(inputs[0]); // 0 is the center cell, the next cells spiral outwards
            int richness = int.Parse(inputs[1]); // 0 if the cell is unusable, 1-3 for usable cells
            int neigh0 = int.Parse(inputs[2]); // the index of the neighbouring cell for each direction
            int neigh1 = int.Parse(inputs[3]);
            int neigh2 = int.Parse(inputs[4]);
            int neigh3 = int.Parse(inputs[5]);
            int neigh4 = int.Parse(inputs[6]);
            int neigh5 = int.Parse(inputs[7]);

            Cell cell = new Cell (index, richness, -1, false, false);
            board.Add (cell);
        }

        int[,] diagonals = new int[,] {{10, 12, 14, 16, 18, 8}, {9, 3, 5, 17, 36, 20}, {23, 11, 4, 6, 7, 21}, {24 ,26, 13, 5, 1, 9}, {11, 27, 29, 15, 6, 2}, 
                    {3, 13, 30, 32, 17, 1}, {2, 4, 15, 33, 35, 7}, {21, 2, 6, 35, -1, -1}, {22, 10, 0, 18, 19, -1}, {-1, 24, 3, 1, 20, -1},
                    {-1, 25, 12, 0, 8, 22}, {-1, -1, 27, 4, 2, 23}, {25, -1, 28, 14, 0, 10}, {26, -1, -1, 30, 5, 3}, {12, 28, -1, 31, 16, 0},
                    {4, 29, -1, -1, 33, 6}, {0, 14, 31, -1, 34, 18}, {1, 5, 32, -1, -1, 36}, {8, 0, 16, 34, -1, 19}, {-1, 8, 18, -1, -1, -1},
                    {-1, 9, 1, 36, -1, -1}, {-1, 23, 2, 7, -1, -1}, {-1, -1, 10, 8, -1, -1}, {-1, -1, 11, 2, 21, -1}, {-1, -1, 26, 3, 9, -1},
                    {-1, -1, -1, 12, 10, -1}, {-1, -1, -1, 13, 3, 24}, {-1, -1, -1, 29, 4, 11}, {-1, -1, -1, -1, 14, 12}, {27, -1, -1, -1, 15, 4},
                    {13, -1, -1, -1, 32, 5}, {14, -1, -1, -1, -1, 16}, {5, 30, -1, -1, -1, 17}, {6, 15, -1, -1, -1, 35}, {18, 16, -1, -1, -1, -1},
                    {7, 6, 33, -1, -1, -1}, {20, 1, 17, -1, -1, -1}};

        int[] nextShadows = new int[36];

        for (int i = 0; i < nextShadows.Length; i++)
        {
            nextShadows[i] = 0;
        }

        // game loop
        while (true)
        {
            string action = "WAIT";
            int numberOfTree0 = 0;
            int numberOfTree1 = 0;
            int numberOfTree2 = 0;
            int numberOfTree3 = 0;

            for (int i = 0; i < numberOfCells; i++)
            {
                board[i].size = -1;
                board[i].isMine = false;
                board[i].isDormant = false;
            }

            int day = int.Parse(Console.ReadLine()); // the game lasts 24 days: 0-23
            int nutrients = int.Parse(Console.ReadLine()); // the base score you gain from the next COMPLETE action
            inputs = Console.ReadLine().Split(' ');
            int sun = int.Parse(inputs[0]); // your sun points
            int score = int.Parse(inputs[1]); // your current score
            inputs = Console.ReadLine().Split(' ');
            int oppSun = int.Parse(inputs[0]); // opponent's sun points
            int oppScore = int.Parse(inputs[1]); // opponent's score
            bool oppIsWaiting = inputs[2] != "0"; // whether your opponent is asleep until the next day
            int numberOfTrees = int.Parse(Console.ReadLine()); // the current amount of trees
            for (int i = 0; i < numberOfTrees; i++)
            {
                inputs = Console.ReadLine().Split(' ');
                int cellIndex = int.Parse(inputs[0]); // location of this tree
                int size = int.Parse(inputs[1]); // size of this tree: 0-3
                bool isMine = inputs[2] != "0"; // 1 if this is your tree
                bool isDormant = inputs[3] != "0"; // 1 if this tree is dormant

                board[cellIndex].size = size;
                board[cellIndex].isMine = isMine;
                board[cellIndex].isDormant = isDormant;

                if (isMine)
                {
                    if (size == 0)
                    {
                        numberOfTree0++;
                    } else if (size == 1) {
                        numberOfTree1++;
                    } else if (size == 2) {
                        numberOfTree2++;
                    } else if (size == 3) {
                        numberOfTree3++;
                    }
                }
            }
            int numberOfPossibleActions = int.Parse(Console.ReadLine()); // all legal actions
            for (int i = 0; i < numberOfPossibleActions; i++)
            {
                string possibleAction = Console.ReadLine(); // try printing something from here to start with
            }

            // Write an action using Console.WriteLine()
            // To debug: Console.Error.WriteLine("Debug messages...");



            int target = -1;

            if (day > 0)
            {
                for (int i = 0; i < numberOfCells; i++)
                {
                    if (board[i].isMine && !board[i].isDormant)
                    {
                        if (board[i].size == 3 && (numberOfTree3 >= 5
                            || day > 18 || (day > 11 && numberOfTree3 >= 3)))
                        {
                            if (sun >= 4)
                            {
                                action = "COMPLETE " + i;
                                numberOfTree3--;
                                break;
                            } else {
                                break;
                            }
                        }

                        if (board[i].size == 0
                            && sun >= numberOfTree1 + 1 && numberOfTree1 == 0
                            && day <= 20)
                        {
                            action = "GROW " + i;
                            numberOfTree1++;
                            numberOfTree0--;
                            break;
                        } else if (board[i].size == 1
                            && sun >= numberOfTree2 + 3 && day <= 21)
                        {
                            action = "GROW " + i;
                            numberOfTree2++;
                            numberOfTree1--;
                            break;
                        } else if (board[i].size == 2
                            && sun >= numberOfTree3 + 7) 
                        {
                            action = "GROW " + i;
                            numberOfTree3++;
                            numberOfTree2--;
                            break;
                        }

                        if (board[i].size >= 2
                            && day < 20 && numberOfTree0 == 0)
                        {
                            for (int j = 0; j < 6; j++)
                            {
                                if (diagonals[i,j] != -1)
                                {
                                    if (board[diagonals[i,j]].richness > 0
                                        && board[diagonals[i,j]].size == -1)
                                    {
                                        target = diagonals[i,j];
                                        break;
                                    }
                                }
                            }
                            if (target != -1)
                            {
                                action = "SEED " + i + " " + target;
                                numberOfTree0++;
                                break;
                            }
                        }
                    }
                }
            }

            Console.WriteLine(action);

            // GROW cellIdx | SEED sourceIdx targetIdx | COMPLETE cellIdx | WAIT <message>
            //Console.WriteLine("WAIT");
        }
    }
}
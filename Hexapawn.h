//Travis Bender

#ifndef Hexapawn_h
#define Hexapawn_h

#include <iostream>
#include <string>
using namespace std;

// Each node of the game tree
struct HEXNODE
{
    char gBoard[9];
    int code;  // Creates a unique code to reduce memory required for comparing gameboards.
    HEXNODE * left;
    HEXNODE * middle;
    HEXNODE * right;
};

// Class for the game
class Hexapawn
{
private:
    HEXNODE * root;  // the root node
    HEXNODE * turnNode; // a node to identify the position within the tree
    char board[9]; // a gameboard to use to compare with each node

public:
    //default constructor
    Hexapawn()
    {
        //manually loads the entire game tree
        createGameTree();
        //initializes the turn at the root
        turnNode = root;
        
        //initializes the gameboard
        for (int i = 0; i < 9; i++)
        {
            if (i < 3)
            {
                board[i] = 'O';
            }
            else if (i > 5)
            {
                board[i] = 'X';
            }
            else
            {
                board[i] = ('1' + i);
            }
        }
    }
    // creates a tree starting at begin with depth
    HEXNODE * createTree(HEXNODE * begin, int depth);
    // hardcodes all the game states in
    void createGameTree();
    // deletes the tree starting at the top node
    void deleteTree(HEXNODE * top);
    // displays the gameboard
    void displayBoard(HEXNODE * temp);
    // allows the game to be played
    void playGame();
    // creates a unique code for each gameboard state
    HEXNODE * createCode(HEXNODE * temp);
};

// displays the gameboard
void Hexapawn::displayBoard(HEXNODE * temp)
{
    for (int i = 0; i < 9; i++)
    {
        cout << "[ " << temp->gBoard[i] << " ]   ";
        if (i == 2 || i == 5)
        {
            cout << endl;
        }
    }
    cout << endl;
}

// allows the game to be played
void Hexapawn::playGame()
{
    cout << "Welcome to Hexapawn!" << endl;
    cout << "The pawns play like normal chess pawns." << endl;
    cout << "They can move forward to an open space or " << endl;
    cout << "diagonally to capture." << endl << endl;
    
    cout << "The game ends when a player reaches the other side" << endl;
    cout << "or a stalemate is reached and the player who " << endl;
    cout << "caused the stalemate wins." << endl;
    
    
    
    bool good = true;
    
    // The game loop
    while(good)
    {
        // checks if the child nodes are null
        if ((turnNode->left == nullptr && turnNode->middle == nullptr) && turnNode->right == nullptr)
        {
            // if so, then the computer wins because X can not make any more moves
            // and it is the end of the tree
            cout << endl << endl;
            cout << "O wins" << endl;
            
            displayBoard(turnNode);
            
            cout << "O wins. The End." << endl;

            good = false;
            return;
        }
        
        
        cout << endl;
        cout << "X\'s turn: " << endl;
        
        bool valid = true;
        
        displayBoard(turnNode);
        
        // loop to verify that user input is valid
        do {
            valid = true;
            int player = -1;
            int spot = -1;
            
            //gather user input
            cout << "Enter the number of the location \n"
            << "of the \"X\" to move (Example: \"9\"): ";
            cin >> player;
            cout << endl;
            cout << "Enter the number of the location \n"
            << " of the spot to move to (Example: \"6\"): ";
            cin >> spot;
            
            // decrements the numbers to represent actual indices
            player--;
            spot--;
            
            // checks if numbers are within range
            if ((player < 0 || player > 8) || (spot < 0 || spot > 8))
            {
                cout << endl << "Invalid choice. Try again." << endl << endl;
                valid = false;
            }
            
            // if the input is valid continue with the game
            if (valid)
            {
                // reset the player to move with the number (+49 for ASCII)
                board[player] = (player + 49);
                // put the X in spot
                board[spot] = 'X';
                
                // creates a unique identifier for the current gameboard
                int iden = 0;
                for (int i = 0; i < 9; i++)
                {
                    if (i == 3 || i == 6)
                    {
                        iden *= 100;
                    }
                    if (board[i] == 'O')
                    {
                        iden += 1;
                    }
                    else if (board[i] == 'X')
                    {
                        iden += 4;
                    }
                    else
                    {
                        iden += (board[i] - 38);
                    }
                }
                
                //matches the gameboard to the tree node
                if (turnNode->left != nullptr && iden == turnNode->left->code)
                {
                    turnNode = turnNode->left;
                }
                else if (turnNode->middle != nullptr && iden == turnNode->middle->code)
                {
                    turnNode = turnNode->middle;
                }
                else if (turnNode->right != nullptr && iden == turnNode->right->code)
                {
                    turnNode = turnNode->right;
                }
                else if (turnNode->right->left != nullptr && iden == turnNode->right->left->code)
                {
                    turnNode = turnNode->right->left;
                }
                else if (turnNode->right->middle != nullptr && iden == turnNode->right->middle->code)
                {
                    turnNode = turnNode->right->middle;
                }
                // choice if the choice is not allowed
                else
                {
                    cout << endl << "Invalid choice. Try Again" << endl << endl;
                    valid = false;
                    
                    //reset the gameboard
                    for (int i = 0; i < 9; i++)
                    {
                        board[i] = turnNode->gBoard[i];
                    }
                }
                // if the turn is valid then it is O's turn
                if (valid)
                {
                    cout << endl;
                    cout << "O\'s turn: "<< endl;
                    displayBoard(turnNode);
                    turnNode = turnNode->left;
                    for (int i = 0; i < 9; i++)
                    {
                        board[i] = turnNode->gBoard[i];
                    }
                }
            }
        }
        while (!valid);
    }
}

//creates a tree beginning at node begin with depth
HEXNODE * Hexapawn::createTree(HEXNODE * begin, int depth)
{
    // case if depth is 0
    if (depth == 0)
    {
        return nullptr;
    }
    else
    {
        // create and initialize new node
        begin = new HEXNODE;
        begin->left = nullptr;
        begin->middle = nullptr;
        begin->right = nullptr;
        
        // initialize gameboard
        for (int i = 0; i < 9; i++)
        {
            if (i < 3)
            {
                begin->gBoard[i] = 'O';
            }
            else if (i > 5)
            {
                begin->gBoard[i] = 'X';
            }
            else
            {
                begin->gBoard[i] = ('1' + i);
            }
        }
        // continue tree for each node
        begin->left = createTree(begin->left, depth - 1);
        begin->middle = createTree(begin->middle, depth - 1);
        begin->right = createTree(begin->right, depth - 1);
        return begin;
    }
}

// deletes a tree starting at top
void Hexapawn::deleteTree(HEXNODE * top)
{
    if (top != nullptr)
    {
        deleteTree(top->left);
        deleteTree(top->middle);
        top->middle = nullptr;
        deleteTree(top->right);
        top->right = nullptr;
        
        delete top;
        return;
        
    }
}

// creates a unique code for each game state
HEXNODE * Hexapawn::createCode(HEXNODE * temp)
{
    int iden = 0;
    for (int i = 0; i < 9; i++)
    {
        if (i == 3 || i == 6)
        {
            iden *= 100;
        }
        if (temp->gBoard[i] == 'O')
        {
            iden += 1;
        }
        else if (temp->gBoard[i] == 'X')
        {
            iden += 4;
        }
        else
        {
            iden += (temp->gBoard[i] - 38);
        }

    }
    temp->code = iden;
    return temp;
}

// hardcodes all the possible game states into the tree
void Hexapawn::createGameTree()
{
    root = createTree(root, 7);
    
    HEXNODE * temp = root;
    temp = createCode(temp);
    HEXNODE * temp2 = root->left;
    for (int i = 0; i < 9; i++)
    {
        temp2->gBoard[i] = temp->gBoard[i];
    }
    temp2->gBoard[6] = '7';
    temp2->gBoard[3] = 'X';
    temp2 = createCode(temp2);
    
    HEXNODE * temp3 = temp2->left;
    for (int i = 0; i < 9; i++)
    {
        temp3->gBoard[i] = temp2->gBoard[i];
    }
    temp3->gBoard[1] = '2';
    temp3->gBoard[3] = 'O';
    temp3 = createCode(temp3);
    
    HEXNODE * temp4 = temp3->left;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[7] = '8';
    temp4->gBoard[3] = 'X';
    temp4 = createCode(temp4);
    
    HEXNODE * temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[2] = '3';
    temp5->gBoard[5] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    deleteTree(temp2->middle);
    temp2->middle = nullptr;
    deleteTree(temp2->right);
    temp2->right = nullptr;
    
    
    temp4 = temp3->middle;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[8] = '9';
    temp4->gBoard[5] = 'X';
    temp4 = createCode(temp4);
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[3] = '4';
    temp5->gBoard[6] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp4 = temp3->right;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[7] = '8';
    temp4->gBoard[4] = 'X';
    temp4 = createCode(temp4);
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[3] = '4';
    temp5->gBoard[6] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp2 = temp->middle;
    for (int i = 0; i < 9; i++)
    {
        temp2->gBoard[i] = temp->gBoard[i];
    }
    temp2->gBoard[7] = '8';
    temp2->gBoard[4] = 'X';
    temp2 = createCode(temp2);
    
    deleteTree(temp2->middle);
    temp2->middle = nullptr;
    deleteTree(temp2->right);
    temp2->right = nullptr;
    
    temp3 = temp2->left;
    for (int i = 0; i < 9; i++)
    {
        temp3->gBoard[i] = temp2->gBoard[i];
    }
    temp3->gBoard[2] = '3';
    temp3->gBoard[4] = 'O';
    temp3 = createCode(temp3);
    
    temp4 = temp3->left;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[6] = '7';
    temp4->gBoard[4] = 'X';
    temp4 = createCode(temp4);
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[0] = '1';
    temp5->gBoard[3] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    HEXNODE * temp6 = temp5->left;
    for (int i = 0; i < 9; i++)
    {
        temp6->gBoard[i] = temp5->gBoard[i];
    }
    temp6->gBoard[8] = '9';
    temp6->gBoard[5] = 'X';
    temp6 = createCode(temp6);
    
    deleteTree(temp6->middle);
    temp6->middle = nullptr;
    deleteTree(temp6->right);
    temp6->right = nullptr;
    
    HEXNODE * temp7 = temp6->left;
    for (int i = 0; i < 9; i++)
    {
        temp7->gBoard[i] = temp6->gBoard[i];
    }
    temp7->gBoard[3] = '4';
    temp7->gBoard[6] = 'O';
    temp7 = createCode(temp7);
    
    deleteTree(temp7->middle);
    temp7->middle = nullptr;
    deleteTree(temp7->right);
    temp7->right = nullptr;
    
    temp4 = temp3->middle;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[8] = '9';
    temp4->gBoard[4] = 'X';
    temp4 = createCode(temp4);
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[0] = '1';
    temp5->gBoard[3] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;

    temp4 = temp3->right;  //////////////////////////////
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[8] = '9';
    temp5->gBoard[5] = 'X';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    temp6 = temp5->left;
    for (int i = 0; i < 9; i++)
    {
        temp6->gBoard[i] = temp5->gBoard[i];
    }
    temp6->gBoard[4] = '5';
    temp6->gBoard[7] = 'O';
    temp6 = createCode(temp6);
    
    
    
    deleteTree(temp6->left);
    temp6->left = nullptr;
    deleteTree(temp6->middle);
    temp6->middle = nullptr;
    deleteTree(temp6->right);
    temp6->right = nullptr;
    
    temp5 = temp4->middle;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[6] = '7';
    temp5->gBoard[3] = 'X';
    temp5 = createCode(temp5);
    
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    temp6 = temp5->left;
    for (int i = 0; i < 9; i++)
    {
        temp6->gBoard[i] = temp5->gBoard[i];
    }
    temp6->gBoard[4] = '5';
    temp6->gBoard[7] = 'O';
    temp6 = createCode(temp6);
    
    deleteTree(temp6->left);
    temp6->left = nullptr;
    deleteTree(temp6->middle);
    temp6->middle = nullptr;
    deleteTree(temp6->right);
    temp6->right = nullptr;
    
    
    
    temp2 = temp->right;
    for (int i = 0; i < 9; i++)
    {
        temp2->gBoard[i] = temp->gBoard[i];
    }
    temp2->gBoard[8] = '9';
    temp2->gBoard[5] = 'X';
    temp2 = createCode(temp2);
    
    deleteTree(temp2->middle);
    temp2->middle = nullptr;
    deleteTree(temp2->right);
    temp2->right = nullptr;
    
    temp3 = temp2->left;
    for (int i = 0; i < 9; i++)
    {
        temp3->gBoard[i] = temp2->gBoard[i];
    }
    temp3->gBoard[1] = '2';
    temp3->gBoard[5] = 'O';
    temp3 = createCode(temp3);
    
    temp4 = temp3->left;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[6] = '7';
    temp4->gBoard[3] = 'X';
    temp4 = createCode(temp4);
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[5] = '6';
    temp5->gBoard[8] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    temp4 = temp3->middle;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[7] = '8';
    temp4->gBoard[4] = 'X';
    temp4 = createCode(temp4);
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[5] = '6';
    temp5->gBoard[8] = 'O';
    temp3 = createCode(temp3);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    temp4 = temp3->right;
    for (int i = 0; i < 9; i++)
    {
        temp4->gBoard[i] = temp3->gBoard[i];
    }
    temp4->gBoard[7] = '8';
    temp4->gBoard[5] = 'X';
    temp4 = createCode(temp4);
    
    deleteTree(temp4->middle);
    temp4->middle = nullptr;
    deleteTree(temp4->right);
    temp4->right = nullptr;
    
    temp5 = temp4->left;
    for (int i = 0; i < 9; i++)
    {
        temp5->gBoard[i] = temp4->gBoard[i];
    }
    temp5->gBoard[5] = '3';
    temp5->gBoard[8] = 'O';
    temp5 = createCode(temp5);
    
    deleteTree(temp5->left);
    temp5->left = nullptr;
    deleteTree(temp5->middle);
    temp5->middle = nullptr;
    deleteTree(temp5->right);
    temp5->right = nullptr;
    
    root = temp;
}
#endif /* Hexapawn_h */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>
#include<cmath>
using namespace std;
const int MAXIMUM = 50;
string wordFile;
ifstream otherFile;
ifstream myFile;
string puzzleFile;
string arrayDir[8] = { "right", "left", "down", "up", "left/down", "right/down", "left/up", "right/up" };
enum dir {LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, LEFT_DOWN, RIGHT_DOWN, LEFT_UP, RIGHT_UP};
struct wordSearchFind
{
    string word;
    bool found = false;
    int row;
    int column;
    dir where;
    int foundCount = 0;
};
struct wordSearchGame
{
    int numberRows;
    int numberColumns;
    char puzzleArr[MAXIMUM][MAXIMUM];
    int version=2;
};
bool readPuzzle(wordSearchGame& tempGame, string inputFile)
{
    char addedLetter = ' ';
    myFile.open(inputFile);
    if (!myFile)
        return false;
    myFile >> tempGame.numberRows;
    myFile >> tempGame.numberColumns;
    if(!(tempGame.numberRows>0) && !(tempGame.numberRows<51))
        return false;
    for (int x = 0; x < tempGame.numberRows; ++x)
    {
        for (int y = 0; y < tempGame.numberColumns; ++y)
        {
            if(!(myFile >> addedLetter))
            {
                return false;
            }
            tempGame.puzzleArr[x][y] = toupper(addedLetter);
            
        }
        
    }
    return true;
}
bool readWord(string inputFile)
{
    otherFile.open(inputFile);
    if (!otherFile.is_open())
    {
        return false;
    }
    otherFile.close();
    return true;
}
void displayPuzzle(wordSearchGame& tempGame)
{
    for (int x = 0; x < tempGame.numberRows; x++)
    {
        for (int y = 0; y < tempGame.numberColumns; y++)
        {
            cout << tempGame.puzzleArr[x][y];
        }
        cout << endl;
    }
}
bool upDown(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    
    for (int i = 0; i < tempGame.numberRows; i++)
    {
        for (int j = 0; j < tempGame.numberColumns; j++)
        {
            if (i + int(theFind.word.length()) - 1 < tempGame.numberRows)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i + int(k)][j];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = DOWN;
                }
            }
        }
    }
    return theFind.found;
}
bool downUp(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    for (int j = tempGame.numberRows-1; j > -1; j--)
    {
        for (int i = tempGame.numberColumns-1; i > -1; i--)
        {
            if (j - int(theFind.word.length()) + 1 > -1)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[j - int(k)][i];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = j + 1;
                    theFind.column = i + 1;
                    theFind.foundCount++;
                    theFind.where = UP;
                }
            }
        }
    }
    return theFind.found;
}
bool leftRight(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    for (int i = 0; i < tempGame.numberRows; i++)
    {
        for (int j = 0; j < tempGame.numberColumns; j++)
        {
            if (j + int(theFind.word.length()) - 1 < tempGame.numberColumns)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i][j + int(k)];
                }
                if (temp.compare(theFind.word)==0)
                {
                    
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = LEFT_RIGHT;
                }
            }
        }
    }
    return theFind.found;
}
bool rightLeft(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    
    for (int i = tempGame.numberRows - 1; i > -1; i--)
    {
        for (int j = tempGame.numberColumns - 1; j > -1; j--)
        {
            if (j - int(theFind.word.length()) + 1 > -1)
            {
                
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i][j - int(k)];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = RIGHT_LEFT;
                }
            }
        }
    }
    return theFind.found;
}

bool rightDown(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    for (int i = 0; i < tempGame.numberRows; i++)
    {
        for (int j = 0; j < tempGame.numberColumns; j++)
        {
            if (j + int(theFind.word.length()) - 1 <tempGame.numberColumns && i + int(theFind.word.length()) - 1 < tempGame.numberRows)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i + int(k)][j + int(k)];
                }
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = RIGHT_DOWN;
                }
            }
        }
    }
    return theFind.found;
}


bool leftDown(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    for (int i = 0; i < tempGame.numberRows; i++)
    {
        for (int j = tempGame.numberColumns; j > -1; j--)
        {
            if (j - int(theFind.word.length()) +1 > -1 && i + int(theFind.word.length()) - 1 < tempGame.numberRows)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i + int(k)][j - int(k)];
                }
                
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = LEFT_DOWN;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words diagonally left to up
bool leftUp(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    for (int i = tempGame.numberRows; i > -1; i--)
    {
        for (int j = 0; j < tempGame.numberColumns; j++)
        {
            if (j + int(theFind.word.length()) - 1 <tempGame.numberColumns && i - int(theFind.word.length()) + 1 > -1)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i - int(k)][j + int(k)];
                }
                
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = RIGHT_UP;
                }
            }
        }
    }
    return theFind.found;
}

//searches for words diagonally from right to up
bool rightUp(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    
    for (int i = tempGame.numberRows; i > -1; i--)
    {
        for (int j = tempGame.numberColumns; j > -1; j--)
        {
            if (j - int(theFind.word.length()) + 1 >-1 && i - int(theFind.word.length()) + 1 > -1)
            {
                string temp = "";
                for (unsigned int k = 0; k < theFind.word.length(); k++)
                {
                    temp += tempGame.puzzleArr[i - int(k)][j - int(k)];
                }
                
                if (temp.compare(theFind.word)==0)
                {
                    theFind.found = true;
                    theFind.row = i + 1;
                    theFind.column = j + 1;
                    theFind.foundCount++;
                    theFind.where = LEFT_UP;
                }
            }
        }
    }
    return theFind.found;
}
void findWord(wordSearchGame& tempGame, wordSearchFind& theFind)
{
    leftRight(tempGame, theFind);
    rightLeft(tempGame, theFind);
    upDown(tempGame, theFind);
    downUp(tempGame, theFind);
    leftDown(tempGame, theFind);
    rightDown(tempGame, theFind);
    leftUp(tempGame, theFind);
    rightUp(tempGame, theFind);
}

int main()
{
    wordSearchGame initGame;
    wordSearchFind word1;
    cout<< "Enter puzzle file name: ";
    cin >> puzzleFile;
    if (!readPuzzle(initGame, puzzleFile))
    {
        cout << "The puzzle file " << "\"" << puzzleFile << "\"" << " could not be opened or is invalid" << endl;
        return 0;
    }
    else
    {
        cout << "The puzzle from file " << "\"" << puzzleFile << "\"" << endl;
        displayPuzzle(initGame);
        cout<<"Enter file name containing words to search for: ";
        cin >> wordFile;
        if (!readWord(wordFile))
        {
            cout << "The puzzle file " << "\"" << wordFile << "\"" << " could not be opened or is invalid" << endl;
        }
        
        else
        {
            otherFile.open(wordFile);
            
            while(otherFile>>word1.word)
            {
                for(unsigned int i=0; i<word1.word.length(); i++)
                {
                    word1.word.at(i)=toupper(word1.word.at(i));
                }
                findWord(initGame, word1);
                if(word1.found)
                {
                    
                    if (word1.foundCount > 1)
                    {
                        cout << "The word " << word1.word << " was found " << word1.foundCount << " times" << endl;
                    }
                    
                    else if (word1.foundCount == 1)
                    {
                        cout << "The word " << word1.word << " was found at (" << word1.row << ", " << word1.column << ") - " << arrayDir[word1.where] << endl;
                    }
                }
                
                else
                {
                    cout << "The word " << word1.word << " was not found" << endl;
                }
                word1.found=false;
                word1.foundCount=0;
            }
        }
        
        
    }
    
    myFile.close();
    otherFile.close();
    return 0;
}

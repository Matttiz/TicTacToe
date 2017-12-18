#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool locationValidate(string location)
{
    bool validate = false;
    char characterFirst = location[0];
    char characterSecond = location[1];
    if ((characterFirst >= 49 && characterFirst <= 51) && (characterSecond >= 97 && characterSecond <= 99 )) {
        validate = true;
    } else {
        if ((characterSecond >= 49 && characterSecond <= 51) && (characterFirst >= 97 && characterFirst <= 99 )) {
            validate = true;
        }
    }
    if (location.length() != 2){
        validate = false;
    }
    if(!validate){
        cout << "You have input wrong location. Please try once again." << endl;
        cout << "Where do you want to put your sign."<< endl;
    }
    return validate;
}

void initialaizeCharArray(char *table, int size)
{
    for(int index = 0; index <= size; index++) {
        table [index] = ' ';
    }
}

void initialaizeIntArray(int *table, int size)
{
    for(int index = 0; index <= size; index++) {
        table[index] = 0;
    }
}

void writeCharArray(char *table, int size)
{
    for(int index = 0; index <= size; index++) {
        cout << table [index] << " ";
        if (((index + 1) % 3) == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void writeIntArray(int *table, int size)
{
    for(int index = 0; index < size; index++) {
        cout << table [index] << " ";
        if (((index + 1) % 3) == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void writeIntArrayWithMarks(char *table, int size)
{
    size = pow((sqrt(size) + 1),2);
    int sqrSize = sqrt(size);
    int variable;
    for(int index = 0; index < size; index++) {
        //.cout << table [index] << " ";
        switch(index) {
        case 0:
            cout << " ";
            break;
        case 1:
            cout << "a";
            break;
        case 2:
            cout << "b";
            break;
        case 3:
            cout << "c";
            break;
        case 4:
            cout << "1";
            break;
        case 8:
            cout << "2";
            break;
        case 12:
            cout << "3";
            break;
        default:
            variable = index  - sqrSize - (index / sqrSize);
            cout << table[variable];
            break;
        }
        cout << " ";
        if (((index + 1) % 4) == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

int locationToIndex(string location)
{
    int xAxis = 0;
    int yAxis = 0;
    int index = 0;
    char character = location[0];
    if (character >= 97 && character <= 99) {
        if (character == 'a') {
            xAxis = 0;
        };
        if (character == 'b') {
            xAxis = 1;
        };
        if (character == 'c') {
            xAxis = 2;
        };
        yAxis = (location[1] - 48);
        index = ((yAxis - 1) * 3) + xAxis;
    } else {
        character = location [1];
        if (character == 'a') {
            yAxis = 0;
        };
        if (character == 'b') {
            yAxis = 1;
        };
        if (character == 'c') {
            yAxis = 2;
        };
        yAxis = (location[0] - 48);
        index = ((xAxis - 1) * 3) + yAxis;
    }
    return index;
}

char oppositeSign(char sign)
{
    char opposite;
    if (sign == 'X') {
        opposite = 'O';
    } else {
        opposite = 'X';
    }
    return opposite;
}

int value (int index, char *charTable, char playerSign){
    int value = 0;
    if ( charTable[index] == playerSign){
        value = 1;
    };
    if ( charTable[index] == oppositeSign(playerSign)){
        value = -1;
    };
    return value;
}

int putOppositeSign (char *charTable, int *intTable, int size)
{

}

class TicTacToe
{
    friend istream &operator >>(istream &stream, TicTacToe &ticTacToe);
    friend ostream &operator <<(ostream &stream, const TicTacToe &ticTacToe);
public:
    TicTacToe();
    void writeTicTacToe();
    TicTacToe &putSign(char character, string location);
    char *getTicTacToeTable() const;
    char *getTicTacToeTable();
    char getChar() const;
    int getSize() const;
    int *getSignsInLine();
    int *getChanceToLoseOrWine();
    TicTacToe &setPlayerCharacter();
    TicTacToe &countSignsInLinesAndChanceToLoseOrWin();
    void areaIsOccupied (int &number, int index) const;
    //~TicTacToe();
private:
    int size = 9;
    char playerCharacter;
    char *ticTacTable = new char [size];
    int *signsInLine = new int [size];
    int *chanceToLoseOrWin = new int [size];
};

TicTacToe::TicTacToe()
{
    initialaizeCharArray(ticTacTable, size);
    initialaizeIntArray(signsInLine, size);
    initialaizeIntArray(chanceToLoseOrWin, size);
}

char *TicTacToe::getTicTacToeTable() const
{
    return ticTacTable;
}

char *TicTacToe::getTicTacToeTable()
{
    return ticTacTable;
}

int *TicTacToe::getSignsInLine(){
    return signsInLine;
}

int *TicTacToe::getChanceToLoseOrWine(){
    return chanceToLoseOrWin;
}

char TicTacToe::getChar() const
{
    return playerCharacter;
}

int TicTacToe::getSize() const
{
    return size;
}

TicTacToe &TicTacToe::setPlayerCharacter()
{
    string input;
    do {
        cout << "Choose your sign (X/O): " << endl;
        cin >> input;
    } while (input[0] != 'X' && input[0] != 'O');
    playerCharacter = input[0];
    return *this;
}

istream &operator >>(istream &stream, TicTacToe &ticTacToe)
{
    string location;
    do {
        location.clear();
        stream >> location;
    } while (!locationValidate(location));
    int index = locationToIndex(location);
    *(ticTacToe.getTicTacToeTable() + index) = ticTacToe.getChar();
    // mechanizmy aktualizujące pozostałe tabele
    ticTacToe.countSignsInLinesAndChanceToLoseOrWin();

    return stream;
}

ostream &operator <<(ostream &stream, const TicTacToe &ticTacToe)
{
    //writeIntArrayWithMarks(this -> ticTacToe, this -> size);
//    char *pointer = ticTacToe.getTicTacToeTable();
//    int size = ticTacToe.getSize();
    writeIntArrayWithMarks(ticTacToe.getTicTacToeTable(), ticTacToe.getSize());
    return stream;
}

void TicTacToe::writeTicTacToe()
{
    writeIntArrayWithMarks(ticTacTable, size);
    writeIntArray(signsInLine, size);
    writeIntArray(chanceToLoseOrWin, size);
}

TicTacToe &TicTacToe::putSign(char character, string location)
{
    int index = locationToIndex(location);
    ticTacTable[index] = character;

    // mechanizmy aktualizujące pozostałe tabele - wartość obliczania

    writeCharArray(ticTacTable, size);
    return *this;
}

void TicTacToe::areaIsOccupied (int &number, int index) const
{   
    char *charTable = (*this).getTicTacToeTable();
    char playerSign = (*this).getChar();
    char opposite = oppositeSign(playerSign);
    if(charTable[index] == opposite || charTable[index] == playerSign) {
        number++;
    }
}


//void countSignsInLines(char playerSign, char *charTable, int *signsInLine, int *chanceToLoseOrWin, int size)
TicTacToe &TicTacToe::countSignsInLinesAndChanceToLoseOrWin()
{
    char playerSign = (*this).getChar();
    char *charTable = (*this).getTicTacToeTable();
    int *signsInLine = (*this).getSignsInLine();
    int *chanceToLoseOrWin = (*this).getChanceToLoseOrWine();
    int singsNumberInLine;
    int valueInLine;
    for (int lineNumber = 0; lineNumber < 8; lineNumber++) {
        singsNumberInLine = 0;
        valueInLine = 0;
        switch(lineNumber) {
        case 0:
            for (int index = 0; index < 3; index++) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[0] = singsNumberInLine;
            chanceToLoseOrWin[0] = valueInLine;
            break;
        case 1:
            for (int index = 3; index < 6; index++) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[1] = singsNumberInLine;
            chanceToLoseOrWin[1] = valueInLine;
            break;
        case 2:
            for (int index = 6; index < 9; index++) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[2] = singsNumberInLine;
            chanceToLoseOrWin[2] = valueInLine;
            break;
        case 3:
            for (int index = 0; index < 9; index+=3) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[3] = singsNumberInLine;
            chanceToLoseOrWin[3] = valueInLine;
            break;
        case 4:
            for (int index = 1; index < 9; index+=3) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[4] = singsNumberInLine;
            chanceToLoseOrWin[4] = valueInLine;
            break;
        case 5:
            for (int index = 2; index < 9; index+=3) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[5] = singsNumberInLine;
            chanceToLoseOrWin[5] = valueInLine;
            break;
        case 6:
            for (int index = 0; index < 9; index+=4) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[6] = singsNumberInLine;
            chanceToLoseOrWin[6] = valueInLine;
            break;
        case 7:
            for (int index = 2; index < 7; index+=2) {
                (*this).areaIsOccupied(singsNumberInLine, index);
                valueInLine += value (index, charTable, playerSign);
            };
            signsInLine[7] = singsNumberInLine;
            chanceToLoseOrWin[7] = valueInLine;
            break;
        }
    }
    return *this;
}


int main()
{
    TicTacToe ticTacToe;
    //ticTacToe.writeTicTacToe();
    ticTacToe.setPlayerCharacter();
    //cout << ticTacToe;
    cout << "Where do you want to put your sign" << endl;
    cin >> ticTacToe;
    cout << ticTacToe;
    ticTacToe.writeTicTacToe();
}

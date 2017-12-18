#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool locationValidate(string location){
    bool validate = false;
    char characterFirst = location[0];
    char characterSecond = location[1];
    if ((characterFirst <= 49 && characterFirst <= 51) && (characterSecond <= 97 && characterSecond <= 99 )){
        validate = true;
    }else{
        if ((characterSecond <= 49 && characterSecond <= 51) && (characterFirst <= 97 && characterFirst <= 99 )){
            validate = true;
        }
    }
    return validate;
}

void initialaizeCharArray(char *table, int sizeCharTable){
    for(int index = 0; index <= sizeCharTable; index++){
        table [index] = ' ';
    }
}

void initialaizeIntArray(int *table, int sizeIntTable){
        for(int index = 0; index <= sizeIntTable; index++){
        table[index] = 0;
    }
}

void writeCharArray(char *table, int size){
    for(int index = 0; index <= size * size; index++){
        cout << table [index] << " ";
        if (((index + 1) % 3) == 0){
            cout << endl;
        }
    }
    cout << endl;
}

void writeIntArray(int *table, int size){
    for(int index = 0; index < size; index++){
        cout << table [index] << " ";
        if (((index + 1) % 3) == 0){
            cout << endl;
        }
    }
    cout << endl << endl;
}

void writeIntArrayWithMarks(char *table, int size){
   size = pow((sqrt(size) + 1),2);
   int sqrSize = sqrt(size);
   int variable;
    for(int index = 0; index < size; index++){
        //.cout << table [index] << " ";
            switch(index){
                case 0: cout << " ";
                        break;
                case 1: cout << "a";
                        break;
                case 2: cout << "b";
                        break;
                case 3: cout << "c";
                        break;
                case 4: cout << "1";
                        break;
                case 8: cout << "2";
                        break;
                case 12: cout << "3";
                        break;
                default: 
                        variable = index  - sqrSize - (index / sqrSize);
                        cout << table[variable];
                        break;
            }
            cout << " ";
        if (((index + 1) % 4) == 0){
            cout << endl;
        }
    }
    cout << endl;
}

int locationToIndex(string location){
    int xAxis = 0;
    int yAxis = 0;
    int index = 0;
    char character = location[0];
    if (character <= 97 && character <= 99){
      if (character == 'a'){
        xAxis = 0;
      };
      if (character == 'b'){
        xAxis = 1;
      };
      if (character == 'c'){
        xAxis = 2;
      };
      yAxis = (location[1] - 48);
      index = ((yAxis - 1) * 3) + xAxis;
    }else{
      cout << "Tutaj " << endl;
      character = location [1];
      if (character == 'a'){
        yAxis = 0;
      };
      if (character == 'b'){
        yAxis = 1;
      };
      if (character == 'c'){
        yAxis = 2;
      };
      yAxis = (location[0] - 48);
      index = ((xAxis - 1) * 3) + yAxis;
    }
    cout << index << endl;
    return index;
}

char oppositeSign(char sign){
  char opposite;
  if (sign == 'X'){
    opposite = 'O';
  }else{
    opposite = 'X';
  }
  return opposite;
}

int areaIsOccupied (int &number, int index, char *charTable, char playerSign){
  char opposite = oppositeSign(playerSign);
  if(charTable[index] == opposite || charTable[index] == playerSign){
                number++;
  }
  return number;
}


// zmiany do liczenia znaków swój znak powinien być przezroczysty dla linii, ale na polu powinno być 0
int countSignsInLines(char playerSign, char *charTable, int *intTable, int size){
  /*    Wygląd i numeracja linii 
        linie 1 2 3 to kolumny, linie 4 5  6 to wiersze, 7 8 diagonalne
                                  7 1 2 3 8
                                  4  | | 
                                    - - -
                                  5  | | 
                                    - - -
                                  6  | | 
  
  */
  
  char opposite = oppositeSign(playerSign);
  int singsNumberInLine;
   // tu będzie forek
   for (int lineNumber = 0; lineNumber < 8; lineNumber++){
   singsNumberInLine = 0;
  switch(lineNumber){
    case 0: for (int index = 0; index < 3; index++){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[0] = singsNumberInLine;
            break;
    case 1: for (int index = 3; index < 6; index++){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[1] = singsNumberInLine;
            break;
    case 2: for (int index = 6; index < 9; index++){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[2] = singsNumberInLine;
            break;
    case 3: for (int index = 0; index < 9; index+3){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[3] = singsNumberInLine;
            break;
    case 4: for (int index = 1; index < 9; index+3){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[4] = singsNumberInLine;
            break;
    case 5: for (int index = 2; index < 9; index+3){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[5] = singsNumberInLine;
            break;
    case 6: for (int index = 0; index < 9; index+4){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[6] = singsNumberInLine;
            break;
    case 7: for (int index = 2; index < 7; index+2){
              areaIsOccupied(singsNumberInLine, index, charTable, playerSign);
            };
            intTable[7] = singsNumberInLine;
            break;
    }
   }
}
  

int putOppositeSign (char *charTable, int *intTable, int size){
  
}

class TicTacToe{
    friend istream &operator >>(istream &stream, TicTacToe &ticTacToe);
    friend ostream &operator <<(ostream &stream, const TicTacToe &ticTacToe);
    public:
        TicTacToe();
        void writeTicTacToe();
        TicTacToe &putSign(char character, string location);
        char *getTicTacToeTable() const;
        char *getTicTacToeTable();
        char getChar();
        int getSize() const;
        TicTacToe &startGame();
        TicTacToe &setPlayerCharacter();
        TicTacToe &game();
        //~TicTacToe();
    private:
        int size = 3;
        char playerCharacter;
        char lastSignPlacedOnBoard;
        char *ticTacTable = new char [size * size];
        int *opportunity = new int [size * size];
        int *chanceToWin = new int [2 * size + 2];
        int *chanceToLose = new int [2 * size + 2];
};

TicTacToe::TicTacToe(){
    int sizeCharTable = size * size;
    int sizeIntTable = 2 * size + 2;
    //cout << size << " " << sizeCharTable << " " << sizeIntTable << endl;
    initialaizeCharArray(ticTacTable, sizeCharTable);
    initialaizeIntArray(opportunity, sizeCharTable);
    initialaizeIntArray(chanceToWin, sizeIntTable);
    initialaizeIntArray(chanceToLose, sizeIntTable);
}

// wstawienie znaku to obiektu

//zaprzyjaźnienie wypisywania i wczytywania
char *TicTacToe::getTicTacToeTable() const{
    return ticTacTable;
}

char *TicTacToe::getTicTacToeTable(){
    return ticTacTable;
}

char TicTacToe::getChar(){
    return playerCharacter;
}

int TicTacToe::getSize() const{
    return size;
}

TicTacToe &TicTacToe::setPlayerCharacter(){
    char character;
    // Pętla z walidacją
    do {
      cout << "Choose your sign (X/O): " << endl;
      cin >> character;
    } while (character != 'X' && character != 'O');
    playerCharacter = character;
    cout << endl;
    return *this;
}

istream &operator >>(istream &stream, TicTacToe &ticTacToe){
    string location;
    //do {
        stream >> location;
    //} while (locationValidate(location));
    int index = locationToIndex(location);
    //char character = ticTacToe.getChar();
    *(ticTacToe.getTicTacToeTable() + index) = ticTacToe.getChar();
    //ticTacTable[index] = character;
    
    // mechanizmy aktualizujące pozostałe tabele
    
    writeCharArray(ticTacToe.getTicTacToeTable(), ticTacToe.getSize());
    return stream;
}

ostream &operator <<(ostream &stream, const TicTacToe &ticTacToe){
    //writeIntArrayWithMarks(this -> ticTacToe, this -> size);
//    char *pointer = ticTacToe.getTicTacToeTable();
//    int size = ticTacToe.getSize();
    int sizeCharTable = ticTacToe.getSize() * ticTacToe.getSize();
    writeIntArrayWithMarks(ticTacToe.getTicTacToeTable(), sizeCharTable);
    return stream;
}

void TicTacToe::writeTicTacToe(){
    int sizeCharTable = size * size;
    int sizeIntTable = 2 * size + 2;
    writeIntArrayWithMarks(ticTacTable, sizeCharTable);
    writeIntArray(opportunity, sizeCharTable);
    writeIntArray(chanceToWin, sizeIntTable);
    writeIntArray(chanceToLose, sizeIntTable);
}

TicTacToe &TicTacToe::game(){
  (*this).setPlayerCharacter();
  if ((*this).getChar() == 'O'){
    cout << "Your move." << endl;
    //Twój ruch
    cin >> (*this);
  }else{
    cout << "Computer move." << endl;
    //ruch komputera
    cout << (*this);
  }
  return (*this);
}

TicTacToe &TicTacToe::putSign(char character, string location){
    int index = locationToIndex(location);
    ticTacTable[index] = character;
    
    // mechanizmy aktualizujące pozostałe tabele - wartość obliczania
    
    writeCharArray(ticTacTable, size);
    return *this;
}



int main(){
    TicTacToe ticTacToe;
    ticTacToe.writeTicTacToe();
    ticTacToe.setPlayerCharacter();
    // Pętla gry
    cout << ticTacToe;
    // napis mądrze wrzucić do metody;
    cout << "Where do you want to put yout sign" << endl;
    cin >> ticTacToe;
    cout << ticTacToe;
    // Koniec pętli gry
}

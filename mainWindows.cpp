#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <windows.h>

using namespace std;

map<string, vector<string>> berserkDeck = {
    {"Raider[1]", {"| |                    | |", "| |        /\\          | |", "| |       (oo)         | |", "| |       /||\\         | |", "| |      / || \\        | |", "| |      ||  ||        | |", "| |                    | |"}},
    {"Brute[2]", {"| |                    | |", "| |       ,\\_/,        | |", "| |      / o o \\       | |", "| |     (   ^   )      | |", "| |      \\_____/       | |", "| |        |||         | |", "| |                    | |"}},
    {"Berserker[2]", {"| |                    | |", "| |        \\^/         | |", "| |         |          | |", "| |        /v\\         | |", "| |       (o_o)        | |", "| |       / | \\        | |", "| |                    | |"}},
    {"Warlord[3]", {"| |                    | |", "| |        (X)         | |", "| |        / \\         | |", "| |       ( x )        | |", "| |        /|\\         | |", "| |       / | \\        | |", "| |                    | |"}},
    {"Furyborn[4]", {"| |                    | |", "| |        (^)         | |", "| |        >-<         | |", "| |       (o_o)        | |", "| |       /| |\\        | |", "| |      / | | \\       | |", "| |                    | |"}},
    {"Ravager[5]", {"| |                    | |", "| |        <@>         | |", "| |       (o_o)        | |", "| |       /|_|\\        | |", "| |       || ||        | |", "| |      /_   _\\       | |", "| |                    | |"}}
};

map<string, vector<string>> tankDeck = {
    {"Sentinel[1]", {"| |                    | |", "| |       [|||]        | |", "| |       / 0 \\        | |", "| |      /|_|_|\\       | |", "| |       ||   ||      | |", "| |                    | |", "| |                    | |"}},
    {"Defender[2]", {"| |                    | |", "| |       [###]        | |", "| |       / 0 \\        | |", "| |      / ||| \\       | |", "| |       | ||| |      | |", "| |                    | |", "| |                    | |"}},
    {"Bulwark[2]", {"| |                    | |", "| |       {|||}        | |", "| |        |||         | |", "| |       / 0 \\        | |", "| |        || ||       | |", "| |                    | |", "| |                    | |"}},
    {"Colossus[3]", {"| |                    | |", "| |        [@]         | |", "| |        |||         | |", "| |       /ooo\\        | |", "| |      / ||| \\       | |", "| |                    | |", "| |                    | |"}},
    {"Fortress[4]", {"| |                    | |", "| |       [___]        | |", "| |       |[O]|        | |", "| |       /| |\\        | |", "| |      / | | \\       | |", "| |                    | |", "| |                    | |"}},
    {"Bastion[5]", {"| |                    | |", "| |        [X]         | |", "| |        |||         | |", "| |        |   |       | |", "| |        ||_||       | |", "| |                    | |", "| |                    | |"}}

};

map<string, vector<string>> speederDeck = {
    {"Scout[1]", {"| |                    | |", "| |        o/~         | |", "| |        <|>         | |", "| |        / \\         | |", "| |                    | |", "| |                    | |", "| |                    | |"}},
    {"Skirmisher[2]", {"| |                    | |", "| |        ~o~         | |", "| |       <( )>        | |", "| |        / \\         | |", "| |                    | |", "| |                    | |", "| |                    | |"}},
    {"Rogue[2]", {"| |                    | |", "| |        YY          | |", "| |       (o_o)        | |", "| |        / \\         | |", "| |                    | |", "| |                    | |", "| |                    | |"}},
    {"Striker[3]", {"| |                    | |", "| |       (   )        | |", "| |       / o \\        | |", "| |       \\|||/        | |", "| |                    | |", "| |                    | |", "| |                    | |"}},
    {"Harrier[4]", {"| |                    | |", "| |       --0--        | |", "| |       / | \\        | |", "| |       <_ _>        | |", "| |                    | |", "| |                    | |", "| |                    | |"}},
    {"Wraith[5]", {"| |                    | |", "| |       ~~~~>        | |", "| |       (o_o)        | |", "| |        / \\         | |", "| |                    | |", "| |                    | |", "| |                    | |"}}
};

ostream& operator<<(ostream& s, vector<string> art) {
    for (unsigned short int i = 0; i < art.size(); i++) {
        s << art[i] << "\n";
    }
    return s;
}

void setFullScreen() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD topLeft = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(hOut, &screen);
    DWORD consoleSize = screen.dwSize.X * screen.dwSize.Y;

    FillConsoleOutputCharacter(hOut, ' ', consoleSize, topLeft, &written);
    FillConsoleOutputAttribute(hOut, screen.wAttributes, consoleSize, topLeft, &written);
    SetConsoleCursorPosition(hOut, topLeft);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

class Card {
protected:
    int health = 0;
    unsigned short int speed = 0;
    int attack = 0;
    unsigned short int cost = 0;
    string name = "";
    vector<string> art = {};
public:
    Card(int health = 0, unsigned short int speed = 0, int attack = 0, string name = " ", vector<string> art = {}, unsigned short int cost = 0) {
        this->health = health;
        this->speed = speed;
        this->attack = attack;
        this->name = name;
        this->art = art;
        this->cost = cost;
    }

    int getHealth() { return health; }
    unsigned short int getSpeed() { return speed; }
    int getAttack() { return attack; }
    unsigned short int getCost() { return cost; }
    string getName() { return name; }
    vector<string> getArt() { return art; }

    void setHealth(int health) { this->health = health; }

    void printCard() {
        int nameLenght = name.length();

        cout << "/------------------------\\\n";
        cout << "| /--------------------\\ |\n";
        cout << "| |" << name;

        for (int i = 0; i < 20 - nameLenght; i++) {
            cout << " ";
        }
        cout << "| |";
        cout << "\n| |--------------------| |\n";
        cout << art;
        cout << "| \\--------------------/ |\n";
        cout << "| 00 00       *    \\ | / |\n";
        cout << "|0000000     **    /---\\ |\n";
        cout << "| 00000    *****  //---\\\\|\n";
        cout << "|  000      **    \\-----/|\n";
        cout << "|  [" << health << "]";
        int spaceNumber = health > 9 ? 4 : 5;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }
        cout << "[" << speed << "]";
        spaceNumber = attack > 9 ? 4 : 5;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }
        cout << " [" << attack << "]";
        spaceNumber = speed > 9 ? 1 : 2;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }
        cout << "|\n";
        cout << "|                        |\n";
        cout << "\\------------------------/\n";
    }

    virtual vector<string> cardDetails() {
        vector<string> cardDetails;
        cardDetails.push_back(name);
        cardDetails.push_back(to_string(health));
        cardDetails.push_back(to_string(speed));
        cardDetails.push_back(to_string(attack));
        return cardDetails;
    };

    virtual void shuffleDeck() {};
    virtual Card getCard(int index) { return Card(); };
    virtual void printDeck() {};
    virtual void deckList() {};
    virtual void drawTopCard() {};
    virtual int getDeckSize() { return -1; };
};

class Board {
private:
    vector<Card> player1 = { Card(), Card(), Card() };
    vector<Card> player2 = { Card(), Card(), Card() };
    unsigned short int boardCounterP2 = 0;
    unsigned short int boardCounterP1 = 0;
public:
    Board() {
        player1 = { Card(), Card(), Card() };
        player2 = { Card(), Card(), Card() };
    }

    void addCard(Card card, int player) {
        if (player == 1) {
            player1[boardCounterP1] = card;
            if (boardCounterP1 > 2) {
                cout << "Board is full\n";
            }
            else {
                boardCounterP1 += 1;
            }
        }
        else {
            player2[boardCounterP2] = card;
            if (boardCounterP2 > 2) {
                cout << "Board is full\n";
            }
            else {
                boardCounterP2 += 1;
            }
        }
    }

    unsigned short int removeCardP1(int index) {
        if (index < 0 || index >= player1.size()) {
            cout << "Error: Invalid index (" << index << ")." << endl;
            return 0; // Return a meaningful default value or use exceptions
        }

        unsigned short int manaReturn;

        if (player1[index].getCost() > 0 and player1[index].getCost() <= 2) {
            manaReturn = player1[index].getCost();
        }
        else if (player1[index].getCost() >= 3) {
            manaReturn = 0;
        }

        player1.erase(player1.begin() + index);
        player1.push_back(Card());
        boardCounterP1 -= 1;

        return manaReturn;
    }


    void battle() {
        for (unsigned short int i = 0; i < 3; i++) {
            if (i >= player1.size() || i >= player2.size()) {
                continue;
            }

            if (player1[i].getSpeed() > player2[i].getSpeed()) {
                player2[i].setHealth(player2[i].getHealth() - player1[i].getAttack());
                if (player2[i].getHealth() <= 0) {
                    player2.erase(player2.begin() + i);
                    player2.push_back(Card());
                    boardCounterP2 -= 1;
                }
                else {
                    player1[i].setHealth(player1[i].getHealth() - player2[i].getAttack());
                    if (player1[i].getHealth() <= 0) {
                        player1.erase(player1.begin() + i);
                        boardCounterP1 -= 1;
                    }
                }
            }
            else if (player1[i].getSpeed() < player2[i].getSpeed()) {
                player1[i].setHealth(player1[i].getHealth() - player2[i].getAttack());
                if (player1[i].getHealth() <= 0) {
                    player1.erase(player1.begin() + i);
                    player1.push_back(Card());
                    boardCounterP1 -= 1;
                }
                else {
                    player2[i].setHealth(player2[i].getHealth() - player1[i].getAttack());
                    if (player2[i].getHealth() <= 0) {
                        player2.erase(player2.begin() + i);
                        player2.push_back(Card());
                        boardCounterP2 -= 1;
                    }
                }
            }
            else {
                player1[i].setHealth(player1[i].getHealth() - player2[i].getAttack());
                player2[i].setHealth(player2[i].getHealth() - player1[i].getAttack());
                if (player1[i].getHealth() <= 0) {
                    player1.erase(player1.begin() + i);
                    boardCounterP1 -= 1;
                }
                if (player2[i].getHealth() <= 0) {
                    player2.erase(player2.begin() + i);
                    player2.push_back(Card());
                    boardCounterP2 -= 1;
                }
            }
        }

        while (player2.size() < 3) {
            player2.push_back(Card());
        }

        while (player1.size() < 3) {
            player1.push_back(Card());
        }

        cout << endl << "/------------------------------------------------------------------------------------------------\\" << endl;
        switch (getBoardCounterP2()) {
        case 0:
            for (unsigned short int i = 0; i < 19; i++) {
                cout << endl;
            }
            break;
        case 1:
            oneCardBoard(getPlayer2());
            break;
        case 2:
            twoCardBoard(getPlayer2());
            break;
        case 3:
            threeCardBoard(getPlayer2());
            break;
        default:
            break;
        }
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        switch (getBoardCounterP1()) {
        case 0:
            for (unsigned short int i = 0; i < 19; i++) {
                cout << endl;
            }
            break;
        case 1:
            oneCardBoard(getPlayer1());
            break;
        case 2:
            twoCardBoard(getPlayer1());
            break;
        case 3:
            threeCardBoard(getPlayer1());
            break;
        default:
            break;
        }
        cout << "\\------------------------------------------------------------------------------------------------/" << endl;
        cin.get();
        cin.get();
    }

    vector<Card> getPlayer1() {
        return player1;
    }

    vector<Card> getPlayer2() {
        return player2;
    }

    int getBoardCounterP1() {
        return boardCounterP1;
    }

    int getBoardCounterP2() {
        return boardCounterP2;
    }

    void zeroCardBoard() {
        cout << endl << "/------------------------------------------------------------------------------------------------------------------------------------\\" << endl;
        for (unsigned short int i = 0; i < 19; i++) {
            cout << endl;
        }
        cout << "\\------------------------------------------------------------------------------------------------------------------------------------/" << endl;

    }

    void oneCardBoard(vector<Card> player) {
        player[0].printCard();
    }

    void twoCardBoard(vector<Card> player) {
        int nameLenght = player[0].getName().length();
        cout << "/------------------------\\          /------------------------\\\n";
        cout << "| /--------------------\\ |          | /--------------------\\ |\n";
        cout << "| |" << player[0].getName(); ;

        for (unsigned short int i = 0; i < 20 - nameLenght; i++) {
            cout << " ";
        }
        cout << "| |          | |" << player[1].getName();

        nameLenght = player[1].getName().length();
        for (unsigned short int i = 0; i < 20 - nameLenght; i++) {
            cout << " ";
        }
        cout << "| |\n";
        cout << "| |--------------------| |          | |--------------------| |\n";
        for (unsigned short int i = 0; i < 7; i++) {
            cout << player[0].getArt()[i] << "          " << player[1].getArt()[i] << endl;
        }

        cout << "| \\--------------------/ |          | \\--------------------/ |\n";
        cout << "| 00 00       *    \\ | / |          | 00 00       *    \\ | / | \n";
        cout << "|0000000     **    /---\\ |          |0000000     **    /---\\ |\n";
        cout << "| 00000    *****  //---\\\\|          | 00000    *****  //---\\\\|\n";
        cout << "|  000      **    \\-----/|          |  000      **    \\-----/|\n";

        cout << "|  [" << player[0].getHealth() << "]";
        int spaceNumber = player[0].getHealth() > 9 ? 4 : 5;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }

        cout << "[" << player[0].getAttack() << "]";
        spaceNumber = player[0].getSpeed() > 9 ? 4 : 5;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }

        cout << " [" << player[0].getSpeed() << "]";
        spaceNumber = player[0].getAttack() > 9 ? 1 : 2;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }

        cout << "|          | [" << player[1].getHealth() << "]";
        spaceNumber = player[1].getHealth() > 9 ? 4 : 5;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }

        cout << "[" << player[1].getAttack() << "]";
        spaceNumber = player[1].getAttack() > 9 ? 4 : 5;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }

        cout << "  [" << player[1].getSpeed() << "]";
        spaceNumber = player[1].getSpeed() > 9 ? 1 : 2;
        for (unsigned short int i = 0; i < spaceNumber; i++) {
            cout << " ";
        }
        cout << "|\n";
        cout << "|                        |          |                        |\n";
        cout << "\\------------------------/          \\------------------------/\n";
    }

    void threeCardBoard(vector<Card> player) {
        int nameLength[3];
        for (unsigned short int i = 0; i < 3; i++) {
            nameLength[i] = player[i].getName().length();
        }

        cout << "/------------------------\\          /------------------------\\          /------------------------\\\n";
        cout << "| /--------------------\\ |          | /--------------------\\ |          | /--------------------\\ |\n";

        for (int i = 0; i < 3; i++) {
            cout << "| |" << player[i].getName();
            for (unsigned short int j = 0; j < 20 - nameLength[i]; ++j) {
                cout << " ";
            }
            cout << "| |";
            if (i < 2) cout << "          ";
        }
        cout << "\n";

        cout << "| |--------------------| |          | |--------------------| |          | |--------------------| |\n";
        for (unsigned short int i = 0; i < 7; i++) {
            cout << player[0].getArt()[i] << "          "
                << player[1].getArt()[i] << "          "
                << player[2].getArt()[i] << endl;
        }

        cout << "| \\--------------------/ |          | \\--------------------/ |          | \\--------------------/ |\n";
        cout << "| 00 00       *    \\ | / |          | 00 00       *    \\ | / |          | 00 00       *    \\ | / |\n";
        cout << "|0000000     **    /---\\ |          |0000000     **    /---\\ |          |0000000     **    /---\\ |\n";
        cout << "| 00000    *****  //---\\\\|          | 00000    *****  //---\\\\|          | 00000    *****  //---\\\\|\n";
        cout << "|  000      **    \\-----/|          |  000      **    \\-----/|          |  000      **    \\-----/|\n";

        for (unsigned short int i = 0; i < 3; i++) {
            cout << "|  [" << player[i].getHealth() << "]";
            int spaceNumber = player[i].getHealth() > 9 ? 4 : 5;
            for (unsigned short int j = 0; j < spaceNumber; ++j) {
                cout << " ";
            }

            cout << "[" << player[i].getAttack() << "]";
            spaceNumber = player[i].getSpeed() > 9 ? 4 : 5;
            for (unsigned short int j = 0; j < spaceNumber; ++j) {
                cout << " ";
            }

            cout << " [" << player[i].getSpeed() << "]";
            spaceNumber = player[i].getAttack() > 9 ? 1 : 2;
            for (unsigned short int j = 0; j < spaceNumber; ++j) {
                cout << " ";
            }

            cout << "|";
            if (i < 2) cout << "          ";
        }
        cout << "\n";

        cout << "|                        |          |                        |          |                        |\n";
        cout << "\\------------------------/          \\------------------------/          \\------------------------/\n";
    }

    void fourCardBoard(vector<Card> player) {
        int nameLength[4];
        for (unsigned short int i = 0; i < 4; i++) {
            nameLength[i] = player[i].getName().length();
        }

        cout << "/------------------------\\          /------------------------\\          /------------------------\\          /------------------------\\\n";
        cout << "| /--------------------\\ |          | /--------------------\\ |          | /--------------------\\ |          | /--------------------\\ |\n";

        for (int i = 0; i < 4; i++) {
            cout << "| |" << player[i].getName();
            for (unsigned short int j = 0; j < 20 - nameLength[i]; ++j) {
                cout << " ";
            }
            cout << "| |";
            if (i < 3) cout << "          ";
        }
        cout << "\n";

        cout << "| |--------------------| |          | |--------------------| |          | |--------------------| |          | |--------------------| |\n";
        for (unsigned short int i = 0; i < 7; i++) {
            cout << player[0].getArt()[i] << "          "
                << player[1].getArt()[i] << "          "
                << player[2].getArt()[i] << "          "
                << player[3].getArt()[i] << endl;
        }

        cout << "| \\--------------------/ |          | \\--------------------/ |          | \\--------------------/ |          | \\--------------------/ |\n";
        cout << "| 00 00       *    \\ | / |          | 00 00       *    \\ | / |          | 00 00       *    \\ | / |          | 00 00       *    \\ | / |\n";
        cout << "|0000000     **    /---\\ |          |0000000     **    /---\\ |          |0000000     **    /---\\ |          |0000000     **    /---\\ |\n";
        cout << "| 00000    *****  //---\\\\|          | 00000    *****  //---\\\\|          | 00000    *****  //---\\\\|          | 00000    *****  //---\\\\|\n";
        cout << "|  000      **    \\-----/|          |  000      **    \\-----/|          |  000      **    \\-----/|          |  000      **    \\-----/|\n";

        for (unsigned short int i = 0; i < 4; i++) {
            cout << "|  [" << player[i].getHealth() << "]";
            int spaceNumber = player[i].getHealth() > 9 ? 4 : 5;
            for (unsigned short int j = 0; j < spaceNumber; ++j) {
                cout << " ";
            }

            cout << "[" << player[i].getAttack() << "]";
            spaceNumber = player[i].getSpeed() > 9 ? 4 : 5;
            for (unsigned short int j = 0; j < spaceNumber; ++j) {
                cout << " ";
            }

            cout << " [" << player[i].getSpeed() << "]";
            spaceNumber = player[i].getAttack() > 9 ? 1 : 2;
            for (unsigned short int j = 0; j < spaceNumber; ++j) {
                cout << " ";
            }

            cout << "|";
            if (i < 3) cout << "          ";
        }
        cout << "\n";

        cout << "|                        |          |                        |          |                        |          |                        |\n";
        cout << "\\------------------------/          \\------------------------/          \\------------------------/          \\------------------------/\n";
    }

};

class Berserk : public Card {
private:
    vector<Card> deck;
public:
    Berserk() {
        deck.push_back(Card(20, 5, 10, "Raider[1]", berserkDeck["Raider[1]"], 1));
        deck.push_back(Card(20, 5, 10, "Raider[1]", berserkDeck["Raider[1]"], 1));
        deck.push_back(Card(20, 5, 10, "Raider[1]", berserkDeck["Raider[1]"], 1));
        deck.push_back(Card(20, 5, 10, "Raider[1]", berserkDeck["Raider[1]"], 1));
        deck.push_back(Card(20, 5, 10, "Raider[1]", berserkDeck["Raider[1]"], 1));
        deck.push_back(Card(15, 7, 12, "Brute[2]", berserkDeck["Brute[2]"], 2));
        deck.push_back(Card(18, 6, 14, "Berserker[2]", berserkDeck["Berserker[2]"], 2));
        deck.push_back(Card(12, 8, 16, "Warlord[3]", berserkDeck["Warlord[3]"], 3));
        deck.push_back(Card(10, 9, 18, "Furyborn[4]", berserkDeck["Furyborn[4]"], 4));
        deck.push_back(Card(8, 10, 20, "Ravager[5]", berserkDeck["Ravager[5]"], 5));
    }

    vector<string> cardDetails(int index) {
        vector<string> cardDetails;
        cardDetails.push_back(deck[index].getName());
        cardDetails.push_back(to_string(deck[index].getHealth()));
        cardDetails.push_back(to_string(deck[index].getSpeed()));
        cardDetails.push_back(to_string(deck[index].getAttack()));
        cardDetails.push_back(to_string(deck[index].getCost()));
        return cardDetails;
    }

    void shuffleDeck() {
        for (int i = 0; i < deck.size(); i++) {
            int j = rand() % deck.size();
            swap(deck[i], deck[j]);
        }
    }

    Card getCard(int index) {
        return deck[index];
    }

    int getDeckSize() {
        return deck.size();
    }

    void printDeck() {
        for (int i = 0; i < deck.size(); i++) {
            deck[i].printCard();
        }
    }

    void deckList() {
        for (int i = 0; i < deck.size(); i++) {
            cout << deck[i].getName() << "\n";
        }
    }

    void drawTopCard() {
        Card first = deck.front();
        deck.erase(deck.begin());
    }
};

class Tank : public Card {
private:
    vector<Card> deck;
public:
    Tank() {
        deck.push_back(Card(30, 2, 5, "Sentinel[1]", tankDeck["Sentinel[1]"], 1));
        deck.push_back(Card(30, 2, 5, "Sentinel[1]", tankDeck["Sentinel[1]"], 1));
        deck.push_back(Card(30, 2, 5, "Sentinel[1]", tankDeck["Sentinel[1]"], 1));
        deck.push_back(Card(30, 2, 5, "Sentinel[1]", tankDeck["Sentinel[1]"], 1));
        deck.push_back(Card(30, 2, 5, "Sentinel[1]", tankDeck["Sentinel[1]"], 1));
        deck.push_back(Card(40, 3, 7, "Defender[2]", tankDeck["Defender[2]"], 2));
        deck.push_back(Card(45, 3, 8, "Bulwark[2]", tankDeck["Bulwark[2]"], 2));
        deck.push_back(Card(50, 4, 10, "Colossus[3]", tankDeck["Colossus[3]"], 3));
        deck.push_back(Card(55, 4, 12, "Fortress[4]", tankDeck["Fortress[4]"], 4));
        deck.push_back(Card(60, 5, 15, "Bastion[5]", tankDeck["Bastion[5]"], 5));
    }

    vector<string> cardDetails(int index) {
        vector<string> cardDetails;
        cardDetails.push_back(deck[index].getName());
        cardDetails.push_back(to_string(deck[index].getHealth()));
        cardDetails.push_back(to_string(deck[index].getSpeed()));
        cardDetails.push_back(to_string(deck[index].getAttack()));
        cardDetails.push_back(to_string(deck[index].getCost()));
        return cardDetails;
    }

    void shuffleDeck() {
        for (int i = 0; i < deck.size(); i++) {
            int j = rand() % deck.size();
            swap(deck[i], deck[j]);
        }
    }

    int getDeckSize() {
        return deck.size();
    }

    Card getCard(int index) {
        return deck[index];
    }

    void printDeck() {
        for (int i = 0; i < deck.size(); i++) {
            deck[i].printCard();
        }
    }

    void deckList() {
        for (int i = 0; i < deck.size(); i++) {
            cout << deck[i].getName() << "\n";
        }
    }

    void drawTopCard() {
        Card first = deck.front();
        deck.erase(deck.begin());
    }
};

class Speeder : public Card {

private:
    vector<Card> deck;
public:
    Speeder() {
        deck.push_back(Card(10, 10, 3, "Scout[1]", speederDeck["Scout[1]"], 1));
        deck.push_back(Card(10, 10, 3, "Scout[1]", speederDeck["Scout[1]"], 1));
        deck.push_back(Card(10, 10, 3, "Scout[1]", speederDeck["Scout[1]"], 1));
        deck.push_back(Card(10, 10, 3, "Scout[1]", speederDeck["Scout[1]"], 1));
        deck.push_back(Card(10, 10, 3, "Scout[1]", speederDeck["Scout[1]"], 1));
        deck.push_back(Card(12, 12, 4, "Skirmisher[2]", speederDeck["Skirmisher[2]"], 2));
        deck.push_back(Card(14, 15, 5, "Rogue[2]", speederDeck["Rogue[2]"], 2));
        deck.push_back(Card(16, 18, 6, "Striker[3]", speederDeck["Striker[3]"], 3));
        deck.push_back(Card(18, 20, 7, "Harrier[4]", speederDeck["Harrier[4]"], 4));
        deck.push_back(Card(20, 25, 8, "Wraith[5]", speederDeck["Wraith[5]"], 5));
    }


    vector<string> cardDetails(int index) {
        vector<string> cardDetails;
        cardDetails.push_back(deck[index].getName());
        cardDetails.push_back(to_string(deck[index].getHealth()));
        cardDetails.push_back(to_string(deck[index].getSpeed()));
        cardDetails.push_back(to_string(deck[index].getAttack()));
        cardDetails.push_back(to_string(deck[index].getCost()));
        return cardDetails;
    }

    void shuffleDeck() {
        for (int i = 0; i < deck.size(); i++) {
            int j = rand() % deck.size();
            swap(deck[i], deck[j]);
        }
    }

    Card getCard(int index) {
        return deck[index];
    }

    int getDeckSize() {
        return deck.size();
    }

    void printDeck() {
        for (int i = 0; i < deck.size(); i++) {
            deck[i].printCard();
        }
    }

    void deckList() {
        for (int i = 0; i < deck.size(); i++) {
            cout << deck[i].getName() << "\n";
        }
    }

    void drawTopCard() {
        Card first = deck.front();
        deck.erase(deck.begin());
    }
};

class Player {
private:
    int baseMana = 0;
    int actualMana = 0;
    string name = "";
public:
    Card* deck;
    vector<Card> hand = { Card(), Card(), Card(), Card() };

    Player(Card* deck, string name = "johnDoe") {
        this->deck = deck;
        this->name = name;
        deck->shuffleDeck();
        for (unsigned short int i = 0; i < 4; i++) {
            hand[i] = deck->getCard(i);
            deck->drawTopCard();
        }
    }

    void printMana() {
        cout << "  /-------\\ \n /         \\ \n \\   [" << actualMana << "]   /  [MANA] \n  \\       /   \n   \\-----/    \n";
    }

    int getMana() { return baseMana; }
    int getActualMana() { return actualMana; }
    string getName() { return name; }

    void addMana(int newMana = 0, bool newTurn = false) {
        if (newTurn && baseMana < 6) {
            baseMana += 1;
            if (baseMana >= 6) baseMana = 6;
            actualMana = baseMana;
        }

        if (newMana != 0) {
            actualMana += newMana;
            if (actualMana > 6) {
                actualMana = 6;
            }
            else if (actualMana < 0) {
                actualMana = 0;
            }
        }
    }


    void drawTopCard() {
        if (deck == nullptr) {
            cout << "Error: Deck is not initialized!" << endl;
            return;
        }
        if (deck->getDeckSize() == 0) {
            cout << "Error: Attempt to draw from an empty deck!" << endl;
            return;
        }
        if (hand.size() < 4) {
            hand.push_back(deck->getCard(0));
            deck->drawTopCard();
        }
        else {
            cout << "Hand is full. Cannot draw more cards." << endl;
        }
    }

    void removeCard(int index) {
        if (hand.empty()) {
            cout << "Error: Cannot remove a card from an empty hand!" << endl;
            return;
        }
        if (index < 0 || index >= hand.size()) {
            cout << "Error: Invalid index (" << index << ") for removeCard. Valid range: 0 to " << hand.size() - 1 << "." << endl;
            return;
        }

        hand.erase(hand.begin() + index);
    }

    void printHand() {
        Board board;
        switch (hand.size()) {
        case 0:
            board.zeroCardBoard();
            break;
        case 1:
            board.oneCardBoard(hand);
            break;
        case 2:
            board.twoCardBoard(hand);
            break;
        case 3:
            board.threeCardBoard(hand);
            break;
        case 4:
            board.fourCardBoard(hand);
            break;
        default:
            cout << "Error: Invalid hand size!" << endl;
            break;
        }
    }

};

Card* selectDeck(int choice) {
    static Berserk berserkDeck;
    static Tank tankDeck;
    static Speeder speederDeck;

    switch (choice) {
    case 1: return &berserkDeck;
    case 2: return &tankDeck;
    case 3: return &speederDeck;
    default:
        int randomDeck = rand() % 3 + 1;
        return selectDeck(randomDeck);
    }
}

void printBoardP1(Board board, bool breakMode = false) {
    if (breakMode) cout << endl << "/------------------------------------------------------------------------------------------------\\" << endl;
    switch (board.getBoardCounterP1()) {
    case 0:
        for (unsigned short int i = 0; i < 19; i++) {
            cout << endl;
        }
        break;
    case 1:
        board.oneCardBoard(board.getPlayer1());
        break;
    case 2:
        board.twoCardBoard(board.getPlayer1());
        break;
    case 3:
        board.threeCardBoard(board.getPlayer1());
        break;
    default:
        cout << "Board is empty" << endl;
        break;
    }
    if (breakMode) cout << "\\------------------------------------------------------------------------------------------------/" << endl;
}

void printBoardP2(Board board) {
    switch (board.getBoardCounterP2()) {
    case 0:
        for (unsigned short int i = 0; i < 19; i++) {
            cout << endl;
        }
        break;
    case 1:
        board.oneCardBoard(board.getPlayer2());
        break;
    case 2:
        board.twoCardBoard(board.getPlayer2());
        break;
    case 3:
        board.threeCardBoard(board.getPlayer2());
        break;
    default:
        cout << "Board is empty" << endl;
        break;
    }
}

int main() {
    srand(time(0));
    setFullScreen();
    unsigned short int choice = 0;
    string userName = "";
    bool gameEnded = false;

    cout << R"(
     __  _       ____  _____ __ __      _____  ____    ___   ____   ______ 
    /  ]| T     /    T/ ___/|  T  T    |     ||    \  /   \ |    \ |      T
   /  / | |    Y  o  (   \_ |  l  |    |   __j|  D  )Y     Y|  _  Y|      |
  /  /  | l___ |     |\__  T|  _  |    |  l_  |    / |  O  ||  |  |l_j  l_j
 /   \_ |     T|  _  |/  \ ||  |  |    |   _] |    \ |     ||  |  |  |  |  
 \     ||     ||  |  |\    ||  |  |    |  T   |  .  Yl     !|  |  |  |  |  
  \____jl_____jl__j__j \___jl__j__j    l__j   l__j\_j \___/ l__j__j  l__j)" << endl;

    cout << "Inserisci il nome utente: ";
    cin >> userName;

    for (auto& c : userName) c = tolower(c);

    cout << "Benvenuto " << userName << "!" << endl;

    do {
        cout << "Premi 1 per far partire la partita" << endl;
        cout << "Premi 2 per le regole" << endl;
        cout << "Premi 3 per uscire" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            int deckChoice = 0;
            cout << "Scegli uno dei 3 mazzi:";
            cout << "\n\t1: Berserk deck [+ATK, /SPD, -HTH]";
            cout << "\n\t2: Tank deck [+HTH, /ATK, -SPD]";
            cout << "\n\t3: Speeder deck [+SPD, /HTH, -ATK]";
            cin >> deckChoice;

            Player player1(selectDeck(deckChoice), userName);
            Player player2(selectDeck(rand() % 3 + 1));

            cout << R"(
  _____ ______   ____  ____  ______ 
 / ___/|      T /    T|    \|      T
(   \_ |      |Y  o  ||  D  )      |
 \__  Tl_j  l_j|     ||    /l_j  l_j
 /  \ |  |  |  |  _  ||    \  |  |  
 \    |  |  |  |  |  ||  .  Y |  |  
  \___j  l__j  l__j__jl__j\_j l__j  )" << endl;

            cin.get();
            cin.get();

            Board board;

            do {
                setFullScreen();
                if (player1.getMana() == 6) {
                    player1.addMana(6, true);
                    player2.addMana(6, true);
                }
                else {
                    player1.addMana(0, true);
                    player2.addMana(0, true);
                }
                unsigned short int cardChoice;

                if (board.getBoardCounterP1() != 3) {
                    if (player1.hand.size() > 0 and player1.hand.size() <= 4 and board.getBoardCounterP1() < 3 or player1.deck->getDeckSize() > 0) {
                        if (player1.hand.size() >= 0 and player1.hand.size() < 4) {
                            player1.drawTopCard();
                        }

                        unsigned short int cardChoice;
                        bool breakMode = false;
                        bool breakModeHappened = false;
                        do {
                            cout << player1.getName() << ", select a card to play (1-" << player1.hand.size() << "):" << endl;
                            player1.printHand();
                            player1.printMana();
                            cout << "Press 0 to end turn" << endl << "Press 5 to break cards in exchange for mana (ONLY ONCE)" << endl;
                            cin >> cardChoice;
                            if (cardChoice == 0) {
                                break;
                            }
                            else if (cardChoice == 5 and breakModeHappened == false) {
                                breakMode = true;
                                breakModeHappened = true;
                            }

                            if (breakMode) {
                                setFullScreen();
                                do {
                                    cout << "Select a card to break (1-" << player1.hand.size() << "):" << endl;
                                    printBoardP1(board, true);
                                    cin >> cardChoice;
                                } while (cardChoice < 0 or cardChoice > board.getBoardCounterP1());

                                breakMode = false;
                                player1.addMana(board.removeCardP1(cardChoice - 1));
                                cardChoice = 0;
                            }

                            if (cardChoice < 0 or cardChoice > player1.hand.size() or player1.hand[cardChoice - 1].getCost() > player1.getActualMana()) {
                                setFullScreen();
                                if (cardChoice != 5) cout << "Invalid choice. Please try again." << endl;
                            }
                            else if (cardChoice != 0 or player1.hand[cardChoice - 1].getCost() < player1.getActualMana()) {
                                board.addCard(player1.hand[cardChoice - 1], 1);
                                player1.addMana(-player1.hand[cardChoice - 1].getCost());
                                player1.removeCard(cardChoice - 1);
                                setFullScreen();
                            }
                            if (board.getBoardCounterP1() == 3) {
                                cout << "You have reached the maximum number of cards on the board." << endl;
                                break;
                            }
                        } while (cardChoice < 1 or cardChoice > player1.hand.size() or player1.hand[cardChoice - 1].getCost() > player1.getActualMana() or player1.getActualMana() > 0);
                    }
                }

                setFullScreen();

                if (board.getBoardCounterP2() != 3) {
                    if (player2.hand.size() > 0 and player2.hand.size() <= 4 and board.getBoardCounterP2() < 3 or player2.deck->getDeckSize() > 0) {
                        if (player2.hand.size() >= 0 and player2.hand.size() < 4) {
                            player2.drawTopCard();
                        }

                        do {
                            cout << "Player 2, select a card to play (1-" << player2.hand.size() << "):" << endl;
                            player2.printHand();
                            player2.printMana();
                            cardChoice = rand() % player2.hand.size() + 1;
                            bool canPlayCard = false;
                            for (unsigned short int i = 0; i < player2.hand.size(); i++) {
                                if (player2.hand[i].getCost() <= player2.getActualMana()) {
                                    canPlayCard = true;
                                    break;
                                }
                            }
                            if (!canPlayCard) {
                                break;
                            }
                            if (cardChoice < 1 or cardChoice > player2.hand.size() or player2.hand[cardChoice - 1].getCost() > player2.getActualMana()) {
                                setFullScreen();
                                cout << "Invalid choice. Please try again." << endl;
                            }
                        } while (cardChoice < 1 or cardChoice > player2.hand.size() or player2.hand[cardChoice - 1].getCost() > player2.getActualMana());

                        board.addCard(player2.hand[cardChoice - 1], 2);
                        player2.addMana(-player2.hand[cardChoice - 1].getCost());
                        player2.removeCard(cardChoice - 1);
                    }
                }

                setFullScreen();

                cout << endl << "/------------------------------------------------------------------------------------------------\\" << endl;
                printBoardP2(board);
                cout << "--------------------------------------------------------------------------------------------------" << endl;
                printBoardP1(board);
                cout << "\\------------------------------------------------------------------------------------------------/" << endl;

                cin.get();
                cin.get();

                if (board.getBoardCounterP1() == 3 and board.getBoardCounterP2() == 3) {
                    cout << R"( 
 ____    ____  ______  ______  _        ___           _____ ______   ____  ____  ______ 
|    \  /    T|      T|      T| T      /  _]         / ___/|      T /    T|    \|      T
|  o  )Y  o  ||      ||      || |     /  [_         (   \_ |      |Y  o  ||  D  )      |
|     T|     |l_j  l_jl_j  l_j| l___ Y    _]         \__  Tl_j  l_j|     ||    /l_j  l_j
|  O  ||  _  |  |  |    |  |  |     T|   [_          /  \ |  |  |  |  _  ||    \  |  |  
|     ||  |  |  |  |    |  |  |     ||     T         \    |  |  |  |  |  ||  .  Y |  |  
l_____jl__j__j  l__j    l__j  l_____jl_____j          \___j  l__j  l__j__jl__j\_j l__j)" << endl;
                    board.battle();
                }

            } while ((player1.deck->getDeckSize() > 0 and player2.deck->getDeckSize() > 0) and (player1.hand.size() > 0 || player2.hand.size() > 0));

            if ((board.getBoardCounterP1() == 0 and player1.deck->getDeckSize() == 0) or (board.getBoardCounterP2() > board.getBoardCounterP1())) {
                cout << R"(
 __ __   ___   __ __          _       ___    _____   ___ 
|  T  T /   \ |  T  T        | T     /   \  / ___/  /  _]
|  |  |Y     Y|  |  |        | |    Y     Y(   \_  /  [_ 
|  ~  ||  O  ||  |  |        | l___ |  O  | \__  TY    _]
l___, ||     ||  :  |        |     T|     | /  \ ||   [_ 
|     !l     !l     |        |     |l     ! \    ||     T
l____/  \___/  \__,_j        l_____j \___/   \___jl_____j)" << endl;
            }
            else if ((board.getBoardCounterP2() == 0 and player2.deck->getDeckSize() == 0) or (board.getBoardCounterP1() > board.getBoardCounterP2())) {
                cout << R"(
 __ __   ___   __ __          __    __  ____  ____  
|  T  T /   \ |  T  T        |  T__T  Tl    j|    \
|  |  |Y     Y|  |  |        |  |  |  | |  T |  _  Y
|  ~  ||  O  ||  |  |        |  |  |  | |  | |  |  |
l___, ||     ||  :  |        l  `  '  ! |  | |  |  |
|     !l     !l     |         \      /  j  l |  |  |
l____/  \___/  \__,_j          \_/\_/  |____jl__j__j
                                                    )" << endl;
            }
            else if ((board.getBoardCounterP1() == board.getBoardCounterP2()) and (player1.deck->getDeckSize() == player2.deck->getDeckSize())) {
                cout << R"(
 ___    ____    ____  __    __ 
|   \  |    \  /    T|  T__T  T
|    \ |  D  )Y  o  ||  |  |  |
|  D  Y|    / |     ||  |  |  |
|     ||    \ |  _  |l  `  '  !
|     ||  .  Y|  |  | \      / 
l_____jl__j\_jl__j__j  \_/\_/  
                               )" << endl;
            }
            gameEnded = true;

            cin.get();
            cin.get();

            cout << R"( 
 ____   __ __    ___ 
|    \ |  T  T  /  _]
|  o  )|  |  | /  [_ 
|     T|  ~  |Y    _]
|  O  |l___, ||   [_ 
|     ||     !|     T
l_____jl____/ l_____j)" << endl;

            return 0;
            break;
        }
        case 2: {
            cout << R"( 
 ____   __ __  _        ___  _____
|    \ |  T  T| T      /  _]/ ___/
|  D  )|  |  || |     /  [_(   \_ 
|    / |  |  || l___ Y    _]\__  T
|    \ |  :  ||     T|   [_ /  \ |
|  .  Yl     ||     ||     T\    |
l__j\_j \__,_jl_____jl_____j \___j
                                  
The game starts asking you to choose the deck you wnat ot play with by inserting the number of the deck you want to play with.
The game will then shuffle the deck and deal 4 cards to the player and 4 cards to the computer.
Every turn the player will have to choose a card at the cost of mana. The starting mana is 1, and it will increase by 1 every turn.
The mana can also be obtained by breaking one card, but pay attention, you can only break one card per game.
Breaking card will give the player mana, but only for cards with 1 or 2 of cost of mana, the cards with greater mana cost will not give any mana.
When the player will have placed all the cards on the board (3), the battle will start.
The battle will be based by the speed of the cards, the fastest card in the column will attack first, then the other card will attack and so on.
If a card is defeated it will be removed from the board, granting the player the possibility to refill the board. 
The player that will empty the deck first will lose the game.)" << endl;
            break;
        }
        default: {
            cout << R"( 
 ____   __ __    ___ 
|    \ |  T  T  /  _]
|  o  )|  |  | /  [_ 
|     T|  ~  |Y    _]
|  O  |l___, ||   [_ 
|     ||     !|     T
l_____jl____/ l_____j)" << endl;
            break;
        }
        }


    } while (choice != 3 or gameEnded == true);
    return 0;
}
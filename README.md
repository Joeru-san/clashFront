# clashFront

clashFront is a C++ game that can be played entirely from the terminal. It's an academic project made for "Nautilus Academy".


# DISCLAIMER
The mainLinux.cpp file is the first version of the game, developed on Arch Linux. The game was then ported to Windows due to Windows terminal not supporting UTF-8 characters and some other bugs, the mainWindows.cpp file is the ported version of the game.

The Windows version will only have graphical differences, the game is the same of game you can play in Linux.

In the release section you can find the compiled version of the game for Windows and Linux.
Due to myself that i don't like to have VMs (lol), if you notice some bugs on the Windows release, open a pull request or an issue and i will fix it as soon as possible. THANKS
# gamePlay

The game is a turn-based card game. The player chooses the name a deck among these 3:
 - Berserk deck: high attack, medium health, low speed
 - Tank deck: high health, medium attack, low speed
 - Speed deck: high speed, medium attack, low health

The computer will choose a random deck and then the game will start.
The game will then shuffle the deck and deal 4 cards to the player and 4 cards to the computer.
Every turn the player will have to choose a card at the cost of mana. The starting mana is 1, and it will increase by 1 every turn for a maximum of 6.
The mana can also be obtained by breaking one card, but pay attention, you can only break one card per game.
Breaking card will give the player mana, but only for cards with 1 or 2 of cost of mana, the cards with greater mana cost will not give any mana.
When the player will have placed all the cards on the board (3), the battle will start.
The battle will be based by the speed of the cards, the fastest card in the column will attack first, then the other card will attack and so on.
If a card is defeated it will be removed from the board, granting the player the possibility to refill the board. 
The player that will empty the deck first will lose the game.)
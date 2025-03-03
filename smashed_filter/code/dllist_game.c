#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "mydllist.c"
#define PLAYERLIMIT 5
#define NUMBER_OF_CARDS 13
typedef enum {true, false} bool;

void whosGo(struct Node* CurrentPlayer, struct Node* PreviousPlayer , struct Node* sentinel){

  printf ("***%s it is your go!***\n", CurrentPlayer->data);

  if (CurrentPlayer->prev != sentinel) {
    PreviousPlayer = CurrentPlayer->prev;
    
  }
  else {
    PreviousPlayer = sentinel->next;
  }
}

void whosNext(struct Node* CurrentPlayer, struct Node* PreviousPlayer, struct Node* sentinel){

  if (CurrentPlayer->next != sentinel) {
    CurrentPlayer = CurrentPlayer->next;
  }
  else {
    CurrentPlayer = sentinel->prev;
  }
}

void printCurrentCard(int currentCard){

  if (currentCard < 11) {
        printf("\nThe current card is a %d.\n", currentCard);
    }
    else if (currentCard == 11) {
        printf("\nThe current card is a jack.\n");
    }
    else if (currentCard == 12) {
        printf("\nThe current card is a queen.\n");
    }
    else if (currentCard == 13) {
        printf("\nThe current card is a king.\n");
    }
    else if (currentCard == 14) {
        printf("\nThe current card is an ace.\n");
    }   
}

bool areWeFinished(struct Node* CurrentPlayer, struct Node* sentinel){

  bool PlayGame = true;
  if ((CurrentPlayer->next == sentinel) && (CurrentPlayer->prev == sentinel)) {
    PlayGame = false;
  }
  return PlayGame;
}

int main(int argc, char *argv[]) {

//Entering all player names into the doubly linked list
printf ("Enter the names of the players. Press Enter after each new player\n");
printf ("Must have 5 Players'.'\n\n");

int entered_players = 1;
char name[20];

while ((entered_players <= PLAYERLIMIT)) {
    printf("Player: ");
    scanf ("%s", name);
    InsertAtHead(name);
    entered_players++;
}

PrintHead();

//Starting the Game

//Initialising Variables for the game
int nextCard = 0;
int currentCard = 0;
int score = 0;
char oppositeGuess[20] = "";
int userChoice = 0 ;
bool playGame = true;
struct Node* CurrentPlayer = head;
struct Node* PreviousPlayer = head->prev;

//Setting up the random cards
int range = NUMBER_OF_CARDS;
srand(time(NULL));

nextCard = rand() % range + 2;
currentCard = rand() % range + 2;

while (playGame == true) {

    //Change current card to past card before creating a new current card
    currentCard = nextCard;

    //generate a random int for card
    nextCard = rand() % range + 2;

    printCurrentCard(currentCard);

    whosGo(CurrentPlayer, PreviousPlayer, sentinel);

    printf("Will the next card be higher(1) or lower(2)?\n");
    scanf("%d", &userChoice);
    printf("\n");
    printf ("***%s would you like to guess the opposite?***\n", PreviousPlayer->data);
    
    scanf("%s", oppositeGuess);

    if (strncmp(oppositeGuess, "Yes", 4) == 0) {

        if (userChoice == 1) {
            if (currentCard < nextCard) {
                printf("\nSorry, %s was correct. You are out!\n", CurrentPlayer->data);
                DeleteEntry(PreviousPlayer);

            }
            else if (currentCard > nextCard) {
                printf ("Congratulations! player %s was wrong and is now out!\n", CurrentPlayer->data);
                DeleteEntry(CurrentPlayer);

            }
            else if (currentCard == nextCard){
                printf("\nCards were equal. Next players turn.\n");
            }
        }
        else if (userChoice == 2) {
            if (currentCard < nextCard) {
                printf("Congratulations! player %s was wrong and is now out!\n", CurrentPlayer->data);
                DeleteEntry(CurrentPlayer);

            }
            else if (currentCard > nextCard) {
                printf ("\nSorry, %s was correct. You are out!\n", CurrentPlayer->data);
                DeleteEntry(PreviousPlayer);

            }
            else if (currentCard == nextCard){
                printf("\nCards were equal. Next players turn.\n");
            }
        }
    }
    if (strncmp(oppositeGuess, "No", 4) == 0) {

        if (userChoice == 1) {
            if (currentCard > nextCard) {
                printf ("\nSorry you have guessed incorrectly, you are out!\n");
                DeleteEntry(CurrentPlayer);

            }

            else if (currentCard < nextCard) {
                printf("\nCongratualtions you were correct, next players turn.\n");
            }
            else if (currentCard == nextCard) {
                printf("\nThe cards are the same. Next players turn.\n");
            }
        }
        else if (userChoice == 2) {
            if (currentCard > nextCard) {
                printf ("\nCongratualtions you were correct, next players turn.\n");

            }
            else if (currentCard < nextCard) {
                printf("\nSorry you have guessed incorrectly, you are out!\n");
                DeleteEntry(CurrentPlayer);
            }
            else if (currentCard == nextCard) {
                printf("\nThe cards are the same. Next players turn.\n");
            }
        }
        else {
            printf("\nPlease enter a valid choice.\n");
        }
    }
    
    PrintHead();

    whosNext(CurrentPlayer, PreviousPlayer, sentinel);
    
    playGame = areWeFinished(CurrentPlayer, sentinel);

 }
 printf("%s you are the Winner!\n", CurrentPlayer->data);
}

//Christopher Deluigi
//Dr. Steinberg
//COP3223C Section 1
//Large Program 3

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define SIZE 20

void rules(void); //display rules of the game
void maskWord (char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no

int main()
{
    //points to file word and opens it
    FILE * fp;
    fp = fopen("words.txt", "r");
    char answer[SIZE];
    char starword[SIZE];
    

    //calls function that prints the rules out for user
    rules();

    int choice = 1; //sets Variable to 1 so loop begins 
    
    do
    {
        //once word file is open, it gets scanned for each word on each line
        fscanf(fp, "%s", answer);
        int size = strlen(answer); //checks to see how long the string (the word) is

        //runs function that checks the size of the string and prints asterisks for how ever long the current word is
        maskWord(starword, size);

        // checks to see what was returned from function playROund
        //if user won, 1 is retuned and if anything else is retuned lose statement gets printed, and if user win 1 is returned and victory statement is printed
        int win_lose = playRound(starword, answer);
        if (win_lose == 1)
            printf("Congratulations! You won! The word was %s\n", answer);
        else
            printf("Sorry you did not win the round. The word was %s.\n", answer);

        playAgain(&choice); // asks user is they want to play another game
    }
    while (choice != 2);

    //if user doesnt want to play then file gets closed
    fclose(fp);

    printf("Thank you for playing today!\n"); //prints end statement
    return 0;
}


void rules(void)
{ //prints the user rules on how to play
    printf("Welcome to the Hangman Game!\n");
    printf("************************************************************************\n");
    printf("Here are the rules.\n");
    printf("I will provide you a set of * characters for each round.\n");
    printf("Each * represents a letter in the English Alphabet.\n");
    printf("You must figure out each letter of the missing word.\n");
    printf("For every correct letter guessed, I will reveal its place in the word.\n");
    printf("Each mistake will result in a strike.\n");
    printf("6 strikes will result in a loss that round.\n");
    printf("Are you ready? Here we go!\n");
    printf("************************************************************************\n");

}

void maskWord (char starword[], int size)
{
    for (int sp = 0; sp < size; ++sp) //uses if statement to check how long the word is, and how ever may characters it is, it gets *** so user cant see word until letters are guessed
    {
        starword[sp] = '*';
        starword[sp + 1] = '\0'; //runs until whole word is checked
    }
}

int playRound(char starword[], char answer[])
{
    int strikes = 0; //creates variables to saved the amount of strikes/the amount of wrong guesss the user has, starts at 0
    int size = strlen(answer); //checks to see how long the string (the word) is 

    char guessed_letters[SIZE]; //creates string for guessed user letters to be stored
    guessed_letters[0] = '\0';
    char guess; //saves user guesses to variable
    int total_guesses = 0; //counts total guesses

    printf("Welcome to the Round!\n"); //[prints welcome statement]
    printf("The size of the word has %d letters.\n\n", size); //prints the amount of letters the word contains

    //while loop runs until the user messes up 7 times, if user chooses incorrectly 7 times its counted in the variable strikes and loop will end
    while (strikes < 6)
    {
        printf("You currently have %d strike(s).\n", strikes); //tells user how many strikes they have, and what letters theyve guessed
        printf("Letter(s) you have guessed: %s\n\n", guessed_letters);

        printf("%s\n\n", starword); //prints the word after a guess 

        printf("Enter your guess: "); //takes in user guess and saves it to variable guess
        scanf(" %c", &guess);

        //auto checks to make sure all inputs are changed to lowercase, if user inputs upper case, will convert automatically
        guess = tolower(guess);

        //sets up to check if user input is a letter
        int alphabetical = (int)guess;

        // Checks if guess is a letter, if not prints to user input was not a letter
        if (!isalpha(guess))
            printf("\nYou did not enter a letter from the alphabet.\n\n");
        else
        { 
            //if it was a letter it gets added to the string
            guessed_letters[total_guesses + 1] = '\0';
            guessed_letters[total_guesses] = guess;
            total_guesses++;

            printf("\n");

            //counts the amount of times a letter appears in the word
            int letter_count = occurancesInWord(guess, answer);

            if (letter_count == 0) //checks to see if the letter entered isnt in the word, then sest up print statement saying user entered wrong, and a strike is added to count, to variable strikes
            {
                printf("The letter %c is NOT in the word.\n\n", guess);
                strikes++;
            }
            else
            {
                //if user letter is in the word, then function that repalces the * is called to remove them, and reveal the letter(s) in the words
                updateStarWord(starword, answer, guess);
                int win_lose = strcmp(starword, answer);
                if (win_lose == 0) //checks to see if user wins, if they do 1 is returned, if anything else is retuned they lose
                    return 1;
                printf("The letter %c is in the word.\n\n", guess);
            }
        }
    }
    printf("************************************************************************\n");
    return 0;
}

int occurancesInWord(char userguess, char answer[])
{
    //loop checks to see how many times the letter the user inputed is in the string
    int size = strlen(answer); //checks to see how long the string (the word) is 
    int letter_count = 0;
    for (int i = 0; i < size; ++i) //checks to see how long the word is, then checks users letter and checks to see how many times that letter appears in the word
        if (answer[i] == userguess)
            letter_count++; //that count is then returned back to main
    return letter_count;
}

void updateStarWord(char starword[], char answer[], char userguess)
{
    int size = strlen(answer); //checks to see how long the string (the word) is

    //runs loop to check entire word, once checked every letter guess correctly and was updated to count, will replace a * shown to the user in the terminal
    for (int re = 0; re < size; ++re)
        if (answer[re] == userguess)
              starword[re] = userguess;
}

void playAgain(int *play)
{ //sets up print statement to ask user to play again, users asnwer is saved to *play, which is called and checked in main

     printf("************************************************************************\n");
    printf("Would you like to play another round?\n");
    printf("1: Yes\n");
    printf("2: No\n");
    printf("Choice: ");
    scanf("%d", play);
    printf("\n");
    printf("************************************************************************\n");
    //else
    //printf("************************************************************************\n");
    //printf("Thank you for playing today!\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the maximum number of cards a player can hold
#define MAX_CARDS 10

// Define a structure to represent a card
typedef struct {
    int value;  // The value of the card in Blackjack
    char *name; // The name (rank) of the card
} Card;

// Global array to hold the deck of cards
Card deck[52];
int deckIndex = 0; // Index to track the current position in the deck

// Function to create a standard deck of 52 cards
void createDeck() {
    // Array of card names (ranks)
    char *names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    
    // Loop to initialize the deck
    for (int i = 0; i < 52; i++) {
        deck[i].name = names[i % 13]; // Assign the card name
        // Assign the card value: face cards (J, Q, K) are worth 10, others are worth their number
        if (i % 13 >= 10) {
            deck[i].value = 10; // Face cards
        } else {
            deck[i].value = (i % 13) + 2; // Number cards
        }
    }
}

// Function to shuffle the deck of cards randomly
void shuffleDeck() {
    // Shuffle using the Fisher-Yates algorithm
    for (int i = 0; i < 52; i++) {
        int j = rand() % 52; // Pick a random index
        // Swap the cards at index i and j
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Function to calculate the total value of a hand of cards
int calculateHandValue(Card hand[], int handSize) {
    int value = 0; // Total value of the hand
    int aces = 0;  // Counter for aces

    // Loop through the hand to sum values
    for (int i = 0; i < handSize; i++) {
        value += hand[i].value; // Add the card's value to the total
        if (hand[i].name[0] == 'A') aces++; // Count aces
    }

    // Adjust for aces: if the total exceeds 21 and we have aces, count them as 1
    while (value > 21 && aces > 0) {
        value -= 10; // Reduce the value by 10 for each ace
        aces--; // Decrease the ace count
    }
    return value; // Return the final hand value
}

// Function to print the cards in a hand
void printHand(Card hand[], int handSize) {
    for (int i = 0; i < handSize; i++) {
        printf("%s ", hand[i].name); // Print each card name
    }
    printf("\n"); // New line after printing the hand
}

// Function to display the rules of Blackjack
void displayRules() {
    printf("Welcome to Blackjack!\n");
    printf("Here are the rules:\n");
    printf("1. The goal is to beat the dealer by having a hand value closer to 21 without going over.\n");
    printf("2. Face cards (J, Q, K) are worth 10. Aces can be worth 1 or 11.\n");
    printf("3. Each player starts with two cards, and the dealer has one card face up and one face down.\n");
    printf("4. Players can choose to 'hit' (take another card) or 'stand' (keep their current hand).\n");
    printf("5. If your hand exceeds 21, you bust and lose.\n");
    printf("6. The dealer must hit until their hand value is 17 or higher.\n");
    printf("7. The player wins if their hand value is higher than the dealer's without busting.\n");
    printf("8. If both the player and dealer have the same value, it is a tie.\n");
}

// Function to show a menu for the rules or starting the game
void showRulesMenu() {
    int choice;
    do {
        // Display menu options
        printf("\nHow would you like to see the rules?\n");
        printf("1. View Rules\n");
        printf("2. Start Game\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Get user choice

        // Handle the user's choice
        switch (choice) {
            case 1:
                displayRules(); // Show rules
                break;
            case 2:
                return; // Start the game
            case 3:
                exit(0); // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1); // Loop until a valid option is chosen
}

// Main function to run the Blackjack game
int main() {
    srand(time(NULL)); // Seed the random number generator
    createDeck(); // Create the deck of cards
    shuffleDeck(); // Shuffle the deck

    showRulesMenu(); // Display rules menu

    int credits = 500; // Starting credits for the player
    char playAgain; // Variable to check if player wants to play again

    do {
        // Check if the player has credits to play
        if (credits <= 0) {
            printf("You've run out of credits! Game over.\n");
            break; // Exit the loop if out of credits
        }

        printf("You have %d credits.\n", credits);
        printf("Enter your bet (1 to %d): ", credits);
        int bet;
        scanf("%d", &bet); // Get the player's bet

        // Validate the bet amount
        if (bet < 1 || bet > credits) {
            printf("Invalid bet amount. Please try again.\n");
            continue; // Retry betting if invalid
        }

        Card playerHand[MAX_CARDS]; // Array for player's hand
        Card dealerHand[MAX_CARDS]; // Array for dealer's hand
        int playerHandSize = 0, dealerHandSize = 0; // Hand sizes

        // Deal initial cards to both player and dealer
        playerHand[playerHandSize++] = deck[deckIndex++];
        dealerHand[dealerHandSize++] = deck[deckIndex++];
        playerHand[playerHandSize++] = deck[deckIndex++];
        dealerHand[dealerHandSize++] = deck[deckIndex++];

        // Player's turn
        char choice; // To store player's choice for hitting or standing
        int playerValue = 0; // Initialize player's hand value
        do {
            printf("Your hand: ");
            printHand(playerHand, playerHandSize); // Show player's hand
            playerValue = calculateHandValue(playerHand, playerHandSize); // Calculate hand value
            printf("Value: %d\n", playerValue); // Display hand value

            // Check for bust
            if (playerValue > 21) {
                printf("You bust! Dealer wins.\n");
                credits -= bet; // Deduct bet from credits
                break; // End player's turn if they bust
            }

            // Prompt player for action
            printf("Hit (h) or Stand (s)? ");
            scanf(" %c", &choice); // Get player choice

            switch (choice) {
                case 'h':
                    playerHand[playerHandSize++] = deck[deckIndex++]; // Draw a card
                    break;
                case 's':
                    break; // End player's turn
                default:
                    printf("Invalid choice. Please enter 'h' or 's'.\n");
            }
        } while (choice != 's'); // Continue until player stands

        // Dealer's turn if player didn't bust
        if (playerValue <= 21) {
            printf("Dealer's hand: ");
            printHand(dealerHand, dealerHandSize); // Show dealer's hand

            // Dealer hits until their hand value is 17 or higher
            while (calculateHandValue(dealerHand, dealerHandSize) < 17) {
                dealerHand[dealerHandSize++] = deck[deckIndex++]; // Draw a card
            }

            // Determine the final values for comparison
            int dealerValue = calculateHandValue(dealerHand, dealerHandSize);
            printf("Your final value: %d\n", playerValue);
            printf("Dealer's final value: %d\n", dealerValue);

            // Determine the winner
            if (dealerValue > 21 || playerValue > dealerValue) {
                printf("You win!\n");
                credits += bet; // Player wins
            } else if (playerValue < dealerValue) {
                printf("Dealer wins!\n");
                credits -= bet; // Dealer wins
            } else {
                printf("It's a tie!\n"); // Tie condition
            }
        }

        // Ask the player if they want to play again
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y'); // Repeat if player wants to continue

    // Thank the player and show final credits
    printf("Thank you for playing! You finished with %d credits.\n", credits);
    return 0; // End
}
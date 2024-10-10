# Blackjack Game in C

Welcome to the Blackjack Game implemented in C! This project simulates the classic card game where players aim to have a hand value closer to 21 than the dealer without exceeding it.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Game Rules](#game-rules)
- [Contributing](#contributing)
- [License](#license)

## Features
- Standard 52-card deck creation and shuffling
- Player and dealer hands with Blackjack rules
- Ability to hit (take another card) or stand (keep current hand)
- Automatic dealer actions based on hand values
- Player betting system with credits
- Display of game results (win/loss/tie)

## Installation
To compile and run the game, you need a C compiler (like GCC). Follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/blackjack.git
### Usage
When you run the game, you'll be welcomed with a menu that allows you to view the rules, start the game, or exit.

### Gameplay:
You start with 500 credits.
You can place bets (between 1 and your available credits).
The game follows standard Blackjack rules:
The goal is to beat the dealer without going over 21.
Face cards are worth 10, and Aces can be 1 or 11.
If your hand exceeds 21, you bust and lose your bet.

### Game Rules
The player starts with two cards, and the dealer has one card face up and one face down.
Players can choose to "hit" (take another card) or "stand" (keep their current hand).
If the player's hand exceeds 21, they lose.
The dealer must hit until their hand value is 17 or higher.
The player wins if their hand value is higher than the dealer's without busting.
If both the player and dealer have the same value, it is a tie.

### Contributing
Contributions are welcome! If you'd like to improve the game, feel free to fork the repository and submit a pull request.

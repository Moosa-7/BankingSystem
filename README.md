# BankingSystem

# Simulated Banking System

This is a simple banking system built in C++ that allows users to open an account, perform transactions (deposit and withdrawal), and view transaction history.

## Features

- Open New Account
- Show Account Holder Details
- Perform Transaction (Deposit/Withdraw)
- Display Transaction History

## Requirements

- C++ Compiler (g++, clang++, etc.)

## How to Run

1. **Clone the repository:**

    ```bash
    git clone https://github.com/your-username/banking-system.git
    ```

2. **Navigate to the project folder:**

    ```bash
    cd banking-system
    ```

3. **Compile the code:**

    ```bash
    g++ -o banking_system main.cpp
    ```

4. **Run the program:**

    ```bash
    ./banking_system
    ```

## Usage

- **Open New Account**: Choose option 1 and follow the prompts to enter your account information.
- **Show Account Holder Details**: Choose option 2 to display the details of all customers.
- **Perform Transaction**: Choose option 3 to deposit or withdraw money from an existing account.
- **Display Transaction History**: Choose option 4 to view the transaction history of an account.
- **Exit**: Choose option 5 to exit the program.

## Data Structures Used

- **Binary Search Tree (BST)**: For efficient storage and searching of customer accounts.
- **Queue**: To keep track of the transaction history for each account.


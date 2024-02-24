//Merchant Challenge 1.07

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

struct Item {
    string name;
    int price;
    int quantity;
};

vector<Item> items = {
    {"Health Potion", 25, 3},
    {"Sword", 50, 1},
    {"Magic Scroll", 75, 10}
};

int gold = 100;
vector<Item> inventory;

void printInventory() {
    cout << "\n** Welcome to the Goblin Merchant **\n";
    cout << "Items available for purchase:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i].name << " - " << items[i].price << " gold (" << items[i].quantity << " available)\n";
    }
    cout << "Your Gold: " << gold << " gold\n";

    if (!inventory.empty()) {
        cout << "\nYour Inventory:\n";
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << i + 1 << ". " << inventory[i].name << endl;
        }
    }
    else {
        cout << "\nYour Inventory is empty.\n";
    }
}

void buyItem(int index) {
    if (inventory.size() >= 3) {
        cout << "Your inventory is full. You cannot carry any more items.\n";
        return;
    }

    if (index >= 1 && index <= static_cast<int>(items.size())) {
        Item& item = items[index - 1];
        if (item.quantity > 0 && gold >= item.price) {
            gold -= item.price;
            cout << "You purchased " << item.name << " for " << item.price << " gold.\n";
            inventory.push_back(item);
            item.quantity--;
        }
        else if (item.quantity == 0) {
            cout << "Sorry, " << item.name << " is out of stock.\n";
        }
        else {
            cout << "Tis a shame but you are broke af adventurer.\n";
        }
    }
    else {
        cout << "Invalid item number.\n";
    }
}

void sellItem(int index) {
    if (index >= 1 && index <= static_cast<int>(inventory.size())) {
        Item& item = inventory[index - 1];
        gold += item.price;
        cout << "You sold " << item.name << " for " << item.price << " gold.\n";
        inventory.erase(inventory.begin() + index - 1);
    }
    else {
        cout << "Invalid item number.\n";
    }
}

int main() {
    while (true) {
        printInventory();

        cout << "\nWhat would you like to do?\n";
        cout << "1. Browse items\n";
        cout << "2. Buy item\n";
        cout << "3. Sell item\n";
        cout << "4. Exit\n";

        string input;
        cin >> input;

        if (input.size() != 1 || !isdigit(input[0])) {
            cout << "I am unable to help you adventurer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int choice = input[0] - '0';

        switch (choice) {
        case 1:
            printInventory();
            break;
        case 2: {
            int itemIndex;
            cout << "Which item would you like to buy? Enter the item number: ";
            cin >> itemIndex;
            buyItem(itemIndex);
            break;
        }
        case 3: {
            int itemIndex;
            cout << "Which item would you like to sell? Enter the item number: ";
            cin >> itemIndex;
            sellItem(itemIndex);
            break;
        }
        case 4:
            cout << "Thank you for visiting the Fantasy Merchant. Farewell!\n";
            return 0;
        default:
            cout << "I am unable to help you adventurer.\n";
            break;
        }
    }

    return 0;
}

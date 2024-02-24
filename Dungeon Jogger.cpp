#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// Constants
const int MAX_HEALTH = 10;

// Player class
class Player {
public:
    std::string name;
    int health;
    int gold;
    std::string className;

    Player(const std::string& initialName, int initialHealth, int initialGold, const std::string& initialClassName)
        : name(initialName), health(initialHealth), gold(initialGold), className(initialClassName) {}
};

// Function prototypes
int getRandomNumber(int min, int max);
void combat(Player& player);
void attackMonster(Player& player, int& monsterHealth, int& monsterGold);
void castSpell(Player& player, int& monsterHealth, int& monsterGold);
void flee(Player& player);
void encounterMerchant(Player& player);

// Random number generator function
int getRandomNumber(int min, int max) {
    return min + (std::rand() % (max - min + 9));
}

void combat(Player& player) {
    static const int NUM_MONSTER_TYPES = 3;
    static const std::string MONSTER_NAMES[NUM_MONSTER_TYPES] = { "Goblin", "Succubus", "Hell Hound" };
    static const int MONSTER_HEALTH[NUM_MONSTER_TYPES] = { 99, 69, 666 };
    static const int MONSTER_GOLD[NUM_MONSTER_TYPES] = { 9, 69, 999 };

    int monsterType = getRandomNumber(0, NUM_MONSTER_TYPES - 1);
    int monsterHealth = MONSTER_HEALTH[monsterType];
    int monsterGold = MONSTER_GOLD[monsterType];

    std::cout << "You encounter a " << MONSTER_NAMES[monsterType] << "!\n";
    std::cout << "Monster Health: " << monsterHealth << std::endl;
    std::cout << "Your Health: " << player.health << std::endl;

    while (player.health > 0 && monsterHealth > 0) {
        std::cout << "Choose an action:\n";
        std::cout << "1. Attack\n";
        if (player.className == "Mage") {
            std::cout << "2. Cast Teleport\n";
            std::cout << "3. Cast Fireball\n";
        }
        std::cout << "4. Flee\n";
        std::cout << "5. Quit Game\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            attackMonster(player, monsterHealth, monsterGold);
            break;
        case 2:
            if (player.className == "Mage") {
                castSpell(player, monsterHealth, monsterGold);
            }
            else {
                std::cout << "Invalid choice. Try again.\n";
            }
            break;
        case 3:
            if (player.className == "Mage") {
                std::cout << "You cast Fireball and deal massive damage!\n";
                monsterHealth -= monsterHealth * 0.9; // Subtract 90% of monster's health
            }
            else {
                std::cout << "Invalid choice. Try again.\n";
            }
            break;
        case 4:
            flee(player);
            break;
        case 5:
            std::cout << "Quitting game...\n";
            exit(0);
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }

        std::cout << "Monster Health: " << monsterHealth << std::endl;
        std::cout << "Your Health: " << player.health << std::endl;
    }

    if (player.health > 0) {
        std::cout << "You defeated the " << MONSTER_NAMES[monsterType] << " and gained " << monsterGold << " gold!\n";
        player.gold += monsterGold;
    }
    else {
        std::cout << "You have been defeated by the " << MONSTER_NAMES[monsterType] << ". Game over!\n";
        // exit(0); // Consider using a different method to handle game over
    }
}

void attackMonster(Player& player, int& monsterHealth, int& monsterGold) {
    int damage = player.className == "Warrior" ? getRandomNumber(1, 2) : getRandomNumber(1, 3);
    std::cout << "You attack the monster for " << damage << " damage.\n";
    monsterHealth -= damage;

    if (monsterHealth > 0) {
        int monsterDamage = getRandomNumber(1, 3);
        std::cout << "The monster attacks you for " << monsterDamage << " damage.\n";
        player.health -= monsterDamage;
    }
}

void castSpell(Player& player, int& monsterHealth, int& monsterGold) {
    if (player.className == "Mage") {
        std::cout << "You cast Teleport and flee from the combat!\n";
        flee(player); // Call the flee function to display the flee dialogue
        monsterHealth = 0; // Monster defeated
    }
    else {
        std::cout << "Invalid spell. Try again.\n";
    }
}

void flee(Player& player) {
    std::cout << "You try to flee...\n";
    if (getRandomNumber(1, 2) == 1) {
        std::cout << "You successfully escape!\n";
    }
    else {
        std::cout << "You failed to escape. The monster attacks!\n";
        int monsterDamage = getRandomNumber(1, 3);
        std::cout << "The monster attacks you for " << monsterDamage << " damage.\n";
        player.health -= monsterDamage;
    }
}

void encounterMerchant(Player& player) {
    // 50% chance of encountering the merchant
    if (getRandomNumber(1, 2) == 1) {
        std::cout << "You encounter a traveling wizard merchant!\n";
        std::cout << "Hello Dungeon Jogger. Would you like to browse my wares?:\n";
        std::cout << "1. Health Potion (50 gold) - Restores player health to max 100\n";
        std::cout << "2. Wish Scroll (1000 gold) - Allows player to flee encounters\n";
        std::cout << "3. Magic Sword (500 gold) - Adds 100% to player damage\n";
        std::cout << "Enter the item number you wish to purchase (or 0 to return to the Dungeon): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            if (player.gold >= 50) {
                std::cout << "You purchase a Health Potion.\n";
                player.gold -= 50;
                player.health = MAX_HEALTH;
            }
            else {
                std::cout << "Not enough gold to purchase the Health Potion.\n";
            }
            break;
        case 2:
            if (player.gold >= 1000) {
                std::cout << "You purchase a Wish Scroll.\n";
                player.gold -= 1000;
            }
            else {
                std::cout << "Not enough gold to purchase the Wish Scroll.\n";
            }
            break;
        case 3:
            if (player.gold >= 500) {
                std::cout << "You purchase a Magic Sword.\n";
                player.gold -= 500;
                // Add magic sword effect to player
            }
            else {
                std::cout << "Not enough gold to purchase the Magic Sword.\n";
            }
            break;
        default:
            std::cout << "No item purchased.\n";
            break;
        }
    }
    else {
        std::cout << "You rest at a campsite but encounter no one.\n";
    }
}

int main() {
    // Initialize random seed
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Get player's name
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    // Select player class
    std::cout << "Choose your class:\n";
    std::cout << "1. Warrior\n";
    std::cout << "2. Mage\n";
    std::cout << "3. Priestess\n";
    int classChoice;
    std::cin >> classChoice;

    std::string className;
    switch (classChoice) {
    case 1:
        className = "Warrior";
        break;
    case 2:
        className = "Mage";
        break;
    case 3:
        className = "Priestess";
        break;
    default:
        std::cout << "Invalid choice. Defaulting to Warrior.\n";
        className = "Warrior";
        break;
    }

    // Create player
    Player player(playerName, MAX_HEALTH, 100, className);

    // Game loop
    while (player.health > 0) {
        combat(player);
        encounterMerchant(player);
    }

    std::cout << "Game over!\n";

    return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <random>  // Added for randomization
#include <limits>

using namespace std;

const int GRID_SIZE = 14;

// ASCII art
const string linkAscii = R"(
   .---_   _--._---.__
  /   _ \/\     \     ''-.
 |   / \ | \      '.     '.     .'¯|
 |  / __\|  '.      '.     '    \ _|
 | | |_  .-'_'.      .    _.-|  $$
 | | \U\\ .¯U' '..    _.-' .'  $$
  \| /¯ /  ¯¯     ' |'   .'|   $$
    \| '-          '|  .'  |  $$
      \ ___         /.      \ $$
       \          .'  \ __   |$$
        '.   ___.'  | ////¯¯''.._
          ¯|¯      _'.//_ ..   ||||
     _ .-¯|\|----¯¯¯  |\|¯¯|---||||
)";

const string linksmirkAscii = R"(
   .---_   _--._---.__
  /   _ \/\     \     ''-.
 |   / \ | \      '.     '.     .'¯|
 |  / __\|  '.      '.     '    \ _|
 | | |_  .-'_'.      .    _.-|  $$
 | | \U\\ .¯U' '..    _.-' .'  $$
  \| /¯ /  ¯¯     ' |'   .'|   $$
    \| '-          '|  .'  |  $$
      \ ___/        /.      \ $$
       \          .'  \ __   |$$
        '.   ___.'  | ////¯¯''.._
          ¯|¯      _'.//_ ..   ||||
     _ .-¯|\|----¯¯¯  |\|¯¯|---||||
)";

const string linkSadAscii = R"(
   .---_   _--._---.__
  /   _ \/\     \     ''-.
 |   / \ | \      '.     '.     .'¯|
 |  / __\|  '.      '.     '    \ _|
 | | |_  .-'_'.      .    _.-|  $$
 | | \U\\ .¯U' '..    _.-' .'  $$
  \| /¯ /  ¯¯     ' |'   .'|   $$
    \| '-          '|  .'  |  $$
      \   ___       /.      \ $$
       \ /   \     .'  \ __   |$$
        '.   ___.'  | ////¯¯''.._
          ¯|¯      _'.//_ ..   ||||
     _ .-¯|\|----¯¯¯  |\|¯¯|---||||
)";

const string chuchuAscii = R"(

              -=*#####+-
          :#@#******++++*%=
        =@@@%#***#%@@@@%%*+**
      =*-:::@%**%@#::::-+%%*+#-
     *+%=::-@#**%%-:::-%#:%%++%=
    -#--::=@%***#%+-:::--:+@**+#:
     #%%%@%#*****#@#*+++*%@#*++*+
    -@###***********####***%#+++%
    +%#%@%%%%%%%%%%%%%%@@%#*++++%-
    +%####******************++++#=
     @######****************++++#=
     :%#####****************++++%:
       *%####***************+++*%
        :@####**************+++#=
          -%####***********++++#
            +%##**********+++*@:
              %%#*********++*%
              :#@#*******+*#%
            *%###%******+*#@%%@%+
        :=*%@%##*#********%***##*#-
     :%%####*************##********#%- 
     +####****##*******++#######****#=
      +%@@@@@%%#*********@:::=+###*=
              =%%#***###+                                                  
)";
const string zoraAscii = R"(
                   @@@@@@@@@@@@@@                
               @@@@@+::::::::::::@@@@@            
 @@@@@@@      @@++++-::::::::::::++++#@@          
@@@@@@@@@@  @@%#-::::::::::::::::::::+%%@@        
   @@#*#@@@@%%-:::--::::-----::::::::--*%@@@      
   @@%***#@@------**=:::+@@@@--:::::-*@#:=@@@     
     @@%*+:-**@@@@@@#*=:+@@@@@@-:::*@@@#:=@@@     
   @@#***#@@@@@     @@*:::-@@@@-:::*@@@#:=@@@     
   @@#*%@@          @@%*+::::::::::::::=*#@@@     
@@@@@@@@          @@@@@@%**::::::::::=*#@@        
 @@@@@@@       @@@####%@@@%++::::::=+#@@@@@@@@@   
              @@@@%%#**+*##%%######%%@@@##++++@@@ 
            @@####%%%#+:-++##########@@%++::++@@@ 
           @@@=-::**%@*--::::::::::--#@#---=@@@   
              @@-:::#@%*+::::::::::+*%@@@@@@@     
               @@@@@#***#@@::::::**%@%*#@@@@@     
               @@@@@@@@@@@@@@@@@@@@*:::::-**@@@   
                              @@@@@@@@@@@@@@@@@              

)";
const string goronAscii = R"(
                  @@@@@@                  
               @@@#*****@@@               
               @@@=::::-@@@               
            @@@*===========@@@            
         @@@@##+===========%%%@@@         
         @@@%================*@@@         
      @@@%======================*@@@      
      @@@%==+**+===========***==*@@@      
      @@@%==*@@*===========@@%==*@@@      
   @@@@=====#@@*===========@@%=====#@@@   
   @@@@=====*@@*=====+++===@@%=====#@@@   
   @@@@===:::::+=====@@@===:::::-==#@@@   
   @@@@==*@@%================*@@%==#@@@@@@
   @@@@==*@@%================*@@%==#@@@@@@
 @@@==+@@%==#@@@@@@@@@@@@@@@@%==*@@%==@@@@
 @@@==+@@@@@%++++++++++++++++*@@@@@#--%@@@
 @@@==+@@@@@%================*@@@@@#::%@@@
 @@@=====*@@@@@@@@@@@@@@@@@@@@==*@@@@@@   
 @@@%%%==+++++++++%@@########*==*@@@@@@   
   @@@@===::::::::%@@+==========*@@@      
      @@@#:::::%@@*====+@@@@@@@@@@@@      
    @@@@@%+++++%@@#****#%%%%%%%%%%%@@@@   
   @@@@@@@@@@@@@@@@@@@@@===::::::::#@@@   
         @@@@@@@@@@@@@@@@@@@@@@@@@@@      
         @@@@@@@@@@@@@@@@@@@@@@@@@@@
)";
const string dragonAscii = R"(
                                                 /===-_---~~~~~~~~~------____
                                                |===-~___                _,-'
                 -==\\                         `//~\\   ~~~~`---.___.-~~
             ______-==|                         | |  \\           _-~`
       __--~~~  ,-/-==\\                        | |   `\        ,'
    _-~       /'    |  \\                      / /      \      /
  .'        /       |   \\                   /' /        \   /'
 /  ____  /         |    \`\.__/-~~ ~ \ _ _/'  /          \/'
/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`
                  \_|      /        _)   ;  ),   __--~~
                    '~~--_/      _-~/-  / \   '-~ \
                   {\__--_/}    / \\_&gt;- )&lt;__\      \
                   /'   (_/  _-~  | |__&gt;--&lt;__|      |
                  |0  0 _/) )-~     | |__&gt;--&lt;__|     |
                  / /~ ,_/       / /__&gt;---&lt;__/      |
                 o o _//        /-~_&gt;---&lt;__-~      /
                 (^(~          /~_&gt;---&lt;__-      _-~
                ,/|           /__&gt;--&lt;__/     _-~
             ,//('(          |__&gt;--&lt;__|     /                  .----_
            ( ( '))          |__&gt;--&lt;__|    |                 /' _---_~\
         `-)) )) (           |__&gt;--&lt;__|    |               /'  /     ~\`\
        ,/,'//( (             \__&gt;--&lt;__\    \            /'  //        ||
      ,( ( ((, ))              ~-__&gt;--&lt;_~-_  ~--____---~' _/'/        /'
    `~/  )` ) ,/|                 ~-_~&gt;--&lt;_/-__       __-~ _/
  ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~
   ;'( ')/ ,)(                              ~~~~~~~~~~
  ' ') '( (/
    '   '  `)";

const string dogAscii =
"                             |' \\ \n"
"         _                  ; : ; \n"
"        / `-.              /: : | \n"
"       |  ,-.`-.          ,': : | \n"
"       \\  :  `. `.       ,'-. : | \n"
"        \\ ;    ;  `-.__,'    `-.| \n"
"         \\ ;   ;  :::  ,::'`:.  `. \n"
"          \\ `-. :  `    :.    `.  \\ \n"
"           \\   \\    ,   ;   ,:    (\\ \n"
"            \\   :., :.    ,'o)): ` `-.\n"
"           ,/,' ;' ,::\"'`.`---'   `.  `-.\n"
"         ,/  :  ; '\"      `;'          ,--`.\n"
"        ;/   :; ;             ,:'     (   ,:) \n"
"          ,.,:.    ; ,:.,  ,-._ `.     \\\"\"'/ \n"
"          '::'     `:'`  ,'(  \\`._____.-\"\"'      \n"
"             ;,   ;  `.  `. `._`-.  \\\\           \n"
"             ;:.  ;:       `-._`-.\\  \\`.         \n"
"              '`:. :        |' `. `\\  ) \\ \n"
"                 ` ;:       |    `--\\__,'       \n"
"                   '`      ,'                    \n"
;
const string goombaAscii = R"(
                               
           ++++++++           
         ++++++++++++         
       ++++++++++++++++       
   ###++++++++++++++++++###   
   #######++++++++++#####+##  
  ++++++.+##++++++###.-+++++  
  ++++++.+###########.-+++++  
++++++++.+#-.++++.-##.-+++++++
++++++++.....++++.....-+++++++
+++++++++++++++++++++++++++++#
  ++++++++-----------+++++++  
       ----------------       
    ####--------------+####   
  #########+-------#########  
  ###########----###########  
    ##########   ##########   )";

const string triforceAscii = R"(
     /\     
    /  \    
   /____\   
  /\    /\  
 /  \  /  \ 
/____\/____\)";

const string zeldaAscii = R"(
                                        /\
                                       /@/
                       __        __   /\/
                      /==\      /  \_/\/   
                    /======\    \/\__ \__
                  /==/\  /\==\    /\_|__ \
               /==/    ||    \=\ / / / /_/
             /=/    /\ || /\   \=\/ /     
          /===/   /   \||/   \   \===\
        /===/   /_________________ \===\
     /====/   / |                /  \====\
   /====/   /   |  _________    /  \   \===\    THE LEGEND OF 
   /==/   /     | /   /  \ / / /  __________\_____      ______       ___
  |===| /       |/   /____/ / /   \   _____ |\   /      \   _ \      \  \
   \==\             /\   / / /     | |  /= \| | |        | | \ \     / _ \
   \===\__    \    /  \ / / /   /  | | /===/  | |        | |  \ \   / / \ \
     \==\ \    \\ /____/   /_\ //  | |_____/| | |        | |   | | / /___\ \
     \===\ \   \\\\\\\/   /////// /|  _____ | | |        | |   | | |  ___  |
       \==\/     \\\\/ / //////   \| |/==/ \| | |        | |   | | | /   \ |
       \==\     _ \\/ / /////    _ | |==/     | |        | |  / /  | |   | |
         \==\  / \ / / ///      /|\| |_____/| | |_____/| | |_/ /   | |   | |
         \==\ /   / / /________/ |/_________|/_________|/_____/   /___\ /___\
           \==\  /               | /==/         C++ RPG ADVENTURE
           \=\  /________________|/=/    
             \==\     _____     /==/ 
            / \===\   \   /   /===/
           / / /\===\  \_/  /===/
          / / /   \====\ /====/
         / / /      \===|===/
         |/_/         \===/
                        =  
)";

const string gameOverascii = R"(
   _____              __  __   ______      ____   __      __  ______   _____  
  / ____|     /\     |  \/  | |  ____|    / __ \  \ \    / / |  ____| |  __ \ 
 | |  __     /  \    | \  / | | |__      | |  | |  \ \  / /  | |__    | |__) |
 | | |_ |   / /\ \   | |\/| | |  __|     | |  | |   \ \/ /   |  __|   |  _  / 
 | |__| |  / ____ \  | |  | | | |____    | |__| |    \  /    | |____  | | \ \ 
  \_____| /_/    \_\ |_|  |_| |______|    \____/      \/     |______| |_|  \_\
)";

bool flyingType = false;


class Character {
public:
    string name;
    int x;
    int y;
    int health;
    int attack;
    int maxMagic;
    int magic;
    int arrows;  

    Character(string n, int h, int a, int m) : name(n), x(0), y(0), health(h), attack(a), maxMagic(m), magic(m), arrows(10) {}


    void replenishArrows() {
        arrows += 1;
        if (arrows > 10) {
            arrows = 10;
        }
    }
    bool isAlive() {
        return health > 0;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }
    
    int attackEnemySword() {
        
        if (rand() % 5 == 0) {
            cout << "Critical hit! ";
            return 2 * attack; 
        }
        return attack;
    }
    int attackEnemyBow() {
        if (arrows > 0) {
            attack = 25;  // Adjust arrow damage as needed
            if (flyingType == true)
            {
                attack *= 3;
                cout << "You shoot an arrow on a flying enemy who are weak to arrows. You deal " << attack << " damage." << endl;
            }
            else
            {
                cout << "You shoot an arrow for " << attack << " damage." << endl;
            }
            arrows--;
        }
        else {
            cout << "You don't have enough arrows!" << endl;
        }
        return attack;
    }

    bool canHeal() {
        return magic > 0;
    }

    void heal() {
        if (canHeal()) {
            int healAmount = 40;  // Adjust base healing amount as needed

            // Add a random chance to heal double (25% chance)
            if (rand() % 4 == 0) {
                healAmount *= 2; // Double healing
                cout << "Double healing! ";
            }

            health += healAmount;
            if (health > 200) {
                health = 200;
            }
            magic--;
            cout << "You healed for " << healAmount << " HP. Your health is now " << health << "." << endl;
        }
        else {
            cout << "You don't have enough magic to heal!" << endl;
        }
    }

    void replenishMagic() {
        magic = maxMagic;
    }
};

class Enemy {
public:
    string name;
    int x;
    int y;
    int health;
    int attack;

    Enemy(string n, int h, int a) : name(n), health(h), attack(a) {
        // Randomly set initial positions, ensuring no overlap
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (x == y); // Ensuring no overlap
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) {
            health = 0;
        }
    }

    bool missesAttack() const {
        // Add a 1 in 5 chance (20%) for the enemy to miss their attack
        return rand() % 5 == 0;
    }
    
    int attackPlayer() {
        // Check if the enemy misses their attack
        if (missesAttack()) {
            cout << name << " misses their attack!" << endl;
            return 0; // No damage on a miss
        }
        return attack;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayGrid(Character& player, vector<Enemy>& enemies) {
    clearScreen();
    cout << "Player Health: " << player.health << endl;

    // Display the ASCII art
    cout << "Link: " << endl;
    if (player.health >= 150 && player.health <= 200) {
        cout << linksmirkAscii << endl;
    }
    else if (player.health > 50 && player.health < 150) {
        cout << linkAscii << endl;
    }
    else if (player.health < 50) {
        cout << linkSadAscii << endl;
    }
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (i == player.y && j == player.x) {
                cout << "L ";
            }
            else {
                bool enemyPresent = false;
                for (const auto& enemy : enemies) {
                    if (enemy.x == j && enemy.y == i && enemy.isAlive()) {
                        cout << enemy.name[0] << " "; // Display the initial of the enemy
                        enemyPresent = true;
                        break;
                    }
                }
                if (!enemyPresent) {
                    cout << ". ";
                }
            }
        }
        cout << endl;
    }
}

void displayFightScene(Character& player, Enemy& enemy) {
    clearScreen();
    cout << "Player Health: " << player.health << endl;
    cout << "Enemy Health: " << enemy.health << endl;

    // Display the ASCII art
    cout << "link: " << endl;
    cout << linkAscii << endl;

    cout << "VS" << endl;

    if (enemy.name == "Chuchu") {
        cout << "Enemy: " << endl;
        cout << chuchuAscii << endl;
    }
    else if (enemy.name == "Zora") {
        cout << "Enemy: " << endl;
        cout << zoraAscii << endl;
    }
    else if (enemy.name == "Goron") {
        cout << "Enemy: " << endl;
        cout << goronAscii << endl;
    }
    else if (enemy.name == "Dragon") {
        flyingType = true;
        cout << "Enemy: " << endl;
        cout << dragonAscii << endl;
    }
    else if (enemy.name == "Dog") {
        cout << "Enemy: " << endl;
        cout << dogAscii << endl;
    }
    else if (enemy.name == "Goomba") {
        cout << "Enemy: " << endl;
        cout << goombaAscii << endl;
    }
    cout << "Amount of arrows in quiver: " << player.arrows << endl;
}

void combat(Character& player, Enemy& enemy) {
    cout << "You encounter a " << enemy.name << " with " << enemy.health << " health." << endl;

    while (player.isAlive() && enemy.isAlive()) {
        int playerDamage = 0;

        displayFightScene(player, enemy);

        // Player's turn
        cout << "Your turn! Choose an action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Heal" << endl;
        cout << "3. Shoot Bow" << endl;
        cout << "4. Flee the battle" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            // Player attacks enemy
            playerDamage = player.attackEnemySword();
            cout << "You attack " << enemy.name << " for " << playerDamage << " damage." << endl;
            enemy.takeDamage(playerDamage);
            break;
        case 2:
            // Player heals
            if (player.canHeal()) {
                player.heal();
            }
            else {
                cout << "You don't have enough magic to heal!" << endl;
            }
            break;
        case 3:
            playerDamage = player.attackEnemyBow();
            enemy.takeDamage(playerDamage);
            break;
        case 4:
            if (rand() % 3 == 0) {
                player.health += 10;
                return;
            }
            else
            {
                cout << "you failed to flee the battle" << endl;
                break;
            }
        default:
            continue;
        }

        if (!enemy.isAlive()) {
            cout << "You defeated " << enemy.name << "!" << endl;
            flyingType = false;
            player.replenishArrows();
            player.replenishMagic();
            break;
        }

        // Enemy's turn
        int enemyDamage = enemy.attackPlayer();
        if (enemyDamage > 0) {
            cout << enemy.name << " attacks you for " << enemyDamage << " damage." << endl;
        }

        player.takeDamage(enemyDamage);
        cout << "Your current health is: " << player.health << endl;
        if (!player.isAlive()) {
            cout << "You were defeated by " << enemy.name << "!" << endl;
            break;
        }

        // Pause to let the player see the results
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

void displayWinScreen() {
    clearScreen();
    cout << triforceAscii << endl;
    cout << "Congratulations! You defeated all the enemies and won the game!" << endl;
    cout << "Thanks for playing!" << endl;
}

int main() {
    srand(time(0));
    
    cout << zeldaAscii << endl;
    cout << "Welcome to the Legend of Zelda C++ RPG!" << endl;
    cout << "After you press enter, you'll be in a " << GRID_SIZE << "x" << GRID_SIZE << " grid.Explore and encounter enemies.Your character is the letter L." << endl;
    cout << "Press Enter to continue...";
    cin.ignore();

    // Wait for the player to press Enter to start the game
    

    Character player("link", 200, 40, 12); // 1 = HP, 2= DMG, 3= amount of healing potions.
    vector<Enemy> enemies = {
        Enemy("Chuchu", 40, 10),
        Enemy("Chuchu", 30, 10),
        Enemy("Zora", 80, 15),
        Enemy("Zora", 80, 15),
        Enemy("Goron", 120, 25),
        Enemy("Goron", 120, 25),
        Enemy("Dragon", 200, 30),
        Enemy("Dog", 60, 12),
        Enemy("Goomba", 40, 8)
    };

    // Ensure enemies don't overlap
    for (size_t i = 0; i < enemies.size(); i++) {
        for (size_t j = i + 1; j < enemies.size(); j++) {
            while (enemies[i].x == enemies[j].x && enemies[i].y == enemies[j].y) {
                enemies[j].x = rand() % GRID_SIZE;
                enemies[j].y = rand() % GRID_SIZE;
            }
        }
    }

    while (player.isAlive()) {
        displayGrid(player, enemies);

        bool combatEngaged = false; // Check if combat is engaged

        cout << "Enter WASD to move (q to quit): ";
        char move;
        cin >> move;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        int newX = player.x;
        int newY = player.y;

        // Check if the player lands on an enemy's position
        for (auto& enemy : enemies) {
            if (enemy.x == player.x && enemy.y == player.y && enemy.isAlive()) {
                combat(player, enemy);
                combatEngaged = true;

                if (!player.isAlive()) {
                    clearScreen();
                    cout << gameOverascii << endl;
                    cout << "Game Over! You lose!" << endl;
                    break;
                }

                player.replenishMagic();
                break; // No need to check other enemies if combat is engaged
            }
        }

        if (!combatEngaged) {
            if (move == 'w' && player.y > 0) {
                newY--;
            }
            else if (move == 's' && player.y < GRID_SIZE - 1) {
                newY++;
            }
            else if (move == 'a' && player.x > 0) {
                newX--;
            }
            else if (move == 'd' && player.x < GRID_SIZE - 1) {
                newX++;
            }
            else if (move == 'q') {
                cout << "You quit the game." << endl;
                cout << gameOverascii << endl;
                cin.ignore();
                break;
            }
            else {
                cout << "Invalid move." << endl;
            }
        }

        // Move enemies randomly if combat is not engaged
        for (auto& enemy : enemies) {
            if (enemy.isAlive()) {
                // Randomly choose a direction (up, down, left, right)
                int direction = rand() % 4;

                // Update the enemy's position based on the chosen direction
                if (direction == 0 && enemy.y > 0) {
                    enemy.y--;
                }
                else if (direction == 1 && enemy.y < GRID_SIZE - 1) {
                    enemy.y++;
                }
                else if (direction == 2 && enemy.x > 0) {
                    enemy.x--;
                }
                else if (direction == 3 && enemy.x < GRID_SIZE - 1) {
                    enemy.x++;
                }

                // Check for combat if an enemy moves to the player's position
                if (enemy.x == player.x && enemy.y == player.y && enemy.isAlive()) {
                    combat(player, enemy);
                    combatEngaged = true;

                    if (!player.isAlive()) {
                        clearScreen();
                        cout << gameOverascii << endl;
                        cout << "Game Over! You lose!" << endl;
                        break;
                    }

                    player.replenishMagic();
                    break; // No need to check other enemies if combat is engaged
                }
            }
        }

        // Update the player's position even when combat is engaged
        player.x = newX;
        player.y = newY;

        // Check if all enemies are defeated and display the win screen
        bool allEnemiesDefeated = true;
        for (const auto& enemy : enemies) {
            if (enemy.isAlive()) {
                allEnemiesDefeated = false;
                break; // Exit the loop as soon as we find a living enemy
            }
        }

        if (allEnemiesDefeated) {
            displayWinScreen();
            break;
        }
    }
    return 0;
}
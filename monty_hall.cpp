/*
    Autor: Nof
    Date: 30/09/2022
 
    Description: Simulator of the game "Monty Hall" with a random generator.
*/

#include <iostream>
#include <string>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

class Strategy {
    public:
        const static int COMMON = 0;
        const static int SMART = 1;

        struct Doors {
            int commonChosenDoor = 0;   // Door chosen by player common
            int smartChosenDoor = 0;    // Door chosen by player smart
            int prizeDoor = 0;          // Prize door
            int firstOpenDoor = 0;      // First open door
        } doors;

        int getRandChoice() { return (rand() % DOORS) + 1; }
        void chooseDoor() { doors.prizeDoor = this->getRandChoice(); }
        bool virtual isWinner() { return true; }
    
    private:
        const static int DOORS = 3;
};

class CommonStrategy : public Strategy {
    public:
        void chooseDoor() {
            Strategy::chooseDoor();
            doors.commonChosenDoor = this->getRandChoice();
            // The first open door can't be common chosen door or the prize door
            do {
                doors.firstOpenDoor = this->getRandChoice();
            } while (doors.firstOpenDoor == doors.commonChosenDoor || doors.firstOpenDoor == doors.prizeDoor);
        }

        bool isWinner() { return doors.commonChosenDoor == doors.prizeDoor; }
};

class SmartStrategy : public CommonStrategy {
    public:
        void chooseDoor() {
            CommonStrategy::chooseDoor();
            // The second open door can't be the common chosen door or the first open door
            do {
                doors.smartChosenDoor = Strategy::getRandChoice();
            }while(doors.firstOpenDoor == doors.smartChosenDoor || doors.commonChosenDoor == doors.smartChosenDoor);
        }

        bool isWinner() { return doors.smartChosenDoor == doors.prizeDoor; }
};

class Game {
    private:
        SmartStrategy smartStrategy;
        CommonStrategy commonStrategy;

    public:
        const static long long MAX_GAMES = 10000000;

        struct Stadistics {
            long long games = 0;    // Total games

            long long smartPlayers = 0;   // Quantity of smart players
            long long commonPlayers = 0;  // Quantity of common players

            long long smartPlayerWinners = 0;   // Quantity of smart player winners
            long long commonPlayerWinners = 0;  // Quantity of common player winners

            float perSmartPlayers = 0;  // Percentage of smart players
            float perCommonPlayers = 0;  // Percentage of common players

            float perSmartWinners = 0;  // Percentage of smart player winners
            float perCommonWinners = 0; // Percentage of smart player winners

            void calculate() {
                perSmartPlayers = (smartPlayers / (float)games) * 100;
                perCommonPlayers = (commonPlayers / (float)games) * 100;

                perSmartWinners = (smartPlayerWinners / (float)smartPlayers) * 100;
                perCommonWinners = (commonPlayerWinners / (float)commonPlayers) * 100;
            }
        };

        Game() { }
        ~Game() { }

        Stadistics play(long long runs) {
            Stadistics stadistics;
            int strategy = 0;
            
            // Set seed
            srand(time(0));
            
            for(long long i=0; i < runs; i++) 
            {
                // Random strategy
                strategy = (rand() % 2);
                
                switch (strategy)
                {
                    case Strategy::COMMON:
                        commonStrategy.chooseDoor();
                        if (commonStrategy.isWinner())
                            stadistics.commonPlayerWinners++;
                        stadistics.commonPlayers++;
                        break;
                    case Strategy::SMART:
                        smartStrategy.chooseDoor();
                        if (smartStrategy.isWinner())
                            stadistics.smartPlayerWinners++;
                        stadistics.smartPlayers++;
                }
            }

            stadistics.games = runs;
            stadistics.calculate();
            return stadistics;
        }
};

int main(int argc, char** argv) {
    Game game;

    long long runs = Game::MAX_GAMES;

    if (argc != 2) 
    {
        std::cout << "Invalid parameters.";
        return -1;
    }

    // Convert input string to long long
    runs = atoll(argv[1]);

    // Check input value to max long long
    if (runs >= std::numeric_limits<long long>().max()) {
        std::cout << "Try a smaller number.";
        return -2;  
    }

    cout << "Starting the game with " << runs << " runs\n\n";

    // run the game
    Game::Stadistics result = game.play(runs);
    std::cout.precision(5);

    cout << "Game stadistics:\n\n";
    cout << "Total games: " << result.games;
    cout << "\nSmart players (" << result.perSmartPlayers << "%): " << result.smartPlayers;
    cout << "\nCommon players (" << result.perCommonPlayers << "%): " << result.commonPlayers;
    cout << "\nSmart players winners (" << result.perSmartWinners << "%): " << result.smartPlayerWinners;
    cout << "\nCommon players winners (" << result.perCommonWinners << "%): " << result.commonPlayerWinners;

    cout << "\nThanks for play :)";

    return 0;
}
#ifndef GAME_HPP
#define GAME_HPP

#include "House.hpp"
#include "FamilyMember.hpp"
#include "Inventory.hpp"
#include "ObjectiveList.hpp"
using namespace std;

class Game {
    private:
        House myHouse;
        MissionList myObjectives;
        Inventory myInventory;
        FamilyMember members[5];
    public:
        Game();
        void setupHouse(string roomFile, string edgeFile);
        void setupObjectives(string objectiveFile);
        void setupFamilyMember(string memberFile,int index);
        void placeFamily(string familyFile);
        void setupRoomItems(string itemFile);
        void interaction();
        void printObjectiveRequirements();
        void checkObjectiveCompletion();
        bool acquireItem();
        void promptNextRoom();
        void moods();
        void run(); // run game
};

#endif
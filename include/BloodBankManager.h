#ifndef BLOOD_BANK_MANAGER_H
#define BLOOD_BANK_MANAGER_H

#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <optional>

#include "Models.h"

using namespace std;

class BloodBankManager
{
private:

    // Comparator for FEFO (First Expire, First Out)
    struct CompareBloodUnits
    {
        bool operator()(const BloodUnit& a,
                        const BloodUnit& b) const
        {
            return a.daysToExpiry > b.daysToExpiry;
        }
    };

    // Inventory:
    // Key   -> Blood Group (A+, O-, etc.)
    // Value -> Priority Queue sorted by expiry date
    unordered_map<
        string,
        priority_queue<
            BloodUnit,
            vector<BloodUnit>,
            CompareBloodUnits
        >
    > inventory;

public:

    /*
    |--------------------------------------------------------------------------
    | Inventory Management
    |--------------------------------------------------------------------------
    */

    void addUnit(
        string id,
        string group,
        int daysToExpiry,
        string fridge,
        string shelf,
        int slot
    );

    bool requestBlood(
        string group,
        BloodUnit& allocatedUnit
    );

    bool removeUnit(string unitId);

    bool updateExpiry(
        string unitId,
        int newDays
    );

    void removeExpiredUnits();

    /*
    |--------------------------------------------------------------------------
    | Search
    |--------------------------------------------------------------------------
    */

    BloodUnit* searchUnit(string unitId);

    vector<BloodUnit> getBloodGroupInventory(
        string group
    );

    /*
    |--------------------------------------------------------------------------
    | Statistics
    |--------------------------------------------------------------------------
    */

    int getTotalUnits(
        string group
    );

    int getTotalInventory();

    bool isLowStock(
        string group,
        int threshold
    );

    /*
    |--------------------------------------------------------------------------
    | Display
    |--------------------------------------------------------------------------
    */

    void displayInventory();

    void displayDetailedInventory();

    /*
    |--------------------------------------------------------------------------
    | Persistence
    |--------------------------------------------------------------------------
    */

    void saveInventory();

    void loadInventory();
};

#endif
#include "BloodBankManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils.h"


using namespace std;


void BloodBankManager::addUnit(
    string id,
    string group,
    int daysToExpiry,
    string fridge,
    string shelf,
    int slot)
{
    // Validate Blood Group
    if (!isValidBloodGroup(group))
    {
        cout << "[ERROR] Invalid blood group.\n";
        return;
    }

    // Validate Expiry
    if (!isPositive(daysToExpiry))
    {
        cout << "[ERROR] Expiry days must be greater than 0.\n";
        return;
    }

    // Validate Fridge
    if (isEmpty(fridge))
    {
        cout << "[ERROR] Fridge ID cannot be empty.\n";
        return;
    }

    // Validate Shelf
    if (isEmpty(shelf))
    {
        cout << "[ERROR] Shelf ID cannot be empty.\n";
        return;
    }

    // Validate Slot
    if (slot < 0)
    {
        cout << "[ERROR] Invalid slot number.\n";
        return;
    }

    // Prevent duplicate blood unit IDs
    if (searchUnit(id) != nullptr)
    {
        cout << "[WARNING] Blood Unit "
             << id
             << " already exists.\n";
        return;
    }

    BloodUnit unit;

    unit.unitId = id;
    unit.bloodGroup = group;
    unit.daysToExpiry = daysToExpiry;
    unit.fridgeId = fridge;
    unit.shelfId = shelf;
    unit.slotNumber = slot;

    inventory[group].push(unit);

    cout << "[SUCCESS] Blood Unit Added\n";
}

bool BloodBankManager::requestBlood(
    string group,
    BloodUnit& allocatedUnit)
{
    // Validate blood group
    if (!isValidBloodGroup(group))
    {
        cout << "[ERROR] Invalid blood group requested.\n";
        return false;
    }

    // Check if the blood group exists
    if (inventory.find(group) == inventory.end())
    {
        cout << "[ERROR] Blood group not available.\n";
        return false;
    }

    while (!inventory[group].empty())
    {
        BloodUnit current = inventory[group].top();
        inventory[group].pop();

        if (current.daysToExpiry > 0)
        {
            allocatedUnit = current;
            return true;
        }
    }

    cout << "[ERROR] No usable blood units available.\n";
    return false;
}

void BloodBankManager::removeExpiredUnits()
{
    for (auto& bloodGroup : inventory)
    {
        auto& pq = bloodGroup.second;

        priority_queue<
            BloodUnit,
            vector<BloodUnit>,
            CompareBloodUnits
        > temp;

        while (!pq.empty())
        {
            BloodUnit current = pq.top();
            pq.pop();

            if (current.daysToExpiry > 0)
                temp.push(current);
        }

        pq = temp;
    }
}

void BloodBankManager::displayInventory()
{
    cout << "\n===== BLOOD INVENTORY =====\n";

    for (const auto& item : inventory)
    {
        cout << item.first
             << " : "
             << item.second.size()
             << " Units\n";
    }
}


vector<BloodUnit> BloodBankManager::getBloodGroupInventory(
    string group)
{
    vector<BloodUnit> result;

    auto it = inventory.find(group);

    if (it == inventory.end())
        return result;

    auto tempQueue = it->second;

    while (!tempQueue.empty())
    {
        result.push_back(tempQueue.top());
        tempQueue.pop();
    }

    return result;
}

/*
|--------------------------------------------------------------------------
| Get Total Units of a Blood Group
|--------------------------------------------------------------------------
*/

int BloodBankManager::getTotalUnits(string group)
{
    auto it = inventory.find(group);

    if (it == inventory.end())
        return 0;

    return static_cast<int>(it->second.size());
}
/*
|--------------------------------------------------------------------------
| Get Total Inventory
|--------------------------------------------------------------------------
*/

int BloodBankManager::getTotalInventory()
{
    int total = 0;

    for (const auto& item : inventory)
    {
        total += item.second.size();
    }

    return total;
}

/*
|--------------------------------------------------------------------------
| Check Low Stock
|--------------------------------------------------------------------------
*/

bool BloodBankManager::isLowStock(
    string group,
    int threshold)
{
    return getTotalUnits(group) <= threshold;
}

/*
|--------------------------------------------------------------------------
| Display Detailed Inventory
|--------------------------------------------------------------------------
*/

void BloodBankManager::displayDetailedInventory()
{
    cout << "\n========== DETAILED BLOOD INVENTORY ==========\n";

    if (inventory.empty())
    {
        cout << "Inventory is empty.\n";
        return;
    }

    for (const auto& item : inventory)
    {
        cout << "\nBlood Group : "
             << item.first
             << "\n";

        auto tempQueue = item.second;

        while (!tempQueue.empty())
        {
            BloodUnit unit = tempQueue.top();
            tempQueue.pop();

            cout << "----------------------------------\n";

            cout << "Unit ID     : "
                 << unit.unitId
                 << endl;

            cout << "Expiry      : "
                 << unit.daysToExpiry
                 << " Days\n";

            cout << "Fridge      : "
                 << unit.fridgeId
                 << endl;

            cout << "Shelf       : "
                 << unit.shelfId
                 << endl;

            cout << "Slot        : "
                 << unit.slotNumber
                 << endl;
        }
    }

    cout << "=============================================\n";
}


/*
|--------------------------------------------------------------------------
| Search Blood Unit
|--------------------------------------------------------------------------
*/

BloodUnit* BloodBankManager::searchUnit(string unitId)
{
    static BloodUnit foundUnit;

    for (const auto& item : inventory)
    {
        auto tempQueue = item.second;

        while (!tempQueue.empty())
        {
            BloodUnit current = tempQueue.top();
            tempQueue.pop();

            if (current.unitId == unitId)
            {
                foundUnit = current;
                return &foundUnit;
            }
        }
    }

    return nullptr;
}


/*
|--------------------------------------------------------------------------
| Remove Blood Unit
|--------------------------------------------------------------------------
*/

bool BloodBankManager::removeUnit(string unitId)
{
    // Check every blood group
    for (auto& item : inventory)
    {
        auto& originalQueue = item.second;

        priority_queue<
            BloodUnit,
            vector<BloodUnit>,
            CompareBloodUnits
        > tempQueue;

        bool found = false;

        while (!originalQueue.empty())
        {
            BloodUnit current = originalQueue.top();
            originalQueue.pop();

            if (current.unitId == unitId)
            {
                found = true;
                continue; // Skip this unit (delete it)
            }

            tempQueue.push(current);
        }

        // Restore the queue without the deleted unit
        originalQueue = tempQueue;

        if (found)
            return true;
    }

    return false;
}


/*
|--------------------------------------------------------------------------
| Update Blood Unit Expiry
|--------------------------------------------------------------------------
*/

bool BloodBankManager::updateExpiry(
    string unitId,
    int newDays)
{
    // Check every blood group
    for (auto& item : inventory)
    {
        auto& originalQueue = item.second;

        priority_queue<
            BloodUnit,
            vector<BloodUnit>,
            CompareBloodUnits
        > tempQueue;

        bool found = false;

        while (!originalQueue.empty())
        {
            BloodUnit current = originalQueue.top();
            originalQueue.pop();

            if (current.unitId == unitId)
            {
                current.daysToExpiry = newDays;
                found = true;
            }

            tempQueue.push(current);
        }

        // Restore queue
        originalQueue = tempQueue;

        if (found)
            return true;
    }

    return false;
}



/*
|--------------------------------------------------------------------------
| Save Inventory
|--------------------------------------------------------------------------
*/

void BloodBankManager::saveInventory()
{
    ofstream file("database/blood_inventory.txt");

    if (!file.is_open())
    {
        cout << "[ERROR] Unable to save inventory.\n";
        return;
    }

    for (const auto& item : inventory)
    {
        auto tempQueue = item.second;

        while (!tempQueue.empty())
        {
            BloodUnit unit = tempQueue.top();
            tempQueue.pop();

            file << unit.unitId << ","
                 << unit.bloodGroup << ","
                 << unit.daysToExpiry << ","
                 << unit.fridgeId << ","
                 << unit.shelfId << ","
                 << unit.slotNumber << "\n";
        }
    }

    file.close();

    cout << "[SUCCESS] Blood inventory saved.\n";
}



void BloodBankManager::loadInventory()
{
    ifstream file("database/blood_inventory.txt");

    if (!file.is_open())
    {
        cout << "[INFO] No existing inventory found.\n";
        return;
    }

    inventory.clear();

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        BloodUnit unit;

        getline(ss, unit.unitId, ',');
        getline(ss, unit.bloodGroup, ',');

        string expiry;
        getline(ss, expiry, ',');
        unit.daysToExpiry = stoi(expiry);

        getline(ss, unit.fridgeId, ',');
        getline(ss, unit.shelfId, ',');

        string slot;
        getline(ss, slot, ',');
        unit.slotNumber = stoi(slot);

        inventory[unit.bloodGroup].push(unit);
    }

    file.close();

    cout << "[SUCCESS] Blood inventory loaded.\n";
}
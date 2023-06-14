#include "slot_map.h"
#include "Timer/auto_clock.h"

#include <Windows.h>
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

// Compares performance between slot-map and various std data-structures
// Of course these measurements does not represent real life performance
// due to cache warming and elements in a slot-map will no longer be 
// aligned nicely with the keys as it is here the case.
int main()
{
    int loopCount = 10'000'000;

    {
        printf("<<< SLOT-MAP >>>\n\n");
        using Key = int;

        TSlotMap<int, Key, 24, 8> slotMap;
        slotMap.reserve(loopCount + 1);

        std::vector<Key> keys(loopCount + 1);

        printf("Adding %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                keys[i] = slotMap.push_back(i);
        }

        printf("Retrieving %d elements...\n", loopCount);
        {
            AutoClock clock;
            uint64_t sum = 0;
            for (int i = 0; i < loopCount; i++)
                sum += *slotMap[keys[i]];
        }

        printf("Removing %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                slotMap.erase(keys[i]);
        }
    }

    {
        printf("\n\n<<< STD::MAP >>>\n\n");
        std::map<int, int> map;

        printf("Adding %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                map[i] = i;
        }

        printf("Retrieving %d elements...\n", loopCount);
        {
            AutoClock clock;
            uint64_t sum = 0;
            for (int i = 0; i < loopCount; i++)
                sum += map[i];
        }

        printf("Removing %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                map.erase(i);
        }
    }

    {
        printf("\n\n<<< STD::UNORDERED_MAP >>>\n\n");

        std::unordered_map<int, int> map;

        printf("Adding %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                map[i] = i;
        }

        printf("Retrieving %d elements...\n", loopCount);
        {
            AutoClock clock;
            uint64_t sum = 0;
            for (int i = 0; i < loopCount; i++)
                sum += map[i];
        }

        printf("Removing %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                map.erase(i);
        }
    }

    {
        printf("\n\n<<< STD::VECTOR >>>\n\n");

        std::vector<int> vector;

        printf("Adding %d elements...\n", loopCount);
        {
            AutoClock clock;
            for (int i = 0; i < loopCount; i++)
                vector.push_back(i);
        }

        printf("Retrieving %d elements...\n", loopCount);
        {
            AutoClock clock;
            uint64_t sum = 0;
            for (int i = 0; i < loopCount; i++)
                sum += vector[i];
        }

        printf("Removing %d elements...\n", loopCount);
        {
            AutoClock clock;
            vector.clear();
        }
    }

    system("pause");
    return 0;
}
#include <iostream>
#include <string>
using namespace std;
class StringPool {
private:
    string** stringPool;
    int currentSize;  
    int maxSize;

public:
    StringPool(int max = 5) {
        maxSize = max;
        currentSize = 0;
        stringPool = new string*[maxSize];
        for (int i = 0; i < maxSize; ++i) {
            stringPool[i] = nullptr;
        }
    }
    bool addString(const string& value) {
        if (currentSize >= maxSize) {
            cout << "[Pool Full] Could not add: \"" << value << "\"\n";
            return false;
        }
        stringPool[currentSize] = new string(value);
        currentSize++;
        cout << "[Added] \"" << value << "\" at index " << (currentSize - 1) << "\n";
        return true;
    }

    string* removeString(int index) {
        if (index < 0 || index >= currentSize) {
            cout << "[Error] Invalid index: " << index << "\n";
            return nullptr;
        }

        string* leakedPtr = stringPool[index];

        for (int i = index; i < currentSize - 1; ++i) {
            stringPool[i] = stringPool[i + 1];
        }

        stringPool[currentSize - 1] = nullptr;
        currentSize--;

        cout << "[Removed without deleting] Ptr address: " << leakedPtr << "\n";
        return leakedPtr;
    }
    void displayPoolStatus() const {
        cout << "\n--- Current Pool Status (" << currentSize << "/" << maxSize << ") ---\n";
        if (currentSize == 0) {
            cout << "Pool is empty.\n";
        } else {
            for (int i = 0; i < currentSize; ++i) {
                cout << "Index " << i << ": \"" << *stringPool[i] 
                     << "\" (Address: " << stringPool[i] << ")\n";
            }
        }
        cout << "-------------------------------------\n\n";
    }
    ~StringPool() {
        for (int i = 0; i < currentSize; ++i) {
            delete stringPool[i];
        }
        delete[] stringPool;
    }
};

int main() {
    StringPool pool(5);

    cout << "=== 1. Adding Strings to the Pool ===\n";
    pool.addString("Alpha");
    pool.addString("Beta");
    pool.addString("Gamma");
    pool.addString("Delta");

    pool.displayPoolStatus();

    cout << "=== 2. Removing Strings (Creating Leaks) ===\n";

    string* leakedString1 = pool.removeString(1); // Removes "Beta"
    string* leakedString2 = pool.removeString(1); // Removes "Gamma"

    pool.displayPoolStatus();
    cout << "=== 3. Detecting and Fixing the Memory Leaks ===\n";

    if (leakedString1 != nullptr) {
        cout << "Fixing leak for string: \"" << *leakedString1 << "\" at " << leakedString1 << "\n";
        delete leakedString1; // Freeing heap memory manually
        leakedString1 = nullptr;
    }
    if (leakedString2 != nullptr) {
        cout << "Fixing leak for string: \"" << *leakedString2 << "\" at " << leakedString2 << "\n";
        delete leakedString2;
        leakedString2 = nullptr;
    }
    cout << "\nLeaks resolved successfully.\n";
    pool.displayPoolStatus();
    return 0;
}
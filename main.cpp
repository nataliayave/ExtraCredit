#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
using namespace std;


class InMemoryDB {
private:
    unordered_map<string, int> main_state; // Committed data
    unordered_map<string, int> transaction_state; // Transaction data
    bool in_transaction = false; // Transaction status

public:
    // Start a new transaction
    void begin_transaction() {
        if (in_transaction) {
            throw runtime_error("A transaction is already in progress.");
        }
        in_transaction = true;
        transaction_state.clear();
    }

    // Insert or update a key-value pair within a transaction
    void put(const string& key, int value) {
        if (!in_transaction) {
            throw runtime_error("No active transaction.");
        }
        transaction_state[key] = value;
    }

    // Retrieve a value for a key
    int* get(const string& key) const {
        if (in_transaction && transaction_state.find(key) != transaction_state.end()) {
            return const_cast<int*>(&transaction_state.at(key));
        }
        if (main_state.find(key) != main_state.end()) {
            return const_cast<int*>(&main_state.at(key));
        }
        return nullptr; // Return null pointer if key does not exist
    }

    // Commit the transaction
    void commit() {
        if (!in_transaction) {
            throw runtime_error("No active transaction to commit.");
        }
        for (const auto& [key, value] : transaction_state) {
            main_state[key] = value;
        }
        in_transaction = false;
        transaction_state.clear();
    }

    // Rollback the transaction
    void rollback() {
        if (!in_transaction) {
            throw runtime_error("No active transaction to rollback.");
        }
        in_transaction = false;
        transaction_state.clear();
    }
};

int main() {
    InMemoryDB db;

    try {
        // Example 1: Retrieve a non-existent key
        int* result = db.get("A");
        if (result) {
            cout << "Value of A: " << *result << "\n";
        } else {
            cout << "Key A does not exist.\n";
        }

        // Example 2: Insert without a transaction (should throw an error)
        try {
            db.put("A", 5);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }

        // Example 3: Begin transaction and update a key
        db.begin_transaction();
        db.put("A", 5);
        result = db.get("A");
        if (result) {
            cout << "Value of A (within transaction): " << *result << "\n";
        } else {
            cout << "Key A does not exist (within transaction).\n";
        }

        // Commit the transaction
        db.commit();
        result = db.get("A");
        if (result) {
            cout << "Value of A (after commit): " << *result << "\n";
        }

        // Example 4: Attempt rollback and commit without a transaction
        try {
            db.rollback();
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
        try {
            db.commit();
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }

        // Example 5: Transaction with rollback
        db.begin_transaction();
        db.put("B", 10);
        db.rollback();
        result = db.get("B");
        if (result) {
            cout << "Value of B: " << *result << "\n";
        } else {
            cout << "Key B does not exist (after rollback).\n";
        }
    } catch (const exception& e) {
        cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}

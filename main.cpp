#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> main_state; // Committed data
    std::unordered_map<std::string, int> transaction_state; // Transaction data
    bool in_transaction = false;

public:
    // Start a new transaction
    void begin_transaction() {
        if (in_transaction) {
            throw std::runtime_error("A transaction is already in progress.");
        }
        in_transaction = true;
        transaction_state.clear();
    }

    // Insert or update a key-value pair within a transaction
    void put(const std::string& key, int value) {
        if (!in_transaction) {
            throw std::runtime_error("No active transaction.");
        }
        transaction_state[key] = value;
    }

    // Retrieve a value for a key
    int get(const std::string& key) const {
        if (in_transaction && transaction_state.find(key) != transaction_state.end()) {
            return transaction_state.at(key);
        }
        if (main_state.find(key) != main_state.end()) {
            return main_state.at(key);
        }
        throw std::runtime_error("Key does not exist.");
    }

    // Commit the transaction
    void commit() {
        if (!in_transaction) {
            throw std::runtime_error("No active transaction to commit.");
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
            throw std::runtime_error("No active transaction to rollback.");
        }
        in_transaction = false;
        transaction_state.clear();
    }
};

// Example usage
int main() {
    InMemoryDB db;

    try {
        db.begin_transaction();
        db.put("A", 5);
        std::cout << "Value of A (within transaction): " << db.get("A") << "\n";
        db.commit();
        std::cout << "Value of A (after commit): " << db.get("A") << "\n";

        db.begin_transaction();
        db.put("B", 10);
        db.rollback();
        try {
            std::cout << "Value of B (after rollback): " << db.get("B") << "\n";
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}

#include "HashTable.hpp"
#include <string>

struct Human
{
    std::string name;
    int age;

    Human(std::string name, int age) : name(name), age(age) {}
    Human(const Human &other)
    {
        this->name = other.name;
        this->age = other.age;
    }
};

int main(int argc, char const *argv[])
{
    // Init the hash Table
    HashTable<int, Human> human_hash_table = HashTable<int, Human>(10);

    // Insert some Value
    std::cout << "===============================================================" << std::endl;
    human_hash_table.Insert(
        21,
        Human("Sad Nguyen", 21)

    );

    human_hash_table.Insert(
        10,
        Human("Duy Tran", 10)

    );

    human_hash_table.Insert(
        31,
        Human("Tuan Anh", 31)

    );
    
    human_hash_table.Print();

    // Try to Search the value with the key
    std::cout << "===============================================================" << std::endl;
    std::size_t key_to_search = 31;
    Human* human_to_search = human_hash_table.Search(key_to_search);

    std::cout << std::format(
        "{} {} appear in the Hash Table!\n",
        key_to_search,
        (human_to_search == nullptr) ? "is not" : "is"

    );

    // Delete the key
    std::cout << "===============================================================" << std::endl;
    std::size_t key_to_delete = 21;
    human_hash_table.Delete(key_to_delete);

    std::cout << std::format(
        "Hash Table after delete key {}!\n",
        key_to_delete

    );
    human_hash_table.Print();

    // Try to use the Copy Constructor
    std::cout << "===============================================================" << std::endl;
    HashTable<int, Human> human_hash_table_copy = HashTable<int, Human>(human_hash_table);
    
    std::cout << "New Hash Table after copy!" << std::endl;
    human_hash_table_copy.Print();

    return 0;
}

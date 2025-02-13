#include "HashTable.h"
#include <cassert>
#include <string>
void assertStringsEqual(const std::string& expected, const std::string& actual, const std::string& message) 
{
    if (expected != actual) 
    {
        std::cerr << "Assertion Failed: " << message << ". Expected: \"" << expected << "\", Actual: \"" << actual << "\"\n";
        assert(false);
    }
}

void testHashTableAddAndFind()
{
    HashTable<int, std::string> table;
    table.Add(1, "one");
    table.Add(2, "two");
    table.Add(3, "three");

    assert(table.FindElement(1) != nullptr);
	assertStringsEqual("one", table.FindElement(1)->second, "Value for key 1 is incorrect");
    assert(table.FindElement(2) != nullptr);
	assertStringsEqual("two", table.FindElement(2)->second, "Value for key 2 is incorrect");
    assert(table.FindElement(3) != nullptr);
	assertStringsEqual("three", table.FindElement(3)->second, "Value for key 3 is incorrect");
     assert(table.FindElement(4) == nullptr);
     std::cout << "test HashTable Add And Find passed" << std::endl;

}

void testHashTableDelete() 
{
	HashTable<int, std::string> table;
	table.Add(1, "one");
	table.Add(2, "two");
	table.Add(3, "three");
	table.Delete(2);
	assert(table.FindElement(1) != nullptr);
	assert(table.FindElement(2) == nullptr);
	assert(table.FindElement(3) != nullptr);
    std::cout << "test HashTable Delete passed" << std::endl;

}

void testHashTableSize() 
{
	HashTable<int, std::string> table;
	assert(table.SizeTable() == 0);
	table.Add(1, "one");
	table.Add(2, "two");
	assert(table.SizeTable() == 2);
	table.Delete(2);
	assert(table.SizeTable() == 1);

	std::cout << "test HashTable Size passed" << std::endl;
}

void testHashTableEmpty() 
{
    HashTable<int, std::string> table;
    assert(table.Empty());
    table.Add(1, "one");
    assert(!table.Empty());
     table.Delete(1);
    assert(table.Empty());
    std::cout << "test HashTable Empty passed" << std::endl;

}

void testHashTableRehashing()
{
	HashTable<int, std::string> table;
	for (int i = 0; i < 100; ++i) {
		table.Add(i, std::to_string(i));
		assert(table.FindElement(i) != nullptr);
	}
	for (int i = 0; i < 100; ++i) {
		assertStringsEqual(std::to_string(i), table.FindElement(i)->second, "Value after rehashing is incorrect");
	}
	std::cout << "test HashTable Rehashing passed" << std::endl;

}
void testHashTableKeys() 
{
	HashTable<std::string, int> table;
	table.Add("apple", 1);
	table.Add("banana", 2);
	table.Add("cherry", 3);

	ArraySequence<std::string> keys = table.Keys();
	assert(keys.GetLength() == 3);
	bool apple_found = false;
	bool banana_found = false;
	bool cherry_found = false;
	for (int i = 0; i < keys.GetLength(); ++i)
	{
		if (keys.Get(i) == "apple") apple_found = true;
		if (keys.Get(i) == "banana") banana_found = true;
		if (keys.Get(i) == "cherry") cherry_found = true;
	}
	assert(apple_found && banana_found && cherry_found);
	std::cout << "test HashTable Keys passed" << std::endl;


}

void testHashTableDeleteWithKeys() 
{
    HashTable<std::string, int> table;
    table.Add("apple", 1);
    table.Add("banana", 2);
    table.Add("cherry", 3);
    table.Delete("banana");

    ArraySequence<std::string> keys = table.Keys();
    assert(keys.GetLength() == 2);
    bool apple_found = false;
    bool cherry_found = false;
    for(int i = 0; i < keys.GetLength(); ++i)
    {
        if(keys.Get(i) == "apple") apple_found = true;
        if(keys.Get(i) == "cherry") cherry_found = true;
    }
    assert(apple_found &&  cherry_found);
   assert(table.FindElement("banana") == nullptr);
   std::cout << "test HashTable Delete With Keys passed" << std::endl;

}

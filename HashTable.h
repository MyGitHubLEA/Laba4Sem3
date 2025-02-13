#pragma once
#include <functional>
#include "..\..\..\Documents\Laba3Sem3\Sequence.h"


template <class Key, class Value, class Hash = std::hash<Key>>
class HashTable 
{
private:
    ArraySequence<ArraySequence<std::pair<Key, Value>>> table;
    size_t count; //кол-во
    double threshold = 0.7;

    size_t Index(const Key& key) const 
    {
        return Hash()(key) % table.GetLength();
    }

    void Rehash() 
    {
        size_t oldCapacity = table.GetLength();
        size_t newCapacity = oldCapacity * 2 + 1; 
        ArraySequence<ArraySequence<std::pair<Key, Value>>> newTable(newCapacity);  

        // элементы из старой таблицы в новую
        //std::cout << "HiRehash";
        for (auto iterator = begin(); iterator != end(); ++iterator)
        {
            const auto& pair = (*iterator);
            size_t newIndex = Hash()(pair.first) % newCapacity;
            newTable.Get(newIndex).Append(pair);
        }
        
        table = newTable; 
    }
public:
    HashTable() : table(5), count(0) {}


    std::pair<Key, Value>* FindElement(const Key& key) 
    {
        size_t index = Index(key);

        for (auto iterator = begin(); iterator != end(); ++iterator)
        {
            if (key == (*iterator).first)
            {
                return &(*iterator);  // указатель на элемент.
            }
        }
        return nullptr; // Ёлемента нет
    }

    Value Get(const Key& key)
    {
        size_t index = Index(key);

        for (auto iterator = begin(); iterator != end(); ++iterator)
        {
            if (key == (*iterator).first)
            {
                return (*iterator).second;  // указатель на элемент.
            }
        }
        return nullptr; // Ёлемента нет
    }
    void Add(const Key& key, const Value& value) 
    {
        if (FindElement(key))
        {
            // обновл€ем значение.
            size_t index = Index(key);

            for (auto iterator = begin(); iterator != end(); ++iterator)
            {
                if (key == (*iterator).first)
                    (*iterator).second = value;

            }
        }

        if ((double)(count + 1) / table.GetLength() > threshold)
        {
            Rehash(); // рехеширование, если -//-
        }

        size_t index = Index(key);
        table.Get(index).Append({ key, value }); 
        ++count; 
    }

    void Delete(const Key& key) 
    {
        size_t index = Index(key);

        for (size_t i = 0; i < table.Get(index).GetLength(); ++i) 
        {
            if (key == table.Get(index).Get(i).first)
            {
                table.Get(index).Delete(i);
                --count; 
                return;
            }
        }
    }

    ArraySequence<Key> Keys() const
    {
        ArraySequence<Key> keyList;


        for (auto iterator = begin(); iterator != end(); ++iterator)
        {
            keyList.Append((*iterator).first);
        }
        /*
        return out;
        for (size_t i = 0; i < table.GetLength(); ++i) 
        {
            for (size_t j = 0; j < table.Get(i).GetLength(); ++j)
            {
                keyList.Append(table.Get(i).Get(j).first); 
            }
        }
        */
        return keyList; // список ключей(name).
    }

    size_t SizeTable() const 
    {
        return count;
    }

    bool Empty() const 
    {
        return count == 0;
    }

    class HashTableIterator
    {
    public:
        const HashTable& hashTable;
        int currentIndex;
        int currentBucket;

    public:
        HashTableIterator(const HashTable& hashTable) : hashTable(hashTable), currentBucket(0), currentIndex(0) {}

        void FindNext()
        {
            while (currentBucket < hashTable.table.GetLength())
            {
                if (currentIndex < hashTable.table.Get(currentBucket).GetLength())
                {
                    return;
                }
                else
                {
                    currentBucket++;
                    currentIndex = 0;
                }
            }
        }

        std::pair<Key, Value>& operator*() const
        {

            if (currentBucket >= hashTable.table.GetLength())
            {
                throw std::out_of_range("Iterator out of range");
            }
            if (hashTable.table.Get(currentBucket).GetLength() == 0)
            {
                throw std::out_of_range("Iterator out of range");
            }
            if (currentIndex >= hashTable.table.Get(currentBucket).GetLength())
            {
                throw std::out_of_range("Iterator out of range");
            }
            //std::pair<Key, Value> kv(hashTable.table.Get(currentBucket).Get(currentIndex).first, hashTable.table.Get(currentBucket).Get(currentIndex).second);
            //std::cout << kv.key << " " << kv.value << std::endl;
            return hashTable.table.Get(currentBucket).Get(currentIndex);
        }

        bool operator!=(const HashTableIterator& other) const
        {
            return currentBucket != other.currentBucket || currentIndex != other.currentIndex;
        }

        bool operator==(const HashTableIterator& other) const
        {
            return currentBucket == other.currentBucket && currentIndex == other.currentIndex;
        }


        HashTableIterator& operator++()
        {
            currentIndex++;
            FindNext();
            return *this;
        }
    };


    HashTableIterator begin() const
    {
        HashTableIterator iterator(*this);
        iterator.FindNext();
        return iterator;
    }

    HashTableIterator end() const
    {
        HashTableIterator iterator(*this);
        iterator.currentBucket = table.GetLength();
        return iterator;
    }

    template<class T, class U>
    friend std::ostream& operator<<(std::ostream& out, const HashTable<T, U>& hashTable);
};

template <class Key, class Value>
std::ostream& operator<<(std::ostream& out, const HashTable<Key, Value>& hashTable)
{
    for (auto iterator = hashTable.begin(); iterator != hashTable.end(); ++iterator)
    {
        out << (*iterator).first << " " << (*iterator).second << std::endl;
    }
    return out;
}

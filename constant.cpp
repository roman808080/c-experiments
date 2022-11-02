#include <iostream>
#include <vector>
#include <list>
#include <memory>

struct Data
{
    int number;
};

struct DataObject
{
    unsigned int id;
    Data data;
};

class StoragePool
{
public:
    StoragePool(size_t maxCount)
    {
        dataVector.resize(maxCount);
        count = 0;
    }

    void insert(std::unique_ptr<DataObject> dataObject)
    {
        const unsigned int idObject = dataObject->id;
        dataVector[idObject] = std::move(dataObject);
        ++count;
    }

    DataObject* search(unsigned int idObject)
    {
        return dataVector[idObject].get();
    }

    void remove(unsigned int idObject)
    {
        dataVector[idObject].reset();
        --count;
    }

    size_t size()
    {
        return count;
    }

private:
    std::vector<std::unique_ptr<DataObject>> dataVector;
    size_t count;
};


class StoragePoolWithBuckets
{
public:
    StoragePoolWithBuckets(size_t bucketCount)
    {
        dataVector.resize(bucketCount);
        count = 0;
    }

    void insert(std::unique_ptr<DataObject> dataObject)
    {
        const unsigned int idHash = dataObject->id % dataVector.size();
        dataVector[idHash].push_back(std::move(dataObject));
        ++count;
    }

    DataObject* search(unsigned int idObject)
    {
        const unsigned int idHash = idObject % dataVector.size();
        for (auto const& dataObject : dataVector[idHash])
        {
            if (dataObject->id == idObject)
            {
                return dataObject.get();
            }
        }

        throw std::runtime_error("Data object is not found.");
    }

    void remove(unsigned int idObject)
    {
        const unsigned int idHash = idObject % dataVector.size();
        for (auto& dataObject : dataVector[idHash])
        {
            if (dataObject->id == idObject)
            {
                dataObject.reset();
                --count;
            }
        }

        throw std::runtime_error("Data object is not found.");
    }

    size_t size()
    {
        return count;
    }

private:
    std::vector<std::list<std::unique_ptr<DataObject>>> dataVector;
    size_t count;
};

int main()
{
    std::cout << "Hello hell" << std::endl;
    return 0;
}
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

// A linked list node
class Node {
public:
    int data;

    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};
 
/* Given a reference (pointer to pointer)
to the head of a list
and an int, inserts a new node on the
front of the list. */
std::shared_ptr<Node> push(std::shared_ptr<Node> head_ref, int new_data)
{
    /* 1. allocate node */
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
 
    /* 2. put in the data */
    new_node->data = new_data;
 
    /* 3. Make next of new node as head
    and previous as NULL */
    new_node->next = head_ref;
    new_node->prev = nullptr;
 
    /* 4. change prev of head node to new node */
    if (head_ref.get() != nullptr)
    {
        head_ref->prev = new_node;
    }
 
    /* 5. move the head to point to the new node */
    return new_node;
}
 
/* Given a node as prev_node, insert
a new node after the given node */
std::shared_ptr<Node> insertAfter(std::shared_ptr<Node> prev_node, int new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node.get() == nullptr) {
        std::cout << "the given previous node cannot be NULL" << std::endl;
        return nullptr;
    }
 
    /* 2. allocate new node */
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
 
    /* 3. put in the data */
    new_node->data = new_data;
 
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
 
    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;
 
    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;
 
    /* 7. Change previous of new_node's next node */
    if (new_node->next != nullptr)
    {
        new_node->next->prev = new_node;
    }

    return new_node;
}
 
/* Given a reference (pointer to pointer) to the head
of a DLL and an int, appends a new node at the end */
std::shared_ptr<Node> append(std::shared_ptr<Node> head_ref, int new_data)
{
    /* 1. allocate node */
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
 
    /* 2. put in the data */
    new_node->data = new_data;
 
    /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
    new_node->next = nullptr;
 
    /* 4. If the Linked List is empty, then make the new
        node as head */
    if (head_ref.get() == nullptr) {
        new_node->prev = nullptr;
        return new_node;
    }
 
    /* 5. Else traverse till the last node */
    std::shared_ptr<Node> last = head_ref; /* used in step 5*/
    while (last->next != nullptr)
    {
        last = last->next;
    }
 
    /* 6. Change the next of last node */
    last->next = new_node;
 
    /* 7. Make last node as previous of new node */
    new_node->prev = last;
 
    return new_node;
}
 
// This function prints contents of
// linked list starting from the given node
void printList(std::shared_ptr<Node> node)
{
    std::shared_ptr<Node> last;
    std::cout << "\nTraversal in forward direction \n";

    while (node.get() != nullptr) {
        std::cout << " " << node->data << " ";
        last = node;
        node = node->next;
    }
 
    std::cout << "\nTraversal in reverse direction \n";
    while (last.get() != nullptr) {
        std::cout << " " << last->data << " ";
        last = last->prev;
    }
}
 
// Driver code
int main()
{
    /* Start with the empty list */
    std::shared_ptr<Node> head = std::make_shared<Node>();
 
    // Insert 6. So linked list becomes 6->NULL
    append(head, 6);
 
    // Insert 7 at the beginning. So
    // linked list becomes 7->6->NULL
    head = push(head, 7);
 
    // Insert 1 at the beginning. So
    // linked list becomes 1->7->6->NULL
    head = push(head, 1);
 
    // Insert 4 at the end. So linked
    // list becomes 1->7->6->4->NULL
    append(head, 4);
 
    // Insert 8, after 7. So linked
    // list becomes 1->7->8->6->4->NULL
    insertAfter(head->next, 8);
 
    std::cout << "Created DLL is: ";
    printList(head);
 
    return 0;
}

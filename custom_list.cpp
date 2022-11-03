#include <iostream>
#include <vector>
#include <list>
#include <memory>

struct Data
{
    Data(int number, unsigned int id)
    : number (number),
      id (id)
    {}

    int number;
    unsigned int id;
};

// A linked list node
class Node
{
public:
    std::shared_ptr<Data> data {nullptr};

    std::shared_ptr<Node> next {nullptr};
    std::shared_ptr<Node> prev {nullptr};
};

/* Given a reference (pointer to pointer)
to the head of a list
and an int, inserts a new node on the
front of the list. */
std::shared_ptr<Node> push(std::shared_ptr<Node> head_ref, std::shared_ptr<Data> new_data)
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
std::shared_ptr<Node> insertAfter(std::shared_ptr<Node> prev_node, std::shared_ptr<Data> new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node.get() == nullptr)
    {
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

void removeNode(std::shared_ptr<Node> node_to_remove)
{
    /*1. check if the given prev_node is NULL */
    if (node_to_remove.get() == nullptr)
    {
        std::cout << "the given previous node cannot be NULL" << std::endl;
        return;
    }

    auto prev_node = node_to_remove->prev;
    auto next_node = node_to_remove->next;

    if (prev_node.get() != nullptr)
    {
        prev_node->next = next_node;
    }

    if (next_node.get() != nullptr)
    {
        next_node->prev = prev_node;
    }
}

void removeNode(Node* node_to_remove)
{
    /*1. check if the given prev_node is NULL */
    if (node_to_remove == nullptr)
    {
        std::cout << "the given previous node cannot be NULL" << std::endl;
        return;
    }

    auto prev_node = node_to_remove->prev;
    auto next_node = node_to_remove->next;

    if (prev_node != nullptr)
    {
        prev_node->next = next_node;
    }

    if (next_node != nullptr)
    {
        next_node->prev = prev_node;
    }
}

/* Given a reference (pointer to pointer) to the head
of a DLL and an int, appends a new node at the end */
std::shared_ptr<Node> append(std::shared_ptr<Node> head_ref, std::shared_ptr<Data> new_data)
{
    /* 1. allocate node */
    std::shared_ptr<Node> new_node = std::make_shared<Node>();

    /* 4. If the Linked List is empty, then make the new
        node as head */
    if (head_ref.get() == nullptr)
    {
        throw std::runtime_error("Head should be empty, but not nullptr.");
    }

    /* 5. Else traverse till the last node */
    std::shared_ptr<Node> last = head_ref; /* used in step 5*/
    while (last->next != nullptr)
    {
        last = last->next;
    }

    if (last->data != nullptr)
    {
        throw std::runtime_error("The data in the last element is not null.");
    }

    last->data = new_data;
    last->next = new_node;
    new_node->prev = last;

    return new_node;
}

// This function prints contents of
// linked list starting from the given node
void printList(std::shared_ptr<Node> node)
{
    std::shared_ptr<Node> last;
    std::cout << "\nTraversal in forward direction \n";

    while (node.get() != nullptr && node->data.get() != nullptr)
    {
        std::cout << " " << node->data->number << " ";
        last = node;
        node = node->next;
    }

    std::cout << "\nTraversal in reverse direction \n";
    while (last.get() != nullptr && last->data.get() != nullptr)
    {
        std::cout << " " << last->data->number << " ";
        last = last->prev;
    }
}

class StoragePool
{
public:
    StoragePool(size_t maxCount)
    {
        dataVector.resize(maxCount);
        count = 0;
    }

    Node* insert(std::shared_ptr<Data> dataObject)
    {
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->data = dataObject;

        const unsigned int idObject = dataObject->id;
        dataVector[idObject] = node.get();

        ++count;
        return node.get();
    }

    Node *search(unsigned int idObject)
    {
        return dataVector[idObject];
    }

    void remove(unsigned int idObject)
    {
        removeNode(dataVector[idObject]);
        dataVector[idObject] = nullptr;
        --count;
    }

    size_t size()
    {
        return count;
    }

private:
    std::vector<Node*> dataVector;
    std::shared_ptr<Node> head = std::make_shared<Node>();

    size_t count;
};

// Driver code
int main()
{
    /* Start with the empty list */
    std::shared_ptr<Node> head = std::make_shared<Node>();

    // Insert 6. So linked list becomes 6->NULL
    append(head, std::make_shared<Data>(6, 1));

    // Insert 7 at the beginning. So
    // linked list becomes 7->6->NULL
    head = push(head, std::make_shared<Data>(7, 2));

    // Insert 1 at the beginning. So
    // linked list becomes 1->7->6->NULL
    head = push(head, std::make_shared<Data>(1, 3));

    // Insert 4 at the end. So linked
    // list becomes 1->7->6->4->NULL
    append(head, std::make_shared<Data>(4, 4));

    // Insert 8, after 7. So linked
    // list becomes 1->7->8->6->4->NULL
    auto number_eight = insertAfter(head->next, std::make_shared<Data>(8, 1));

    std::cout << "Created DLL is: ";
    printList(head);

    removeNode(number_eight);
    printList(head);

    return 0;
}

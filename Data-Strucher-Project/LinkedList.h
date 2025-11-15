#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
    Node<T>* Head;

public:
    LinkedList() : Head(nullptr) {}

    ~LinkedList() {
        clear();
    }

    bool isEmpty() const {
        return Head == nullptr;
    }

    void InsertBeg(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->setNext(Head);
        Head = newNode;
    }

    void InsertEnd(const T& data) {
        Node<T>* newNode = new Node<T>(data);

        if (!Head) {
            Head = newNode;
            return;
        }

        Node<T>* temp = Head;
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }

    bool DeleteFirst(T& removedItem) {
        if (!Head)
            return false;

        Node<T>* temp = Head;
        removedItem = temp->getItem();
        Head = Head->getNext();
        delete temp;
        return true;
    }

    bool DeleteLast(T& removedItem) {
        if (!Head)
            return false;

        if (Head->getNext() == nullptr) {
            removedItem = Head->getItem();
            delete Head;
            Head = nullptr;
            return true;
        }

        Node<T>* prev = nullptr;
        Node<T>* curr = Head;

        while (curr->getNext() != nullptr) {
            prev = curr;
            curr = curr->getNext();
        }

        removedItem = curr->getItem();
        delete curr;
        prev->setNext(nullptr);
        return true;
    }

    bool Find(const T& key) const {
        Node<T>* temp = Head;

        while (temp != nullptr) {
            if (temp->getItem() == key)
                return true;
            temp = temp->getNext();
        }

        return false;
    }

    bool DeleteNode(const T& value) {
        if (!Head)
            return false;

        if (Head->getItem() == value) {
            Node<T>* temp = Head;
            Head = Head->getNext();
            delete temp;
            return true;
        }

        Node<T>* prev = nullptr;
        Node<T>* curr = Head;

        while (curr != nullptr) {
            if (curr->getItem() == value) {
                prev->setNext(curr->getNext());
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->getNext();
        }

        return false;
    }

    void clear() {
        T x;
        while (DeleteFirst(x));
    }

    void PrintList() const {
        Node<T>* temp = Head;
        while (temp) {
            cout << temp->getItem() << " ";
            temp = temp->getNext();
        }
        cout << endl;
    }
};

#endif

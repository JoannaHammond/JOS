#pragma once
#include <stddef.h>
#include <stdint.h>

template <class T>
class LinkedList {
    private:
    template <class J>
    class Entry {
        public:
        Entry<J>* next = NULL;
        Entry<J>* previous = NULL;
        J* item;    
    };
    Entry<T> *first = NULL;
    Entry<T> *last = NULL;
    Entry<T> *current = NULL;

    public:
    LinkedList() 
    {
        first = NULL;
        last = NULL;
        current = NULL;
    }

    void addItem(T* item)
    {
        if(last == NULL)
        {
            this->first = new Entry<T>();
            this->last = first;
            first->next = NULL;
            first->previous = NULL;
            first->item = item;
        }
        else
        {
            Entry<T>* newEntry = new Entry<T>();
            newEntry->previous = this->last;
            newEntry->next = NULL;
            newEntry->item = item;
            last->previous = newEntry;
            last = newEntry;
        }
    }
    
    void removeItem(T* item)
    {
        // TODO:
    }

    T* firstItem()
    {
        current = first;
        if(current != NULL)
        {
            return current->item;
        }
        return NULL;
    }

    T* nextItem()
    {
        if(current != NULL)
        {
            current = current->next;
        }
        if(current != NULL)
        {
            return current->item;
        }
        return NULL;
    }

    T* previousItem()
    {
        if(current != NULL)
        {
            current = current->previous;
        }
        if(current != NULL)
        {
            return current->item;
        }
        return NULL;
    }

    T* lastItem()
    {
        current = last;
        if(current != NULL)
        {
            return current->item;
        }
        return NULL;
    }
};
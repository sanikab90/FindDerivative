// Sanika Buche ssb170002

#ifndef List_hpp
#define List_hpp

//#include <stdio.h>
#include "Node.hpp"

class List{
private:
    Node *head;
    
public:
    
    //default constructor
    List();
    
    //overloaded constructor
    List(Node*);
    
    //accessor
    Node* getHead() {return head;}
    void displayExponent();
    void sort();
    
    //mutator
    void setHead(Node *h) {head = h;};
    
    //destructor
    ~List();
    
    //overloaded operators
    void operator++();    //prefix
    Node& operator[](int index);
    friend std::ostream& operator<<(std::ostream& out, List &l);
};

#endif /* List_hpp */

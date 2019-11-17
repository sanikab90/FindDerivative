// Sanika Buche ssb170002

#include "List.hpp"
#include <string>
#include <iostream>
#include <cmath>


//List

//default
List::List(){
}

//overloaded
List::List(Node *h){
    Node *temp = nullptr, *ref;
    int index = 0;
    
    //assign passed pointer to head pointer
    ref = new Node();
    head = ref;
    
    ref->setExponenet(h->getExponent());
    ref->setOuterCoefficient(h->getOuterCoefficient());
    ref->setInnerCoefficient(h->getInnerCoefficient());
    ref->setTrigId(h->getTrigIdentifier());
    
    //while we're not at the end of the list
    while(h->getNext() != nullptr){
        //move passed pointer
        h = h->getNext();
        //create new node
        Node *ptr = new Node();
        if(index == 0){
            index++;
            ref->setNext(ptr);
        }
        else{
            temp->setNext(ptr);
        }
        //assign pased node to temp node
        ptr->setOuterCoefficient(h->getOuterCoefficient());
        ptr->setExponenet(h->getExponent());
        ptr->setInnerCoefficient(h->getInnerCoefficient());
        ptr->setTrigId(h->getTrigIdentifier());
        
        temp = ptr;
    }
}

//destructor
List::~List(){
    Node *ref = head;
    
    //while not at end of list
    while(ref->getNext() != nullptr){
        Node *ptr = ref;
        //increment pointer
        ref = ref->getNext();
        
        //delete pointer
        delete ptr;
    }
    //delete head
    delete ref;
}

//accessor
void List::displayExponent(){
    //get position of head
    Node *ref = head;
    
    //show first member of list
    std::cout << ref->getExponent() << " ";
    
    while(ref->getNext() != nullptr){
        //go to next node
        ref = ref->getNext();
        
        //display the contents of node
        std::cout << ref->getExponent() << " ";
    }
    
    std::cout << std::endl;
}

void List::sort(){
    Node *temp = head;
    int count = 0;
    
    //get total nodes in list
    while(temp->getNext() != nullptr){
        count++;
        temp = temp->getNext();
    }
    
    //bubble sort
    for(int i = 0; i < count; i++){
        Node *prev = nullptr, *ptr = head, *next = ptr->getNext();
        
        for(int j = 0; j < count - i; j++){
            //if current exponent is bigger than the next exponent
            if(abs(ptr->getExponent()) < abs(next->getExponent())){
                //switch nodes
                ptr->setNext(next->getNext());
                next->setNext(ptr);
                
                //if ptr is pointing to head assign head to next
                if(ptr == head)
                    head = next;
                else{
                    prev->setNext(next);
                }
                
                //change pointer locations
                temp = ptr;
                ptr = next;
                next = temp;
            }
            
            //if theres trig function swap them
            if(ptr->getTrigIdentifier() != " " && next->getTrigIdentifier() != " "){
                ptr->setNext(next->getNext());
                next->setNext(ptr);
                
                //if ptr is pointing to head assign head to next
                if(ptr == head)
                    head = next;
                else{
                    prev->setNext(next);
                }
                
                //change pointer locations
                temp = ptr;
                ptr = next;
                next = temp;
            }
            
            //reassign pointers to next position
            prev = ptr;
            ptr = ptr->getNext();
            next = next->getNext();
        }
    }
}

//Node

//default
Node::Node(){
    outerCoefficient = 0;
    innerCoefficient = 0;
    exponent = 0;
    denominator = 0;
    numerator = 0;
    trigIdentifier = " ";
    next = nullptr;
}

//overloaded
Node::Node(int oCoefficient, int iCoefficient, int exp, int numer, int denom, std::string trig, Node *n){
    outerCoefficient = oCoefficient;
    innerCoefficient = iCoefficient;
    exponent = exp;
    numerator = numer;
    denominator = denom;
    trigIdentifier = trig;
    next = n;
}


//overloaded <<
std::ostream& operator<<(std::ostream& out, Node n){
    //if trig id is empty check if outerCoefficien is empty
    if(n.getTrigIdentifier() == " "){
        //if outercoefficient isn't empty check exponents
        if(n.getOuterCoefficient() != 0 && n.getNumerator() == 0 && n.getDenominator() == 0){
            if(n.getExponent() > 1 || n.getExponent() < 0)
                out << n.getOuterCoefficient() << "x^" << n.getExponent() << " ";
            //if exponent is 1
            else if(n.getExponent() == 1){
                out << n.getOuterCoefficient() << "x ";
            }
            //if exponent is 0
            else if(n.getExponent() == 0){
                out << n.getOuterCoefficient();
            }
        }
        
        //if outercoefficient is empty print fraction
        else if(n.getNumerator() != 0 && n.getDenominator() != 0){
            
            //if fraction is simplified all the way check exponent
            if(n.getExponent() > 1 || n.getExponent() < 0){
                
                //if numerator and denominator are the same
                if(n.getNumerator() == n.getDenominator())
                    out << "x^" << n.getExponent() << " ";
                
                //if denominator is 1
                else if(n.getDenominator() == 1){
                    out << n.getNumerator() << "x^" << n.getExponent() << " ";
                }
                else{
                    out << "(" << n.getNumerator() << "/" << n.getDenominator() << ")x^" << n.getExponent() << " ";
                }
            }
            
            //if exponent is 1
            else if(n.getExponent() == 1){
                
                //if numerator and denominator are the same
                if(n.getNumerator() == n.getDenominator())
                    out << "x ";
                
                //if denominator is 1
                else if(n.getDenominator() == 1){
                    out << n.getNumerator() << "x ";
                }
                
                else{
                    out << "(" << n.getNumerator() << "/" << n.getDenominator() << ")x ";
                }
            }
            
            //if exponent is 0
            else if(n.getExponent() == 0){
                
                //if numerator and denominator are the same
                if(n.getNumerator() == n.getDenominator())
                    out << "1 ";
                
                //if denominator is 1
                else if(n.getDenominator() == 1){
                    out << n.getNumerator() << " ";
                }
                else{
                    out << "(" << n.getNumerator() << "/" << n.getDenominator() << ")";
                }
            }
        }
    }
    
    //if trig id isn't empty print outer << trig << inner and x
    else{
        //if outerCoeffiicent isn't empty check exponents
        if(n.getOuterCoefficient() != 0 && n.getNumerator() == 0 && n.getDenominator() == 0){
            
            if(n.getOuterCoefficient() > 1 || n.getOuterCoefficient() < 0){
                if(n.getInnerCoefficient() > 1 || n.getInnerCoefficient() < 0)
                    out << n.getOuterCoefficient() << n.getTrigIdentifier() << " " << n.getInnerCoefficient() << "x ";
                //if inner coefficient is 1
                else{
                    if(n.getOuterCoefficient() == 1)
                        out << n.getTrigIdentifier() << " x";
                    else if(n.getOuterCoefficient() == -1){
                        out << "-" << n.getTrigIdentifier() << " x";
                    }
                    else{
                        out << n.getOuterCoefficient() << n.getTrigIdentifier() << " x";
                    }
                }
            }
        
            //if outer coefficient is 1
            else{
                if(n.getOuterCoefficient() == 1)
                    out << n.getTrigIdentifier() << " x";
                else if(n.getOuterCoefficient() == -1){
                    out << "-" << n.getTrigIdentifier() << " x";
                }
                else{
                    out << n.getTrigIdentifier() << " " << n.getInnerCoefficient() << "x";
                }
            }
        }
        
        //if outercoefficient is empty print fraction
        else if(n.getNumerator() != 0 && n.getDenominator() != 0){
            
            //if inner coefficient is not 1
            if(n.getInnerCoefficient() > 1 || n.getInnerCoefficient() < 0){
                
                //if numereator and denominator are the same
                if(n.getNumerator() == n.getDenominator()){
                    out << n.getNumerator() << n.getTrigIdentifier() << " " << n.getInnerCoefficient() << "x ";
                }
                
                //if denominator is 1
                else if(n.getDenominator() == 1){
                    out << n.getNumerator() << n.getTrigIdentifier() << " " << n.getTrigIdentifier() << "x ";
                }
                else{
                    out << "(" << n.getNumerator() << "/" << n.getDenominator() << ")" << n.getTrigIdentifier() << " " << n.getInnerCoefficient() << "x ";
                }
            }
            //if innercoefficient is 1
            else{
                
                //if numerator and denominator are the same
                if(n.getNumerator() == n.getDenominator()){
                    out << n.getTrigIdentifier() << " x ";
                }
                
                //if denominator is 1
                else if(n.getDenominator() == 1){
                    out << n.getNumerator() << n.getTrigIdentifier() << " x ";
                }
                else{
                    out << "(" << n.getNumerator() << "/" << n.getDenominator() << ")" << n.getTrigIdentifier() << " x ";
                }
            }
        }
    }
    return out;
}



//overloaded []
Node& List::operator[](int index){
    Node *ref = head;
    
    for(int i = 0; i < index; i++){
        ref = ref->getNext();
        
        if(!ref){
            std::cout << "Invalid index" << std::endl;
            break;
        }
    }
    return *ref;
}

//overloaded <<
std::ostream& operator<<(std::ostream& out, List &list){
    Node *temp = list.getHead();
    int count = 1;
    
    //get number of nodes in linked list
    while(temp->getNext() != nullptr){
        count++;
        temp = temp->getNext();
    }
    
    for(int i = 0; i < count; i++){
        Node *ptr;
         ptr = &list[i];
        
        //check if ptr holds a constant
        if(ptr->getOuterCoefficient() == 0 && ptr->getExponent() == 0){
            ptr = ptr->getNext();
            i++;
        }
       
        if(i != count-1){
            //check if ptr has trig id
            if(ptr->getTrigIdentifier() != " "){
                //check sign of outerCoef
                if(ptr->getNext()->getOuterCoefficient() > 0)
                    out << *ptr << " + ";
                else{
                    int outCoef = ptr->getNext()->getOuterCoefficient();
                    int newOutCoef = -1 * outCoef;
                    ptr->getNext()->setOuterCoefficient(newOutCoef);
                    out << *ptr << " - ";
                }
            }
            //if theres no trig id
            else{
                //check sign of outercoef
                if(ptr->getNext()->getOuterCoefficient() > 0)
                    out << *ptr << "+ ";
                else if(ptr->getNext()->getOuterCoefficient() < 0){
                    int outCoef = ptr->getNext()->getOuterCoefficient();
                    int newOutCoef = -1 * outCoef;
                    ptr->getNext()->setOuterCoefficient(newOutCoef);
                    out << *ptr << "- ";
                }
                //if the next outer coefficient is the last exit function
                else{
                    out << *ptr;
                    return out;
                }
            }
        }
        else{
            out << *ptr;
        }
     }
    
    return out;
}

//overloaded ++
void List::operator++(){
    Node *newHead = new Node();
    newHead->setNext(head);
    head = newHead;
}

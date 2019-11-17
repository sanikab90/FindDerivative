// Sanika Buche ssb170002

#ifndef Node_hpp
#define Node_hpp
#include <string>

class Node{
private:
    //variables
    int outerCoefficient;
    int innerCoefficient;
    int numerator;
    int denominator;
    int exponent;
    std::string trigIdentifier;
    Node *next;
    
public:
    //default constructor
    Node();
    
    //overloaded constructor
    Node(int, int, int, int, int, std::string, Node*);
    
    //accessors
    int getOuterCoefficient() const {return outerCoefficient;}
    int getInnerCoefficient() const {return innerCoefficient;}
    int getNumerator() const {return numerator;}
    int getDenominator() const {return denominator;}
    int getExponent() const {return exponent;}
    std::string getTrigIdentifier() {return trigIdentifier;}
    Node* getNext() {return next;}
    
    //mutators
    void setOuterCoefficient(int coefficient) {outerCoefficient = coefficient;}
    void setInnerCoefficient(int coefficient) {innerCoefficient = coefficient;}
    void setExponenet(int exp) {exponent = exp;}
    void setTrigId(std::string trig) {trigIdentifier = trig;}
    void setNext(Node *n) {next = n;}
    void setNum(int n) {numerator = n;}
    void setDenom(int d) {denominator = d;}
    
    //overloaded functions
    friend std::ostream& operator<<(std::ostream& out, Node n);
    
    
};


#endif /*Node_hpp*/

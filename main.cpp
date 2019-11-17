/*
 * Sanika Buche ssb170002
 * A program that reads in a function from a file and takes the derivative of it
 */

#include <iostream>
#include "List.hpp"
#include "Node.hpp"
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
void parse(string equation, unsigned long equationLength, fstream &output);
void trigParse(string equation, unsigned long equationLength, fstream &output);
void trigDerive(fstream &output, List &list);
void derive(fstream &output, List &list);
int gcd(int a, int b);

int gcd(int a, int b){
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

/*
 * A function that parses the function if said function has a trig fucntion sin, cos or tan
 * using a pointer to loop through each character and assign nodes using the pointer
 *
 * Parameters:
 *      string equation - the equation to parse. includes sin, cos and tan
 *      unsigned long equationLength - the length of the equation
 *      fstream &output - variable to output derivative of equation to a file
 *
 * Return: void
 */
void trigParse(string equation, unsigned long equationLength, fstream &output){
    bool isNeg = false, constant = false;
    Node *temp = new Node();
    List list;
    int index = 0;
    char *ptr = nullptr, *temp2 = nullptr, *next = nullptr, *prev = nullptr, *twoBack = nullptr, *negCheck = nullptr;
    
    //make first node head of list
    list.setHead(temp);
    
    //set ptr to first character
    ptr = &equation[0];
    
    //keep looping while ptr doesnt get to the end of the equation
    while(ptr != &equation[equationLength]){
        
        //continue if there's no space
        if(*ptr != ' '){
            //if it's the first time going through loop don't incremnent list
            if(index > 0)
                ++list;
            index++;
            
            //save position of ptr
            temp2 = ptr;
            
            //loop through and look for parenthesis
            while(*ptr != '(' && *ptr != ' ')
                ptr++;
            //if parenthesis is found look for numerator and denominator
            if(*ptr == '('){
                next = ptr + 1;
                list.getHead()->setNum((*next-'0'));
                ptr += 2;
                next += 2;
                list.getHead()->setDenom((*next-'0'));
            }
            //set ptr back to original position
            ptr = temp2;
            
            //save initial position
            temp2 = ptr;
            
            //loop until trig function is found or a space is found
            while(*ptr != 's' && *ptr != 'c' && *ptr != 't' && *ptr != ' ')
                ptr++;

            //if no trig function is found look for outer coefficient and exponent
            if(*ptr != 's' && *ptr != 'c' && *ptr != 't'){
                //set ptr back to initial position
                ptr = temp2;
                next = ptr + 1;
                prev = ptr - 1;
                twoBack = prev - 1;
                
                //loop until x is found or space is reached
                while(*ptr != 'x' && *ptr != ' '){
                    ptr++;
                    next++;
                    prev++;
                    twoBack++;
                }
                //if x is found and theres a number behind it set that as outerCoefficient
                if(*ptr == 'x' && isdigit(*prev)){
                    
                    //check if twoBack is a digit. if it is set outerCoefficient to 10
                    if(isdigit(*twoBack)){
                        if(isNeg)
                            list.getHead()->setOuterCoefficient(-10);
                        else{
                            list.getHead()->setOuterCoefficient(10);
                        }
                    }
                    //if twoBack isn't a digit set outerCoefficient to prev
                    else{
                        if(isNeg)
                            list.getHead()->setOuterCoefficient(-1 * (*prev - '0'));
                        else{
                            list.getHead()->setOuterCoefficient((*prev - '0'));
                        }
                    }
                }
                
                //if x is found and theres no number behind it set outerCoefficient to 1
                else if(*ptr == 'x' && !(isdigit(*prev))){
                    list.getHead()->setOuterCoefficient(1);
                }
                
                //otherwise if x isn't found exit bc then number is a constant
                else if(*ptr != 'x'){
                    constant = true;
                }
                
                //next find exponent
                
                //loop until ^ is found or a space is reached
                while(*ptr != '^' && *ptr != ' '){
                    ptr++;
                    next++;
                    prev++;
                    twoBack++;
                }
                
                //if ^ is found and theres a number in front of it set that as exponent
                if(*ptr == '^' && isdigit(*next))
                    list.getHead()->setExponenet((*next-'0'));
                //otherwise if there's no ^ set exponent to 1
                else if(*ptr != '^'){
                    list.getHead()->setExponenet(1);
                }
                
                //loop until space or operator is found
                while(*ptr != ' ' || (*prev != '+' && *prev != '-')){
                    ptr++;
                    next++;
                    prev++;
                    //if ptr reaches the end of the equation
                    if(ptr == &equation[equationLength])
                        break;
                }
                //if prev is '-' the the next coefficient is negative
                if(*prev == '-')
                    isNeg = true;
                
                //otherwise it's positive
                else if(*prev == '+'){
                    isNeg = false;
                }
            }
            
            //if a trig function is found put it in the list
            else{
                next = ptr + 1;
                prev = ptr - 1;
                twoBack = prev - 1;
                
                //check if ptr is 's' 'c' or 't' for sin cos or tan
                if(*ptr == 's')
                    list.getHead()->setTrigId("sin");
                else if(*ptr == 'c')
                    list.getHead()->setTrigId("cos");
                else if(*ptr == 't')
                    list.getHead()->setTrigId("tan");
                
                //check behind trig function to get outerCoefficient
                if(isdigit(*prev)){
                    
                    //check behind previous digit to see if coefficient is 10
                    if(isdigit(*twoBack)){
                        negCheck = twoBack - 1;
                        
                        //if the character behind 10 is - set outerCoefficient to -10
                        if(*negCheck == '-' || isNeg)
                            list.getHead()->setOuterCoefficient(-10);
                        else{
                            list.getHead()->setOuterCoefficient(10);
                        }
                    }
                    
                    //if check behind previous digit isn't a number set outercoefficient as whatever number prev is
                    else{
                        if(isNeg)
                            list.getHead()->setOuterCoefficient(-1 * (*prev - '0'));
                        else{
                            list.getHead()->setOuterCoefficient((*prev - '0'));
                        }
                    }
                }
                
                //if theres no digit behind trig fucntion set coefficient to 1
                else{
                    if(isNeg)
                        list.getHead()->setOuterCoefficient(-1);
                    else{
                        list.getHead()->setOuterCoefficient(1);
                    }
                }
                
                //loop until x is found
                while(*ptr != 'x'){
                    ptr++;
                    next++;
                    prev++;
                    twoBack++;
                }
                
                //once x is found check behind it for innercoefficient
                if(isdigit(*prev)){
                    
                    //check if twoBack is also a digit if it is set innerCoefficient to 10
                    if(isdigit(*twoBack))
                        list.getHead()->setInnerCoefficient(10);
                    
                    //otherwise set innercoefficient to whatever number prev is
                    else{
                        list.getHead()->setInnerCoefficient((*prev-'0'));
                    }
                }
                
                //if whats behind x isn't a digit set inner coefficient to 1
                else{
                    list.getHead()->setInnerCoefficient(1);
                }
                
                //loop until space or operator is found
                while(*ptr != ' ' || (*prev != '+' && *prev != '-')){
                    ptr++;
                    next++;
                    prev++;
                    //if ptr reaches the end of the equation
                    if(ptr == &equation[equationLength])
                        break;
                }
                //if prev is '-' the the next coefficient is negative
                if(*prev == '-')
                    isNeg = true;
                
                //otherwise it's positive
                else if(*prev == '+'){
                    isNeg = false;
                }
                
            }
        }
        //if there's a space increment ptr
        else{
            ptr++;
        }
    }
    if(ptr == &equation[equationLength]){
        //call derive function
        trigDerive(output, list);
    }
}

/*
 * A function that parses the function if said function doesn't have a trig function such as sin, cos or tan
 * using a pointer to loop through each character and assign nodes using the pointer
 *
 * Parameters:
 *      string equation - the equation to parse
 *      unsigned long equationLength - the length of the equation
 *      fstream &output - variable to output derivative of equation to a file
 *
 * Return: void
 */
void parse(string equation, unsigned long equationLength, fstream &output){
    bool isNeg = false;
    Node *temp = new Node();
    List list;
    char *ptr = nullptr, *prev = nullptr, *next = nullptr, *temp2 = nullptr, *twoBack = nullptr;
    
    //make initial node head of list
    list.setHead(temp);
    
    //set ptr to first character
    ptr = &equation[0];
    
    int i = 0;
    while(ptr != &equation[equationLength]){
        next = ptr + 1;
        prev = ptr - 1;
        twoBack = prev - 1;
        
        //check if theres a space
        if(*ptr != ' '){
            
            //if this is the first time going through the loop don't increment the node to the list
            if(i > 0)
                ++list;
            i++;
            
            //save position of ptr
            temp2 = ptr;

            //loop through and look for parenthesis
            while(*ptr != '(' && *ptr != ' ')
                ptr++;
            
            //if parenthesis is found look for numerator and denominator
            if(*ptr == '('){
                next = ptr + 1;
                list.getHead()->setNum((*next-'0'));
                ptr += 2;
                next += 2;
                list.getHead()->setDenom((*next-'0'));
            }
            
            //set ptr back to original position
            ptr = temp2;
            
            //loop until x is found or pointer reaches end of line
            while(*ptr != 'x' && ptr != &equation[equationLength-1]){
                ptr++;
                next++;
                prev++;
                twoBack++;
            }
            
            //if x isn't found number is a constant and can be disreguarded
            if(*ptr != 'x')
                bool isConst = true;
            
            //otherwise if x is found and there is a number behind it check to see if it is negative
            else if(isdigit(*prev)){
                
                //if character behind prev is digit then coefficient is 10
                if(isdigit(*twoBack)){
                    if(isNeg)
                        list.getHead()->setOuterCoefficient(-10);
                    else{
                        list.getHead()->setOuterCoefficient(10);
                    }
                }
                
                //if theres no digit behind prev set coefficient to prev
                else{
                    if(isNeg)
                        list.getHead()->setOuterCoefficient((-1 * (*prev-'0')));
                    else{
                        list.getHead()->setOuterCoefficient((*prev-'0'));
                    }
                }
            }
            
            //if prev isn't a digit set coefficient to 1
            else{
                if(isNeg)
                    list.getHead()->setOuterCoefficient(-1);
                else{
                    list.getHead()->setOuterCoefficient(1);
                }
            }
            
            //get the exponenet
            
            //set temp equal to ptr
            temp2 = ptr;
            
            //loop until '^' is found
            while (*ptr != '^' && *ptr != ' ' && ptr != &equation[equationLength]) {
                ptr++;
                next = ptr + 1;
                prev = ptr - 1;
            }
            
            //if ^ isnt found set pointer back to orig
            if(*ptr != '^' ){
                
                //if thers no ^ then the exponent is 1
                if(list.getHead()->getOuterCoefficient() != 0)
                    list.getHead()->setExponenet(1);
                
                ptr = temp2;
                next = ptr + 1;
                prev = ptr - 1;
                twoBack = prev - 1;
            }
            
            //if character after '^' is a number set that as the exponent
            else if(isdigit(*next)){
                list.getHead()->setExponenet((*next-'0'));
            }
            
            //if character after '^' is '-' set the character after as the exponent
            else if(*next == '-'){
                ptr++;
                prev++;
                next++;
                twoBack++;
                int exp = -1 * (*next-'0');
                list.getHead()->setExponenet(exp);
            }
            
            //once exponent is found loop until a space is found or end of equation is reached
            while(*ptr != ' ' || (*prev != '+' && *prev != '-')){
                ptr++;
                next++;
                prev++;
                if(ptr == &equation[equationLength])
                    break;
            }
            
            
            //if prev is '-' the the next coefficient is negative
            if(*prev == '-')
                isNeg = true;
            
            //otherwise the next coefficient is positive
            else if(*prev == '+'){
                isNeg = false;
            }
        }
        
        //if ptr is a space increment ptr
        else{
            ptr++;
        }
    }
    
    //call derive function
    derive(output, list);
}

/*
 * a function that prints the derivative of the equation passed in to a file
 *
 * Parameters:
 *      fstream &output - variable to output derivative of equation to a file
 *      List &list - passes in the list by reference to get all the nodes in the equation
 *
 * Return: void
 */
void derive(fstream &output, List &list){
    int newCoef, newExp;
    
    //set Node to head of the list
    Node *temp = list.getHead();
    int count = 1;
    
    //get number of nodes in list
    while (temp->getNext() != nullptr) {
        count++;
        temp = temp->getNext();
    }
    
    //sort list
    list.sort();
    
    //loop through list and take derivative
    for(int i = 0; i < count; i++){
        
        //check if numerator and denominator is empty
        if(list[i].getNumerator() == 0 && list[i].getDenominator() == 0){
        
            //multiply exponent by outer coefficient
            newCoef = list[i].getExponent() * list[i].getOuterCoefficient();
            list[i].setOuterCoefficient(newCoef);
            
            //subtract exponent by 1
            newExp = list[i].getExponent() - 1;
            list[i].setExponenet(newExp);
        }
        
        //if numeraotr and denominator isn't empty
        else{
            
            //multiply numerator by exponent
            list[i].setNum(list[i].getNumerator() * list[i].getExponent());
            
            //subtract 1 from exponent
            list[i].setExponenet(list[i].getExponent() - 1);
            
            //if numerator and denominator doens't have a remainder print like that
            if(list[i].getNumerator() % list[i].getDenominator() != 0){
                int mod = gcd(list[i].getNumerator(), list[i].getDenominator());
                
                list[i].setNum(list[i].getNumerator() / mod);
                list[i].setDenom(list[i].getDenominator() / mod);
            }
        }
        
    }
    
    //output to file
    cout << list << endl;
    //output << list << endl;
    
}

/*
 * a function that prints the derivative of the equation passed in to a file
 * if the function includes sin, cos or tan
 *
 * Parameters:
 *      fstream &output - variable to output derivative of equation to a file
 *      List &list - passes in the list by reference to get all the nodes in the equation
 *
 * Return: void
 */
void trigDerive(fstream &output, List &list){
    int newExp, newOutCoef;
    
    //set Node to head of the list
    Node *temp = list.getHead();
    int count = 1;
    
    //get number of nodes in the list
    while(temp->getNext() != nullptr){
        count++;
        temp = temp->getNext();
    }
    
    //sort list
    list.sort();
    
    //loop through list and take derivative
    for(int i = 0; i < count; i++){
        
        //if this node doesn't have a trig function derive noramlly
        if(list[i].getTrigIdentifier() == " "){
            
            //check if numerator and denominator is empty
            if(list[i].getNumerator() == 0 && list[i].getDenominator() == 0){
                
                //multiply exponent by outerCoefficient
                newOutCoef = list[i].getExponent() * list[i].getOuterCoefficient();
                list[i].setOuterCoefficient(newOutCoef);
            
                //subtract 1 from the exponent
                newExp = list[i].getExponent() - 1;
                list[i].setExponenet(newExp);
            }
            
            //otherwise derive based on numerator
            else{
                
                //multiply numerator by exponent
                list[i].setNum(list[i].getNumerator() * list[i].getExponent());
                
                //subtract 1 from exponent
                list[i].setExponenet(list[i].getExponent() - 1);
                
                //if numerator and denominator doens't have a remainder print like that
                if(list[i].getNumerator() % list[i].getDenominator() == 0){
                    int mod = gcd(list[i].getNumerator(), list[i].getDenominator());
                    
                    list[i].setNum(list[i].getNumerator() / mod);
                    list[i].setDenom(list[i].getDenominator() / mod);
                }
            }
        }
        
        //if node has trig function
        else{
            
            //check if numerator and denominator is empty
            if(list[i].getNumerator() == 0 && list[i].getDenominator() == 0){
                
                //multiply innerCoefficient by outerCoefficient
                newOutCoef = list[i].getInnerCoefficient() * list[i].getOuterCoefficient();
                list[i].setOuterCoefficient(newOutCoef);
            }
            
            //if outerCoefficient is empty derive based on numerator
            else{
                
                //multiply numerator by innerCoefficient
                list[i].setNum(list[i].getNumerator() * list[i].getInnerCoefficient());
                
                //if numerator and denominator doens't have a remainder print like that
                if(list[i].getNumerator() % list[i].getDenominator() != 0){
                    newOutCoef = gcd(list[i].getNumerator(), list[i].getDenominator());
                    
                    list[i].setNum(list[i].getNumerator() / newOutCoef);
                    list[i].setDenom(list[i].getDenominator() / newOutCoef);
                }
            }
            
            //check which trig function is being used
            if(list[i].getTrigIdentifier() == "sin")
                list[i].setTrigId("cos");
            else if(list[i].getTrigIdentifier() == "cos"){
                newOutCoef *= -1;
                list[i].setOuterCoefficient(newOutCoef);
                list[i].setTrigId("sin");
            }
            else if(list[i].getTrigIdentifier() == "tan")
                list[i].setTrigId("sec^2");
        }
    }
    
    //output to file
    cout << list << endl;
//    output << list << endl;
}

int main(){
    string equation, trig;
    Node node;
    unsigned long equationLength;
    bool isTrig = false;
    char *ptr = nullptr;

    //declare and open read file
    fstream file;
    file.open("/Users/sanikabuche/Downloads/Project4TestCases(2)/functionsExtra_1.txt", ios::in | ios::out);
    
    //declare and open output file
    fstream output;
    output.open("derive.txt", ios::out | ios::app);

    //loop until end of file
    while(getline(file, equation)){
        isTrig = false;
        equationLength = equation.length();

        ptr = &equation[0];
        //loop through once to find if theres a trig function
        while(ptr != &equation[equationLength-1]){
            //if there is a a trig function break out of loop
            if(isalpha(*ptr) && *ptr != 'x'){
                isTrig = true;
                break;
            }
            //otherwise keep going
            else{
                ptr++;
            }
        }

        //if function includes trig go into trigParse
        if(isTrig)
            trigParse(equation, equationLength, output);
        //otherwise go into parse function
        else{
            parse(equation, equationLength, output);
        }

    }
    
    cout << "Derivative printed to file" << endl;
    
    return 0;
}


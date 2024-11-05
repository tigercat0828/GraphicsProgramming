#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;
class Lsystem {
private:
    unordered_map<char, string> rules;
public:
    string mAxiom;
    Lsystem(const string& axiom) : mAxiom(axiom){}
    
    string ApplyRules(int iteration){
        return ApplyRules(mAxiom, iteration);
    }
    string ApplyRules(const string& input, int iteration){
        string current = input;
        for (int i = 0; i < iteration; i++)
        {
            current = applyRules(current);
        }
        return current;
    }
    void NewRule(const char symbol, string replacement){
        rules[symbol] = replacement;
    }
    string GetRule(const char symbol, string& replacement){
        return  rules[symbol];
    }
private:
    string applyRules(const string& input){
        ostringstream next;
        for(char c : input) {
            if(rules.find(c) != rules.end()){
                next<<rules.at(c);
            }else{  
                next << c; // no rule found, so keep charater
            }
        }
        return next.str();
    }
};
int main(){

    Lsystem sys("A");
    sys.NewRule('A',"AB");
    sys.NewRule('B',"A");

    for (int i = 0; i <= 7; i++){
        cout << sys.ApplyRules(i) << endl;    
    }
    return 0;
}



#ifndef automata_H
#include "nodeAutomata.cc"
#define automata_H
#endif

#include <stack>
#include <iostream>

automata* conversionNode(string regex) {
    if (regex == "") {
        regex = "(1)*";
    }
    stack <automata*> automatons;
    stack <char> operators;

    int i = 0;
    while (i < regex.length()) {
        // Generate Automata
        int num = 0;
        while (regex[i] == '(') {
            operators.push('(');
            ++i;
        }
        while (isdigit(regex[i])) {
            num = num*10 + (regex[i] - '0');
            ++i;
        }
        
        automata* curr = new automata(num);
        // Do operation on Automata
        if (operators.empty()) {
            automatons.push(curr);
        }
        else if (operators.top() == '.') {
            automata* operated = automatons.top();
            operated->concat(curr);
            automatons.pop();
            operators.pop();
            automatons.push(operated);
        }
        else if (operators.top() == 'U') {
            automata* operated = automatons.top();
            operated->unionor(curr);
            automatons.pop();
            operators.pop();
            automatons.push(operated);
        }
        else {
            automatons.push(curr);
        }

        while (regex[i] == ')') {
            operators.pop();
            if (operators.empty()) {
            }
            else if (operators.top() == '.') {
                automata* operated = automatons.top();
                automatons.pop();
                automata* operated2 = automatons.top();
                automatons.pop();
                operated2->concat(operated);
                operators.pop();
                automatons.push(operated2);
            }
            else if (operators.top() == 'U') {
                automata* operated = automatons.top();
                automatons.pop();
                automata* operated2 = automatons.top();
                automatons.pop();
                operated2->unionor(operated);
                operators.pop();
                automatons.push(operated2);
            }
            ++i;
            
        }
        // Next operator push or operate(if * or +)
        if (regex[i] == '.') {
            operators.push('.');
            ++i;
        }
        else if (regex[i] == 'U') {
            operators.push('U');
            ++i;
        }
        else if (regex[i] == '*') {
            automata* operated = automatons.top();
            operated->closure();
            automatons.pop();
            automatons.push(operated);
            ++i;
        }
        else if (regex[i] == '+') {
            automata* operated = automatons.top();
            operated->plus();
            automatons.pop();
            automatons.push(operated);
            ++i;
        }

        while (regex[i] == ')') {
            operators.pop();
            if (operators.empty()) {
            }
            else if (operators.top() == '.') {
                automata* operated = automatons.top();
                automatons.pop();
                automata* operated2 = automatons.top();
                automatons.pop();
                operated2->concat(operated);
                operators.pop();
                automatons.push(operated2);
            }
            else if (operators.top() == 'U') {
                automata* operated = automatons.top();
                automatons.pop();
                automata* operated2 = automatons.top();
                automatons.pop();
                operated2->unionor(operated);
                operators.pop();
                automatons.push(operated2);
            }
            ++i; 
            if (regex[i] == '.') {
                operators.push('.');
                ++i;
            }
            else if (regex[i] == 'U') {
                operators.push('U');
                ++i;
            }
            else if (regex[i] == '*') {
                automata* operated = automatons.top();
                operated->closure();
                automatons.pop();
                automatons.push(operated);
                ++i;
            }
            else if (regex[i] == '+') {
                automata* operated = automatons.top();
                operated->plus();
                automatons.pop();
                automatons.push(operated);
                ++i;
            }
        }
    }
    automata* a = automatons.top();
    state* finalState = new state(-2);
    for (int i = 0; i < a->finalStates.size(); ++i) {
        finalState->setTransition(a->finalStates[i],false);
    }

    a->finalState = finalState;
    return a;

}
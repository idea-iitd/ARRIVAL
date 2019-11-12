#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void lt (vector<int> a, int* c)
{
    *c = a[0] > a[1];
}
void gt (vector<int> a, int* c)
{
    *c = a[0] < a[1];
}
void equals (vector<int> a, int* c)
{
    *c = a[0] == a[1];
}

class Function {

public:
    Function(string s);

    vector<void (*)(vector<int>, int*)> functions;
    vector<void (*)(vector<int>, int*)> secfunctions;

    vector<string> funattr;
    vector<string> secfunattr;

    vector<int> params;
    vector<int> secparams;

    vector<int> fnType;
};

Function::Function(string s)
{

    int i = 0;
    while (s[i]) {
        switch (s[i]) {
            case '&':
                fnType.push_back(1);
                i++;
                break;
            case '|':
                fnType.push_back(2);
                i++;
                break;
            default:
                fnType.push_back(0);
                break;
        }
        switch (s[i]) {
            case 'l':
                functions.push_back(lt);
                break;
            case 'g':
                functions.push_back(gt);
                break;
            case 'e':
                functions.push_back(equals);
                break;
        }
        ++i;
        ++i;
        string st = "";
        while (s[i]!='_')
        {
            st.push_back(s[i]);
            ++i;
        }
        funattr.push_back(st);
        ++i;
        int num = 0;
        while (isdigit(s[i]))
        {
            num = num * 10 + (s[i] - '0');
            ++i;
        }
        params.push_back(num);
        if(!s[i])
        break;
        ++i;

        if (fnType.back() != 0)
        {
            switch (s[i]) {
                case 'l':
                    secfunctions.push_back(lt);
                    break;
                case 'g':
                    secfunctions.push_back(gt);
                    break;
                case 'e':
                    secfunctions.push_back(equals);
                    break;
            }
            ++i;

            string st = "";
            while (s[i]!='_')
            {
                st.push_back(s[i]);
                ++i;
            }
            secfunattr.push_back(st);
            ++i;

            int num = 0;
            while (isdigit(s[i]))
            {
                num = num * 10 + (s[i] - '0');
                ++i;
            }
            secparams.push_back(num);
            ++i;
        }  
        else {
            secfunctions.push_back(lt);
            secfunattr.push_back("");
            secparams.push_back(0);
        } 
    }
    
}

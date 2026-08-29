#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <cstdlib>

using namespace std;

struct DFAState
{
    set<int> nfaStates;
    bool isFinal;
};

string setToString(set<int> states)
{
    string result = "{";

    for (set<int>::iterator it = states.begin(); it != states.end(); ++it)
    {
        if (it != states.begin())
            result += ",";

        result += "q";
        result += char('0' + *it);
    }

    result += "}";

    return result;
}

void clearScreen()
{
    system("cls");
}

int main()
{
    /*
        NFA:

        States: q0, q1, q2
        Alphabet: 0, 1
        Start: q0
        Final: q2

        Transitions:

        q0 --0--> q0
        q0 --0--> q1
        q0 --1--> q2

        q1 --1--> q2

        q2 --0--> q2
        q2 --1--> q2
    */

    map<int, map<char, set<int> > > nfa;

    nfa[0]['0'].insert(0);
    nfa[0]['0'].insert(1);
    nfa[0]['1'].insert(2);

    nfa[1]['1'].insert(2);

    nfa[2]['0'].insert(2);
    nfa[2]['1'].insert(2);

    set<int> start;
    start.insert(0);

    queue< set<int> > pending;
    vector< set<int> > dfaStates;

    map< set<int>, int > stateNumber;

    pending.push(start);
    stateNumber[start] = 0;
    dfaStates.push_back(start);

    cout << "\n";
    cout << "==============================================================\n";
    cout << "              NFA TO DFA CONVERSION\n";
    cout << "                 SUBSET CONSTRUCTION\n";
    cout << "==============================================================\n\n";

    cout << "NFA STATES : q0, q1, q2\n";
    cout << "ALPHABET   : {0, 1}\n";
    cout << "START      : q0\n";
    cout << "FINAL      : q2\n\n";

    cout << "NFA TRANSITIONS\n";
    cout << "--------------------------------------------------------------\n";
    cout << "q0 --0--> {q0,q1}\n";
    cout << "q0 --1--> {q2}\n";
    cout << "q1 --0--> {}\n";
    cout << "q1 --1--> {q2}\n";
    cout << "q2 --0--> {q2}\n";
    cout << "q2 --1--> {q2}\n";
    cout << "--------------------------------------------------------------\n";

    cout << "\n\nPress ENTER to begin conversion...";
    cin.get();

    while (!pending.empty())
    {
        set<int> current = pending.front();
        pending.pop();

        int currentNumber = stateNumber[current];

        clearScreen();

        cout << "\n";
        cout << "==============================================================\n";
        cout << "              NFA TO DFA CONVERSION\n";
        cout << "==============================================================\n\n";

        cout << "Currently processing DFA state:\n\n";

        cout << "D" << currentNumber << " = "
             << setToString(current);

        bool currentFinal = false;

        if (current.find(2) != current.end())
            currentFinal = true;

        if (currentFinal)
            cout << "   <-- FINAL STATE";

        cout << "\n\n";

        cout << "Finding transitions...\n\n";

        for (int symbolIndex = 0; symbolIndex < 2; symbolIndex++)
        {
            char symbol = char('0' + symbolIndex);

            set<int> destination;

            for (set<int>::iterator it = current.begin();
                 it != current.end();
                 ++it)
            {
                int nfaState = *it;

                if (nfa[nfaState][symbol].size() > 0)
                {
                    destination.insert(
                        nfa[nfaState][symbol].begin(),
                        nfa[nfaState][symbol].end()
                    );
                }
            }

            cout << "D" << currentNumber
                 << " --" << symbol << "--> ";

            if (destination.empty())
            {
                cout << "{}\n";
            }
            else
            {
                cout << setToString(destination);

                if (stateNumber.find(destination) == stateNumber.end())
                {
                    int newNumber = dfaStates.size();

                    stateNumber[destination] = newNumber;
                    dfaStates.push_back(destination);

                    pending.push(destination);

                    cout << "   [NEW DFA STATE D"
                         << newNumber << "]";
                }

                cout << "\n";
            }
        }

        cout << "\nPress ENTER for next DFA state...";
        cin.get();
    }

    clearScreen();

    cout << "\n";
    cout << "==============================================================\n";
    cout << "                DFA CONVERSION COMPLETE\n";
    cout << "==============================================================\n\n";

    cout << "DFA STATES GENERATED:\n\n";

    for (int i = 0; i < dfaStates.size(); i++)
    {
        cout << "D" << i << " = "
             << setToString(dfaStates[i]);

        if (dfaStates[i].find(2) != dfaStates[i].end())
            cout << "   <-- FINAL";

        if (i == 0)
            cout << "   <-- START";

        cout << "\n";
    }

    cout << "\n\n";
    cout << "==============================================================\n";
    cout << "                  DFA TRANSITION TABLE\n";
    cout << "==============================================================\n\n";

    cout << "State       0              1\n";
    cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < dfaStates.size(); i++)
    {
        set<int> current = dfaStates[i];

        set<int> destination0;
        set<int> destination1;

        for (set<int>::iterator it = current.begin();
             it != current.end();
             ++it)
        {
            int nfaState = *it;

            destination0.insert(
                nfa[nfaState]['0'].begin(),
                nfa[nfaState]['0'].end()
            );

            destination1.insert(
                nfa[nfaState]['1'].begin(),
                nfa[nfaState]['1'].end()
            );
        }

        cout << "D" << i << "          ";

        if (destination0.empty())
            cout << "{}";
        else
            cout << "D" << stateNumber[destination0];

        cout << "             ";

        if (destination1.empty())
            cout << "{}";
        else
            cout << "D" << stateNumber[destination1];

        cout << "\n";
    }

    cout << "\n==============================================================\n";
    cout << "                    FINAL DFA\n";
    cout << "==============================================================\n\n";

    cout << "                 0\n";
    cout << "          +---------------+\n";
    cout << "          |               |\n";
    cout << "          v               |\n";
    cout << "       +-------+           |\n";
    cout << "       |       |           |\n";
    cout << " START |  D0   |-----------+\n";
    cout << "       | {q0}  |     1\n";
    cout << "       +-------+\n";
    cout << "           |\n";
    cout << "           | 0\n";
    cout << "           v\n";
    cout << "       +-------+\n";
    cout << "       |       |\n";
    cout << "       |  D1   |----1---->\n";
    cout << "       |{q0,q1}|\n";
    cout << "       +-------+\n";
    cout << "           |\n";
    cout << "           | 1\n";
    cout << "           v\n";
    cout << "       +=========+\n";
    cout << "       ||        ||\n";
    cout << "       ||   D2   ||\n";
    cout << "       ||  {q2}  ||\n";
    cout << "       || FINAL  ||\n";
    cout << "       +==========+\n";

    cout << "\n==============================================================\n";
    cout << "              NFA -> DFA SUCCESSFULLY COMPLETED\n";
    cout << "==============================================================\n";

    return 0;
}

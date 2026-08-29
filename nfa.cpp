#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen()
{
    system("cls");
}

void drawNFA()
{
    cout << "\n";
    cout << "==============================================================\n";
    cout << "                     NFA VISUALIZATION\n";
    cout << "==============================================================\n\n";

    cout << "                 0                    1\n";
    cout << "        +----------------+    +----------------+\n";
    cout << "        |                |    |                |\n";
    cout << "        v                |    v                |\n";
    cout << "   +---------+           |  +=========+        |\n";
    cout << "   |         |           |  ||        ||       |\n";
    cout << "   |   q0    |-----------+->||   q1   ||-------+\n";
    cout << "   |         |     0        ||        ||   0,1 |\n";
    cout << "   +---------+              +=========+        |\n";
    cout << "        |                         |             |\n";
    cout << "        |                         | 1           |\n";
    cout << "        | 1                       v             |\n";
    cout << "        |                   +=========+        |\n";
    cout << "        +------------------>|   q2    |<-------+\n";
    cout << "                            |  FINAL  |\n";
    cout << "                            +=========+\n";
    cout << "\n";

    cout << "                    ^\n";
    cout << "                    |\n";
    cout << "                  START\n";

    cout << "\n==============================================================\n";
    cout << "START STATE : q0\n";
    cout << "FINAL STATE : q2\n";
    cout << "TYPE        : NON-DETERMINISTIC FINITE AUTOMATON\n";
    cout << "==============================================================\n";

    cout << "\nTransitions:\n";
    cout << "q0 --0--> q0\n";
    cout << "q0 --0--> q1\n";
    cout << "q0 --1--> q2\n";
    cout << "q1 --1--> q2\n";
    cout << "q2 --0--> q2\n";
    cout << "q2 --1--> q2\n";

    cout << "\n==============================================================\n";
}

int main()
{
    string input;

    clearScreen();
    drawNFA();

    cout << "\nEnter a binary string: ";
    cin >> input;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] != '0' && input[i] != '1')
        {
            cout << "\nInvalid input!";
            cout << "\nOnly 0 and 1 are allowed.\n";
            return 0;
        }
    }

    cout << "\nNFA transition table:\n\n";

    cout << "State       0             1\n";
    cout << "--------------------------------\n";
    cout << "q0          {q0,q1}       {q2}\n";
    cout << "q1          {}             {q2}\n";
    cout << "q2          {q2}           {q2}\n";

    cout << "\n\nInput String : " << input;
    cout << "\n\nNFA can have MULTIPLE possible states after reading a symbol.";
    cout << "\nTherefore, unlike a DFA, one state can have multiple transitions";
    cout << "\nfor the same input symbol.";

    cout << "\n\n==============================================================\n";
    cout << "                   NFA VISUALIZATION END\n";
    cout << "==============================================================\n";

    return 0;
}

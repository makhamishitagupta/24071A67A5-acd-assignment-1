#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void clearScreen()
{
    system("cls");
}

void drawDFA()
{
    cout << "\n";
    cout << "==============================================================\n";
    cout << "                     DFA VISUALIZATION\n";
    cout << "==============================================================\n\n";

    cout << "                         1\n";
    cout << "                    +---------+\n";
    cout << "                    |         |\n";
    cout << "                    |         |\n";
    cout << "                    +---------+\n";
    cout << "                         ^\n";
    cout << "                         |\n";
    cout << "                         |\n";
    cout << "                         |\n";
    cout << "                    +---------+\n";
    cout << "                 0  |         |  1\n";
    cout << "              +---->|    q1   |------+\n";
    cout << "              |     |         |      |\n";
    cout << "              |     +---------+      |\n";
    cout << "              |          |           |\n";
    cout << "              |          | 1         |\n";
    cout << "              |          v           |\n";
    cout << "              |     +===========+    |\n";
    cout << "              +-----|    q2      |<--+\n";
    cout << "                    |   FINAL    |\n";
    cout << "                    +===========+\n";
    cout << "\n";

    cout << "                    +---------+\n";
    cout << "              START |    q0   |\n";
    cout << "                    +---------+\n";
    cout << "                         |\n";
    cout << "                         | 0\n";
    cout << "                         v\n";
    cout << "                        q1\n";

    cout << "\n==============================================================\n";
    cout << "START STATE : q0\n";
    cout << "FINAL STATE : q2\n";
    cout << "\nTransitions:\n";
    cout << "q0 --0--> q1\n";
    cout << "q0 --1--> q0\n";
    cout << "q1 --0--> q1\n";
    cout << "q1 --1--> q2\n";
    cout << "q2 --0--> q2\n";
    cout << "q2 --1--> q2\n";
    cout << "==============================================================\n";
}

string getNextState(string state, char input)
{
    if (state == "q0")
    {
        if (input == '0')
            return "q1";
        else
            return "q0";
    }

    if (state == "q1")
    {
        if (input == '0')
            return "q1";
        else
            return "q2";
    }

    if (state == "q2")
    {
        return "q2";
    }

    return "q0";
}

int main()
{
    string input;
    string state = "q0";

    clearScreen();

    drawDFA();

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

    cout << "\nStarting DFA execution...\n";
    cout << "Press ENTER to continue.";

    cin.ignore();
    cin.get();

    for (int i = 0; i < input.length(); i++)
    {
        string currentState = state;
        string nextState = getNextState(state, input[i]);

        clearScreen();

        drawDFA();

        cout << "\n\n==============================================================\n";
        cout << "                    DFA EXECUTION\n";
        cout << "==============================================================\n";

        cout << "\nInput string : " << input;
        cout << "\nReading      : " << input[i];
        cout << "\nCurrent state: " << currentState;
        cout << "\nTransition   : " << currentState
             << " --" << input[i] << "--> "
             << nextState;

        cout << "\n\nPress ENTER for next transition...";

        state = nextState;

        cin.get();
    }

    clearScreen();

    drawDFA();

    cout << "\n\n==============================================================\n";
    cout << "                       RESULT\n";
    cout << "==============================================================\n";

    cout << "\nInput String : " << input;
    cout << "\nFinal State  : " << state;

    if (state == "q2")
    {
        cout << "\n\nRESULT : ACCEPTED";
        cout << "\nThe DFA reached the final state q2.";
    }
    else
    {
        cout << "\n\nRESULT : REJECTED";
        cout << "\nThe DFA did not reach the final state q2.";
    }

    cout << "\n\n==============================================================\n";

    return 0;
}

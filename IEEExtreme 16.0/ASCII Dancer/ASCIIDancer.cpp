#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

vector<string> human;
bool is_turned;

void initialize_human() {
    human = {" o ", "/|\\", "/ \\"};
    is_turned = false;
}

void print_human() {
    for(string s : human) cout << s << endl;
}

bool is_say(string& word) {
    return word == "say";
}

pair<string, string> first_word(string& s) {
    string res;
    int i = 0;
    for(i = 0; i < s.size(); i++) {
        if(s[i] == ' ') break;
        else         res += s[i];
    }
    return make_pair(res, i == s.size() ? "" : s.substr(i+1));
}

void turn() {
    //turn first row
    if(human[0][0] == '(' && human[0][2] == ' ') {
        human[0][0] = ' ';
        human[0][2] = ')';
    } else if(human[0][0] == ' ' && human[0][2] == ')') {
        human[0][0] = '(';
        human[0][2] = ' ';
    }

    //turn second row
    if (human[1][0] == '<' && human[1][2] == '\\') {
        human[1][0] = '/';
        human[1][2] = '>';
    }
    else if (human[1][0] == '/' && human[1][2] == '>') {
        human[1][0] = '<';
        human[1][2] = '\\';
    }
    else if (human[1][0] == ' ' && human[1][2] == '\\') {
        human[1][0] = '/';
        human[1][2] = ' ';
    }
    else if (human[1][0] == ' ' && human[1][2] == '>') {
        human[1][0] = '<';
        human[1][2] = ' ';
    }
    else if (human[1][0] == '/' && human[1][2] == ' ') {
        human[1][0] = ' ';
        human[1][2] = '\\';
    }
    else if (human[1][0] == '<' && human[1][2] == ' ') {
        human[1][0] = ' ';
        human[1][2] = '>';
    }

    //turn third row
    if(human[2][0] == '<' && human[2][2] == '\\') {
        human[2][0] = '/';
        human[2][2] = '>';
    }
    else if(human[2][0] == '/' && human[2][2] == '>') {
        human[2][0] = '<';
        human[2][2] = '\\';
    }
}

void execute_command(string& command) {
    if(command == "left hand to head") {
        if(is_turned) {
            human[0][0] = '(';
            human[1][0] = ' ';
        } else {
            human[0][2] = ')';
            human[1][2] = ' ';
        }
    } else if(command == "left hand to hip") {
        if(is_turned) {
            human[0][0] = ' ';
            human[1][0] = '<';
        } else {
            human[0][2] = ' ';
            human[1][2] = '>';
        }
    } else if(command == "left hand to start") {
        if(is_turned) {
            human[0][0] = ' ';
            human[1][0] = '/';
        } else {
            human[0][2] = ' ';
            human[1][2] = '\\';
        }
    } else if(command == "left leg in") {
        if(is_turned) {
            human[2][0] = '<';
        } else {
            human[2][2] = '>';
        }
    } else if(command == "left leg out") {
        if(is_turned) {
            human[2][0] = '/';
        } else {
            human[2][2] = '\\';
        }
    } else if(command == "right hand to head") {
        if(is_turned) {
            human[0][2] = ')';
            human[1][2] = ' ';
        } else {
            human[0][0] = '(';
            human[1][0] = ' ';
        }
    } else if(command == "right hand to hip") {
        if(is_turned) {
            human[0][2] = ' ';
            human[1][2] = '>';
        } else {
            human[0][0] = ' ';
            human[1][0] = '<';
        }
    } else if(command == "right hand to start") {
        if(is_turned) {
            human[0][2] = ' ';
            human[1][2] = '\\';
        } else {
            human[0][0] = ' ';
            human[1][0] = '/';
        }
    } else if(command == "right leg in") {
        if(is_turned) {
            human[2][2] = '>';
        } else {
            human[2][0] = '<';
        }
    } else if(command == "right leg out") {
        if(is_turned) {
            human[2][2] = '\\';
        } else {
            human[2][0] = '/';
        }
    } else if(command == "turn") {
        turn();
        is_turned = !is_turned;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t, d;
    cin >> t;
    while(t--) {
        cin >> d;
        string command;
        getline(cin, command); //gets rid of new line reamining in cin.
        initialize_human();
        while(d--) {
            getline(cin, command);
            pair<string, string> s = first_word(command);
            if(is_say(s.first)) cout << s.second << endl;
            else {
                execute_command(command);
                print_human();
            }
        }
    }

    return 0;
}
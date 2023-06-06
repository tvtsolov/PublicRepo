#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

void copy(const string & text, stack<string> & clipboard, const pair<int, int> & positions) {
    //define words:
    vector<pair <int, int>> positionsV;
    vector<string> wordsV;


    int startPos = 0;
    int endPos;
    istringstream ss(text);
    string word;
    while (ss >> word){

        endPos = startPos + word.size()-1;
        pair <int, int> key = make_pair(startPos, endPos);
        positionsV.push_back(key);
        wordsV.push_back(word);
        startPos = endPos+2;
    }

    string x = "";

    for (int i = 0; i < positionsV.size(); i ++) { 
        if ( (positionsV[i].first >= positions.first && positionsV[i].first <= positions.second) 
        || (positionsV[i].second >= positions.first && positionsV[i].second <= positions.second) 
        || (positionsV[i].first <= positions.first && positionsV[i].second >= positions.second) 
         ){
            x += wordsV[i] + " ";
        }
    }
        x.pop_back();
        clipboard.push(x);
}

void paste(string & text, stack<string> & clipboard, const int & position){

        string pasteStr = " ";
        if ((text[position])== ' ') {
            pasteStr.insert(1, clipboard.top());
            text.insert(position, pasteStr);
        }
        else {
        text.insert(position, clipboard.top());
        }
        clipboard.pop();
}

int main() {

    string initialText;
    getline(cin, initialText);
    if (initialText == "end"){
        return 0;
    }
    
    stack<string> clipboard;
    int position;
    pair<int, int> positions;


    while (true) {
        string command; 
        string input;
        int start, end;
        getline(cin, input);
        istringstream ssk(input);
        ssk >> command;
        if (command[0] == 'c'){
            ssk >> positions.first >> positions.second;
            copy(initialText, clipboard, positions);
        }
        else if (command[0] == 'p'){
            ssk >> position;
            if (!clipboard.empty()) {
                paste(initialText, clipboard, position);
            }
        }
        else {
            break;
        }
    }

    cout << initialText;
    return 0;
}

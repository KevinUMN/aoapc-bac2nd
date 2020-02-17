#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// global variables

int numOfProg;
vector<int> pc; // program counter, pc[pid], track each program's current line number
vector<string> prog;
deque<int> readyQ;
queue<int> blockQ;
int numOfStatement = 5; // there are 5 types of statements;
vector<int> quantumVec(5, 0); // quantum for each type of operation
map<string, int> varMap; // variable map <name, value>
int qt; // quantum;
bool locked;

// run a progam
// pid: program id
void run(int pid) {

  int currQt = qt;
  while(currQt > 0) {

    // get the statement
    string op = prog[pc[pid]];

    if (op.find("=") != std::string::npos) { // assignment

      string varName = op.substr(0, 1);
      string varValue = op.substr(op.find("=")+1);
      int value = stoi(varValue);
      varMap[varName] = value; 
      currQt -= quantumVec[0];

    } else if (op.find("print") != std::string::npos) {

      string varName = op.substr(6,6);
      if (!varMap.count(varName)) {
        varMap[varName] = 0; 
      } 
      cout << pid+1; 
      cout << ": ";
      cout << varMap[varName] << endl;
      currQt -= quantumVec[1];

    } else if (op.find("lock") != std::string::npos && op[0]=='l') {

      if (locked) {
        blockQ.push(pid);
        return;
      } else {
        locked = true;
        currQt -= quantumVec[2];
      }

    } else if (op.find("unlock") != std::string::npos) {

      locked = false;
      if (!blockQ.empty()) {
        int blockedPid = blockQ.front();
        blockQ.pop();
        readyQ.push_front(blockedPid);
      }
      currQt -= quantumVec[3];

    } else { // end
      return;
    } 
    pc[pid]++;
  }
  readyQ.push_back(pid);
} // end of run(); 

int main() {

#ifdef LOCAL
  freopen("sample_input", "r", stdin);
#endif

  int kase;
  cin >> kase;
  while (kase--) {

    cin >> numOfProg;
    for (int i = 0; i < numOfStatement; ++i) {
      int x;
      cin >> x;
      quantumVec[i] = x;
    }
    cin >> qt;

    // read statements of each program
    string opStr;
    int line = 0;
    pc.clear();
    prog.clear();
    for (int j = 0; j < numOfProg; j++) {
      getline(cin, opStr);
      while (opStr == "") {
        getline(cin, opStr);
      }
      pc.push_back(line);
      while(opStr != "end") {
        prog.push_back(opStr);
        line++;
        getline(cin, opStr);
      }
      prog.push_back(opStr);
      line++;
      readyQ.push_back(j); 
    }

    locked = false;
    varMap.clear();
    while (!readyQ.empty()) {
      int pid = readyQ.front(); 
      readyQ.pop_front();
      run(pid);
    }

    if (kase) {
      cout << endl;
    }
  }
  return 0;  
}

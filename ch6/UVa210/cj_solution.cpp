#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {

#ifdef LOCAL
  freopen("data.in", "r", stdin);
#endif

  int kase;
  cin >> kase;
  for (int i = 0; i < kase; ++i) {

    // read num of programs
    int numOfPrograms;
    cin >> numOfPrograms;
    queue<int> readyQueue;
    queue<int> blockQueue;
    for (int j = 0; j < numOfPrograms; ++j) {
      readyQueue.push(j+1);
    }

    // read operation qt
    vector<int> operationQtVec;
    for (int j = 0; j < 5; ++j) {
      int x;
      cin >> x;
      operationQtVec.push_back(x);
    }

    // read qt
    int qt;
    cin >> qt;
   
    // read statements of each program
    map<int, queue<string>> programMap;
    string opStr;
    int n = 1;
    while (getline(cin,opStr) && n<numOfPrograms+1) {
      if (opStr != "") {
        programMap[n].push(opStr);
      }
      if (opStr == "end") {
        n++;
      }
    }

    // lock
    bool lock = false;

    // start execution
    map<string, int> varMap; // variable map <name, value>
    while (!readyQueue.empty()) {
      
      int programID = readyQueue.front();
      int currQt = qt;

      while(currQt > 0) {

        string op = programMap[programID].front();

        if (op.find("=") != std::string::npos) {

          string varName = op.substr(0, 1);
          string varValue = op.substr(op.find("=")+1);
          int value = stoi(varValue);
          varMap[varName] = value; 
          currQt -= operationQtVec[0];
          programMap[programID].pop();

        } else if (op.find("print") != std::string::npos) {

          string varName = op.substr(6,6);
          if (varMap.count(varName)) {
            cout << programID; 
            cout << ": ";
            cout << varMap[varName] << endl;
          }
          currQt -= operationQtVec[1];
          programMap[programID].pop();

        } else if (op.find("lock") != std::string::npos && op[0]=='l') {

          if (lock) {
            currQt = 0;
          } else {
            lock = true;
            currQt -= operationQtVec[2];
            programMap[programID].pop();
          }

        } else if (op.find("unlock") != std::string::npos) {

          lock = false;
          queue<int> temp = readyQueue;
          // clear readyQueue
          while(!readyQueue.empty()) {
            readyQueue.pop();
          }
          readyQueue.push(programID);
          for (unsigned int k = 0; k < blockQueue.size(); ++k) {
            readyQueue.push(blockQueue.front());
            blockQueue.pop();
          }
          temp.pop();
          for (unsigned int k = 0; k < temp.size(); ++k) {
            readyQueue.push(temp.front());
            temp.pop();
          }
          // clear blockqueue
          while(!blockQueue.empty()) {
            blockQueue.pop();
          }
          currQt -= operationQtVec[3];
          programMap[programID].pop();

        } else {

          currQt = 0;
          programMap[programID].pop();

        } 
        if (currQt <= 0) {
          readyQueue.pop();
          if (! (op.find("end") != std::string::npos)) {
            readyQueue.push(programID);
          }
        }
      }
    }

    cout << endl;
  }
  return 0;  
}

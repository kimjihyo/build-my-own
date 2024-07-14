#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;
namespace fs = filesystem;

const int numThreads = 8;
vector<thread> workerThreads;

struct task {
  char *fname;
};

struct taskList {
  struct task task;
  struct taskList *next;
};

taskList *plHead = nullptr, *plTail = nullptr, *plCur = nullptr;
mutex mtx;

void grep(string &fileName, string &keyword) {
  ifstream inputFile(fileName);

  if (!inputFile.is_open()) {
    cerr << "Error opening the file!\n";
    return;
  }

  string line;
  int lineNumber = 1;

  while (getline(inputFile, line)) {
    size_t found = line.find(keyword);
    if (found != string::npos) {
      cout << fileName << ':' << lineNumber << '\n';
    }
    lineNumber++;
  }

  inputFile.close();
}

void initThreadPool() {
  workerThreads.reserve(numThreads);
  for (int i = 0; i < numThreads; i++) {
    workerThreads.emplace_back(
        []() { cout << "Hello world! from another thread..\n"; });
  }
}

void joinThreadPool() {
  for (int i = 0; i < numThreads; i++) {
    workerThreads[i].join();
  }
}

void addFileToList(const char *fpath) {
  taskList *plTmp = nullptr;
  if (fs::is_directory(fpath))
    return;
  plTmp = new taskList;
  plTmp->task.fname = strdup(fpath);
  plTmp->next = nullptr;
  if (plHead == nullptr) {
    plHead = plTmp;
    plTail = plTmp;
  } else {
    plTail->next = plTmp;
    plTail = plTail->next;
  }
}

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    cerr << "Error invalid arguments\n";
    return 1;
  }

  const char *fpath = argv[1];
  const char *keyword = argv[2];

  if (fs::is_directory(fpath)) {
    for (fs::recursive_directory_iterator i(fpath), end; i != end; i++) {
      if (!fs::is_directory(i->path())) {
        addFileToList(i->path().c_str());
      }
    }
  } else {
    addFileToList(fpath);
  }

  plCur = plHead;
  initThreadPool();
  joinThreadPool();
  return 0;
}
#pragma once

#include <string>
#include <iostream>

using namespace std;

#include <string>
#include <vector>
#include "Operation.h"

using namespace std;

class Machine{
 public:

   static Machine& getInstance();
   Machine(const Machine& user) = delete;
   Machine& operator=(const Machine&) = delete;

   void init(string file);
   void scheduale();
   void exec(string file);

   void upadeState(string name, string value);

 private:
   Machine() = default;
   vector<Operation*> waiting_, executing_;
};
#include "terminal.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc!=2) {
        cerr<<"Usage: "<<argv[0]<<" \"expression\"\n";
        return 1;
    }
    load_rules("rules.txt");
    Expr* root = parse_expr(argv[1]);
    bool no_term = false;
    #ifdef TERMINAL_OFF
      no_term = true;
    #endif
    auto t0 = high_resolution_clock::now();
    double result = compute(root, no_term);
    auto t1 = high_resolution_clock::now();
    double ms = duration<double, milli>(t1-t0).count();
    cout<<result<<" "<<ms<<"\n";
    return 0;
}
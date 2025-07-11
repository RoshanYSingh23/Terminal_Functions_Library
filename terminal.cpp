#include "terminal.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
using namespace std;

// Rule storage
unordered_map<Func, unordered_set<Func>> commute;
unordered_set<Func> idempotent;
map<pair<Func,Func>, string> imply;

// Precompute commutation closure via Floyd–Warshall on small function set
static void close_commute() {
    vector<Func> funcs;
    for (auto &p : commute) funcs.push_back(p.first);
    for (auto &f : funcs) commute[f].insert(f);
    for (auto &k : funcs)
      for (auto &i : funcs)
        if (commute[i].count(k))
          for (auto &j : funcs)
            if (commute[k].count(j))
              commute[i].insert(j);
}

void load_rules(const string &filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        if (line.empty() || line[0]=='#') continue;
        auto eq = line.find('=');
        string lhs = line.substr(0, eq);
        string rhs = line.substr(eq+1);
        // trim
        auto trim=[&](string &s){
          s.erase(0, s.find_first_not_of(" \t"));
          s.erase(s.find_last_not_of(" \t")+1);
        };
        trim(lhs); trim(rhs);
        // parse lhs: A(B(x)) or A(A(x)) etc
        auto p1 = lhs.find('(');
        auto fn = lhs.substr(0,p1);
        auto inner = lhs.substr(p1+1, lhs.size()-p1-2);
        auto p2 = inner.find('(');
        string child_fn = p2==string::npos ? "" : inner.substr(0,p2);
        if (child_fn.empty()) {
            // idempotent? pattern A(x)
            idempotent.insert(fn);
        } else if (rhs == lhs) {
            // treat as commute if rhs same shape
        } else if (rhs.find("(x)")!=string::npos && child_fn.size()>0) {
            // check commute vs imply
            if (rhs == child_fn + "(" + fn + "(x))") {
                commute[fn].insert(child_fn);
                commute[child_fn].insert(fn);
            } else {
                imply[{fn, child_fn}] = rhs;
            }
        }
    }
    close_commute();
}

// Very basic parser: literal or fn(inner)
Expr* parse_expr(const string &s) {
    if (isdigit(s[0]) || s[0]=='-'||s[0]=='+') {
        return new Expr(stod(s));
    }
    auto p = s.find('(');
    string fn = s.substr(0,p);
    string inside = s.substr(p+1, s.size()-p-2);
    Expr* child = parse_expr(inside);
    return new Expr(fn, child);
}

// Bottom-up simplification and evaluation
Expr* simplify_node(Expr* e) {
    if (!e->child) return e;
    // simplify child first
    Expr* c = simplify_node(e->child);
    // gather chain of wrappers if commute
    vector<Func> wrap;
    wrap.push_back(e->fn);
    Expr* cur = c;
    while (cur && commute[e->fn].count(cur->fn)) {
        wrap.push_back(cur->fn);
        cur = cur->child;
    }
    // collapse idempotents
    unordered_set<Func> seen;
    vector<Func> canon;
    for (auto &f : wrap) {
      if (idempotent.count(f)) {
        if (seen.insert(f).second) canon.push_back(f);
      } else canon.push_back(f);
    }
    // sort commutable wrappers
    sort(canon.begin(), canon.end());
    // reconstruct chain
    Expr* node = cur;
    for (auto it = canon.rbegin(); it!=canon.rend(); ++it)
        node = new Expr(*it, node);
    return node;
}

double simplify_and_eval(Expr* root) {
    Expr* simp = simplify_node(root);
    return eval(simp);
}

// direct eval
double eval(const Expr* e) {
    if (!e->child) return e->literal;
    double v = eval(e->child);
    const auto &fn = e->fn;
    if (fn=="sin")    return sin(v);
    if (fn=="arcsin") return asin(v);
    if (fn=="tan")    return tan(v);
    if (fn=="abs")    return abs(v);
    if (fn=="f")      return v+1;   // example function, obviously the rules may not hold for these, but we wish to chck if terminal is working
    if (fn=="g")      return v;
    if (fn=="h")      return v*v;
    return v;
}
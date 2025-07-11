#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// AST node for unary functions or literals
typedef string Func;

struct Expr {
    Func fn;               // empty = literal
    double literal = 0.0;  // if fn.empty()
    Expr* child = nullptr;
    Expr() = default;
    Expr(double v): fn(), literal(v), child(nullptr) {}
    Expr(const Func &f, Expr* c): fn(f), literal(0), child(c) {}
};

// Load rewrite rules
enum RuleType { COMMUTE, IDEMPOTENT, IMPLY };
void load_rules(const string &filename);

// Parse string to AST (handles unary only, very simple parser)
Expr* parse_expr(const string &s);

// Simplify & evaluate in one bottom-up pass (polynomial time)
double simplify_and_eval(Expr* root);

double eval(const Expr* root); // direct eval

// Wrapper: compute with optional terminal
inline double compute(Expr* root, bool no_terminal=false) {
    return no_terminal ? eval(root) : simplify_and_eval(root);
}

#endif // TERMINAL_H
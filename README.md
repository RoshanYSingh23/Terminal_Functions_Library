# Terminal Functions Library

A fast expression simplifier and evaluator for unary mathematical functions using custom rewrite rules and commutation logic. The system supports symbolic simplification and direct evaluation modes, making it suitable for terminal-based mathematical engines, calculators, or symbolic algebra systems.

---

## 📁 Repository Structure

| File           | Purpose                                                                 |
|----------------|-------------------------------------------------------------------------|
| `terminal.h`   | Header file defining AST structures, enums, and function declarations   |
| `terminal.cpp` | Core logic: parser, simplifier, evaluator, and rule loader              |
| `main.cpp`     | Sample driver file to run and compare ON/OFF (with/without terminal)    |
| `rules.txt`    | Rewrite rules for simplification                                        |
| `Makefile`     | Build configuration to compile the project                              |
| `examples.sh`  | Shell script with usage examples and test cases                         |
| `script.py`    | (Optional) Python script to run tests and generate formatted output     |
| `output.txt`   | Output results after running the executable                             |
| `Report.pdf`   | Project report describing the design, implementation, and results       |
| `README.md`    | This README file                                                        |
| `.gitignore`   | Prevents accidental commits of binaries or logs                         |

---

## 🔄 Rules File Format (`rules.txt`)

Each line specifies a rewrite rule or logic transformation. The system supports:

### ✨ Basic Rewrite


---

## 🔄 Rules File Format (`rules.txt`)
Each line is a rewrite rule of one of the following forms:

- **Basic rewrite:**
```

arcsin(sin(x)) = x
abs(abs(x)) = abs(x)

```
- **Commutation:**
```

f(g(x)) = g(f(x))

```
- **Implication:**
```

h(f(x)) = x\*x

```
- **Identity:**
```

g(x) = x

````

---

## ⚙️ Build Instructions
Clone and build using:
```bash
git clone git@github.com:RoshanYSingh23/Terminal_Functions_Library.git
cd Terminal_Functions_Library
```

Then, build everything using make:
```bash
make all
```

Run with:
```bash
make run
```

This will execute the main binary on test expressions and save the results in:
```lua
output.txt
```

---

## 👤 Author

**Roshan Y Singh**

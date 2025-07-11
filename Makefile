CXX = g++
CXXFLAGS = -std=c++17 -O2

all: eval_bin eval_bin_nt

eval_bin: terminal.cpp main.cpp
	$(CXX) $(CXXFLAGS) -DTERMINAL_ON -o $@ terminal.cpp main.cpp

eval_bin_nt: terminal.cpp main.cpp
	$(CXX) $(CXXFLAGS) -DTERMINAL_OFF -o $@ terminal.cpp main.cpp

run: all
	bash examples.sh
	python3 script.py

clean:
	rm -f eval_bin eval_bin_nt raw_results.txt output.txt

.PHONY: all run clean

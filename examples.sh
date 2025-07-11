#!/usr/bin/env bash

# Simple test cases
declare -a examples=(
  "tan(arcsin(sin(1.234^2)))"
  "abs(abs(abs(-5)))"
  "g(h(f(3)))"
)

# Deep nesting tests
n1=200
expr1="1.234"
for ((i=0; i<n1; i++)); do
  expr1="sin($expr1)"
  expr1="arcsin($expr1)"
done
expr1="tan($expr1)"
examples+=("$expr1")

n2=300
expr2="5"
for ((i=0; i<n2; i++)); do
  expr2="abs($expr2)"
done
examples+=("$expr2")

# Run tests and capture raw output
for expr in "${examples[@]}"; do
  echo "$expr"
  ./eval_bin "$expr"
  ./eval_bin_nt "$expr"
  echo
done > raw_results.txt

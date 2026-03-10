#!/bin/bash
# Teste do status

echo "Test 1: false"
false
echo "Status after false: $?"

echo ""
echo "Test 2: true"
true
echo "Status after true: $?"

echo ""
echo "Test 3: ls /nonexistent"
ls /nonexistent 2>/dev/null
echo "Status after failed ls: $?"

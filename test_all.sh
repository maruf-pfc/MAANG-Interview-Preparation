#!/bin/bash
PASS=0
FAIL=0

echo "Running tests across all MAANG Prep C++ files..."
echo ""

for file in $(find . -name "*.cpp" | sort); do
    DIR=$(dirname "$file")
    FILE=$(basename "$file")
    BIN="${FILE%.cpp}"
    
    cd "$DIR"
    
    # Compile
    g++ -std=c++17 "$FILE" -o "$BIN" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "[FAIL] $DIR/$FILE failed to compile!"
        FAIL=$((FAIL+1))
        cd - >/dev/null
        continue
    fi
    
    # Run
    OUTPUT=$(./"$BIN" 2>&1)
    if [ $? -ne 0 ] || echo "$OUTPUT" | grep -q "Assertion failed\|Segmentation fault\|Aborted"; then
        echo "[FAIL] $DIR/$FILE crashed or failed assertions: $OUTPUT"
        FAIL=$((FAIL+1))
    else
        # We assume if it compiles and runs without aborting, it passes its own main() tests
        echo "[PASS] $DIR/$FILE"
        PASS=$((PASS+1))
    fi
    
    # Cleanup
    rm -f "$BIN"
    cd - >/dev/null
done

echo ""
echo "Total Passed: $PASS"
echo "Total Failed: $FAIL"

if [ $FAIL -gt 0 ]; then
    exit 1
fi
exit 0

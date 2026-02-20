#!/bin/bash
PASS=0
FAIL=0

echo "Verifying all MAANG Prep C# files individually..."
echo ""

# Store the original directory
ORIG_DIR=$(pwd)

# Create a temporary dotnet project
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"
dotnet new classlib -n DummyProj >/dev/null 2>&1
cd DummyProj
rm -f Class1.cs

for file in $(find "$ORIG_DIR" -name "*.cs" | sort); do
    # Remove any previously copied .cs files in the dummy proj
    rm -f *.cs
    
    # Copy the current file
    cp "$file" .
    
    # Build it
    dotnet build > build.log 2>&1
    
    # Check status
    if [ $? -ne 0 ]; then
        echo "[FAIL] $(basename "$file") failed to compile!"
        cat build.log | grep -E "error CS"
        FAIL=$((FAIL+1))
    else
        echo "[PASS] $(basename "$file") compiled successfully."
        PASS=$((PASS+1))
    fi
done

# Cleanup
cd "$ORIG_DIR"
rm -rf "$TEMP_DIR"

echo ""
echo "Total Passed: $PASS"
echo "Total Failed: $FAIL"

if [ $FAIL -gt 0 ]; then
    exit 1
fi
exit 0

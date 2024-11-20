#!/usr/bin/bash

# remove --show-leak-kinds=all (and --track-origins=yes) if there are many leaks in external libs
cat "${INPUT_FILENAME}" | tr -d '\r' | valgrind --leak-check=full --track-origins=yes --error-exitcode=0 ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &> valgrind_output.txt

# Check for memory leaks in the Valgrind output
if grep -q "definitely lost: 0 bytes" valgrind_output.txt && grep -q "indirectly lost: 0 bytes" valgrind_output.txt; then
    echo "No memory leaks detected 🎉"
else
    echo "Memory leaks detected! 🚨 Ai facut-o de oaie Check the Valgrind output below:"
    cat valgrind_output.txt
fi

# Run the test script after Valgrind checks
bash ./scripts/run_test.sh 10 1 2

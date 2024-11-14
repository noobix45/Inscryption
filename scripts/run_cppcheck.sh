#!/usr/bin/bash

report_file="cppcheck_report.txt"
output_file="cppcheck_output.txt"

cppcheck --enable=all \
    --inline-suppr \
    --check-level=exhaustive \
    --project="${BUILD_DIR:-build}"/compile_commands.json \
    -i"${BUILD_DIR:-build}" --suppress="*:${BUILD_DIR:-build}/*" \
    -i"${EXT_DIR:-ext}" --suppress="*:${EXT_DIR:-ext}/*" \
    -i"${GEN_DIR:-generated}" --suppress="*:${GEN_DIR:-generated}/*" \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=useStlAlgorithm \
    --checkers-report="$report_file" \
    --error-exitcode=1 > "$output_file" 2>&1

echo "Cppcheck checker report saved to $report_file"
echo "Cppcheck output saved to $output_file"
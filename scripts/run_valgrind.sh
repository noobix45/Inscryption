valgrind --leak-check=full --track-origins=yes --error-exitcode=0 ./"${ZIP_NAME}"/"${EXECUTABLE_NAME}" &> valgrind_output.txt
bash ./scripts/run_test.sh 10 1 2
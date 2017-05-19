
# - - - - - - - - - - - - - - - - - - - - - - - - -
echo
make unit
if [ $? -ne 0 ]; then
    echo "FAILED to build unit tests"
    exit 1
fi
./unit
if [ $? -ne 0 ]; then
    exit 1
fi

# - - - - - - - - - - - - - - - - - - - - - - - - -
echo
make contract
if [ $? -ne 0 ]; then
    echo "FAILED to build contract tests"
    exit 1
fi
./contract
if [ $? -ne 0 ]; then
    exit 1
fi

# - - - - - - - - - - - - - - - - - - - - - - - - -
echo
make shouty_report_job
if [ $? -ne 0 ]; then
    exit 1
fi

# - - - - - - - - - - - - - - - - - - - - - - - - -
echo
make e2e
if [ $? -ne 0 ]; then
    exit 1
fi
./e2e
if [ $? -ne 0 ]; then
    exit 1
fi

# - - - - - - - - - - - - - - - - - - - - - - - - -
# green light pattern
echo
echo "All tests passed"

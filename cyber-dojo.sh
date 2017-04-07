
g++ -std=c++14 -Wall -Wextra -Werror -o unit \
  unit.tests.cpp mileage_claim.cpp tinyxml2.cpp \
  shouty_report_processor.cpp \
  zzz_DONT_READ_ME.cpp
if [ $? -ne 0 ]; then
    echo "FAILED to build unit tests"
    exit 1
fi
./unit
if [ $? -ne 0 ]; then
    exit 1
fi

g++ -std=c++14 -Wall -Wextra -Werror -o contract \
    contract.tests.cpp \
    mileage_claim.cpp \
    tinyxml2.cpp \
    zzz_DONT_READ_ME.cpp
if [ $? -ne 0 ]; then
    echo "FAILED to build contract tests"
    exit 1
fi
./contract
if [ $? -ne 0 ]; then
    exit 1
fi

g++ -std=c++14 -Wall -Wextra -Werror -o shouty_report_job \
    shouty_report_job.cpp \
    mileage_claim.cpp \
    shouty_report_processor.cpp \
    tinyxml2.cpp \
    zzz_DONT_READ_ME.cpp
if [ $? -ne 0 ]; then
    exit 1
fi

rm -f ./shouty_report_job.output

g++ -std=c++14 -Wall -Wextra -Werror -o e2e end_to_end.tests.cpp
if [ $? -ne 0 ]; then
    exit 1
fi


./e2e
if [ $? -ne 0 ]; then
    exit 1
fi

# green light pattern
echo "All tests passed"


rm -f ./e2e
rm -f ./shouty_report_job
rm -f ./unit
rm -f ./contract


#make --always-make

CXXFLAGS += -I./src -I./service -std=c++14 -Wall -Wextra -Werror

SRC_PATH = src
SERVICE_PATH = service
TEST_PATH = test
TINYXML2_PATH = src

#- - - - - - - - - - - - - - - - - - - - - -

TINYXML2_DEPENDENTS = \
	${TINYXML2_PATH}/tinyxml2.cpp \
	${TINYXML2_PATH}/tinyxml2.hpp

tinyxml2.o: $(TINYXML2_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

MILEAGE_CLAIM_DEPENDENTS =\
	${SRC_PATH}/mileage_claim.cpp \
	${SRC_PATH}/mileage_claim.hpp

mileage_claim.o: $(MILEAGE_CLAIM_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

MILEAGE_CLAIM_COLLECTION_BUILDER_DEPENDENTS =\
	${TEST_PATH}/mileage_claim_collection_builder.cpp \
	${TEST_PATH}/mileage_claim_collection_builder.hpp \
	${SRC_PATH}/mileage_claim.hpp

mileage_claim_collection_builder.o: $(MILEAGE_CLAIM_COLLECTION_BUILDER_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

ECO_STAT_DEPENDENTS = \
	${SRC_PATH}/eco_stat.cpp \
	${SRC_PATH}/eco_stat.hpp

eco_stat.o: $(ECO_STAT_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

ECO_STAT_COLLECTION_BUILDER_DEPENDENTS = \
	${TEST_PATH}/eco_stat_collection_builder.cpp \
	${TEST_PATH}/eco_stat_collection_builder.hpp \
	${SRC_PATH}/eco_stat.hpp

eco_stat_collection_builder.o: $(ECO_STAT_COLLECTION_BUILDER_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_STATS_SERVICE_EXCEPTION_DEPENDENTS = \
	${SERVICE_PATH}/shouty_stats_service_exception.cpp \
	${SERVICE_PATH}/shouty_stats_service_exception.hpp

shouty_stats_service_exception.o: $(SHOUTY_STATS_SERVICE_EXCEPTION_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

FAKE_STATS_SERVICE_DEPENDENTS = \
	${TEST_PATH}/fake_stats_service.cpp \
	${TEST_PATH}/fake_stats_service.hpp \
	${SRC_PATH}/stats_service.hpp \
	${SERVICE_PATH}/shouty_stats_service_exception.hpp

fake_stats_service.o: $(FAKE_STATS_SERVICE_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

FAKE_STATS_SERVICE_BUILDER_DEPENDENTS = \
	${TEST_PATH}/fake_stats_service_builder.cpp \
	${TEST_PATH}/fake_stats_service_builder.hpp

fake_stats_service_builder.o: $(FAKE_STATS_SERVICE_BUILDER_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

PRODUCTION_STATS_SERVICE_DEPENDENTS = \
	${SRC_PATH}/production_stats_service.cpp \
	${SRC_PATH}/production_stats_service.hpp \
	${SRC_PATH}/stats_service.hpp \
	${SERVICE_PATH}/shouty_stats_service.hpp

production_stats_service.o: $(PRODUCTION_STATS_SERVICE_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_REPORT_PROCESSOR_DEPENDENTS = \
	${SRC_PATH}/shouty_report_processor.cpp \
	${SRC_PATH}/shouty_report_processor.hpp \
	${SRC_PATH}/eco_stat.hpp \
	${SRC_PATH}/mileage_claim.hpp \
	${SRC_PATH}/stats_service.hpp

shouty_report_processor.o: $(SHOUTY_REPORT_PROCESSOR_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_STATS_SERVICE_DEPENDENTS = \
	${SERVICE_PATH}/zzz_DONT_READ_ME.cpp \
	${SERVICE_PATH}/shouty_stats_service.hpp \
	${SERVICE_PATH}/shouty_stats_service_exception.hpp

shouty_stats_service.o: $(SHOUTY_STATS_SERVICE_DEPENDENTS)
	g++ ${CXXFLAGS} -o $@ -c $<

#- - - - - - - - - - - - - - - - - - - - - -

UNIT_TEST_DEPENDENTS = \
	${TEST_PATH}/unit.tests.cpp \
	eco_stat.o \
	eco_stat_collection_builder.o \
	fake_stats_service_builder.o \
	fake_stats_service.o \
	mileage_claim.o \
	mileage_claim_collection_builder.o \
	production_stats_service.o \
	shouty_report_processor.o \
	shouty_stats_service_exception.o \
	shouty_stats_service.o \
	tinyxml2.o

unit: $(UNIT_TEST_DEPENDENTS)
	g++ ${CXXFLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

CONTRACT_TEST_DEPENDENTS = \
	${TEST_PATH}/stats_service.contract.tests.cpp \
	fake_stats_service_builder.o \
	fake_stats_service.o \
	mileage_claim.o \
	production_stats_service.o \
	shouty_stats_service.o \
	shouty_stats_service_exception.o \
	tinyxml2.o

contract: $(CONTRACT_TEST_DEPENDENTS)
	g++ ${CXXFLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_REPORT_JOB_DEPENDENTS = \
	${SRC_PATH}/shouty_report_job.cpp \
	eco_stat.o \
	eco_stat_collection_builder.o \
	fake_stats_service.o \
	mileage_claim.o \
	production_stats_service.o \
	shouty_report_processor.o \
	shouty_stats_service.o \
	shouty_stats_service_exception.o \
	tinyxml2.o

shouty_report_job: $(SHOUTY_REPORT_JOB_DEPENDENTS)
	g++ ${CXXFLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

END_TO_END_TEST_DEPENDENTS = \
	${TEST_PATH}/end_to_end.tests.cpp \
	tinyxml2.o

e2e: $(END_TO_END_TEST_DEPENDENTS)
	g++ ${CXXFLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

clean:
	rm *.o

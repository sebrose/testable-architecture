CXXFLAGS += -I. -std=c++14 -Wall -Wextra -Werror

#- - - - - - - - - - - - - - - - - - - - - -

TINYXML2_DEPENDENTS = \
	/usr/local/src/tinyxml2.cpp \
	/usr/local/include/tinyxml2.hpp

tinyxml2.o: $(TINYXML2_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

MILEAGE_CLAIM_DEPENDENTS =\
	mileage_claim.cpp \
	mileage_claim.hpp

mileage_claim.o: $(MILEAGE_CLAIM_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

MILEAGE_CLAIM_BUILDER_DEPENDENTS =\
	mileage_claim_builder.cpp \
	mileage_claim_builder.hpp \
	mileage_claim.hpp

mileage_claim_builder.o: $(MILEAGE_CLAIM_BUILDER_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

ECO_STAT_DEPENDENTS = \
	eco_stat.cpp \
	eco_stat.hpp

eco_stat.o: $(ECO_STAT_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

ECO_STAT_BUILDER_DEPENDENTS = \
	eco_stat_builder.cpp \
	eco_stat_builder.hpp \
	eco_stat.hpp

eco_stat_builder.o: $(ECO_STAT_BUILDER_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_STATS_SERVICE_EXCEPTION_DEPENDENTS = \
	shouty_stats_service_exception.cpp \
	shouty_stats_service_exception.hpp

shouty_stats_service_exception.o: $(SHOUTY_STATS_SERVICE_EXCEPTION_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

FAKE_STATS_SERVICE_DEPENDENTS = \
	fake_stats_service.cpp \
	fake_stats_service.hpp \
	stats_service.hpp \
	shouty_stats_service_exception.hpp

fake_stats_service.o: $(FAKE_STATS_SERVICE_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

FAKE_STATS_BUILDER_DEPENDENTS = \
	fake_stats_builder.cpp \
	fake_stats_builder.hpp

fake_stats_builder.o: $(FAKE_STATS_BUILDER_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

PRODUCTION_STATS_SERVICE_DEPENDENTS = \
	production_stats_service.cpp \
	production_stats_service.hpp \
	stats_service.hpp \
	shouty_stats_service.hpp

production_stats_service.o: $(PRODUCTION_STATS_SERVICE_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_REPORT_PROCESSOR_DEPENDENTS = \
	shouty_report_processor.cpp \
	shouty_report_processor.hpp \
	eco_stat.hpp \
	mileage_claim.hpp \
	stats_service.hpp

shouty_report_processor.o: $(SHOUTY_REPORT_PROCESSOR_DEPENDENTS)
	g++ ${CXXFLAGS} -c $<

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_STATS_SERVICE_DEPENDENTS = \
	zzz_DONT_READ_ME.cpp \
	shouty_stats_service.hpp \
	shouty_stats_service_exception.hpp

shouty_stats_service.o: $(SHOUTY_STATS_SERVICE_DEPENDENTS)
	g++ ${CXXFLAGS} -o $@ -c $<

#- - - - - - - - - - - - - - - - - - - - - -

UNIT_TEST_DEPENDENTS = \
	unit.tests.cpp \
	eco_stat.o \
	eco_stat_builder.o \
	fake_stats_builder.o \
	fake_stats_service.o \
	mileage_claim.o \
	mileage_claim_builder.o \
	production_stats_service.o \
	shouty_report_processor.o \
	shouty_stats_service_exception.o \
	shouty_stats_service.o \
	tinyxml2.o

unit: $(UNIT_TEST_DEPENDENTS)
	g++ ${FLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

CONTRACT_TEST_DEPENDENTS = \
	contract.tests.cpp \
	fake_stats_builder.o \
	fake_stats_service.o \
	mileage_claim.o \
	production_stats_service.o \
	shouty_stats_service.o \
	shouty_stats_service_exception.o \
	tinyxml2.o

contract: $(CONTRACT_TEST_DEPENDENTS)
	g++ ${FLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

SHOUTY_REPORT_JOB_DEPENDENTS = \
	shouty_report_job.cpp \
	eco_stat.o \
	eco_stat_builder.o \
	fake_stats_service.o \
	mileage_claim.o \
	production_stats_service.o \
	shouty_report_processor.o \
	shouty_stats_service.o \
	shouty_stats_service_exception.o \
	tinyxml2.o

shouty_report_job: $(SHOUTY_REPORT_JOB_DEPENDENTS)
	g++ ${FLAGS} -o $@ $^

#- - - - - - - - - - - - - - - - - - - - - -

END_TO_END_TEST_DEPENDENTS = \
	end_to_end.tests.cpp

e2e: $(END_TO_END_TEST_DEPENDENTS)
	g++ ${FLAGS} -o $@ $<

#- - - - - - - - - - - - - - - - - - - - - -

clean:
	rm *.o

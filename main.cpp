#include <stdio.h>
#include <iostream>

#include "marco.h"
//#include "Test.h"
#include "TestConstructionOrder.h"
#include "LogHelper.h"

INITIALIZE_EASYLOGGINGPP


using namespace std;

void test_easyloggingpp()
{
    el::Loggers::addFlag ( el::LoggingFlag::LogDetailedCrashReason );
    LOG ( INFO ) << "My first info log using default logger";
    LOG ( INFO ) << "ÄãºÃ";
    CLOG ( ERROR, "performance" ) << "This is info log using performance logger";

    for ( int i = 1; i <= 10; ++i ) {
        LOG_EVERY_N ( 2, INFO ) << "Logged every second iter";
    }
    // 5 logs written; 2, 4, 6, 7, 10

    for ( int i = 1; i <= 10; ++i ) {
        LOG_AFTER_N ( 2, INFO ) << "Log after 2 hits; " << i;
    }
    // 8 logs written; 3, 4, 5, 6, 7, 8, 9, 10

    for ( int i = 1; i <= 100; ++i ) {
        LOG_N_TIMES ( 3, INFO ) << "Log only 3 times; " << i;
    }
    // 3 logs writter; 1, 2, 3
    //test_log();
}











class SomeOneClass : public LogHelper
{
    public:
        SomeOneClass() {}
        ~SomeOneClass() {}
        void action()
        {
            SLOG ( INFO ) << "do action!";
        }

};
class SomeTwoClass : public LogHelper
{
    public:
        SomeTwoClass() {}
        ~SomeTwoClass() {}
        void action()
        {
            SLOG ( INFO ) << "do action!";
        }

};



void myCrashHandler ( int sig )
{
    LOG ( FATAL ) << "Woops! Crashed!";
    el::Loggers::flushAll();
    el::base::debug::StackTrace();
    el::Helpers::logCrashReason ( sig );

    // FOLLOWING LINE IS ABSOLUTELY NEEDED AT THE END IN ORDER TO ABORT APPLICATION
    el::Helpers::crashAbort ( sig );
}
int test_crash ( void )
{
    el::Helpers::setCrashHandler ( myCrashHandler );

    LOG ( INFO ) << "My crash handler!";

    int* i = NULL;
    *i = 0; // Crash!

    return 0;
}

void test_baselog()
{
    // Load configuration from file
    el::Configurations conf ( "log.conf" );
    // Actually reconfigure all loggers instead
    el::Loggers::reconfigureAllLoggers ( conf );


//  LOG ( INFO ) << "getLogger test!";
    el::base::Writer (
        el::Level::Info,
        __FILE__,
        __LINE__,
        __FUNCSIG__,
        el::base::DispatchAction::NormalLog
    ).construct (
        1,
        el::base::consts::kDefaultLoggerId
    ) << "getLogger test!";


//  CLOG ( INFO, "default", "network" )
//       << "This will be logged using default and network loggers!~";
    el::base::Writer (
        el::Level::Info,
        __FILE__,
        __LINE__,
        __FUNCSIG__,
        el::base::DispatchAction::NormalLog
    ).construct (
        2,
        "default",
        "network"
    ) << "This will be logged using default and network loggers!~";


    el::Logger *logger = el::Loggers::getLogger ( "" );

    logger->info ( "log output" );

    SomeOneClass some1;
    some1.info ( "log output head" );
    {
        SomeTwoClass some2;
        some2.info ( "log output head inside" );
        some2.info ( "log output tail outside" );
        some2.action();
    }
    some1.info ( "log output tail" );
    some1.action();
    SLOG ( INFO ) << "do action!";
    SLOG ( INFO ) << "do action!";
    SLOG ( INFO ) << "do action!";
    SLOG ( INFO ) << "do action!";
    SLOG ( INFO ) << "do action!";
    SLOG ( INFO ) << "do action!";


    el::Loggers::flushAll();
}

int main ( int argc, char** argv )
{
    test_baselog();
    getchar();
    return 0;
}
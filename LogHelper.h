

#include <typeinfo>
#include <type_traits>
#include "Libs/easylogging++_v9.80.h"



el::Logger* getLogger();

class ClassNameHelper
{
    public:
        ClassNameHelper();
        virtual ~ClassNameHelper();
        virtual const std::string getClassName() final;
};

class LogHelper : public ClassNameHelper
{

    public:
        LogHelper();
        virtual ~LogHelper();
        el::Logger * getLogger();
    private:
        el::Logger * m_pLogger;

#define LOGGER_LEVEL_WRITERS_SIGNATURES(FUNCTION_NAME)\
    template <typename T, typename... Args>\
    void FUNCTION_NAME(const char* s, const T& value, const Args&... args) \
    {\
    getLogger()->FUNCTION_NAME(s, value, args...); \
    }\
    template <typename T>\
    void FUNCTION_NAME(const T& value) \
    { \
    getLogger()->FUNCTION_NAME(value); \
    }

        LOGGER_LEVEL_WRITERS_SIGNATURES ( info )
        LOGGER_LEVEL_WRITERS_SIGNATURES ( debug )
        LOGGER_LEVEL_WRITERS_SIGNATURES ( warn )
        LOGGER_LEVEL_WRITERS_SIGNATURES ( error )
        LOGGER_LEVEL_WRITERS_SIGNATURES ( fatal )
        LOGGER_LEVEL_WRITERS_SIGNATURES ( trace )
#undef  LOGGER_LEVEL_WRITERS_SIGNATURES


        template <typename T, typename... Args>
        void verbose ( int vlevel, const char* s, const T& value,
                       const Args&... args )
        {
            getLogger()->verbose ( vlevel, s, value, args... );
        }

        template <typename T>
        void verbose ( int vlevel, const T& value )
        {
            getLogger()->verbose ( vlevel, value );
        }
};





#define LOGCLASS_WRITE_LOG(writer, level, dispatchAction) \
    writer(level, __FILE__, __LINE__, ELPP_FUNC, dispatchAction).construct(getLogger())
#define LOGCLASS_WRITE_LOG_IF(writer, condition, level, dispatchAction) if (condition) \
    writer(level, __FILE__, __LINE__, ELPP_FUNC, dispatchAction).construct(getLogger())
#define LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, level, dispatchAction) \
if (ELPP->validateEveryNCounter(__FILE__, __LINE__, occasion)) \
    writer(level, __FILE__, __LINE__, ELPP_FUNC, dispatchAction).construct(getLogger())
#define LOGCLASS_WRITE_LOG_AFTER_N(writer, n, level, dispatchAction) \
if (ELPP->validateAfterNCounter(__FILE__, __LINE__, n)) \
    writer(level, __FILE__, __LINE__, ELPP_FUNC, dispatchAction).construct(getLogger())
#define LOGCLASS_WRITE_LOG_N_TIMES(writer, n, level, dispatchAction) \
if (ELPP->validateNTimesCounter(__FILE__, __LINE__, n)) \
    writer(level, __FILE__, __LINE__, ELPP_FUNC, dispatchAction).construct(getLogger())


// Normal logs
#if ELPP_INFO_LOG
#   define LCINFO(writer, dispatchAction) LOGCLASS_WRITE_LOG(writer, el::Level::Info, dispatchAction)
#else
#   define LCINFO(writer, dispatchAction) el::base::NullWriter()
#endif  // ELPP_INFO_LOG
#if ELPP_WARNING_LOG
#   define LCWARNING(writer, dispatchAction) LOGCLASS_WRITE_LOG(writer, el::Level::Warning, dispatchAction)
#else
#   define LCWARNING(writer, dispatchAction) el::base::NullWriter()
#endif  // ELPP_WARNING_LOG
#if ELPP_DEBUG_LOG
#   define LCDEBUG(writer, dispatchAction) LOGCLASS_WRITE_LOG(writer, el::Level::Debug, dispatchAction)
#else
#   define LCDEBUG(writer, dispatchAction) el::base::NullWriter()
#endif  // ELPP_DEBUG_LOG
#if ELPP_ERROR_LOG
#   define LCERROR(writer, dispatchAction) LOGCLASS_WRITE_LOG(writer, el::Level::Error, dispatchAction)
#else
#   define LCERROR(writer, dispatchAction) el::base::NullWriter()
#endif  // ELPP_ERROR_LOG
#if ELPP_FATAL_LOG
#   define LCFATAL(writer, dispatchAction) LOGCLASS_WRITE_LOG(writer, el::Level::Fatal, dispatchAction)
#else
#   define LCFATAL(writer, dispatchAction) el::base::NullWriter()
#endif  // ELPP_FATAL_LOG
#if ELPP_TRACE_LOG
#   define LCTRACE(writer, dispatchAction) LOGCLASS_WRITE_LOG(writer, el::Level::Trace, dispatchAction)
#else
#   define LCTRACE(writer, dispatchAction) el::base::NullWriter()
#endif  // ELPP_TRACE_LOG
#if ELPP_VERBOSE_LOG
#   define LCVERBOSE(writer, vlevel, dispatchAction) if (VLOG_IS_ON(vlevel)) writer(\
    el::Level::Verbose, __FILE__, __LINE__, ELPP_FUNC, dispatchAction, vlevel).construct(el_getVALength(__VA_ARGS__))
#else
#   define LCVERBOSE(writer, vlevel, dispatchAction) el::base::NullWriter()
#endif  // ELPP_VERBOSE_LOG
// Conditional logs
#if ELPP_INFO_LOG
#   define LCINFO_IF(writer, condition_, dispatchAction) \
    LOGCLASS_WRITE_LOG_IF(writer, (condition_), el::Level::Info, dispatchAction)
#else
#   define LCINFO_IF(writer, condition_, dispatchAction) el::base::NullWriter()
#endif  // ELPP_INFO_LOG
#if ELPP_WARNING_LOG
#   define LCWARNING_IF(writer, condition_, dispatchAction)\
    LOGCLASS_WRITE_LOG_IF(writer, (condition_), el::Level::Warning, dispatchAction)
#else
#   define LCWARNING_IF(writer, condition_, dispatchAction) el::base::NullWriter()
#endif  // ELPP_WARNING_LOG
#if ELPP_DEBUG_LOG
#   define LCDEBUG_IF(writer, condition_, dispatchAction)\
    LOGCLASS_WRITE_LOG_IF(writer, (condition_), el::Level::Debug, dispatchAction)
#else
#   define LCDEBUG_IF(writer, condition_, dispatchAction) el::base::NullWriter()
#endif  // ELPP_DEBUG_LOG
#if ELPP_ERROR_LOG
#   define LCERROR_IF(writer, condition_, dispatchAction)\
    LOGCLASS_WRITE_LOG_IF(writer, (condition_), el::Level::Error, dispatchAction)
#else
#   define LCERROR_IF(writer, condition_, dispatchAction) el::base::NullWriter()
#endif  // ELPP_ERROR_LOG
#if ELPP_FATAL_LOG
#   define LCFATAL_IF(writer, condition_, dispatchAction)\
    LOGCLASS_WRITE_LOG_IF(writer, (condition_), el::Level::Fatal, dispatchAction)
#else
#   define LCFATAL_IF(writer, condition_, dispatchAction) el::base::NullWriter()
#endif  // ELPP_FATAL_LOG
#if ELPP_TRACE_LOG
#   define LCTRACE_IF(writer, condition_, dispatchAction)\
    LOGCLASS_WRITE_LOG_IF(writer, (condition_), el::Level::Trace, dispatchAction)
#else
#   define LCTRACE_IF(writer, condition_, dispatchAction) el::base::NullWriter()
#endif  // ELPP_TRACE_LOG
#if ELPP_VERBOSE_LOG
#   define LCVERBOSE_IF(writer, condition_, vlevel, dispatchAction) if (VLOG_IS_ON(vlevel) && (condition_)) writer( \
    el::Level::Verbose, __FILE__, __LINE__, ELPP_FUNC, dispatchAction, vlevel).construct(el_getVALength(__VA_ARGS__))
#else
#   define LCVERBOSE_IF(writer, condition_, vlevel, dispatchAction) el::base::NullWriter()
#endif  // ELPP_VERBOSE_LOG
// Occasional logs
#if ELPP_INFO_LOG
#   define LCINFO_EVERY_N(writer, occasion, dispatchAction)\
    LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, el::Level::Info, dispatchAction)
#else
#   define LCINFO_EVERY_N(writer, occasion, dispatchAction) el::base::NullWriter()
#endif  // ELPP_INFO_LOG
#if ELPP_WARNING_LOG
#   define LCWARNING_EVERY_N(writer, occasion, dispatchAction)\
    LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, el::Level::Warning, dispatchAction)
#else
#   define LCWARNING_EVERY_N(writer, occasion, dispatchAction) el::base::NullWriter()
#endif  // ELPP_WARNING_LOG
#if ELPP_DEBUG_LOG
#   define LCDEBUG_EVERY_N(writer, occasion, dispatchAction)\
    LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, el::Level::Debug, dispatchAction)
#else
#   define LCDEBUG_EVERY_N(writer, occasion, dispatchAction) el::base::NullWriter()
#endif  // ELPP_DEBUG_LOG
#if ELPP_ERROR_LOG
#   define LCERROR_EVERY_N(writer, occasion, dispatchAction)\
    LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, el::Level::Error, dispatchAction)
#else
#   define LCERROR_EVERY_N(writer, occasion, dispatchAction) el::base::NullWriter()
#endif  // ELPP_ERROR_LOG
#if ELPP_FATAL_LOG
#   define LCFATAL_EVERY_N(writer, occasion, dispatchAction)\
    LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, el::Level::Fatal, dispatchAction)
#else
#   define LCFATAL_EVERY_N(writer, occasion, dispatchAction) el::base::NullWriter()
#endif  // ELPP_FATAL_LOG
#if ELPP_TRACE_LOG
#   define LCTRACE_EVERY_N(writer, occasion, dispatchAction)\
    LOGCLASS_WRITE_LOG_EVERY_N(writer, occasion, el::Level::Trace, dispatchAction)
#else
#   define LCTRACE_EVERY_N(writer, occasion, dispatchAction) el::base::NullWriter()
#endif  // ELPP_TRACE_LOG
#if ELPP_VERBOSE_LOG
#   define LCVERBOSE_EVERY_N(writer, occasion, vlevel, dispatchAction)\
    CVERBOSE_IF(writer, ELPP->validateEveryNCounter(__FILE__, __LINE__, occasion), vlevel, dispatchAction)
#else
#   define LCVERBOSE_EVERY_N(writer, occasion, vlevel, dispatchAction) el::base::NullWriter()
#endif  // ELPP_VERBOSE_LOG
// After N logs
#if ELPP_INFO_LOG
#   define LCINFO_AFTER_N(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_AFTER_N(writer, n, el::Level::Info, dispatchAction)
#else
#   define LCINFO_AFTER_N(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_INFO_LOG
#if ELPP_WARNING_LOG
#   define LCWARNING_AFTER_N(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_AFTER_N(writer, n, el::Level::Warning, dispatchAction)
#else
#   define LCWARNING_AFTER_N(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_WARNING_LOG
#if ELPP_DEBUG_LOG
#   define LCDEBUG_AFTER_N(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_AFTER_N(writer, n, el::Level::Debug, dispatchAction)
#else
#   define LCDEBUG_AFTER_N(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_DEBUG_LOG
#if ELPP_ERROR_LOG
#   define LCERROR_AFTER_N(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_AFTER_N(writer, n, el::Level::Error, dispatchAction)
#else
#   define LCERROR_AFTER_N(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_ERROR_LOG
#if ELPP_FATAL_LOG
#   define LCFATAL_AFTER_N(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_AFTER_N(writer, n, el::Level::Fatal, dispatchAction)
#else
#   define LCFATAL_AFTER_N(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_FATAL_LOG
#if ELPP_TRACE_LOG
#   define LCTRACE_AFTER_N(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_AFTER_N(writer, n, el::Level::Trace, dispatchAction)
#else
#   define LCTRACE_AFTER_N(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_TRACE_LOG
#if ELPP_VERBOSE_LOG
#   define LCVERBOSE_AFTER_N(writer, n, vlevel, dispatchAction)\
    CVERBOSE_IF(writer, ELPP->validateAfterNCounter(__FILE__, __LINE__, n), vlevel, dispatchAction)
#else
#   define LCVERBOSE_AFTER_N(writer, n, vlevel, dispatchAction) el::base::NullWriter()
#endif  // ELPP_VERBOSE_LOG
// N Times logs
#if ELPP_INFO_LOG
#   define LCINFO_N_TIMES(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_N_TIMES(writer, n, el::Level::Info, dispatchAction)
#else
#   define LCINFO_N_TIMES(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_INFO_LOG
#if ELPP_WARNING_LOG
#   define LCWARNING_N_TIMES(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_N_TIMES(writer, n, el::Level::Warning, dispatchAction)
#else
#   define LCWARNING_N_TIMES(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_WARNING_LOG
#if ELPP_DEBUG_LOG
#   define LCDEBUG_N_TIMES(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_N_TIMES(writer, n, el::Level::Debug, dispatchAction)
#else
#   define LCDEBUG_N_TIMES(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_DEBUG_LOG
#if ELPP_ERROR_LOG
#   define LCERROR_N_TIMES(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_N_TIMES(writer, n, el::Level::Error, dispatchAction)
#else
#   define LCERROR_N_TIMES(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_ERROR_LOG
#if ELPP_FATAL_LOG
#   define LCFATAL_N_TIMES(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_N_TIMES(writer, n, el::Level::Fatal, dispatchAction)
#else
#   define LCFATAL_N_TIMES(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_FATAL_LOG
#if ELPP_TRACE_LOG
#   define LCTRACE_N_TIMES(writer, n, dispatchAction)\
    LOGCLASS_WRITE_LOG_N_TIMES(writer, n, el::Level::Trace, dispatchAction)
#else
#   define LCTRACE_N_TIMES(writer, n, dispatchAction) el::base::NullWriter()
#endif  // ELPP_TRACE_LOG
#if ELPP_VERBOSE_LOG
#   define LCVERBOSE_N_TIMES(writer, n, vlevel, dispatchAction)\
    CVERBOSE_IF(writer, ELPP->validateNTimesCounter(__FILE__, __LINE__, n), vlevel, dispatchAction)
#else
#   define LCVERBOSE_N_TIMES(writer, n, vlevel, dispatchAction) el::base::NullWriter()
#endif  // ELPP_VERBOSE_LOG


// Normal logs
#define LCLOG(LEVEL)\
    LC##LEVEL(el::base::Writer, el::base::DispatchAction::NormalLog)
#define LCVLOG(vlevel) CVERBOSE(el::base::Writer, vlevel, el::base::DispatchAction::NormalLog)
// Conditional logs
#define LCLOG_IF(condition, LEVEL)\
    LC##LEVEL##_IF(el::base::Writer, condition, el::base::DispatchAction::NormalLog)
#define LCVLOG_IF(condition, vlevel)\
    CVERBOSE_IF(el::base::Writer, condition, vlevel, el::base::DispatchAction::NormalLog)
// Hit counts based logs
#define LCLOG_EVERY_N(n, LEVEL)\
    LC##LEVEL##_EVERY_N(el::base::Writer, n, el::base::DispatchAction::NormalLog)
#define LCVLOG_EVERY_N(n, vlevel)\
    CVERBOSE_EVERY_N(el::base::Writer, n, vlevel, el::base::DispatchAction::NormalLog)
#define LCLOG_AFTER_N(n, LEVEL)\
    LC##LEVEL##_AFTER_N(el::base::Writer, n, el::base::DispatchAction::NormalLog)
#define LCVLOG_AFTER_N(n, vlevel)\
    CVERBOSE_AFTER_N(el::base::Writer, n, vlevel, el::base::DispatchAction::NormalLog)
#define LCLOG_N_TIMES(n, LEVEL)\
    LC##LEVEL##_N_TIMES(el::base::Writer, n, el::base::DispatchAction::NormalLog)
#define LCVLOG_N_TIMES(n, vlevel)\
    CVERBOSE_N_TIMES(el::base::Writer, n, vlevel, el::base::DispatchAction::NormalLog)


/////////////////////// LogClass use it ////////////////////////////////
// Normal logs
#define LLOG(LEVEL) LCLOG(LEVEL)
#define LVLOG(vlevel) LCVLOG(vlevel)
// Conditional logs
#define LLOG_IF(condition, LEVEL) LCLOG_IF(condition, LEVEL)
#define LVLOG_IF(condition, vlevel) LCVLOG_IF(condition, vlevel)
// Hit counts based logs
#define LLOG_EVERY_N(n, LEVEL) LCLOG_EVERY_N(n, LEVEL)
#define LVLOG_EVERY_N(n, vlevel) LCVLOG_EVERY_N(n, vlevel)
#define LLOG_AFTER_N(n, LEVEL) LCLOG_AFTER_N(n, LEVEL)
#define LVLOG_AFTER_N(n, vlevel) LCVLOG_AFTER_N(n, vlevel)
#define LLOG_N_TIMES(n, LEVEL) LCLOG_N_TIMES(n, LEVEL)
#define LVLOG_N_TIMES(n, vlevel) LCVLOG_N_TIMES(n, vlevel)
//////////////////////////////////////////////////////////////////////////


///////////////////////////// Smart Log //////////////////////////////////
//////////// auto select use default logger or LogClass logger ///////////
// Normal logs
#define SLOG(LEVEL) LCLOG(LEVEL)
#define SVLOG(vlevel) LCVLOG(vlevel)
// Conditional logs
#define SLOG_IF(condition, LEVEL) LCLOG_IF(condition, LEVEL)
#define SVLOG_IF(condition, vlevel) LCVLOG_IF(condition, vlevel)
// Hit counts based logs
#define SLOG_EVERY_N(n, LEVEL) LCLOG_EVERY_N(n, LEVEL)
#define SVLOG_EVERY_N(n, vlevel) LCVLOG_EVERY_N(n, vlevel)
#define SLOG_AFTER_N(n, LEVEL) LCLOG_AFTER_N(n, LEVEL)
#define SVLOG_AFTER_N(n, vlevel) LCVLOG_AFTER_N(n, vlevel)
#define SLOG_N_TIMES(n, LEVEL) LCLOG_N_TIMES(n, LEVEL)
#define SVLOG_N_TIMES(n, vlevel) LCVLOG_N_TIMES(n, vlevel)
//////////////////////////////////////////////////////////////////////////
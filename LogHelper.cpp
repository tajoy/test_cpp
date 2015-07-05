#include "LogHelper.h"

inline el::Logger* getLogger()
{
    static auto pLogger = el::Loggers::getLogger ( ELPP_CURR_FILE_LOGGER_ID );
    return pLogger;
}

const std::string ClassNameHelper::getClassName()
{
    const std::type_info & classinfo = typeid ( *this );
    return ( classinfo.name() + 6 );
}

ClassNameHelper::ClassNameHelper()
{
}

ClassNameHelper::~ClassNameHelper()
{
}

LogHelper::LogHelper() : m_pLogger ( NULL )
{
}

LogHelper::~LogHelper()
{
}


el::Logger * LogHelper::getLogger()
{
    if ( m_pLogger == NULL ) {
        auto classname = getClassName();
        m_pLogger = el::Loggers::getLogger ( classname );
    }
    return m_pLogger;
}
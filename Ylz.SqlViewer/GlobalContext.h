#pragma once

#include "Config.h"
#include "DbContext.h"

class GlobalContext
{
public:

    //唯一实例 只要这个类就好了
    static GlobalContext & instance()
    {
        static GlobalContext context;
        return context;
    }

    Config & config()
    {
        return m_config;
    }

    DbContext & db_context()
    {
        return m_db_context;
    }

private:
    //配置文件
    Config m_config;

    //
    DbContext m_db_context;
};

#define  CONTEXT GlobalContext::instance()

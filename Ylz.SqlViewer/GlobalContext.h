#pragma once

#include "Config.h"
#include "DbContext.h"

class GlobalContext
{
public:

    //Ψһʵ�� ֻҪ�����ͺ���
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
    //�����ļ�
    Config m_config;

    //
    DbContext m_db_context;
};

#define  CONTEXT GlobalContext::instance()

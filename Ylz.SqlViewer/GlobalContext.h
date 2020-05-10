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

    //�����ļ�
    Config m_config;

    //
    DbContext m_db_context;
};

#define  CONTEXT GlobalContext::instance()

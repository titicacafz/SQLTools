#pragma once

#include "Config.h"


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


private:
    //�����ļ�
    Config m_config;

};

#define  CONTEXT GlobalContext::instance()

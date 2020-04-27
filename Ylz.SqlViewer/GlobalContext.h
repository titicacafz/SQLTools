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
    Config config;

    //
    DbContext dbContext;
};

#define  CONTEXT GlobalContext::instance()

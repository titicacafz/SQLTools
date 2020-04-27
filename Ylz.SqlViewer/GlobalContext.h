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

    //配置文件
    Config config;

    //
    DbContext dbContext;
};

#define  CONTEXT GlobalContext::instance()

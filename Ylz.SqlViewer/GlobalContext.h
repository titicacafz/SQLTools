#pragma once

#include "Config.h"


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


private:
    //配置文件
    Config m_config;

};

#define  CONTEXT GlobalContext::instance()

#include "Config.h"




Config::Config() {}

Config* Config::GetInstance(){
    if (self == nullptr)
        self = new Config();

    return self;

}

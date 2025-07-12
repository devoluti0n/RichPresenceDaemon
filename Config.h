#ifndef CONFIG_H
#define CONFIG_H

class Config
{
private:
    Config();
    inline static Config* self = nullptr;



    unsigned int port = 32322; // which port to listen to (websocket)
    bool onlyLocal = true; // should we only allow from localhost, or do we allow from someplace else (idk why this would be needed)



public:
    Config*  GetInstance();


    /**
     * Configs should not be cloneable.
     */
    Config(Config &other) = delete;
    /**
     * Configs should not be assignable.
     */
    void operator=(const Config &) = delete;

};

#endif // CONFIG_H

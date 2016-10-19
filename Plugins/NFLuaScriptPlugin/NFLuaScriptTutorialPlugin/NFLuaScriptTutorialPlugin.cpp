#include "NFLuaScriptTutorialPlugin.h"
#include "HelloWorld3Module.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(NFIPluginManager* pm)
{
#if NF_PLATFORM == NF_PLATFORM_WIN
    SetConsoleTitle("Tutorial3");
#endif
    CREATE_PLUGIN(pm, NFLuaScriptTutorialPlugin)

};

NF_EXPORT void DllStopPlugin(NFIPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NFLuaScriptTutorialPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int NFLuaScriptTutorialPlugin::GetPluginVersion()
{
    return 0;
}

const std::string NFLuaScriptTutorialPlugin::GetPluginName()
{
    return GET_CLASS_NAME(NFLuaScriptTutorialPlugin)
}

void NFLuaScriptTutorialPlugin::Install()
{

    REGISTER_MODULE(pPluginManager, HelloWorld3Module, HelloWorld3Module)

}

void NFLuaScriptTutorialPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, HelloWorld3Module, HelloWorld3Module)
}

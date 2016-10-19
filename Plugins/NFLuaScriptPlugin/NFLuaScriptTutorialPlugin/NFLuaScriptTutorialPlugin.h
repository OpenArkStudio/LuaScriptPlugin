// -------------------------------------------------------------------------
//    @FileName			:    NFNFLuaScriptTutorial.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2014-05-14 08:51
//    @Module           :   NFNFLuaScriptTutorial
//
// -------------------------------------------------------------------------

#ifndef NF_NFLUASCRIPTTUTORIAL_H
#define NF_NFLUASCRIPTTUTORIAL_H

///
#include "NFComm/NFPluginModule/NFIPlugin.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

class NFLuaScriptTutorialPlugin : public NFIPlugin
{
public:
    NFLuaScriptTutorialPlugin(NFIPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};
#endif
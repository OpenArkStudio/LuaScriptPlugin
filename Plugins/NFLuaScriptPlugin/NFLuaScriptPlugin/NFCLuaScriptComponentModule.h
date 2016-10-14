// -------------------------------------------------------------------------
//    @FileName			:    NFCLuaScriptComponentModule.h
//    @Author           :    chuanbo.guo
//    @Date             :    2016-07-08
//    @Module           :    NFCLuaScriptComponentModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFC_LUASCRIPTCOMPONENT_MODULE_H
#define NFC_LUASCRIPTCOMPONENT_MODULE_H

#include "Dep/LuaIntf/LuaIntf.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFPluginModule/NFIClassModule.h"
#include "Plugins/NFLuaScriptPlugin/NFInterface/NFILuaScriptModule.h"
#include "Plugins/NFLuaScriptPlugin/NFInterface/NFILuaScriptComponentModule.h"


class NFCLuaScriptComponentModule
    : public NFILuaScriptComponentModule
{
public:
    NFCLuaScriptComponentModule(NFIPluginManager* p)
    {
        pPluginManager = p;
        mnTime = 0;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();

    virtual bool AfterInit();
    virtual bool BeforeShut();

    virtual bool InstallClassComponent(const std::string& strClassName, const std::string& strCompoment);
    virtual bool ExecuteClassComponent(const std::string& strClassName, const std::string& strCompoment);
    virtual bool UnInstallClassComponent(const std::string& strClassName, const std::string& strCompoment);

    virtual bool InstallConfigIDComponent(const std::string& strID, const std::string& strCompoment);
    virtual bool ExecuteConfigIDComponent(const std::string& strID, const std::string& strCompoment);
    virtual bool UnInstallConfigIDComponent(const std::string& strID, const std::string& strCompoment);


protected:
    int OnCheckInstallLuaObjectClassEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var);

protected:
    NFIElementModule* m_pElementModule;
    NFIKernelModule* m_pKernelModule;
    NFIClassModule* m_pLogicClassModule;
    NFILuaScriptModule* m_pLuaScriptModule;

protected:
    NFMapEx<std::string, std::string> mmClassComponent;
    NFMapEx<std::string, std::string> mmConfigIDComponent;
    NFINT64 mnTime;
};

#endif //!NFC_LUASCRIPTCOMPONENT_MODULE_H

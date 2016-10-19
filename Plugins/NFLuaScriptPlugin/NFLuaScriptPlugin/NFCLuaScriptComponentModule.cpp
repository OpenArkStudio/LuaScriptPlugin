// -------------------------------------------------------------------------
//    @FileName			:    NFCLuaScriptComponentModule.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-01-02
//    @Module           :    NFCLuaScriptComponentModule
//    @Desc             :
// -------------------------------------------------------------------------

#include <assert.h>
#include "NFCLuaScriptComponentModule.h"
#include "NFLuaScriptPlugin.h"
#include "NFComm/NFCore/NFTimer.h"
#include "NFComm/NFPluginModule/NFIKernelModule.h"
#include "NFComm/NFMessageDefine/NFProtocolDefine.hpp"

bool NFCLuaScriptComponentModule::Init()
{
    m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();
    m_pLogicClassModule = pPluginManager->FindModule<NFIClassModule>();
    m_pElementModule = pPluginManager->FindModule<NFIElementModule>();
    m_pLuaScriptModule = pPluginManager->FindModule<NFILuaScriptModule>();

    return true;
}

bool NFCLuaScriptComponentModule::AfterInit()
{
    m_pLuaScriptModule->AddScriptPackagePath(pPluginManager->GetConfigPath() + "DataConfig/ScriptComponent"); //Add Search Path to Lua

    NF_SHARE_PTR<NFIClass> pClass = m_pLogicClassModule->First();
    while (pClass)
    {
        NF_SHARE_PTR<NFIComponent> pComponent = pClass->GetComponentManager()->First();
        while (pComponent)
        {
            if (pComponent->Enable())
            {
                InstallClassComponent(pClass->GetClassName(), pComponent->GetComponentName());
            }

            pComponent = pClass->GetComponentManager()->Next();
        }


        NF_SHARE_PTR<NFIProperty> pProperty = pClass->GetPropertyManager()->GetElement("LuaScript");
        if (pProperty)
        {
            std::string strComponent = pProperty->GetString();
            m_pKernelModule->AddClassCallBack(pClass->GetClassName(), this, &NFCLuaScriptComponentModule::OnCheckInstallLuaObjectClassEvent);
        }

        pClass = m_pLogicClassModule->Next();
    }


    return true;
}

bool NFCLuaScriptComponentModule::Shut()
{
    return true;
}

bool NFCLuaScriptComponentModule::Execute()
{
    //10秒钟reload一次
    if (pPluginManager->GetNowTime() - mnTime > 10)
    {
        std::string strClassName;
        for (std::string* pString = mmClassComponent.FirstNude(strClassName); pString != NULL; pString = mmClassComponent.NextNude(strClassName))
        {
            ExecuteClassComponent(strClassName, *pString);
        }

        for (std::string* pString = mmClassComponent.FirstNude(strClassName); pString != NULL; pString = mmClassComponent.NextNude(strClassName))
        {
            ExecuteConfigIDComponent(strClassName, *pString);
        }
    }

    return true;
}

bool NFCLuaScriptComponentModule::BeforeShut()
{
    return true;
}


int NFCLuaScriptComponentModule::OnCheckInstallLuaObjectClassEvent(const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var)
{
    std::string strConfigID = m_pKernelModule->GetPropertyString(self, NFrame::IObject::ConfigID());
    const std::string& strComponent = m_pElementModule->GetPropertyString(strConfigID, "LuaScript");
    if (CLASS_OBJECT_EVENT::COE_CREATE_LOADDATA == eClassEvent)
    {
        if (!strComponent.empty())
        {
            InstallConfigIDComponent(strConfigID, strComponent);
        }
    }

    NF_SHARE_PTR<std::string> pComponent = mmConfigIDComponent.GetElement(strConfigID);
    if (pComponent)
    {
        if (0 == pComponent->compare(strComponent))
        {
            std::string strLuaClassFuncTionName = strComponent + ".OnClassEvent";
            m_pLuaScriptModule->DoLuaClassFunction(strLuaClassFuncTionName, self, strClassName, eClassEvent, var);
        }
    }

    return 0;
}

bool NFCLuaScriptComponentModule::InstallClassComponent(const std::string& strClassName, const std::string& strCompoment)
{
    if (!mmClassComponent.GetElement(strClassName))
    {
        return false;
    }

    std::string strFileName = strCompoment + ".lua";
    if (!m_pLuaScriptModule->LoadScript(strFileName))
    {
        return false;
    }

    if (!mmClassComponent.AddElement(strClassName, NF_SHARE_PTR<std::string>(NF_NEW std::string(strCompoment))))
    {
        return false;
    }

    std::string AfterInitCBName = strCompoment + ".AfterInit";
    m_pLuaScriptModule->DoLuaFunction0(AfterInitCBName);

    std::string strClassEventCBName = strCompoment + ".OnClassEvent";
    m_pLuaScriptModule->AddClassCallBack(strClassName, strClassEventCBName);
    return true;
}

bool NFCLuaScriptComponentModule::ExecuteClassComponent(const std::string& strClassName, const std::string& strCompoment)
{
    if (!mmClassComponent.GetElement(strClassName))
    {
        return false;
    }

    if (!mmClassComponent.AddElement(strClassName, NF_SHARE_PTR<std::string>(NF_NEW std::string(strCompoment))))
    {
        return false;
    }

    std::string ExecuteCBName = strCompoment + ".Execute";
    return m_pLuaScriptModule->DoLuaFunction0(ExecuteCBName);
}

bool NFCLuaScriptComponentModule::UnInstallClassComponent(const std::string& strClassName, const std::string& strCompoment)
{
    if (!mmClassComponent.GetElement(strClassName))
    {
        return false;
    }

    if (!mmClassComponent.AddElement(strClassName, NF_SHARE_PTR<std::string>(NF_NEW std::string(strCompoment))))
    {
        return false;
    }

    std::string UnInstallCBName = strCompoment + ".BeforeShut";
    return m_pLuaScriptModule->DoLuaFunction0(UnInstallCBName);
}

bool NFCLuaScriptComponentModule::InstallConfigIDComponent(const std::string& strID, const std::string& strCompoment)
{
    if (mmConfigIDComponent.GetElement(strID))
    {
        return false;
    }

    std::string strFileName = strCompoment + ".lua";
    if (!m_pLuaScriptModule->LoadScript(strFileName))
    {
        return false;
    }

    if (!mmConfigIDComponent.AddElement(strID, NF_SHARE_PTR<std::string>(NF_NEW std::string(strCompoment))))
    {
        return false;
    }

    std::string AfterInitCBName = strCompoment + ".AfterInit";
    m_pLuaScriptModule->DoLuaFunction0(AfterInitCBName);
}

bool NFCLuaScriptComponentModule::ExecuteConfigIDComponent(const std::string& strID, const std::string& strCompoment)
{
    if (!mmConfigIDComponent.GetElement(strID))
    {
        return false;
    }

    if (!mmConfigIDComponent.AddElement(strID, NF_SHARE_PTR<std::string>(NF_NEW std::string(strCompoment))))
    {
        return false;
    }

    std::string ExecuteCBName = strCompoment + ".Execute";
    return m_pLuaScriptModule->DoLuaFunction0(ExecuteCBName);
}

bool NFCLuaScriptComponentModule::UnInstallConfigIDComponent(const std::string& strID, const std::string& strCompoment)
{
    if (!mmConfigIDComponent.GetElement(strID))
    {
        return false;
    }

    if (!mmConfigIDComponent.AddElement(strID, NF_SHARE_PTR<std::string>(NF_NEW std::string(strCompoment))))
    {
        return false;
    }

    std::string UnInstallCBName = strCompoment + ".BeforeShut";
    return m_pLuaScriptModule->DoLuaFunction0(UnInstallCBName);
}

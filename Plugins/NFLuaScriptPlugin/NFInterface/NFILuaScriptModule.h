// -------------------------------------------------------------------------
//    @FileName         £º    NFILuaScriptModule.h
//    @Author           £º    LvSheng.Huang
//    @Date             £º    2013-07-08
//    @Module           £º    NFILuaScriptModule
//
// -------------------------------------------------------------------------

#ifndef NFI_LUA_SCRIPT_MODULE_H
#define NFI_LUA_SCRIPT_MODULE_H

#include "NFIScriptModule.h"

class NFILuaScriptModule
    : public NFIScriptModule
{
public:
    virtual bool AddPropertyCallBack(const NFGUID& self, std::string& strPropertyName, std::string& luaFunc) = 0;
    virtual bool AddRecordCallBack(const NFGUID& self, std::string& strRecordName, std::string& luaFunc) = 0;
    virtual bool AddEventCallBack(const NFGUID& self, const int nEventID, std::string& luaFunc) = 0;
    virtual bool AddHeartBeat(const NFGUID& self, std::string& strHeartBeatName, std::string& luaFunc, const float fTime, const int nCount) = 0;
    virtual int AddRow(const NFGUID& self, std::string& strRecordName, const NFIDataList& var) = 0;

    virtual bool AddClassCallBack(const std::string& className, std::string& funcName) = 0;

    virtual bool LoadScript(const std::string& strLuaFile) = 0;
    virtual bool DoLuaFunction0(const std::string& strFuncName) = 0;
    virtual bool AddScriptPackagePath(const std::string& strLuaFile) = 0;
    virtual bool DoLuaClassFunction(const std::string& strFuncName, const NFGUID& self, const std::string& strClassName, const CLASS_OBJECT_EVENT eClassEvent, const NFIDataList& var) = 0;

};


#endif
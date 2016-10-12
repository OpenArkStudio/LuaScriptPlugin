echo up DataCfg

@set BaseFrameDir=..\ArkGameFrame

xcopy %BaseFrameDir%\Dep\*.* Dep\ /e/y
xcopy %BaseFrameDir%\Doc\*.* Doc\  /e/y
xcopy %BaseFrameDir%\Plugins\NFLuaScriptPlugin\*.* Plugins\NFLuaScriptPlugin\ /e/y

echo complete up 
pause
@ stdcall -private DllCanUnloadNow()
@ stdcall -private DllGetClassObject(ptr ptr ptr)
@ stdcall -private DllRegisterServer()
@ stdcall -private DllUnregisterServer()
@ stdcall SetInputScope(long long)
@ stub SetInputScopeXML
@ stdcall SetInputScopes(long ptr long ptr long wstr wstr)
@ stub TF_CUASAppFix
@ stub TF_CheckThreadInputIdle
@ stub TF_ClearLangBarAddIns
@ stdcall -stub TF_CreateCategoryMgr(ptr)
@ stdcall -stub TF_CreateCicLoadMutex(ptr)
@ stdcall -stub TF_CreateDisplayAttributeMgr(ptr)
@ stdcall TF_CreateInputProcessorProfiles(ptr)
@ stdcall TF_CreateLangBarItemMgr(ptr)
@ stdcall TF_CreateLangBarMgr(ptr)
@ stdcall TF_CreateThreadMgr(ptr)
@ stdcall -stub TF_DllDetachInOther()
@ stdcall -stub TF_GetGlobalCompartment(ptr)
@ stub TF_GetInputScope
@ stub TF_GetLangIcon
@ stub TF_GetMlngHKL
@ stub TF_GetMlngIconIndex
@ stub TF_GetThreadFlags
@ stdcall TF_GetThreadMgr(ptr)
@ stub TF_InatExtractIcon
@ stdcall TF_InitMlngInfo()
@ stdcall -stub TF_InitSystem()
@ stdcall -stub TF_UninitSystem()
@ stdcall -stub TF_InvalidAssemblyListCache()
@ stdcall TF_InvalidAssemblyListCacheIfExist()
@ stdcall TF_IsCtfmonRunning()
@ stub TF_IsInMarshaling
@ stub TF_MlngInfoCount
@ stdcall TF_RunInputCPL()
@ stdcall -stub TF_PostAllThreadMsg(long long)
@ stdcall TF_RegisterLangBarAddIn(ptr wstr long)
@ stdcall TF_UnregisterLangBarAddIn(ptr long)

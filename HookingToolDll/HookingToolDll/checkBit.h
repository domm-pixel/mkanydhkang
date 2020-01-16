#pragma once

static int check_Bit()
{
	CRegKey key;
	DWORD dw_dbg_val = 0;

	if (key.Open(HKEY_CURRENT_USER, L"Software\\Test\\Inject") == ERROR_SUCCESS)
	{
		if (key.QueryDWORDValue(L"bit", dw_dbg_val) == ERROR_SUCCESS)
		{
			if (dw_dbg_val == 1)
				return 1;   // µû·Î »©¼­ ÇÔ¼ö·Î ¸¸µå´Â°Ô ±ò²ûÇÒµí.
			//else if (dw_dbg_val == 2)
			//	return 2;
			else
				return 0;
		}
	}
	else
	{
		OutputDebugStringW(L"Create Key...location - Software\\Test\\Inject");
		key.Create(HKEY_CURRENT_USER, L"Software\\Test\\Inject");
	}
	key.Close();
	return 0;
}
//static void check_reg(CString pstr_chk, Pg_pOriginFunc_C)
//{
//	CRegKey key;
//	DWORD dw_dbg_val = 0;
//	
//	if (key.Open(HKEY_CURRENT_USER, L"SOFTWARE\\HookingTool") == ERROR_SUCCESS)
//	{
//		if (key.QueryDWORDValue(pstr_chk, dw_dbg_val) == ERROR_SUCCESS)
//		{
//			if (dw_dbg_val == 1)
//				g_pOriginFunc_C = (PFNCreateFile)CreateFile;
//			Change_iat("kernel32.dll", (PROC)g_pOriginFunc_C, (PROC)my_create_file);
//		}
//	}
//}
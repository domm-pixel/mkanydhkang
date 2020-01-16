// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"

LPCWSTR szModuleTag = L"[npp] "; //어플리케이션에서 개별적으로 해당 태그 내용을 정의 하기위해 extern
BOOL g_bDebugOut = check_Bit();

//////////////////////////////////////// check support dll ////////////////////////////////////////
BOOL is_support_dll(TCHAR *p_str_proc_name, TCHAR* cmpModuleList)
{
	USES_CONVERSION;
	//how to solve...
	TCHAR seps[] = L"|";
	TCHAR *token;
	TCHAR tchar_temp[200];
	TCHAR *t_char_next_token;
	wsprintf(tchar_temp, L"%s", cmpModuleList);//?
	token = _tcstok_s(tchar_temp, seps, &t_char_next_token);
	while (token != NULL)
	{
		if (!_tcscmp(p_str_proc_name, token))//i 대소문자 구분 x
		{
			return TRUE;
		}
		token = _tcstok_s(NULL, seps, &t_char_next_token);
	}
	return FALSE;
}
BOOL is_support_ex(wstring wstr_file_ex)
{
	USES_CONVERSION;
	wchar_t seps[]=L"|";
	wchar_t *token;
	wchar_t wchar_temp[200];
	wchar_t *wchar_next_token;
	wsprintf(wchar_temp, L"%s", wstr_file_ex);
	token = _tcstok_s(wchar_temp,seps, &wchar_next_token);
	while (token != NULL)
	{
		if (wcscmp(wstr_file_ex.c_str(), g_wstr_file_ex) == 0)
			return TRUE;
		token = _tcstok_s(NULL, seps, &wchar_next_token);
	}
		return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// check function ////////////////////////////////////////
wstring	check_access(DWORD p_dw_share)
{
	//return 은 
	wstring str_temp;
	if (IS_BIT_SET(GENERIC_ALL, p_dw_share))
		str_temp = L"G_A";
	else if (IS_BIT_SET(GENERIC_EXECUTE, p_dw_share))
		str_temp = L"G_E";
	else if (IS_BIT_SET(GENERIC_READ, p_dw_share))
		str_temp = L"G_R";
	else if (IS_BIT_SET(GENERIC_WRITE, p_dw_share))
		str_temp = L"G_W";
	else if (IS_BIT_SET(DELETE, p_dw_share))
		str_temp = L"DEL";
	else if (IS_BIT_SET(READ_CONTROL, p_dw_share))
		str_temp = L"R_C";
	else if (IS_BIT_SET(WRITE_DAC, p_dw_share))
		str_temp = L"W_D";
	else if (IS_BIT_SET(WRITE_OWNER, p_dw_share))
		str_temp = L"W_O";
	else if (IS_BIT_SET(SYNCHRONIZE, p_dw_share))
		str_temp = L"SYN";
	else
		str_temp = std::to_wstring(p_dw_share);
	return str_temp;
}
wstring	check_share(DWORD p_dw_share)
{
	//dwShareMode
	wstring str_temp;
	if (IS_BIT_SET(0x00000000, p_dw_share))
		str_temp = L"0";
	else if (IS_BIT_SET(FILE_SHARE_DELETE, p_dw_share))
		str_temp = L"F_S_D";
	else if (IS_BIT_SET(FILE_SHARE_READ, p_dw_share))
		str_temp = L"F_S_R";
	else if (IS_BIT_SET(FILE_SHARE_WRITE, p_dw_share))
		str_temp = L"F_S_W";
	else
		str_temp = std::to_wstring(p_dw_share);
	return str_temp;
}
wstring	check_disposition(DWORD p_dw_disposition)
{
	//dwCreationDisposition
	wstring str_temp;
	if (IS_BIT_SET(CREATE_ALWAYS, p_dw_disposition))
		str_temp = L"C_A";
	else if (IS_BIT_SET(CREATE_NEW, p_dw_disposition))
		str_temp = L"C_N";
	else if (IS_BIT_SET(OPEN_ALWAYS, p_dw_disposition))
		str_temp = L"O_A";
	else if (IS_BIT_SET(OPEN_EXISTING, p_dw_disposition))
		str_temp = L"O_E";
	else if (IS_BIT_SET(TRUNCATE_EXISTING, p_dw_disposition))
		str_temp = L"T_E";
	else
		str_temp = std::to_wstring(p_dw_disposition);
	return str_temp;
}
wstring	check_flags(DWORD p_dw_flags)
{
	//dwFlagsAndAttributes
	wstring str_temp;
	//flags
	if (IS_BIT_SET(FILE_FLAG_BACKUP_SEMANTICS, p_dw_flags))
		str_temp = L"B_S";
	else if (IS_BIT_SET(FILE_FLAG_DELETE_ON_CLOSE, p_dw_flags))
		str_temp = L"D_O_C";
	else if (IS_BIT_SET(FILE_FLAG_NO_BUFFERING, p_dw_flags))
		str_temp = L"NO_BUF";
	else if (IS_BIT_SET(FILE_FLAG_OPEN_NO_RECALL, p_dw_flags))
		str_temp = L"O_N_R";
	else if (IS_BIT_SET(FILE_FLAG_OPEN_REPARSE_POINT, p_dw_flags))
		str_temp = L"O_R_P";
	else if (IS_BIT_SET(FILE_FLAG_OVERLAPPED, p_dw_flags))
		str_temp = L"OVER";
	else if (IS_BIT_SET(FILE_FLAG_POSIX_SEMANTICS, p_dw_flags))
		str_temp = L"P_S";
	else if (IS_BIT_SET(FILE_FLAG_RANDOM_ACCESS, p_dw_flags))
		str_temp = L"R_A";
	else if (IS_BIT_SET(FILE_FLAG_SESSION_AWARE, p_dw_flags))
		str_temp = L"S_A";
	else if (IS_BIT_SET(FILE_FLAG_SEQUENTIAL_SCAN, p_dw_flags))
		str_temp = L"S_S";
	else if (IS_BIT_SET(FILE_FLAG_WRITE_THROUGH, p_dw_flags))
		str_temp = L"W_T";
	else if (IS_BIT_SET(FILE_FLAG_FIRST_PIPE_INSTANCE, p_dw_flags))
		str_temp = L"F_P_I";
	//attributes
	else if (IS_BIT_SET(FILE_ATTRIBUTE_DIRECTORY, p_dw_flags))
		str_temp = L"DIR";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_DEVICE, p_dw_flags))
		str_temp = L"DEV";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_SPARSE_FILE, p_dw_flags))
		str_temp = L"S_F";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_REPARSE_POINT, p_dw_flags))
		str_temp = L"R_P";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_COMPRESSED, p_dw_flags))
		str_temp = L"COM";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_NOT_CONTENT_INDEXED, p_dw_flags))
		str_temp = L"N_C_I";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_INTEGRITY_STREAM, p_dw_flags))
		str_temp = L"I_S";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_VIRTUAL, p_dw_flags))
		str_temp = L"VIR";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_NO_SCRUB_DATA, p_dw_flags))
		str_temp = L"N_C_D";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_EA, p_dw_flags))
		str_temp = L"EA";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_ARCHIVE, p_dw_flags))
		str_temp = L"ARC";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_ENCRYPTED, p_dw_flags))
		str_temp = L"ENC";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_HIDDEN, p_dw_flags))
		str_temp = L"HID";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_NORMAL, p_dw_flags))
		str_temp = L"NOR";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_OFFLINE, p_dw_flags))
		str_temp = L"OFF";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_READONLY, p_dw_flags))
		str_temp = L"READ";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_SYSTEM, p_dw_flags))
		str_temp = L"SYS";
	else if (IS_BIT_SET(FILE_ATTRIBUTE_TEMPORARY, p_dw_flags))
		str_temp = L"TEM";
	else
		str_temp = std::to_wstring(p_dw_flags);
	return str_temp;
}
wstring	check_method(DWORD p_dw_flags)
{
	wstring str_temp;
	if (FILE_BEGIN == p_dw_flags)
		str_temp = L"FILE_BEGIN";
	else if (FILE_CURRENT == p_dw_flags)
		str_temp = L"FILE_CURRENT";
	else if (FILE_END == p_dw_flags)
		str_temp = L"FILE_END";
	else
		str_temp = std::to_wstring(p_dw_flags);
	return str_temp;
}
wstring	check_dw_flags(DWORD p_dw_flags)
{
	wstring str_temp;
	if (IS_BIT_SET(MOVEFILE_COPY_ALLOWED, p_dw_flags))
		str_temp = L"MOVEFILE_COPY_ALLOWED";
	else if (IS_BIT_SET(FILE_CURRENT, p_dw_flags))
		str_temp = L"MOVEFILE_CREATE_HARDLINK";
	else if (IS_BIT_SET(MOVEFILE_DELAY_UNTIL_REBOOT, p_dw_flags))
		str_temp = L"MOVEFILE_DELAY_UNTIL_REBOOT";
	else if (IS_BIT_SET(MOVEFILE_FAIL_IF_NOT_TRACKABLE, p_dw_flags))
		str_temp = L"MOVEFILE_FAIL_IF_NOT_TRACKABLE";
	else if (IS_BIT_SET(MOVEFILE_REPLACE_EXISTING, p_dw_flags))
		str_temp = L"MOVEFILE_REPLACE_EXISTING";
	else if (IS_BIT_SET(MOVEFILE_WRITE_THROUGH, p_dw_flags))
		str_temp = L"MOVEFILE_WRITE_THROUGH";
	else
		str_temp = std::to_wstring(p_dw_flags);
	return str_temp;
}
wstring	check_dw_copy_flags(DWORD p_dw_flags)
{
	wstring str_temp;
	if (IS_BIT_SET(COPY_FILE_ALLOW_DECRYPTED_DESTINATION, p_dw_flags))
		str_temp = L"COPY_FILE_ALLOW_DECRYPTED_DESTINATION";
	else if (IS_BIT_SET(COPY_FILE_COPY_SYMLINK, p_dw_flags))
		str_temp = L"COPY_FILE_COPY_SYMLINK";
	else if (IS_BIT_SET(COPY_FILE_FAIL_IF_EXISTS, p_dw_flags))
		str_temp = L"COPY_FILE_FAIL_IF_EXISTS";
	else if (IS_BIT_SET(COPY_FILE_NO_BUFFERING, p_dw_flags))
		str_temp = L"COPY_FILE_NO_BUFFERING";
	else if (IS_BIT_SET(COPY_FILE_OPEN_SOURCE_FOR_WRITE, p_dw_flags))
		str_temp = L"COPY_FILE_OPEN_SOURCE_FOR_WRITE";
	else if (IS_BIT_SET(COPY_FILE_RESTARTABLE, p_dw_flags))
		str_temp = L"COPY_FILE_RESTARTABLE";
	else
		str_temp = std::to_wstring(p_dw_flags);
	return str_temp;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// wstr_get_extension ////////////////////////////////////////
wstring wstr_get_extension(wstring wstr_file_name)
{
	return wstr_file_name.substr(wstr_file_name.find_last_of(L".") + 1);
}
 HMODULE	hmod;
 TCHAR		t_char_dll_include[200] = { 0, };
 TCHAR		t_char_ex_include[200] = { 0, };
 /////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// my_create_file ////////////////////////////////////////
 HANDLE WINAPI my_create_file(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	USES_CONVERSION;

	wstring		str_share;
	wstring		str_flags;
	wstring		str_disposi;
	wstring		str_access;
	wstring		str_file_name;
	
	//g_wstr_file_ex = wstr_get_extension(lpFileName);//extension
	str_file_name = lpFileName;//full path
	str_access = check_access(dwDesiredAccess);
	str_share = check_share(dwShareMode);
	str_disposi = check_disposition(dwCreationDisposition);
	str_flags = check_flags(dwFlagsAndAttributes);

	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);

	g_tch_master_handle = g_pOriginFunc_C(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))// && !wcscmp(g_wstr_file_ex.c_str(), L"txt"))//최초 1회만 로드하게... global로 비교
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] Name:[%s] DLL:[%s] AC:[%s] SH:[%s] DIS:[%s] FLG&ATT:[%s]", g_tch_master_handle, __FUNCTIONW__, str_file_name.c_str(), PathFindFileName(t_char_dll_include), str_access.c_str(), str_share.c_str(), str_disposi.c_str(), str_flags.c_str());
		//MYDEBUG(L"g_wstr_file_ex : [%s]", g_wstr_file_ex.c_str());
	}
	return g_tch_master_handle;
}

//////////////////////////////////////// my_create_fileA ////////////////////////////////////////
 HANDLE WINAPI my_create_fileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	USES_CONVERSION;

	//string		str_tt;
	wstring		str_share;
	wstring		str_flags;
	wstring		str_disposi;
	wstring		str_access;
	wstring		str_file_name;

	//g_wstr_file_ex = wstr_get_extension(A2W(lpFileName));//extension
	str_file_name = A2W(lpFileName);//full path
	str_access = check_access(dwDesiredAccess);
	str_share = check_share(dwShareMode);
	str_disposi = check_disposition(dwCreationDisposition);
	str_flags = check_flags(dwFlagsAndAttributes);

	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);

	g_tch_master_handle = g_pOriginFunc_CA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] Name:[%s] DLL:[%s] AC:[%s] SH:[%s] DIS:[%s] FLG&ATT:[%s]", g_tch_master_handle, __FUNCTIONW__, str_file_name.c_str(), PathFindFileName(t_char_dll_include), str_access.c_str(), str_share.c_str(), str_disposi.c_str(), str_flags.c_str());
		//MYDEBUG(L"g_wstr_file_ex : [%s]", g_wstr_file_ex.c_str());
	}
	return g_tch_master_handle;
}

//////////////////////////////////////// my_read_file ////////////////////////////////////////
 BOOL WINAPI my_read_file(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
	BOOL bIsOk = g_pOriginFunc_R(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
	if (!bIsOk)
		return FALSE;
	else{
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
		GetModuleFileName(hmod, t_char_dll_include, 200);

		if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
		{
			MYDEBUG(L"☆HDL:[%p] FN:[%s] BTR[%u] BR[%u] OVR[%d]", hFile, __FUNCTIONW__, nNumberOfBytesToRead, *lpNumberOfBytesRead, lpOverlapped);
		}
		return bIsOk;
	}
}

//////////////////////////////////////// my_read_fileEx ////////////////////////////////////////
 BOOL WINAPI my_read_fileEx(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	BOOL bIsOk = g_pOriginFunc_RX(hFile, lpBuffer, nNumberOfBytesToRead, lpOverlapped, lpCompletionRoutine);
	if (!bIsOk)
		return FALSE;
	else{
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
		GetModuleFileName(hmod, t_char_dll_include, 200);

		if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
		{
			MYDEBUG(L"☆HDL:[%p] FN:[%s] BTR[%d] OVR[%d]", hFile, __FUNCTIONW__, nNumberOfBytesToRead, lpOverlapped);
		}
		return bIsOk;
	}
}
 
 //////////////////////////////////////// my_write_file ////////////////////////////////////////
 BOOL WINAPI my_write_file(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	BOOL bIsOk = g_pOriginFunc_W(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] BTW[%d] BW[%d] OVR[%d]", hFile, __FUNCTIONW__, nNumberOfBytesToWrite, *lpNumberOfBytesWritten, lpOverlapped);
	}
	return bIsOk;
}

//////////////////////////////////////// my_write_fileEx ////////////////////////////////////////
BOOL WINAPI my_write_fileEx(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	BOOL bIsOk = g_pOriginFunc_WX(hFile, lpBuffer, nNumberOfBytesToWrite, lpOverlapped, lpCompletionRoutine);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] BTW[%d] OVR[%d]", hFile, __FUNCTIONW__, nNumberOfBytesToWrite, lpOverlapped);
	}
	return bIsOk;
}

//////////////////////////////////////// my_close_handle ////////////////////////////////////////
BOOL WINAPI my_close_handle(HANDLE hObject)
{
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hObject)
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s]", hObject, __FUNCTIONW__);
	}
	return g_pOriginFunc_Cl(hObject);
}

//////////////////////////////////////// count_print_page ////////////////////////////////////////
 int n_count_page = 0;
//////////////////////////////////////// my_start_doc ////////////////////////////////////////
 //_return address 모듈명으로 구분하기.
int WINAPI my_start_doc(HDC hdc, const DOCINFOW *lpdi)
{
	int nIsOk = ((PFNStartDoc)g_pOriginFunc_D)(hdc, lpdi);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	MYDEBUG(L"☆HDL:[%p] DLL:[%s] ☆FN:[%s]  DOC_NAME:[%s]", hdc, PathFindFileName(t_char_dll_include), __FUNCTIONW__, PathFindFileName(lpdi->lpszDocName));
	//if{
	//return ((PFNStartDoc)g_pOriginFunc_D)(hdc, lpdi); // -> original return function...
	return nIsOk;
}
//////////////////////////////////////// my_start_doca ////////////////////////////////////////
int WINAPI my_start_doca(HDC hdc, const DOCINFOA *lpdi)
{
	USES_CONVERSION;
	int n_IsOk = g_pOriginFunc_DA(hdc, lpdi);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s]  DOC_NAME:[%s]", hdc, __FUNCTIONW__, PathFindFileName(t_char_dll_include), PathFindFileName(A2W(lpdi->lpszDocName)));
	}
	return n_IsOk;
}
//////////////////////////////////////// my_start_page ////////////////////////////////////////
int WINAPI my_start_page(HDC hdc)
{
	int nIsOk = g_pOriginFunc_ST(hdc);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s]", hdc, __FUNCTIONW__, PathFindFileName(t_char_dll_include));
	return nIsOk;
	//return 0;
}

//////////////////////////////////////// my_end_page ////////////////////////////////////////
int WINAPI my_end_page(HDC hdc)
{
	int nIsOk = g_pOriginFunc_END(hdc);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s]", hdc, __FUNCTIONW__, PathFindFileName(t_char_dll_include));
	n_count_page++;
	return nIsOk;
}

//////////////////////////////////////// my_end_doc ////////////////////////////////////////
int WINAPI my_end_doc(HDC hdc)
{
	int nIsOk = g_pOriginFunc_ED(hdc);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s] PAGES:(%d)", hdc, __FUNCTIONW__, PathFindFileName(t_char_dll_include), n_count_page);
	//MYDEBUG(L"☆HDL:[%p] DLL:[%s] FN:[%s]  Pages : (%d)", hdc, PathFindFileName(t_char_dll_include), __FUNCTIONW__, n_count_page);
	n_count_page = 0;
	return nIsOk;
}

//////////////////////////////////////// 2020-01-07 ////////////////////////////////////////
//////////////////////////////////////// my_set_file_pointer ////////////////////////////////////////
DWORD WINAPI my_set_file_pointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
{
	BOOL bIsOk = g_pOriginFunc_SP(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);

	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
	{

		wstring str_temp;
		str_temp = check_method(dwMoveMethod);
		MYDEBUG(L"☆HDL:[%p] FN:[%s] DToM:(%d)->DToMH:(%d) MoveMethod:[%s]", hFile, __FUNCTIONW__, lpDistanceToMoveHigh, lpDistanceToMoveHigh, str_temp);

	}
	return bIsOk;
}

//////////////////////////////////////// my_set_file_pointerEx ////////////////////////////////////////
BOOL WINAPI my_set_file_pointerEx(HANDLE hFile, LARGE_INTEGER  liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod)
{
	BOOL bIsOk = g_pOriginFunc_SPX(hFile, liDistanceToMove, lpNewFilePointer, dwMoveMethod);

	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);

	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
	{

		wstring str_temp;
		str_temp = check_method(dwMoveMethod);//위에서 정의를 하고
		MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s] DistanceToMove:(%lld) NewFilePointer:(%lld) MoveMethod:[%s])", hFile, __FUNCTIONW__, PathFindFileName(t_char_dll_include), liDistanceToMove.QuadPart, lpNewFilePointer->QuadPart, str_temp);

	}
	return bIsOk;
}

//////////////////////////////////////// my_get_file_size ////////////////////////////////////////
BOOL WINAPI my_get_file_size(HANDLE  hFile, LPDWORD lpFileSizeHigh)
{
	BOOL bIsOk = g_pOriginFunc_GFS(hFile, lpFileSizeHigh);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s] FileSizeHigh:(%p)", hFile, __FUNCTIONW__, PathFindFileName(t_char_dll_include), lpFileSizeHigh);
	}
	return bIsOk;
}

//////////////////////////////////////// my_get_file_sizeEx ////////////////////////////////////////
BOOL WINAPI my_get_file_sizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize)
{
	BOOL bIsOk = g_pOriginFunc_GFSX(hFile, lpFileSize);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp) && g_tch_master_handle == hFile)
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] DLL:[%s] FileSize:(%lld)", hFile, __FUNCTIONW__, PathFindFileName(t_char_dll_include), lpFileSize->QuadPart);
	}
	return bIsOk;
}

//////////////////////////////////////// my_move_file ////////////////////////////////////////
BOOL WINAPI my_move_file(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName)
{
	BOOL bIsOk = g_pOriginFunc_MF(lpExistingFileName, lpNewFileName);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	//GetModuleBaseName()
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		MYDEBUG(L"☆FN:[%s] DLL:[%s] ExFile[%s] NewFile[%s]", __FUNCTIONW__, PathFindFileName(t_char_dll_include), lpExistingFileName, lpNewFileName);
	}
	return bIsOk;
}

//////////////////////////////////////// my_move_fileEx ////////////////////////////////////////
BOOL WINAPI my_move_fileEx(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, DWORD dwFlags)
{
	BOOL bIsOk = g_pOriginFunc_MFX(lpExistingFileName, lpNewFileName, dwFlags);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		wstring str_temp;
		str_temp = check_dw_flags(dwFlags);
		MYDEBUG(L"☆FN:[%s] DLL:[%s] ExFile:[%s] NewFile:[%s] Flags:[%s]", __FUNCTIONW__, PathFindFileName(t_char_dll_include), lpExistingFileName, lpNewFileName, str_temp);
	}
	return bIsOk;
}

//////////////////////////////////////// my_copy_file ////////////////////////////////////////
BOOL WINAPI my_copy_file(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists)
{
	BOOL bIsOk = g_pOriginFunc_CF(lpExistingFileName, lpNewFileName, bFailIfExists);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		MYDEBUG(L"☆FN:[%s] DLL:[%s] ExFileName:[%s] NewFileName:[%s] FailEx:(%d)", __FUNCTIONW__, PathFindFileName(t_char_dll_include), lpExistingFileName, lpNewFileName, bFailIfExists);
	}
	return bIsOk;
}

//////////////////////////////////////// my_copy_fileEx ////////////////////////////////////////
BOOL WINAPI my_copy_fileEx(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags)
{
	BOOL bIsOk = g_pOriginFunc_CFX(lpExistingFileName, lpNewFileName, lpProgressRoutine, lpData, pbCancel, dwCopyFlags);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		wstring str_temp;
		str_temp = check_dw_copy_flags(dwCopyFlags);
		MYDEBUG(L"☆FN:[%s] DLL:[%s] ExfileName:[%s] NewFileName:[%s] Flags:[%s]", __FUNCTIONW__, PathFindFileName(t_char_dll_include), lpExistingFileName, lpNewFileName, str_temp);
	}
	return bIsOk;
}

//////////////////////////////////////// my_create_windowexa ////////////////////////////////////////
HWND WINAPI my_create_windowexa(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	
	HWND hw_IsOk = g_pOriginFunc_CWA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] Ex_S:(%d) C_Name:[%s] W_Name:[%s] Sty:(%d) X:(%d) Y:(%d) W:(%d) H:(%d) ", hw_IsOk,__FUNCTIONW__, dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight);
	}
	return hw_IsOk;
}
//////////////////////////////////////// my_create_windowexw ////////////////////////////////////////
HWND WINAPI my_create_windowexw(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	HWND hw_IsOk = g_pOriginFunc_CWW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	GetModuleFileName(hmod, t_char_dll_include, 200);
	if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	{
		MYDEBUG(L"☆HDL:[%p] FN:[%s] Ex_S:(%d) C_Name:[%s] W_Name:[%s] Sty:(%d) X:(%d) Y:(%d) Width:(%d) Height:(%d)", hw_IsOk,__FUNCTIONW__, dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight);
	}
	return hw_IsOk;
}
//////////////////////////////////////// my_create_dca ////////////////////////////////////////
HDC WINAPI my_create_dca(LPCSTR pwszDriver, LPCSTR pwszDevice, LPCSTR pszPort, const DEVMODEA *pdm)
{
	USES_CONVERSION;
	HDC h_IsOk = g_pOriginFunc_CDA(pwszDriver, pwszDevice, pszPort, pdm);
	//GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	//GetModuleFileName(hmod, t_char_dll_include, 200);
	//if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	//{
	MYDEBUG(L"☆FN:[%s] Drive:[%s] Device:[%s] Port:[%s]", __FUNCTIONW__, A2W(pwszDriver), A2W(pwszDevice), A2W(pszPort));
	//}
	return h_IsOk;
}
//////////////////////////////////////// my_create_dcw ////////////////////////////////////////
HDC WINAPI my_create_dcw(LPCWSTR pwszDriver, LPCWSTR pwszDevice, LPCWSTR pszPort, const DEVMODEW *pdm)
{
	HDC h_IsOk = g_pOriginFunc_CDW(pwszDriver, pwszDevice, pszPort, pdm);
	//GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)_ReturnAddress(), &hmod);
	//GetModuleFileName(hmod, t_char_dll_include, 200);
	//if (is_support_dll(PathFindFileName(t_char_dll_include), g_T_temp))
	//{
	MYDEBUG(L"☆FN:[%s] Drive:[%s] Device:[%s] Port:[%s]", __FUNCTIONW__, pwszDriver, pwszDevice, pszPort);
	//}
	return h_IsOk;
}

//////////////////////////////////////// function detour start ////////////////////////////////////////
void detour_attach()
{
	USES_CONVERSION;
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// 레지스트리 사용시 형태
	//if (key.Open(HKEY_CURRENT_USER, L"SOFTWARE\\HookingTool") == ERROR_SUCCESS)
	//{
	//	if (key.QueryDWORDValue(L"CreateFileA", dw_dbg_val) == ERROR_SUCCESS)
	//	{
	//		if (dw_dbg_val == 1)
	//		{
	//			//g_pOriginFunc_CA = (PFNCreateFileA)CreateFileA;
	//			DetourAttach(&(PVOID&)g_pOriginFunc_CA, my_create_fileA);
	//			//Change_iat("kernel32.dll", (PROC)g_pOriginFunc_CA, (PROC)my_create_fileA);
	//		}
	//	}
	//}

	//ini 파일 사용시
	TCHAR T_temp1[50];
	memset(T_temp1, 0x00, sizeof(T_temp1));
	GetPrivateProfileString(L"API", L"CREATE_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
	{
		//g_pOriginFunc_C = (PFNCreateFile)CreateFile;
		DetourAttach(&(PVOID&)g_pOriginFunc_C, my_create_file);
		//Change_iat("kernel32.dll", (PROC)g_pOriginFunc_C, (PROC)my_create_file);
	}
	GetPrivateProfileString(L"API", L"CREATE_FILEA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CA, my_create_fileA);

	GetPrivateProfileString(L"API", L"READ_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_R, my_read_file);

	GetPrivateProfileString(L"API", L"READ_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_RX, my_read_fileEx);

	GetPrivateProfileString(L"API", L"WRITE_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_W, my_write_file);

	GetPrivateProfileString(L"API", L"WRITE_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_WX, my_write_fileEx);

	GetPrivateProfileString(L"API", L"CLOSE_HANDLE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_Cl, my_close_handle);

	GetPrivateProfileString(L"API", L"START_DOC", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_D, my_start_doc);

	GetPrivateProfileString(L"API", L"START_PAGE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_ST, my_start_page);

	GetPrivateProfileString(L"API", L"END_PAGE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_END, my_end_page);

	GetPrivateProfileString(L"API", L"END_DOC", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_ED, my_end_doc);

	//2020-01-07
	GetPrivateProfileString(L"API", L"SET_FILE_POINTER", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_SP, my_set_file_pointer);

	GetPrivateProfileString(L"API", L"SET_FILE_POINTEREX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_SPX, my_set_file_pointerEx);

	GetPrivateProfileString(L"API", L"GET_FILE_SIZE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_GFS, my_get_file_size);

	GetPrivateProfileString(L"API", L"GET_FILE_SIZEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_GFSX, my_get_file_sizeEx);

	GetPrivateProfileString(L"API", L"MOVE_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_MF, my_move_file);

	GetPrivateProfileString(L"API", L"MOVE_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_MFX, my_move_fileEx);


	GetPrivateProfileString(L"API", L"COPY_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CF, my_copy_file);

	GetPrivateProfileString(L"API", L"COPY_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CFX, my_copy_fileEx);
	//2020-01-10
	GetPrivateProfileString(L"API", L"START_DOCA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_DA, my_start_doca);

	GetPrivateProfileString(L"API", L"CRATE_WINDOWEXW", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CWW, my_create_windowexw);
	GetPrivateProfileString(L"API", L"CRATE_WINDOWEXA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CWA, my_create_windowexa);

	GetPrivateProfileString(L"API", L"CREATE_DC", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CDW, my_create_dcw);
	GetPrivateProfileString(L"API", L"CREATE_DCA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourAttach(&(PVOID&)g_pOriginFunc_CDA, my_create_dca);

	memset(T_temp1, 0x00, sizeof(T_temp1));
	////

	DetourTransactionCommit();
	//error = DetourTransactionCommit();
	//if (error == NO_ERROR) {
	//	MYDEBUG(L"NO_ERROR");
	//}
	//else {
	//	MYDEBUG(L"simple %s.dll: Detoured SleepEx().: %d\n", A2W(DETOURS_STRINGIFY(DETOURS_BITS)), error);
	//}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// function detour stop ////////////////////////////////////////
void detour_detach()
{
	USES_CONVERSION;
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	//using registry
	// if (key.Open(HKEY_CURRENT_USER, L"SOFTWARE\\HookingTool") == ERROR_SUCCESS)
	// {
	//	 if (key.QueryDWORDValue(L"CreateFile", dw_dbg_val) == ERROR_SUCCESS)
	//	 {
	//		 if (dw_dbg_val == 1)
	//		 {
	//			 DetourDetach(&(PVOID&)g_pOriginFunc_C, my_create_file);
	//			 //if want iat hooking use below
	//			 //Change_iat("kernel32.dll", (PROC)my_create_file, (PROC)g_pOriginFunc_C);
	//		 }
	//	 }
	// }
	TCHAR T_temp1[50];
	memset(T_temp1, 0x00, sizeof(T_temp1));
	GetPrivateProfileString(L"API", L"CREATE_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
	{
		//g_pOriginFunc_C = (PFNCreateFile)CreateFile;
		DetourDetach(&(PVOID&)g_pOriginFunc_C, my_create_file);
		//Change_iat("kernel32.dll", (PROC)g_pOriginFunc_C, (PROC)my_create_file);
	}
	GetPrivateProfileString(L"API", L"CREATE_FILEA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CA, my_create_fileA);

	GetPrivateProfileString(L"API", L"READ_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_R, my_read_file);

	GetPrivateProfileString(L"API", L"READ_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_RX, my_read_fileEx);

	GetPrivateProfileString(L"API", L"WRITE_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_W, my_write_file);

	GetPrivateProfileString(L"API", L"WRITE_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_WX, my_write_fileEx);

	GetPrivateProfileString(L"API", L"CLOSE_HANDLE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_Cl, my_close_handle);

	GetPrivateProfileString(L"API", L"START_DOC", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_D, my_start_doc);

	GetPrivateProfileString(L"API", L"START_PAGE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_ST, my_start_page);

	GetPrivateProfileString(L"API", L"END_PAGE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_END, my_end_page);

	GetPrivateProfileString(L"API", L"END_DOC", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_ED, my_end_doc);

	//2020-01-07
	GetPrivateProfileString(L"API", L"SET_FILE_POINTER", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_SP, my_set_file_pointer);

	GetPrivateProfileString(L"API", L"SET_FILE_POINTEREX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_SPX, my_set_file_pointerEx);

	GetPrivateProfileString(L"API", L"GET_FILE_SIZE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_GFS, my_get_file_size);

	GetPrivateProfileString(L"API", L"GET_FILE_SIZEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_GFSX, my_get_file_sizeEx);

	GetPrivateProfileString(L"API", L"MOVE_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_MF, my_move_file);

	GetPrivateProfileString(L"API", L"MOVE_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_MFX, my_move_fileEx);

	GetPrivateProfileString(L"API", L"COPY_FILE", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CF, my_copy_file);

	GetPrivateProfileString(L"API", L"COPY_FILEEX", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CFX, my_copy_fileEx);
	//2020-01-10
	GetPrivateProfileString(L"API", L"START_DOCA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_DA, my_start_doca);

	GetPrivateProfileString(L"API", L"CRATE_WINDOWEXW", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CWW, my_create_windowexw);
	GetPrivateProfileString(L"API", L"CRATE_WINDOWEXA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CWA, my_create_windowexa);

	GetPrivateProfileString(L"API", L"CREATE_DC", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CDW, my_create_dcw);
	GetPrivateProfileString(L"API", L"CREATE_DCA", L"-", T_temp1, 50, L"C:\\ESD\\test.ini");
	if (!_tcscmp(T_temp1, L"True"))
		DetourDetach(&(PVOID&)g_pOriginFunc_CDA, my_create_dca);

	memset(T_temp1, 0x00, sizeof(T_temp1));
	//
	//key.Close();
	DetourTransactionCommit();
	//error = DetourTransactionCommit();
	//if (error == NO_ERROR) {
	//	MYDEBUG(L"NO_ERROR");
	//}
	//else {
	//	MYDEBUG(L"simple %s.dll: Detoured SleepEx().: %d\n", A2W(DETOURS_STRINGIFY(DETOURS_BITS)), error);
	//}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////// MAIN ////////////////////////////////////////////////
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

	(void)hModule;
	(void)lpReserved;

	if (DetourIsHelperProcess()) {
		return TRUE;
	}
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//ini 체크
		MYDEBUG(L"DLL_ATTACH");
		GetPrivateProfileString(L"DLLS", L"DLL_NAME", L"-", g_T_temp, 200, L"C:\\ESD\\hooking_init.ini");
		GetPrivateProfileString(L"EXTENS", L"EX_LIST", L"-", g_wstr_file_ex, 200, L"C:\\ESD\\hooking_init.ini");
		detour_attach();
		break;
	case DLL_PROCESS_DETACH:
		MYDEBUG(L"DLL_DETACH");
		detour_detach();
		break;
	}
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

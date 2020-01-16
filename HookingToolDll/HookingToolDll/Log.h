#pragma once

extern LPCWSTR szModuleTag; //어플리케이션에서 개별적으로 해당 태그 내용을 정의 하기위해 extern
extern BOOL g_bDebugOut;

#define IS_BIT_SET(bFlag,b) (((bFlag)&(b))==(bFlag))

////////////////////////// to view debug logs //////////////////////////
#define __FILENAMEW__ (wcsrchr(__FILEW__, L'\\') ? wcsrchr(__FILEW__, L'\\') + 1 : __FILEW__)

#define LogW(format, ...)	\
		{ \
		if(g_bDebugOut) \
				{ \
			  const size_t max_format_message = 2048; \
			wchar_t message[max_format_message] = { 0 }; \
			wchar_t output[max_format_message] = { 0 }; \
			if (swprintf_s(message, format, __VA_ARGS__) > 0)	\
						{	\
				if (swprintf_s(output, L"%s %s___<%s::%d>", szModuleTag, message, __FILENAMEW__, __LINE__) > 0 ) \
								{ \
					OutputDebugStringW(output); \
								} \
								else OutputDebugStringW( L">>> dbg_format failure");	\
						}	\
						else OutputDebugStringW( L">>> dbg_format failure");	\
				} \
		}
#define MYDEBUG(fmt, ...)		{ if(g_bDebugOut) LogW(fmt, __VA_ARGS__) }		// debug 보다 상세한 정보를 표시하는 메시지
//////////////////////////////////////////////////////////////////////////////

//  void LOG(const WCHAR *format, ...)
//{
////try - catch 로 예외처리를 하는 것이 좋음...!
//	USES_CONVERSION;
//	if (check_Bit() == 0)
//		return;
//	if (check_Bit() == 1)
//	{
//		try
//		{
//			WCHAR buf[1024];
//			va_list vaList;
//
//			va_start(vaList, format);
//			_vsnwprintf_s(buf, sizeof(buf), format, vaList);
//			va_end(vaList);
//
//			OutputDebugStringW(buf);    // 따로 빼서 함수로 만드는게 깔끔할듯
//			return;
//		}
//		catch (int exceptionCode)
//		{
//			CString str_error;
//			str_error.Format(L"%d", exceptionCode);
//			OutputDebugStringW(str_error);
//		}
//	}
//	if (check_Bit() == 2)
//	{
//		try
//		{
//			WCHAR buf[1024];
//			va_list vaList;
//			ofstream outFile("C:\\ESD\\log.txt", ios_base::out | ios_base::app);
//			CString str_log;
//			LPCWSTR lpc_str;
//			va_start(vaList, format);
//			_vsnwprintf_s(buf, sizeof(buf), format, vaList);
//			va_end(vaList);
//			lpc_str = buf;
//			str_log.Format(L"%s", format);
//			outFile << W2A(lpc_str) << endl;
//			outFile.close();
//		}
//		catch (int exceptionCode)
//		{
//			CString str_error;
//			str_error.Format(L"ERR : %d", exceptionCode);
//			OutputDebugStringW(str_error);
//		}
//	}
//}

#include <Windows.h>

#include <format>
#include <string>
#include <string_view>

#include <vector>
#include <array>

#include <unordered_map>

using namespace std;

class win_logical_drives {
/*
	DWORD GetLogicalDriveStringsW(
		[in]  DWORD  nBufferLength,
		[out] LPWSTR lpBuffer
	);
*/
	DWORD LEN; LPWSTR BUF;
	DWORD logical_drive_str;
};
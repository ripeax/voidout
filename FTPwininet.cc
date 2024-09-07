#include <Windows.h>
#include <wininet.h>

#include <iostream>
#include <array>
#include <vector>


#include "cmdline_base.h"

using namespace std;


class FTP {
//HANDLE
	HINTERNET net_handle;	

// OPEN
	LPCSTR	instance_name = "FTP-WIN";
	DWORD	access_type = INTERNET_OPEN_TYPE_DIRECT;
	LPCSTR	proxy		= NULL;
	LPCSTR	proxy_bypass = NULL;
	DWORD	op_flag = INTERNET_FLAG_OFFLINE;

// CONNECT
	LPCSTR  host_serv_name;
	INTERNET_PORT host_port = INTERNET_DEFAULT_FTP_PORT;
	LPCSTR username = NULL;
	LPCSTR user_pswd = NULL;
	DWORD service = INTERNET_SERVICE_FTP;
	DWORD host_flag = INTERNET_FLAG_PASSIVE;
	DWORD_PTR  context;

public:

	FTP() {
		if (start_serv() == false) {
			line_ err("[FTP]", "- Error :", "server didn't start correctly");
			err.display();
		}
			
		do {
			// ...
		} while (true);
		if (close_serv() == false) {
			line_ err("[FTP]", "- Error :", "server didn't close correctly");
			err.display();
		}
	}

private:
	bool start_serv() {
		net_handle = InternetOpenA(
			instance_name,
			access_type,
			proxy,
			proxy_bypass,
			op_flag
		);
		if (net_handle == NULL) {
			line_ console("[FTP]", "- FAILED :", "InternetOpenA");
			console.display();
			return false;
		}
		else {
			line_ console("[FTP]", "- PROCESS : ", "InternetOpenA");
			console.display();
			return true;
		}
	}

	bool start_host_connection() {
		if (InternetConnectA(
			net_handle,
			host_serv_name,
			host_port,
			username,
			user_pswd,
			service,
			host_flag,
			context
		)) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool close_serv() {
		if (InternetCloseHandle(net_handle)) {
			line_ console("[FTP]", "- Closing :", "InternetCloseHandle");
			console.display();
			return true;
		}
		else {
			line_ console("[FTP]", "- FAILED :", "InternetCloseHandle");
			console.display();
			return false;
		}
	}
};
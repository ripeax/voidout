#pragma once
#include <queue>
#include <unordered_map>
#include <array>

#include "winsockHandler.cc"

#define SeqBlockSz 10

using namespace std;

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

//winsock implementation
class winNetHandler;

template <typename MSG> 
class MsgSequenceAdapter;

template <typename MSG>
class ServerModel : private winNetHandler
{
	unordered_map<MSG, MSG> u_netmap;
public:
	ServerModel() {
		MsgSequenceAdapter<MSG> uSeqAdapter(u_netmap);
	}



};

template <typename MSG> 
class MsgSequenceAdapter {
private:
	queue<MSG> Seq;
	unordered_map<MSG, MSG> _map;

public:
	MsgSequenceAdapter(unordered_map<MSG, MSG> &adaptedMap) : _map(adaptedMap) {}
	void setMap(unordered_map<MSG, MSG> &um) {
		_map = um;
	}
	
private:
	bool AdaptByKeyRange_MapToSeq(array<MSG, SeqBlockSz>) {

	}
	bool AdaptAllKeys_MapToSeq() {
		if (_map.empty()) {
			return false;
		}
		if (!Seq.empty()) {
			//Seq.clear();
		}
		auto get_map_elem = [](const auto& k, const auto& dat)
			{
				return dat;
			};
		for (const pair<const MSG, const MSG>& n : _map) {
			Seq.push(get_map_elem(n.first, n.second));
		}
		return true;
	}
	bool ComposeBatchFromSeq(MSG batch) {
		if (Seq.empty()) {
			return false;
		}
		if (!batch.empty()) {
			batch.clear();
		}
		MSG buf;
		while (!Seq.empty()) {
			buf = Seq.front();
			batch.append(buf);

			Seq.pop();
			buf.clear();
		}
		return true;
	}
};

#include <format>
#include <vector>

class winNetHandler {

	enum netstat {
		fx_fail = 0, fx_success = 1,
		RECV, TRVC
	};
	struct netsock_obj {
		WSADATA wsaData;
		int wsa_ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	}netval;

	vector<char> TRCVbuf, RECVbuf;

	int instate() {

		int& res = netval.wsa_ret;

		if (netval.wsa_ret != fx_fail) {
			printf("WSAStartup failed: %d\n", res);
		}
	}
	
};

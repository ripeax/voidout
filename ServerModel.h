#pragma once
#include <queue>
#include <unordered_map>
#include <array>

#include "winsockHandler.cc"

#define _SeqBlockLen 10
#define _DatBatchSize 16
#define _DatagramDm DatBatchSz*8

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
template <typename P>
class NetPrimitiveOperant {
private:
	P n, m, res;
public:
	NetPrimitiveOperant(P x, P y) : n(x), m(y) {}
	NetPrimitiveOperant operator+(NetPrimitiveOperant const& complex) {
		NetPrimitiveOperant compound;
		compound.n = n + complex.m;
		compound.m = m + complex.n;
		res = compound;
		return compound;
	}
	void showResulant() { cout << format(" [NET<DBG>] {} \n ", res); }
};

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

	bool Sync_SendBatch();
	bool Sync_RecvBatch();
	bool Async_SendBatch() { return true; };
	bool Async_RecvBatch() { return true; };
protected:
	const short BatchSize = _DatBatchSize;
	const int DatagramDimension = _DatagramDm;
	short mut_BatchSz = BatchSize;
	int mut_DatagramDm = DatagramDimension;

	vector<MSG> pax;
};

template <typename MSG>
bool ServerModel<MSG>::Sync_SendBatch(){
	using proto_win_comms{
		bool temp_packet_itel = true;
		
	while (temp_packet_itel) {
		if (Seq.empty()) {
			break;
			}
		// win_send_chunk(pax);
		Seq.pop();
		}
		return true;
	}
}
template <typename MSG>
bool ServerModel<MSG>::Sync_RecvBatch() {
	using proto_win_comms{
		// pax = win_recv_chunk();
		return win_get_chunk();
	}
}

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
		fx_fail = 0, fx_done = 1,
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
		return fx_done;
	}
public: class proto_net_comms {
		bool win_send_chunk() {
			return true;
		}
		bool win_get_chunk() {
			return true;
		}

		bool win_trcv() {
			if (win_send_chunk) {
				return true;
			}
			else {
				return false;
			}
		}
	};
	
};

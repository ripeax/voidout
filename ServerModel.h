#pragma once
#include <queue>
#include <unordered_map>
#include <array>

#define SeqBlockSz 10

using namespace std;

template <typename MSG> 
class MsgSequenceAdapter;

template <typename MSG>
class ServerModel
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



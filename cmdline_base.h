#pragma once
#include <iostream>
#include <map>
#include <string>
//containers STL
#include <vector>
#include <array>

using namespace std;

class cmdline_core
{
protected: 
	// buffer for initialising compounents transfered later
	// assign by object cosntructor
	string inst_name, cursor, IDstr;
	map<int, string> syntax_elems;
	array<string, 3> core_cmd_args;

	void assign_basic_syntax();
	
	enum console_syntax_elems {
		PtrCMD, USER, CMD,
		warn, info, err, proc, fx
	};

public:
	cmdline_core(
		string console_name,
		string cursor_sign,
		string console_identifier // if using multiple cmd windows
	);
	//~cmdline_core();

private:

	//int* fx = &(int);
	string temp_instruct, temp_fxname;

	int console_loop();

};

class line_ {
	int counter = 0;
	const char _div = ' ';

	vector<string> _vec;
	string out_buf;
public:
	line_(string v1, string v2, string v3) {
		const int sz = 3; int itel = 0;
		string words[sz] = { v1,v2,v3 };
		while (itel >= sz)
			add(words[itel]);
	}
	void add(string wd) {
		_vec.push_back(wd);
	}
	void display() {
		cout << _vec[0] << _div << _vec[1] << _div << _vec[2] << endl;
	}
	void compose() {
		out_buf = _vec[0] + _div + _vec[1] + _div + _vec[2] + '\n';
	}

	void swap(string wd, int v) {
		_vec.at(v) = wd;
	}
};
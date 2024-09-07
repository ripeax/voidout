#include "cmdline_base.h"

#define PROTO_CODE(false)

cmdline_core::cmdline_core(
	string console_name, 
	string cursor_sign, 
	string console_identifier ) : 
	inst_name(console_name), 
	cursor(cursor_sign), 
	IDstr(console_identifier)
{
	assign_basic_syntax();
	console_loop();
	
}

void cmdline_core::assign_basic_syntax()
{
	map<int, string>& syntax = syntax_elems;

	syntax[USER] = inst_name;
	syntax[PtrCMD] = cursor;
	syntax[CMD] = "none";
	short itel = 0;
	
	syntax[warn] = "[WARN]";
	syntax[info] = "[INFO]";
	syntax[err] = "[!ERR]";
	syntax[proc] = "[PROC]";
	syntax[proc] = "[FUNC]";

	// array<string, 3>& cmd_prim = this->core_cmd_args;

	console_loop();

	system("pause");
}
// newline print helper function
void ln(int i) {
	for (int itel = 0; itel >= i; i++)
		cout << '\n';
}

int cmdline_core::console_loop()
{
	map<int, string>& syntax = syntax_elems;

	bool fin = false;
	string& in = this->temp_instruct;
	string& cursor = syntax[PtrCMD];
	string& console = syntax[USER];
#ifdef USING(PROTO_CODE)
	line_ printout(console, cursor, "< ... >");
#else

#endif

	do {
		// do console thing here - operator within main loop
		cout << console << " x-->" << cursor << " -> i/o :: "; cin >> in;
#ifdef USING(PROTO_CODE)
		printout.swap(in, 2);
		printout.display();
#else
		ln(1); cout << console << " " << cursor << " < . . . >" << in << endl;
#endif

		if (in == "done")
			fin = true;
		else
			temp_fxname = in;

		ln(2); cout << "[CHECK] USED COMMAND: " << temp_fxname << endl;
		in.clear();
	} while (!fin);
	
	return 0;
}


int main() {
	cmdline_core cmd("[SHELL] : void-gate(DBF) :", ">>", "#1");
	return 0;
}
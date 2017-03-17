#include <iostream>
#include <string>
#include <fstream>
#include <map>

class System {
public:
	static System *GetInstance(); 
	~System() {Log.close();}; 
	void Run();
private:
	typedef void (System::*operation)();
	typedef std::map<std::string, int> node;

	bool delete_goods(std::string, int);
	void show_goods(std::ostream&);
	void readName(std::string &);
	void readCount(int &);
	void WriteToLog(int, std::string &, int, int);
	void WriteToLog(int, std::string &, int);
	void WriteToLog(int, int);

	void Halt();
	void Add();
	void Delete();
	void Query();
	void Stats();
	void Save();

	System();
	void handle();
	
	std::ofstream Log;
	const std::string mainMenu =
    "======== MENU ========\n"
    "0) Exit\n"
    "1) Add\n"
    "2) Delete\n"
    "3) Query\n"
    "4) Stats\n"
    "5) Save\n";
    const int cntMenu = 6;
    int choice = -1;
	operation op[6] = {Halt, Add, Delete, Query, Stats, Save};
	std::string OP[6] = {"Exit", "Add", "Delete", "Query", "Stats", "Save"};
	std::string result[2] = {"Fail", "Success"};
	node goods;
	int tot = 0;
};

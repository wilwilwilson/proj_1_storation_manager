#include "System.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>

bool System::delete_goods(std::string name, int count) {
	if(goods[name] < count) return false;
	goods[name] -= count;
	if(goods[name] == 0) {
		goods.erase(name);
		--tot;
	}
	return true;
}

void System::show_goods(std::ostream &out) {
	for(auto &i: goods)
		out << i.first
			<<"\t"
			<< i.second
			<< std::endl;
}

void System::readName(std::string &name) {
	std::cout << "Enter the name: ";
	std::cin >> name;
}

void System::readCount(int &count) {
	std::cout << "Enter the count: ";
	std::cin >> count;
}

void System::WriteToLog(int op, std::string &name, int count, int res) {
	Log << OP[op]
		<< "\t"
		<< name
		<< "\t"
		<< count
		<< "\t"
		<< result[res]
		<< std::endl;
}

void System::WriteToLog(int op, std::string &name, int res) {
	Log << OP[op]
		<< "\t"
		<< name
		<< "\t"
		<< result[res]
		<< std::endl;
}

void System::WriteToLog(int op, int res) {
		Log << OP[op]
			<< "\t"
			<< result[res]
			<< std::endl;
}

void System::Halt() {
	Save();
	WriteToLog(0, 1);
	getchar();
	getchar();
	exit(0);
}

void System::Add() {
	std::string name;
	readName(name);
	int count;
	readCount(count);
	std::cout << std::endl;
	if(goods.count(name) == 0) ++tot;
	goods[name] += count;
	std::cout << "Done.\n\n";
	WriteToLog(1, name, count, 1);
}

void System::Delete() {
	std::string name;
	readName(name);
	int count;
	readCount(count);
	std::cout << std::endl;
	if(!delete_goods(name, count)) {
		std::cout << "Error!\nPlease check your input.\n\n";
		WriteToLog(2, name, count, 0);
	}
	else {
		std::cout << "Done.\n\n";
		WriteToLog(2, name, count, 1);
	}
}

void System::Query() {
	std::string name;
	readName(name);
	std::cout << std::endl;
	int cnt = goods.count(name);
	if(!cnt)
		std::cout << "No such Goods!\n\n";
	else
		std::cout << "Inventory: "
				  << goods[name]
				  << "\n\n";
	WriteToLog(3, name, 1);
}

void System::Stats() {
	if(tot == 0)
		std::cout << "The storehouse is Empty!\n";
	else
		std::cout << "There are "
				  << tot
				  << " kinds of goods.\n\n"
				  << "Name\tInventory\n\n";
	show_goods(std::cout);
	WriteToLog(4, 1);
}

void System::Save() {
	std::ofstream Inv("Inventory.log");
	show_goods(Inv);
	std::cout <<"Save the inventory successfully.\n";
}

System::System() {
	std::ifstream load("Inventory.log");
	if(!load.is_open()) {
		std::cout << "No inventory record!\n\n";
	}
	else {
		std::string name;
		int count;
		while(load >> name >> count) {
			if(goods.count(name) == 0) ++tot;
			goods[name] += count;
		}
		load.close();
		std::cout << "Successfully loading the inventory record.\n\n";
	}
	Log.open("Operation.log", std::ios::app);
}

void System::handle() {
	choice = -1;
	std::cout << mainMenu;
	do {
		std::cout << "Choose what to do(0 ~ "
			 	  << cntMenu - 1
			 	  << "): ";
		std::cin >> choice;
		if(choice < 0 || choice >= cntMenu)
			std::cout << "Illegal operation!\n\n";
	} while(choice < 0 || choice >= cntMenu);
	std::cout << std::endl;
	(*this.*op[choice])();
}

void System::Run() {
	while(1) handle();
}

System *System::GetInstance() {
	static System *m_pInstance;
    if (m_pInstance == NULL)    
    	m_pInstance = new System();  
    	return m_pInstance;  
}
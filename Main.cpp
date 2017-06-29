/*
 * Main.cpp
 *
 *  Created on: Jun 20, 2017
 *      Author: jrsti
 */

#include "csvstream.h"
#include <cstdlib>
#include <map>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

/*
 * JARET STILLMAN
 * jrsstill@umich.edu
 * Solution for CSV Investment File
 * Talent Tech Labs
 */

bool contains(vector<string> &vec, string &s);
void print_map(map<string,pair<int,vector<string>>> &map, vector<string> &keys);
void parse();

int main()
{
	parse();
}

struct Company
{
	double funding;
	string subvertical;
	string city;
	string date_founded;
};

//Parses CSV File and transforms it into a std::map
void parse()
{
	map<string,Company*> m;
	try
	{
		csvstream csv("merge.csv");
		map<string,string> row;
		vector<string> keys;
		string company;
		Company *c;
		while(csv>>row)
		{
			//Company
			company=row["COMPANY"];

			//Check if company is in map already
			if(!contains(keys,company))
			{
				c=new Company;
				//Subvertical
				*c->subvertical=row["SUBVERTICAL"];
				//City
				*c->city=row["CITY"];
				//Date founded
				*c->date_founded=row["FOUNDED"];
				row["COMPANY"]=c;
			}
			else
			{
				c=row["COMPANY"];
			}
			//Add funding to total funding

			c->funding+=atoi(row["FUNDING"].c_str());
		}
	}
	catch (csvstream_exception &e)
	{
		cout<<e.msg<<endl;
		exit(0);
	}

	for(auto s: m)
	{
		delete m[s];
	}
}

//Checks whether a vector contains a certain string
bool contains(vector<string> &vec, string &s)
{
	for(auto str: vec)
	{
		if(str==s)
		{
			return true;
		}
	}
	return false;
}

//Prints list of investors, num times invested, and companies invested in
//In column format so that it can be easily copies into a spreadsheet
void print_map(map<string,pair<int,vector<string>>> &m, vector<string> &keys)
{
	//INVESTORS
	for(auto st: keys)
	{
		cout<<st<<endl;
	}
	cout<<endl<<endl;

	//# TIMES INVESTED
	for(auto st: keys)
	{
		cout<<m[st].first<<endl;
	}
	cout<<endl<<endl;

	//COMPANIES INVESTED IN
	for(auto st: keys)
	{
		for(auto c: m[st].second)
		{
			cout<<c<<" , ";
		}
		cout<<endl;
	}
}







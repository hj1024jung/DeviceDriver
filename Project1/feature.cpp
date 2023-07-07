#include <iostream>
#include <string>

using namespace std;

class Cal
{
public:
	int sum(int a, int b) { return a + b; }
	int getVal() { return -1; }
};

struct DBAPI
{
	virtual string getDBName() = 0;
};

class DatabaseAPI : public DBAPI
{
public:
	virtual string getDBName()
	{
		return"HIHI";
	}
};

class LogSystem
{
public:
	explicit LogSystem(DBAPI* db)
		:DB(db){}

	string getLogMsg()
	{
		return string("[") + DB->getDBName() + string("]");
	}
private:
	DBAPI* DB;
};
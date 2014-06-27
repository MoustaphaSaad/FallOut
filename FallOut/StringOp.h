#ifndef STRINGOP_H_
#define STRINGOP_H_
#include<string>
#include<vector>

using namespace std;
namespace Fallout{
class StringOp
{
public:
	static vector<string> Split(const string s,char delimeter);
	static string findReplaceAll(const string txt,const string find,const string replace);
	static string findReplaceFirst(const string txt,const string find,const string replace);
	static string deleteLine(const string txt,const string find);
	static string deleteChar(const string txt,const char c);
	static bool Contains(const string txt, const string sub);
	static string clear(const string txt,const string sub);
};

}

#endif
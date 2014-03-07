#include "StringOp.h"
#include<iostream>
#include<sstream>

vector<string> StringOp::Split(const string s,char delimeter){
	vector<string> elems;
	stringstream ss(s);
	string item;

	while(getline(ss,item,delimeter))
		elems.push_back(item);

	return elems;
}
string StringOp::findReplaceAll(const string txt,const string find,const string replace){
	string output = txt;
	size_t fInd = txt.find(find);
	while(fInd!=string::npos){
		output.erase(fInd,find.length());
		output.insert(fInd,replace);
		fInd = output.find(find);
	}
	return output;
}

string StringOp::findReplaceFirst(const string txt,const string find,const string replace){
	string output = txt;
	size_t fInd = txt.find(find);
	if(fInd != string::npos){
		output.erase(fInd,find.size());
		output.insert(fInd,replace);
	}
	return output;
}
string StringOp::deleteLine(const string txt,const string find){
	string output = txt;
	size_t fInd = txt.find(find);

	while(fInd!=string::npos){
		output.erase(fInd,1);
		
		if(output[fInd]=='\n')
			break;
	}
	return output;
}
string StringOp::deleteChar(const string txt,const char c){
	string output = txt;
	for(int i=0;i<output.size();i++){
		if(output[i]==c){
			output.erase(i,1);
			i--;
		}
	}
	return output;
}
#include"GLSLTranslator.h"
#include"StringOp.h"
#include<iostream>
#include<sstream>
#include<GL\glew.h>
using namespace std;
using namespace Fallout;
string GLSL::removeFunction(const string txt, string funcName){
	size_t funcPosition = txt.find(funcName);
	stack<char> stk;
	bool started = false;
	size_t i;
	for (i = funcPosition; i<txt.length(); i++){
		if (txt[i] == '{'){
			stk.push('{');
			started = true;
		}
		else if (txt[i] == '}'){
			stk.pop();
		}
		if (stk.empty() && started)
			break;
	}
	string output = txt;
	output.erase(funcPosition, i - funcPosition + 1);
	return output;
}

string GLSL::removeFunctionCategory(const string txt, const string key){
	string output = txt;
	string line;
	stringstream ss(output);
	while (getline(ss, line)){
		size_t loc = line.find(key);
		if (loc != string::npos){
			output = removeFunction(output, line);
		}
	}
	return output;
}

string GLSL::InOutManagement(const string txt, Shaders type){
	string output = txt;
	if (type == Shaders::VERTEX){
		output = StringOp::findReplaceAll(output, "vout", "out");
		output = StringOp::findReplaceAll(output, "vin", "in");
		output = StringOp::deleteLine(output, "fout");
		output = StringOp::deleteLine(output, "fin");
	}
	else if (type == Shaders::FRAGMENT){
		output = StringOp::findReplaceAll(output, "fout", "out");
		output = StringOp::findReplaceAll(output, "fin", "in");
		output = StringOp::deleteLine(output, "vout");
		output = StringOp::deleteLine(output, "vin");
	}
	return output;
}
string GLSL::UniformManagement(const string txt, Shaders type){
	string output = txt;
	if (type == Shaders::VERTEX){
		output = StringOp::findReplaceAll(output, "vuniform", "uniform");
		while (true){
			string prev = output;
			output = StringOp::deleteLine(output, "funiform");
			if (output == prev)
				break;
		}
	}
	else if (type == Shaders::FRAGMENT){
		output = StringOp::findReplaceAll(output, "funiform", "uniform");
		while (true){
			string prev = output;
			output = StringOp::deleteLine(output, "vuniform");
			if (output == prev)
				break;
		}
	}
	return output;
}

vector<UniformData> GLSL::CreateUniforms(const string txt, unsigned int program, vector<ShaderStruct> strct){
	string shdr2 = StringOp::findReplaceAll(txt,"\r\n","\n");
	vector<UniformData> output;
	stringstream ss(shdr2);
	int samplerID =0;
	string line;
	while (getline(ss, line)){
		vector<string> substrs = StringOp::Split(line, ' ');
		if (substrs.size()>0)
		if (!substrs[0].compare("vuniform") || !substrs[0].compare("funiform")){
			string name = substrs[2];
			int arrnum = 0;
			string number;
			bool isarr = false;
			for (unsigned int i = 0; i<name.size(); i++){
				if (name[i] == ';' || name[i] == ' '){
					name.erase(i, 1);
					i--;
				}
				if (name[i] == ']'){
					isarr = false;
					name.erase(i, 1);
					i--;
				}
				if (isarr){
					number.push_back(name[i]);
					name.erase(i, 1);
					i--;
				}
				if (name[i] == '['){
					isarr = true;
					name.erase(i, 1);
					i--;
				}
			}
			if (number.size()>0){
				arrnum = atoi(number.c_str());
				for (int i = 0; i<arrnum; i++){
					string temp = name;
					temp += "[";
					char* x = new char[30];
					itoa(i, x, 10);
					temp += x;
					temp += "]";
					int ix = -1;
					for (int i = 0; i<strct.size(); i++){
						if (substrs[1] == strct[i].name)
							ix = i;
					}
					string ok = "";
					if (ix != -1){
					for (int i = 0; i<strct[ix].Data.size(); i++){
						ok += temp + ".";
						ok += strct[ix].Data[i].Name;
						unsigned int location = glGetUniformLocation(program, ok.c_str());
						output.push_back(UniformData(location, substrs[1], ok));
						ok = "";
					}
					}else{
						unsigned int location = glGetUniformLocation(program, temp.c_str());
						if(StringOp::Contains(substrs[1],"sampler"))
							glUniform1i(location,samplerID++);
						output.push_back(UniformData(location, substrs[1], temp));
					}
				}
			}
			else{
				int ix = -1;
				for (int i = 0; i<strct.size(); i++){
					if (substrs[1] == strct[i].name)
						ix = i;
				}
				string ok = "";
				if (ix != -1)
				for (int i = 0; i<strct[ix].Data.size(); i++){
					ok += name + ".";
					ok += strct[ix].Data[i].Name;
					unsigned int location = glGetUniformLocation(program, ok.c_str());
					output.push_back(UniformData(location, substrs[1], ok));
					ok = "";
				}
				else{
					unsigned int location = glGetUniformLocation(program, name.c_str());
					if(StringOp::Contains(substrs[1],"sampler"))
							glUniform1i(location,samplerID++);
					output.push_back(UniformData(location, substrs[1], name));
				}
			}
		}
	}
	return output;
}
vector<ShaderStruct> GLSL::CreateStructs( string shdr, unsigned int program){
	string shdr2 = StringOp::findReplaceAll(shdr,"\r\n","\n");
	vector<ShaderStruct> output;
	stringstream ss(shdr2);
	string line;
	bool processing = false;
	while (getline(ss, line)){
		//line = StringOp::clear(line,"\r");
		if (!line.compare("};"))
			processing = false;
		if (line.size()>1 && processing){
			size_t ind = line.find("}");
			string namex = StringOp::Split(line, ' ')[1];
			namex = StringOp::deleteChar(namex, ';');
			namex = StringOp::deleteChar(namex, '}');
			namex = StringOp::deleteChar(namex, '\t');
			if (ind != string::npos){
				processing = false;


			}
			string type = StringOp::Split(line, ' ')[0];
			type = StringOp::deleteChar(type, '\t');
			UniformData xuni(-1, type, namex);
			output.back().Data.push_back(xuni);
		}

		size_t idx = line.find("struct");
		if (idx != string::npos){
			processing = true;
			ShaderStruct st;
			string name = StringOp::Split(line, ' ')[1];
			name = StringOp::deleteChar(name, ' ');
			name = StringOp::deleteChar(name, '{');

			st.name = name;
			output.push_back(st);
		}

		size_t ind = line.find("}");
		if (ind != string::npos)
			processing = false;
	}
	return output;
}

string GLSL::process(string txt, Shaders type){
	txt = StringOp::findReplaceAll(txt,"\r","\n");
	if (type == Shaders::VERTEX){
		string output = txt;
		output = removeFunction(output, "void FSmain()");
		output = removeFunctionCategory(output, "fragment");
		output = StringOp::findReplaceAll(output, "vertex", "");
		
		int i = 0;
		while (true){
			string prev = output;
			string rep = "layout(location =";
			char *x=new char[30];
			_itoa(i,x,10);
			rep.append(x);
			//rep += i + 48;
			rep += " ) in";
			output = StringOp::findReplaceFirst(output, "attribute", rep);
			if (!prev.compare(output))
				break;
			i++;
		}
		output = StringOp::findReplaceAll(output, "varying", "out");
		output = StringOp::findReplaceAll(output, "VSmain()", "main()");

		output = InOutManagement(output, Shaders::VERTEX);
		output = UniformManagement(output, Shaders::VERTEX);
		return output;
	}
	else if (type == Shaders::FRAGMENT){
		string output = txt;
		output = removeFunction(output, "void VSmain()");
		output = removeFunctionCategory(output, "vertex");
		output = StringOp::findReplaceAll(output, "fragment", "");

		while (true){
			string prev = output;
			output = StringOp::deleteLine(output, "attribute");
			if (!prev.compare(output))
				break;
		}
		output = StringOp::findReplaceAll(output, "varying", "in");
		output = StringOp::findReplaceAll(output, "FSmain()", "main()");
		output = InOutManagement(output, Shaders::FRAGMENT);
		output = UniformManagement(output, Shaders::FRAGMENT);
		return output;
	}
	return txt;
}
#include "ExtHelpers.h"

#include <string>
#include <sstream>
using namespace std;


namespace utils {

	auto getPointerSize() -> int
	{
		string objExpression = "sizeof(void*)"s;
		ExtRemoteTyped remoteObj(objExpression.c_str());
		return utils::readIntegral<int>(remoteObj);
	}


	auto escapeDml(const string& str) -> string
	{
		std::string buffer;
		buffer.reserve(str.size());
		for (auto ch : str) {
			switch (ch) {
			case '&':  buffer += "&amp;";  break;
			case '\"': buffer += "&quot;"; break;
			// case '\'': buffer += "&apos;"; break; no DML special character?!
			case '<':  buffer += "&lt;";   break;
			case '>':  buffer += "&gt;";   break;
			default:   buffer += ch;       break;
			}
		}
		return buffer;
	}


	auto link(const string& text, const string& cmd, const string& alt) -> string
	{
		ostringstream oss;
		oss << "<link cmd=\"" << escapeDml(cmd) << "\"";
		if (!alt.empty())
			oss << " alt=\"" << escapeDml(alt) << "\"";
		oss << ">" << escapeDml(text) << "</link>";
		return oss.str();
	}


	auto getFullSymbolName(const string& symbolName) -> string
	{
		ExtBuffer<char> buffer;
		g_Ext->FindFirstModule("python???", &buffer, 0);
		return buffer.GetBuffer() + "!"s + symbolName;
	}

}

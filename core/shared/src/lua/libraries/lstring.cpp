#include "stdafx_shared.h"
#include <pragma/definitions.h>
#include "pragma/lua/libraries/lstring.hpp"
#include <pragma/lua/luaapi.h>

int32_t Lua::string::calc_levenshtein_distance(lua_State *l)
{
	auto *str1 = Lua::CheckString(l,1);
	auto *str2 = Lua::CheckString(l,2);
	auto dist = ustring::calc_levenshtein_distance(str1,str2);
	Lua::PushInt(l,dist);
	return 1;
}
int32_t Lua::string::calc_levenshtein_similarity(lua_State *l)
{
	auto *str1 = Lua::CheckString(l,1);
	auto *str2 = Lua::CheckString(l,2);
	auto sim = ustring::calc_levenshtein_similarity(str1,str2);
	Lua::PushNumber(l,sim);
	return 1;
}
int32_t Lua::string::find_longest_common_substring(lua_State *l)
{
	auto *str1 = Lua::CheckString(l,1);
	auto *str2 = Lua::CheckString(l,2);
	std::size_t startIdx = 0;
	std::size_t endIdx = 0;
	auto len = ustring::longest_common_substring(str1,str2,startIdx,endIdx);
	Lua::PushInt(l,startIdx);
	Lua::PushInt(l,len);
	Lua::PushInt(l,endIdx);
	return 3;
}
int32_t Lua::string::join(lua_State *l)
{
	int32_t t = 1;
	Lua::CheckTable(l,t);

	auto joinChar = ';';
	if(Lua::IsSet(l,2))
		joinChar = *Lua::CheckString(l,2);

	std::string r {};
	auto numEls = Lua::GetObjectLength(l,t);
	auto bFirst = true;
	for(auto i=decltype(numEls){0};i<numEls;++i)
	{
		Lua::PushInt(l,i +1);
		Lua::GetTableValue(l,t);
		auto *v = Lua::CheckString(l,-1);
		if(bFirst == false)
			r += joinChar;
		else
			bFirst = false;
		r += v;
		Lua::Pop(l,1);
	}
	Lua::PushString(l,r);
	return 1;
}
int32_t Lua::string::split(lua_State *l)
{
	std::string str(Lua::CheckString(l,1));
	const char *delimiter = Lua::CheckString(l,2);
	lua_newtable(l);
	int top = lua_gettop(l);
	int n = 1;

	size_t len = strlen(delimiter);
	size_t from = 0;
	size_t f = str.find(delimiter,from);
	while(f != std::string::npos)
	{
		lua_pushstring(l,str.substr(from,f -from).c_str());
		lua_rawseti(l,top,n);
		n++;

		from = f +len;
		f = str.find(delimiter,from);
	}
	lua_pushstring(l,str.substr(from).c_str());
	lua_rawseti(l,top,n);
	n++;
	return 1;
}
int32_t Lua::string::remove_whitespace(lua_State *l)
{
	std::string str = Lua::CheckString(l,1);
	ustring::remove_whitespace(str);
	Lua::PushString(l,str);
	return 1;
}
int32_t Lua::string::remove_quotes(lua_State *l)
{
	std::string str = Lua::CheckString(l,1);
	ustring::remove_quotes(str);
	Lua::PushString(l,str);
	return 1;
}

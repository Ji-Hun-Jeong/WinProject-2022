#pragma once
#pragma comment(lib, "msimg32.lib")
#include <crtdbg.h>
#include <assert.h>
#include <math.h>
#include "define.h"
#include <Windows.h>
#include "enum.h"
#include "struct.h"
#include <wchar.h>
#include <vector>
#include <map>
#include <string>
#include "func.h"
#include <list>
#include <time.h>
using std::list;
using std::vector;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;
template <typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (_vec[i])
			delete _vec[i];
	}
	_vec.clear();
}
template <typename T1,typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	auto iter = _map.begin();
	for (iter; iter != _map.end(); ++iter)
	{
		if (iter->second)
			delete iter->second;
	}
	_map.clear();
}
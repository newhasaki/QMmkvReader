//
// Created by rw on 2022/12/13.
//

#ifndef MMKVREADER_HPP
#define MMKVREADER_HPP

#include "string"
#include "vector"
#include "MMKV.h"

namespace rw
{

using string_type = std::string;

enum types{INT32,UINT32,STRING,FLOAT,INT64,UINT64};
typedef struct {
	string_type field_name;
	types data_type;
}MmkvData;


class MmkvReader
{
public:
	MmkvReader():m_root_path("./"),m_kv(nullptr){

	}
	~MmkvReader() = default;
public:
	void Initialize();
	MMKV * OpenFile(const string_type& filePath, string_type key);
	void ParseFile();
private:
	string_type m_root_path;
	MMKV* m_kv;
	std::vector<string_type> m_all_keys;
	std::vector<MmkvData> m_mmkv_datas;
};

} // rw

#endif //MMKVREADER_HPP

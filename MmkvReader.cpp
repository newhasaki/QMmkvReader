//
// Created by rw on 2022/12/13.
//

#include "MmkvReader.hpp"
#include "iostream"

namespace rw
{

void MmkvReader::Initialize()
{
	MMKV::initializeMMKV(m_root_path, MMKVLogDebug);
}

MMKV * MmkvReader::OpenFile(const string_type& filePath, string_type key= "")
{
	m_kv = MMKV::mmkvWithID(filePath,MMKV_SINGLE_PROCESS,&key,&m_root_path);
	return m_kv;
}

void MmkvReader::ParseFile()
{
//	m_all_keys = m_kv->allKeys();
//	for(const auto& it:m_all_keys){
//
//		MmkvData mmkv_data;
//		mmkv_data.field_name = it;
//		mmkv_data.data_type = STRING;
//
//		size_t value_size = m_kv->getValueSize(it,true);
//		mmkv::MMBuffer mm_buffer = m_kv->getBytes(it);
//
//		// if(value_size > 1){
//		// 	string_type result;
//		// 	bool ret = m_kv->getString(it,result);
//		// 	if(ret){
//		// 		std::cout << it << std::endl;
//		// 		std::cout << result << std::endl;
//		// 	}
//		// }
//	}
}

} // rw
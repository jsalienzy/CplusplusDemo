/*
 *Copyright (c) 2018，博众精工科技股份有限公司北京技术研究院
 *All rights reserved.
 *
 *文件名称：ConfigFile.h
 *摘要：配置文件的读写
 *注意：1. the comments will disappear when saving config
 *	    2. the group and key will be sorted by reversed alpha order when saving config
 *当前版本：1.0
 *作者：江山/王洋
 *完成日期：2018年6月22日
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <cctype>
namespace js
{
	class ConfigFile
	{
	public:
		ConfigFile();
        ConfigFile(const std::string &fileName, std::string delimiter = "=", std::string commentSymbol = "#");
		~ConfigFile();
		bool LoadFile(const std::string &fileName, std::string delimiter = "=", std::string commentSymbol = "#");
        bool FileExist(const std::string &fileName);
        bool SetFileName(const std::string &fileName);
        std::string GetFileName() const;
        std::string GetDelimiter() const;
        std::string GetCommentSymbol() const;
        bool SetDelimiter(const std::string& delimiter);
        bool SetCommentSymbol(const std::string& commentSymbol);
		bool SaveFile();
		bool SaveFileAs(const std::string &fileName);
        
        bool AddString(const std::string &key, const std::string &value, std::string group = "default");
        bool AddInteger(const std::string &key, const int &value, std::string group = "default");
        bool AddDouble(const std::string &key, const double &value, std::string group = "default");
        bool AddBoolean(const std::string &key, const bool &value, std::string group = "default");
        bool Remove(const std::string &key, std::string group = "default");

        bool SetString(const std::string &key, const std::string &value, std::string group = "default");
        bool GetString(const std::string &key, std::string *value, std::string group = "default");
        
        bool SetInteger(const std::string &key, const int &value, std::string group = "default");
        bool GetInteger(const std::string &key, int *value, std::string group = "default");
        
        bool SetDouble(const std::string &key, const double &value, std::string group = "default");
        bool GetDouble(const std::string &key, double *value, std::string group = "default");
        
        bool SetBoolean(const std::string &key, const bool &value, std::string group = "default");
        bool GetBoolean(const std::string &key, bool *value, std::string group = "default");
	
	private:
		static bool TrimString(std::string & str);
		bool SetValue(std::string group, std::string key, std::string value);
		bool GetValue(std::string group, std::string key, std::string *value);
        bool AddValue(std::string group, std::string key, std::string value);
	
	private:
		std::string m_FileName;
        std::string m_Delimiter;
        std::string m_CommentSymbol;
		bool m_Modifyed;
		typedef std::map<std::string, std::string, std::greater<std::string>> Pair;
		typedef std::map<std::string, Pair,   std::greater<std::string>> Paragraph;
		Paragraph m_ParaGroup;
	};
}

#endif //.CONFIGFILE_H_

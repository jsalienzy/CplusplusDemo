#include "stdafx.h"
#include "config_file.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <functional>
#include <cctype>
#include <cassert>

namespace js 
{
	const std::string kDefaultGroup("_default");

	class ConfigFile::ConfigFileImplement
	{
	public:
		static bool TrimString(std::string *str);
		bool SetValue(const std::string &group, const std::string &key, const std::string &value);
		bool GetValue(const std::string &group, const std::string &key, std::string *value);
		bool AddValue(const std::string &group, const std::string &key, const std::string &value);
		std::string file_name_;
		std::string delimiter_;
		std::string comment_symbol_;
		bool modifyed_flag_;
		typedef std::map<std::string, std::string, std::greater<std::string>> Pair;
		typedef std::map<std::string, Pair, std::greater<std::string>> Paragraph;
		Paragraph paragraph_group_;
		std::string error_info_;
	};

	ConfigFile::ConfigFile() :
		config_file_implement_(new ConfigFileImplement)
	{
		config_file_implement_->delimiter_ = std::string(1, '=');
		config_file_implement_->comment_symbol_ = std::string(1, '#');
		config_file_implement_->modifyed_flag_ = false;
	}

	ConfigFile::~ConfigFile()
	{
		if (config_file_implement_->modifyed_flag_)
		{
			SaveFile();
		}
	}

	bool ConfigFile::LoadFile(const char *file_name)
	{
		if (file_name == nullptr)
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		config_file_implement_->file_name_ = file_name;
		config_file_implement_->paragraph_group_.clear();
		std::ifstream file;
		file.open(config_file_implement_->file_name_.c_str(), std::ios::in | std::ios::out);
		if (!file.is_open())
		{
			config_file_implement_->error_info_ = "文件打开失败！";
			return false;
		}
		ConfigFileImplement::Pair pair_key;
		std::string current_group = kDefaultGroup;
		std::string line;
		const std::string::size_type delimiter_length = config_file_implement_->delimiter_.length();
		while (getline(file, line))
		{
			config_file_implement_->TrimString(&line);
			if (0 == line.length())
			{
				continue;
			}
			const std::string::size_type comment_index = line.find(config_file_implement_->comment_symbol_);
			if ((comment_index != std::string::npos) && (comment_index != 0))
			{
				line = line.substr(0, comment_index);
			}

			const std::string::size_type index = line.find(config_file_implement_->delimiter_);
			if (index != std::string::npos)
			{
				std::string key = line.substr(0, index);
				line.replace(0, index + delimiter_length, "");
				ConfigFile::config_file_implement_->TrimString(&key);
				ConfigFile::config_file_implement_->TrimString(&line);
				pair_key[key] = line;
			}
			else
			{
				if (line[0] == '[' && line[line.length() - 1] == ']')
				{
					line.erase(line.length() - 1);
					line.erase(0, 1);				
					current_group = line;
					if (config_file_implement_->paragraph_group_.find(current_group) != config_file_implement_->paragraph_group_.end())
					{
						config_file_implement_->error_info_ = "当前组名已存在！";
						return false;
					}
					config_file_implement_->paragraph_group_[current_group] = pair_key;
					
					pair_key.clear();
				}
				else
				{
					continue;
				}
			}
			config_file_implement_->paragraph_group_[current_group] = pair_key;
		}
		file.close();
		return true;
	}

	bool ConfigFile::FileExist(const char *file_name)
	{
		if (file_name == nullptr)
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::ifstream file(file_name);
		if (!file)
		{
			config_file_implement_->error_info_ = "文件不存在！";
			return false;
		}
		return true;
	}

	bool ConfigFile::SetFileName(const char *file_name)
	{
		if (file_name == nullptr)
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		config_file_implement_->file_name_ = file_name;
		return true;
	}

	const char *ConfigFile::GetFileName() const
	{
		return config_file_implement_->file_name_.c_str();
	}

	const char *ConfigFile::GetDelimiter() const
	{
		return config_file_implement_->delimiter_.c_str();
	}

	const char *ConfigFile::GetCommentSymbol() const
	{
		return config_file_implement_->comment_symbol_.c_str();
	}

	bool ConfigFile::SetDelimiter(const char *delimiter)
	{
		if (delimiter == nullptr)
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		config_file_implement_->delimiter_ = delimiter;
		return true;
	}

	bool ConfigFile::SetCommentSymbol(const char *comment_symbol)
	{
		if (comment_symbol == nullptr)
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		config_file_implement_->comment_symbol_ = comment_symbol;
		return true;
	}

	bool ConfigFile::SaveFile()
	{
		return SaveFileAs(config_file_implement_->file_name_.c_str());
	}

	bool ConfigFile::SaveFileAs(const char *fileName)
	{
		std::ofstream file(fileName);
		if (!file)
		{
			config_file_implement_->error_info_ = "文件新建失败！";
			return false;
		}
		ConfigFileImplement::Pair pairKey = config_file_implement_->paragraph_group_[kDefaultGroup];
		ConfigFileImplement::Pair::iterator pairKeyIter;
		ConfigFileImplement::Paragraph::iterator paraGroupIter;
		std::string delimiter = std::string(" ") + config_file_implement_->delimiter_ + std::string(" ");
		for (pairKeyIter = pairKey.begin(); pairKeyIter != pairKey.end(); ++pairKeyIter)
		{
			file << pairKeyIter->first << delimiter << pairKeyIter->second << std::endl;
		}
		file << std::endl;

		for (paraGroupIter = config_file_implement_->paragraph_group_.begin(); paraGroupIter != config_file_implement_->paragraph_group_.end(); ++paraGroupIter)
		{
			if (paraGroupIter->first == kDefaultGroup)
			{
				continue;
			}
			file << '[' << paraGroupIter->first << ']' << std::endl;
			pairKey = paraGroupIter->second;
			for (pairKeyIter = pairKey.begin(); pairKeyIter != pairKey.end(); ++pairKeyIter)
			{
				file << pairKeyIter->first << delimiter << pairKeyIter->second << std::endl;
			}
			file << std::endl;
		}
		config_file_implement_->modifyed_flag_ = false;
		return true;
	}

	bool ConfigFile::AddString(const char *key, const char *value, const char *group)
	{
		if ((key == nullptr) || (value == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		return config_file_implement_->AddValue(group, key, value);
	}

	bool ConfigFile::AddInteger(const char *key, int value, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		return config_file_implement_->AddValue(group, key, std::to_string(value));
	}

	bool ConfigFile::AddDouble(const char *key, double value, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		return config_file_implement_->AddValue(group, key, std::to_string(value));
	}

	bool ConfigFile::AddBoolean(const char *key, bool value, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::string str = value ? "true" : "false";
		return config_file_implement_->AddValue(group, key, str);
	}

	bool ConfigFile::Remove(const char *key, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		ConfigFileImplement::Paragraph::iterator paraGroupIter = config_file_implement_->paragraph_group_.find(group);
		if (paraGroupIter != config_file_implement_->paragraph_group_.end())
		{
			ConfigFileImplement::Pair &pairKey = paraGroupIter->second;
			ConfigFileImplement::Pair::iterator paraKeyIter = pairKey.find(key);
			if (paraKeyIter != pairKey.end())
			{
				pairKey.erase(key);
			}
			else
			{
				config_file_implement_->error_info_ = "key值没有匹配上";
				return false;
			}
		}
		else
		{
			config_file_implement_->error_info_ = "group值没有匹配上";
			return false;
		}
		config_file_implement_->modifyed_flag_ = true;
		return true;
	}

	bool ConfigFile::SetString(const char *key, const char *value, const char *group)
	{
		if ((key == nullptr) || (value == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		return config_file_implement_->SetValue(group, key, value);
	}

	bool ConfigFile::GetString(const char *key, char *value, int size, const char *group)
	{
		if ((key == nullptr) || (value == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::string string_value;
		if (!config_file_implement_->GetValue(group, key, &string_value))
		{
			config_file_implement_->error_info_ = "根据group和key值获取数据失败";
			return false;
		}
		strcpy_s(value, size, string_value.c_str());
		return true;
	}

	bool ConfigFile::SetInteger(const char *key, int value, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		return config_file_implement_->SetValue(group, key, std::to_string(value));
	}

	bool ConfigFile::GetInteger(const char *key, int *value, const char *group)
	{
		if ((key == nullptr) || (value == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::string str;
		if (!config_file_implement_->GetValue(group, key, &str))
		{
			config_file_implement_->error_info_ = "没有找到当前索引！";
			return false;
		}
		try
		{
			*value = std::stoi(str);
		}
		catch (std::exception &e)
		{
			config_file_implement_->error_info_ = "获取数据转换为整型失败！";
			return false;
		}
		return true;
	}

	bool ConfigFile::SetDouble(const char *key, double value, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		return config_file_implement_->SetValue(group, key, std::to_string(value));
	}

	bool ConfigFile::GetDouble(const char *key, double *value, const char *group)
	{
		if ((key == nullptr) || (value == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::string str;
		if (!config_file_implement_->GetValue(group, key, &str))
		{
			config_file_implement_->error_info_ = "根据group和key值获取数据失败！";
			return false;
		}
		try
		{
			*value = std::stod(str);
		}
		catch (std::exception &e)
		{
			config_file_implement_->error_info_ = "数据转换为double型时出错!";
			return false;
		}
		return true;
	}

	bool ConfigFile::SetBoolean(const char *key, bool value, const char *group)
	{
		if ((key == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::string str = value ? "true" : "false";
		return config_file_implement_->SetValue(group, key, str);
	}

	bool ConfigFile::GetBoolean(const char *key, bool *value, const char *group)
	{
		if ((key == nullptr) || (value == nullptr) || (group == nullptr))
		{
			config_file_implement_->error_info_ = "输入为空指针！";
			return false;
		}
		std::string str;
		if (!config_file_implement_->GetValue(group, key, &str))
		{
			config_file_implement_->error_info_ = "根据group和key值获取数据失败！";
			return false;
		}
		if (str.length() > 0)
		{
			if (str == std::string("true"))
			{
				*value = true;
			}
			else
			{
				*value = false;
			}
		}
		else
		{
			config_file_implement_->error_info_ = "获取的数据为空！";
			return false;
		}
		return true;
	}

	const char * ConfigFile::GetLastError()
	{
		return config_file_implement_->error_info_.c_str();
	}

	bool ConfigFile::ConfigFileImplement::TrimString(std::string *str)
	{
		if (str == nullptr)
		{
			return false;
		}
		size_t pos = 0;
		if (str->length() == 0)
		{
			return true;
		}
		for (pos = 0; pos < str->length() && std::isspace(str->at(pos)); pos++)
		{
			;
		}
		*str = str->substr(pos);
		if (str->length() == 0)
		{
			return true;
		}
		for (pos = str->length() - 1; pos >= 0 && std::isspace(str->at(pos)); pos--)
		{
			;
		}
		str->erase(pos + 1);
		return true;
	}

	bool ConfigFile::ConfigFileImplement::SetValue(const std::string &group, const std::string &key, const std::string &value)
	{
		ConfigFileImplement::Paragraph::iterator paraGroupIter = paragraph_group_.find(group);
		if (paraGroupIter != paragraph_group_.end())
		{
			ConfigFileImplement::Pair &pairKey = paraGroupIter->second;
			ConfigFileImplement::Pair::iterator paraKeyIter = pairKey.find(key);
			if (paraKeyIter != pairKey.end())
			{
				modifyed_flag_ = true;
				paraKeyIter->second = value;
			}
			else
			{
				error_info_ = "key值没有匹配上";
				return false;
			}
		}
		else
		{
			error_info_ = "group值没有匹配上";
			return false;
		}
		return true;
	}

	bool ConfigFile::ConfigFileImplement::GetValue(const std::string &group, const std::string &key, std::string *value)
	{
		if (value == nullptr)
		{
			error_info_ = "输入为空指针！";
			return false;
		}
		ConfigFileImplement::Paragraph::iterator paraGroupIter = paragraph_group_.find(group);
		if (paraGroupIter != paragraph_group_.end())
		{
			ConfigFileImplement::Pair pairKey = paraGroupIter->second;
			ConfigFileImplement::Pair::iterator paraKeyIter = pairKey.find(key);
			if (paraKeyIter != pairKey.end())
			{
				*value = paraKeyIter->second;
			}
			else
			{
				error_info_ = "key值没有匹配上";
				return false;
			}
		}
		else
		{
			error_info_ = "group值没有匹配上";
			return false;
		}
		return true;
	}

	bool ConfigFile::ConfigFileImplement::AddValue(const std::string &group, const std::string &key, const std::string &value)
	{
		std::string temp_group(group);
		std::string temp_key(key);
		ConfigFileImplement::TrimString(&temp_group);
		ConfigFileImplement::TrimString(&temp_key);
		if (paragraph_group_[group].find(key) != paragraph_group_[group].end())
		{
			error_info_ = "当前key值已存在";
			return false;
		}
		ConfigFileImplement::Pair &pairKey = paragraph_group_[group];
		pairKey[key] = value;
		modifyed_flag_ = true;
		return true;
	}

}


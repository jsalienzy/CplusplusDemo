/*
 *Copyright (c) 2018
 *All rights reserved.
 *
 *�ļ����ƣ�config_file.h
 *ժҪ�������ļ��Ķ�д
 *ע�⣺1. the comments will disappear when saving config file.
 *	    2. the group and key will be sorted by reversed alpha order when saving config file
 *��ǰ�汾��0.0.0.1
 *���ߣ�jsalienzy/dzjiangshan@163.com
 *������ڣ�2019��3��17��
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

namespace js
{
	class ConfigFile
	{
	public:
		ConfigFile();
        ConfigFile(const char *file_name, const char *delimiter = "=", const char *comment_symbol = "#");
		~ConfigFile();
		bool LoadFile(const char *file_name, const char *delimiter = "=", const char *comment_symbol = "#");
        bool FileExist(const char *file_name);
        void SetFileName(const char *file_name);
        const char *GetFileName() const;
        const char *GetDelimiter() const;
        const char *GetCommentSymbol() const;
        void SetDelimiter(const char *delimiter);
        void SetCommentSymbol(const char *comment_symbol);
		bool SaveFile();
		bool SaveFileAs(const char *file_name);
        bool AddString(const char *key, const char *value, const char *group = "default");
        bool AddInteger(const char *key, int value, const char *group = "default");
        bool AddDouble(const char *key, double value, const char *group = "default");
        bool AddBoolean(const char *key, bool value, const char *group = "default");
        bool Remove(const char *key, const char *group = "default");
        bool SetString(const char *key, const char *value, const char *group = "default");
        bool GetString(const char *key, char *value, int size, const char *group = "default");
        bool SetInteger(const char *key, int value, const char *group = "default");
        bool GetInteger(const char *key, int *value, const char *group = "default"); 
        bool SetDouble(const char *key, double value, const char *group = "default");
        bool GetDouble(const char *key, double *value, const char *group = "default");
        bool SetBoolean(const char *key, bool value, const char *group = "default");
        bool GetBoolean(const char *key, bool *value, const char *group = "default");
		const char *GetLastError();
	
	private:
		ConfigFile(const ConfigFile &config_file) = delete;
		ConfigFile &operator = (const ConfigFile &config_file) = delete;
		class ConfigFileImplement;
		ConfigFileImplement *config_file_implement_;
	};
}

#endif //.CONFIGFILE_H_

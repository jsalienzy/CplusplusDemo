#include "config_file.h"

using namespace js;

const std::string DEFAULT_GROUP("default");

ConfigFile::ConfigFile():
    m_Delimiter(std::string(1, '=')),
    m_CommentSymbol(std::string(1, '#')),
    m_Modifyed(false)
{
}

ConfigFile::ConfigFile(const std::string &fileName, std::string delimiter, std::string commentSymbol):
    m_FileName(fileName),
    m_Delimiter(delimiter),
    m_CommentSymbol(commentSymbol),
    m_Modifyed(false)
{
    LoadFile(fileName, delimiter, commentSymbol);
}

ConfigFile::~ConfigFile()
{
	if (m_Modifyed)
	{
		SaveFile();
	}
}

bool ConfigFile::LoadFile(const std::string &fileName, std::string delimiter, std::string commentSymbol)
{
    m_FileName = fileName;
    m_Delimiter = delimiter;
    m_CommentSymbol = commentSymbol;
	m_ParaGroup.clear();
	std::ifstream fin(m_FileName);
	if (!fin)
	{
		return false;
	}
	Pair pairKey;                            
	std::string currentGroup = DEFAULT_GROUP;
	std::string line;                        
    const std::string::size_type delimLength = m_Delimiter.length();
	while (getline(fin, line))
	{
		TrimString(line);
		if (0 == line.length())
		{
			continue;
		}
        std::string::size_type commentIndex = line.find(m_CommentSymbol);
        if ((commentIndex != std::string::npos) && (commentIndex != 0))
        {
            line = line.substr(0, commentIndex);
        }

        std::string::size_type index = line.find(m_Delimiter);
        if (index != std::string::npos)
        {
            std::string key = line.substr(0, index);
            line.replace(0, index + delimLength, "");
            ConfigFile::TrimString(key);
            ConfigFile::TrimString(line);
            pairKey[key] = line;
        }
        else
        {
            if (line[0] == '[' && line[line.length() - 1] == ']')
            {
                line.erase(line.length() - 1);
                line.erase(0, 1);             
                m_ParaGroup[currentGroup] = pairKey;
                currentGroup = line;
                pairKey.clear();
            }
        }
        m_ParaGroup[currentGroup] = pairKey;
	}
	fin.close();
	return true;
}

bool ConfigFile::FileExist(const std::string &fileName)
{
    bool exist = false;
    std::ifstream in(fileName);
    if (in)
    {
        exist = true;
    }
    return exist;
}

bool ConfigFile::SetFileName(const std::string & fileName)
{
    m_FileName = fileName;
    return true;
}

std::string ConfigFile::GetFileName() const
{
    return m_FileName;
}

std::string ConfigFile::GetDelimiter() const
{
    return m_Delimiter;
}

std::string ConfigFile::GetCommentSymbol() const
{
    return m_CommentSymbol;
}

bool ConfigFile::SetDelimiter(const std::string & delimiter)
{
    m_Delimiter = delimiter;
    return true;
}

bool ConfigFile::SetCommentSymbol(const std::string & commentSymbol)
{
    m_CommentSymbol = commentSymbol;
    return true;
}

bool ConfigFile::SaveFile()
{
	return SaveFileAs(m_FileName);
}

bool ConfigFile::SaveFileAs(const std::string &fileName)
{
	std::ofstream fout(fileName);
	if (!fout)
	{
		return false;
	}
	Pair pairKey = m_ParaGroup[DEFAULT_GROUP];
	Pair::iterator pairKeyIter;
	Paragraph::iterator paraGroupIter;
    std::string delimiter = std::string(" ") + m_Delimiter + std::string(" ");
	for (pairKeyIter = pairKey.begin(); pairKeyIter != pairKey.end(); ++pairKeyIter)
	{
        fout << pairKeyIter->first << delimiter << pairKeyIter->second << std::endl;
	}
	fout << std::endl;

	for (paraGroupIter = m_ParaGroup.begin(); paraGroupIter != m_ParaGroup.end(); ++paraGroupIter)
	{
		if (paraGroupIter->first == DEFAULT_GROUP)
		{
			continue;
		}
		fout << '[' << paraGroupIter->first << ']' << std::endl;
		pairKey = paraGroupIter->second;
		for (pairKeyIter = pairKey.begin(); pairKeyIter != pairKey.end(); ++pairKeyIter)
		{
			fout << pairKeyIter->first << delimiter << pairKeyIter->second << std::endl;
		}
		fout << std::endl;
	}
    m_Modifyed = false;
	return true;
}

bool ConfigFile::AddString(const std::string & key, const std::string & value, std::string group)
{
    return AddValue(group, key, value);
}

bool ConfigFile::AddInteger(const std::string & key, const int & value, std::string group)
{
    return AddValue(group, key, std::to_string(value));
}

bool ConfigFile::AddDouble(const std::string & key, const double & value, std::string group)
{
    return AddValue(group, key, std::to_string(value));
}

bool ConfigFile::AddBoolean(const std::string & key, const bool & value, std::string group)
{
    std::string str = value ? "true" : "false";
    return AddValue(group, key, str);
}

bool ConfigFile::Remove(const std::string & key, std::string group)
{
    bool status = false;
    std::string szValue;
    Paragraph::iterator paraGroupIter = m_ParaGroup.find(group);
    if (paraGroupIter != m_ParaGroup.end())
    {
        Pair &pairKey = paraGroupIter->second;
        Pair::iterator paraKeyIter = pairKey.find(key);
        if (paraKeyIter != pairKey.end())
        {
            status = true;
            pairKey.erase(key);
        }
        else
        {
            status = false;
        }
    }
    else
    {
        status = false;
    }
    return status;
}

bool ConfigFile::SetString(const std::string &key, const std::string &value, std::string group)
{
	return SetValue(group, key, value);
}

bool ConfigFile::GetString(const std::string &key, std::string *value, std::string group)
{
    return GetValue(group, key, value);
}

bool ConfigFile::SetInteger(const std::string &key, const int &value, std::string group)
{
	return SetValue(group, key, std::to_string(value));
}

bool ConfigFile::GetInteger(const std::string &key, int *value, std::string group)
{
    std::string str;
    bool status = GetValue(group, key, &str);
    try
    {
        *value = std::stoi(str);
    }
    catch (std::exception &e)
    {
        return false;
    }
    return status;
}

bool ConfigFile::SetDouble(const std::string &key, const double &value, std::string group)
{
    return SetValue(group, key, std::to_string(value));
}

bool ConfigFile::GetDouble(const std::string &key, double *value, std::string group)
{
    std::string str;
    bool status = GetValue(group, key, &str);
    try
    {
        *value = std::stod(str);
    }
    catch (std::exception &e)
    {
        return false;
    }
    return status;
}

bool ConfigFile::SetBoolean(const std::string &key, const bool &value, std::string group)
{
	std::string str = value ? "true" : "false";
    return SetValue(group, key, str);
}

bool ConfigFile::GetBoolean(const std::string &key, bool *value, std::string group)
{
    std::string str;
	bool status = GetValue(group, key, &str);
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
        return false;
    }
	return status;
}

bool ConfigFile::TrimString(std::string & str)
{
    size_t pos = 0;
    if (str.length() == 0)
    {
    	return true;
    }
    for (pos = 0; pos < str.length() && std::isspace(str.at(pos)); pos++)
    {
        ;
    }
    str = str.substr(pos);
    if (str.length() == 0)
    {
    	return true;
    }
    for (pos = str.length() - 1; pos >= 0 && std::isspace(str.at(pos)); pos--)
    {
        ;
    }
    str.erase(pos + 1);
    return true;
}

bool ConfigFile::SetValue(std::string group, std::string key, std::string value)
{
    bool status = false;
    Paragraph::iterator paraGroupIter = m_ParaGroup.find(group);
    if (paraGroupIter != m_ParaGroup.end())
    {
        Pair &pairKey = paraGroupIter->second;
        Pair::iterator paraKeyIter = pairKey.find(key);
        if (paraKeyIter != pairKey.end())
        {
            m_Modifyed = true;
            paraKeyIter->second = value;
            status = true;
        }
        else
        {
            status = false;
        }
    }
    else
    {
        status = false;
    }
    return status;
}

bool ConfigFile::GetValue(std::string group, std::string key, std::string *value)
{
    bool status = false;
	Paragraph::iterator paraGroupIter = m_ParaGroup.find(group);
	if (paraGroupIter != m_ParaGroup.end())
	{
		Pair pairKey = paraGroupIter->second;
		Pair::iterator paraKeyIter = pairKey.find(key);
		if (paraKeyIter != pairKey.end())
		{
			*value = paraKeyIter->second;
            status = true;
		}
        else
        {
            status = false;
        }
	}
    else
    {
        status = false;
    }
	return status;
}

bool ConfigFile::AddValue(std::string group, std::string key, std::string value)
{
    ConfigFile::TrimString(group);
    ConfigFile::TrimString(key);
    m_Modifyed = true;
    Pair &pairKey = m_ParaGroup[group];
    pairKey[key] = value;
    return true;
}


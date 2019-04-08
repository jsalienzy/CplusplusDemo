/**
 * \file config_file.h
 * \brief 配置文件的读写
 *
 * \date 2019年4月8日
 * \author 江山
 * \since 0.0.0.1
 * All rights reserved.
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

namespace js {
	
/**
* \class ConfigFile config_file.h
* \brief 配置文件的读写
*
* 本类负责配置文件的读写，提供读取配置文件，修改配置文件名字，更改分隔符、
* 注释符，保存，另存为等功能，另外提供整型、字符串型、浮点型、布尔型数据的
* 添加和更改，能提供GetLastError()获取错误信息。
*
* \author 江山
* \date 2019年4月8日
* \since 0.0.0.1
* \attention 
* *1.读入的配置文件，注释内容会被忽略，保存或另存为时注释内容不会添加。
* *2.保存时同一个组的关键字会被按字母顺序排序
* *3.目前只支持ASCII编码标准
*/
class ConfigFile
{
public:
	/**
	 * \brief 构造函数
	 *
	 * 构造本类，默认分隔符为“=”，默认注释符为“#”，默认组名为“_default”
	 *
	 * \since 0.0.0.1
	 */
	ConfigFile();
	/**
	* \brief 析构函数
	*
	* 析构函数，若对内容作出修改，会执行自动保存修改的操作。
	*
	* \since 0.0.0.1
	*/
	~ConfigFile();
	/**
	* \brief 加载配置文件，把配置文件里面的内容保存到内存
	*
	* 配置文件中的内容会按组存入到内存中，不允许有同样的组名
	* 
	* \param[in] file_name 配置文件名
	* \return
	* *true 加载配置文件内容到内存成功。
	* *false 加载配置文件内容到内存失败。
	* \since 0.0.0.1
	*/
	bool LoadFile(const char *file_name);
	/**
	* \brief 判断该配置文件是否存在。
	*
	* 通过是否能打开该配置文件来判断该配置文件是否存在。
	*
	* \param[in] file_name 配置文件的文件名
	* \return 
	* *true 文件存在
	* *false 文件不存在
	* \since 0.0.0.1
	*/
    bool FileExist(const char *file_name);
	/**
	* \brief 设置配置文件的名称
	*
	* 加载到内存中的配置文件可以被修改名字，也可以通过本方法给配置文件添加名字去写一个新的配置文件。
	*
	* \param[in] file_name 配置文件名
	* \return
	* *true 设置成功
	* *false 设置失败
	* \since 0.0.0.1
	*/
    bool SetFileName(const char *file_name);
	/**
	 * \brief 从内存中获取配置文件的文件名
	 *
	 * 读取当前状态下配置文件的文件名
	 *
	 * \return const char *字符串类型，若当前没有读入文件，且没有设置配置文件名，则返回'\0'。
	 * \since 0.0.0.1
	 * \see SetFileName
	*/
    const char *GetFileName() const;
	/**
	*\brief 从内存中获取配置文件中的分隔符
	*
	* \return const char *字符串类型，默认分隔符为"="
	* \since 0.0.0.1
	* \see SetDelimiter
	*/
    const char *GetDelimiter() const;
	/**
	*\brief 从内存中获取配置文件中的注释符
	*
	* \return const char *字符串类型，默认注释符为"="
	* \since 0.0.0.1
	* \see SetCommentSymbol
	*/
    const char *GetCommentSymbol() const;
	/**
	*\brief 设置配置文件的分隔符
	* \param[in] delimiter 分隔符，不允许为nullptr
	* \return
	* *true 设置成功
	* *false 设置失败
	* \since 0.0.0.1
	* \see GetDelimiter
	*/
    bool SetDelimiter(const char *delimiter);
	/**
	*\brief 设置配置文件的注释符
	* \param[in] comment_symbol 注释符，不允许为nullptr
	* \return
	* *true 设置成功
	* *false 设置失败
	* \since 0.0.0.1
	* \see GetCommentSymbol
	*/
    bool SetCommentSymbol(const char *comment_symbol);
	/**
	*\brief 保存配置文件
	*
	* 保存的文件名为当前内存中存储的文件名
	*
	* \return 
	* *true 保存成功
	* *false 保存失败
	* \since 0.0.0.1
	* \see SaveFileAs
	*/
	bool SaveFile();
	/**
	*\brief 另存为功能
	*
	* 给一个新的文件名，将配置文件保存为该文件名，另存为成功后，当前已修改的状态会转变为未修改的状态
	*
	* \param[in] file_name 配置文件名
	* \return
	* *true 另存为成功
	* *false 另存为失败
	* \since 0.0.0.1
	* \see SaveFile
	*/
	bool SaveFileAs(const char *file_name);
	/**
	*\brief 添加一个内容值为字符串的新条款
	*
	* 添加一个新条款，在group组下，若group值不存在，新建一个名为group的组，若该组中key值已存在，则添加失败，
	* key值，value值，group值都不允许为nullptr
	*
	* \param[in] key 键值，不允许为nullptr
	* \param[in] value 内容值，不允许为nullptr
	* \param[in] group 组名，没有组名则默认为_default
	* \return 
	* *true 添加新条款成功
	* *false 添加新条款失败
	* \since 0.0.0.1
	* \see AddInteger, AddDouble, AddBoolean
	*/
    bool AddString(const char *key, const char *value, const char *group = "_default");
	/**
	*\brief 添加一个内容值为整型的新条款
	*
	* 添加一个新条款，在group组下，若group值不存在，新建一个名为group的组，若该组中key值已存在，则添加失败，
	* key值，group值都不允许为nullptr
	*
	* \param[in] key 键值，不允许为nullptr
	* \param[in] value 内容值
	* \param[in] group 组名，没有组名则默认为_default
	* \return
	* *true 添加新条款成功
	* *false 添加新条款失败
	* \since 0.0.0.1
	* \see AddString, AddDouble, AddBoolean
	*/
    bool AddInteger(const char *key, int value, const char *group = "_default");
	/**
	*\brief 添加一个内容值为浮点型的新条款
	*
	* 添加一个新条款，在group组下，若group值不存在，新建一个名为group的组，若该组中key值已存在，则添加失败，
	* key值，group值都不允许为nullptr
	*
	* \param[in] key 键值，不允许为nullptr
	* \param[in] value 内容值
	* \param[in] group 组名，没有组名则默认为_default
	* \return
	* *true 添加新条款成功
	* *false 添加新条款失败
	* \since 0.0.0.1
	* \see AddString, AddInteger, AddBoolean
	*/
    bool AddDouble(const char *key, double value, const char *group = "_default");
	/**
	*\brief 添加一个内容值为布尔型的新条款
	*
	* 添加一个新条款，在group组下，若group值不存在，新建一个名为group的组，若该组中key值已存在，则添加失败，
	* key值，group值都不允许为nullptr
	*
	* \param[in] key 键值，不允许为nullptr
	* \param[in] value 内容值
	* \param[in] group 组名，没有组名则默认为_default
	* \return
	* *true 添加新条款成功
	* *false 添加新条款失败
	* \since 0.0.0.1
	* \see AddString, AddInteger, AddBoolean
	*/
    bool AddBoolean(const char *key, bool value, const char *group = "_default");
	/**
	*\brief 根据组名和键名移除条款
	*
	* 从内存中寻找当前的组名和键名，若组名或键名不存在，则返回失败，若找到对应的条款，则删除该条款，若
	* 不存在组名，则默认_default.
	*
	* \param[in] key 键值，不允许为nullptr
	* \param[in] group 组名，没有组名则默认为_default
	* \return
	* *true 移除条款成功
	* *false 移除条款失败
	* \since 0.0.0.1
	*/
    bool Remove(const char *key, const char *group = "_default");
	/**
	*\brief 修改配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，修改条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值，不能为nullptr
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return 
	* *true 修改成功
	* *false 修改失败
	* \since 0.0.0.1
	* \see GetString
	*/
    bool SetString(const char *key, const char *value, const char *group = "_default");
	/**
	*\brief 获取配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，获取条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值，不能为nullptr
	* \param[in] size 字符串的长度
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 获取成功
	* *false 获取失败
	* \since 0.0.0.1
	* \see SetString
	*/
    bool GetString(const char *key, char *value, int size, const char *group = "_default");
	/**
	*\brief 修改配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，修改条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 修改成功
	* *false 修改失败
	* \since 0.0.0.1
	* \see GetInteger
	*/
    bool SetInteger(const char *key, int value, const char *group = "_default");
	/**
	*\brief 获取配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，获取条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值，不能为nullptr
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 获取成功
	* *false 获取失败
	* \since 0.0.0.1
	* \see SetInteger
	*/
    bool GetInteger(const char *key, int *value, const char *group = "_default"); 
	/**
	*\brief 修改配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，修改条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 修改成功
	* *false 修改失败
	* \since 0.0.0.1
	* \see GetDouble
	*/
    bool SetDouble(const char *key, double value, const char *group = "_default");
	/**
	*\brief 获取配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，获取条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值，不能为nullptr
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 修改成功
	* *false 修改失败
	* \since 0.0.0.1
	* \see SetDouble
	*/
    bool GetDouble(const char *key, double *value, const char *group = "_default");
	/**
	*\brief 修改配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，修改条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 修改成功
	* *false 修改失败
	* \since 0.0.0.1
	* \see GetBoolean
	*/
    bool SetBoolean(const char *key, bool value, const char *group = "_default");
	/**
	*\brief 获取配置文件中具体条目的内容
	*
	* 根据组名和键值匹配到具体条款，获取条款的内容。没有匹配到具体条款则返回false。
	*
	* \param[in] key 键值，不能为nullptr
	* \param[in] value 内容值，不能为nullptr
	* \param[in] group 组名，没有组名则默认为_default，不能为nullptr
	* \return
	* *true 修改成功
	* *false 修改失败
	* \since 0.0.0.1
	* \see SetBoolean
	*/
    bool GetBoolean(const char *key, bool *value, const char *group = "_default");
	/**
	* \brief 获取错误描述
	* \return const char *字符串类型，错误描述
	* \since 0.0.0.1
	*/
	const char *GetLastError();

private:
	ConfigFile(const ConfigFile &config_file) = delete;
	ConfigFile &operator = (const ConfigFile &config_file) = delete;
	class ConfigFileImplement;
	ConfigFileImplement *config_file_implement_;
};
}

#endif //.CONFIGFILE_H_

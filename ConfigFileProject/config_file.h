/**
 * \file config_file.h
 * \brief �����ļ��Ķ�д
 *
 * \date 2019��4��8��
 * \author ��ɽ
 * \since 0.0.0.1
 * All rights reserved.
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

namespace js {
	
/**
* \class ConfigFile config_file.h
* \brief �����ļ��Ķ�д
*
* ���ฺ�������ļ��Ķ�д���ṩ��ȡ�����ļ����޸������ļ����֣����ķָ�����
* ע�ͷ������棬���Ϊ�ȹ��ܣ������ṩ���͡��ַ����͡������͡����������ݵ�
* ��Ӻ͸��ģ����ṩGetLastError()��ȡ������Ϣ��
*
* \author ��ɽ
* \date 2019��4��8��
* \since 0.0.0.1
* \attention 
* *1.����������ļ���ע�����ݻᱻ���ԣ���������Ϊʱע�����ݲ�����ӡ�
* *2.����ʱͬһ����Ĺؼ��ֻᱻ����ĸ˳������
* *3.Ŀǰֻ֧��ASCII�����׼
*/
class ConfigFile
{
public:
	/**
	 * \brief ���캯��
	 *
	 * ���챾�࣬Ĭ�Ϸָ���Ϊ��=����Ĭ��ע�ͷ�Ϊ��#����Ĭ������Ϊ��_default��
	 *
	 * \since 0.0.0.1
	 */
	ConfigFile();
	/**
	* \brief ��������
	*
	* �����������������������޸ģ���ִ���Զ������޸ĵĲ�����
	*
	* \since 0.0.0.1
	*/
	~ConfigFile();
	/**
	* \brief ���������ļ����������ļ���������ݱ��浽�ڴ�
	*
	* �����ļ��е����ݻᰴ����뵽�ڴ��У���������ͬ��������
	* 
	* \param[in] file_name �����ļ���
	* \return
	* *true ���������ļ����ݵ��ڴ�ɹ���
	* *false ���������ļ����ݵ��ڴ�ʧ�ܡ�
	* \since 0.0.0.1
	*/
	bool LoadFile(const char *file_name);
	/**
	* \brief �жϸ������ļ��Ƿ���ڡ�
	*
	* ͨ���Ƿ��ܴ򿪸������ļ����жϸ������ļ��Ƿ���ڡ�
	*
	* \param[in] file_name �����ļ����ļ���
	* \return 
	* *true �ļ�����
	* *false �ļ�������
	* \since 0.0.0.1
	*/
    bool FileExist(const char *file_name);
	/**
	* \brief ���������ļ�������
	*
	* ���ص��ڴ��е������ļ����Ա��޸����֣�Ҳ����ͨ���������������ļ��������ȥдһ���µ������ļ���
	*
	* \param[in] file_name �����ļ���
	* \return
	* *true ���óɹ�
	* *false ����ʧ��
	* \since 0.0.0.1
	*/
    bool SetFileName(const char *file_name);
	/**
	 * \brief ���ڴ��л�ȡ�����ļ����ļ���
	 *
	 * ��ȡ��ǰ״̬�������ļ����ļ���
	 *
	 * \return const char *�ַ������ͣ�����ǰû�ж����ļ�����û�����������ļ������򷵻�'\0'��
	 * \since 0.0.0.1
	 * \see SetFileName
	*/
    const char *GetFileName() const;
	/**
	*\brief ���ڴ��л�ȡ�����ļ��еķָ���
	*
	* \return const char *�ַ������ͣ�Ĭ�Ϸָ���Ϊ"="
	* \since 0.0.0.1
	* \see SetDelimiter
	*/
    const char *GetDelimiter() const;
	/**
	*\brief ���ڴ��л�ȡ�����ļ��е�ע�ͷ�
	*
	* \return const char *�ַ������ͣ�Ĭ��ע�ͷ�Ϊ"="
	* \since 0.0.0.1
	* \see SetCommentSymbol
	*/
    const char *GetCommentSymbol() const;
	/**
	*\brief ���������ļ��ķָ���
	* \param[in] delimiter �ָ�����������Ϊnullptr
	* \return
	* *true ���óɹ�
	* *false ����ʧ��
	* \since 0.0.0.1
	* \see GetDelimiter
	*/
    bool SetDelimiter(const char *delimiter);
	/**
	*\brief ���������ļ���ע�ͷ�
	* \param[in] comment_symbol ע�ͷ���������Ϊnullptr
	* \return
	* *true ���óɹ�
	* *false ����ʧ��
	* \since 0.0.0.1
	* \see GetCommentSymbol
	*/
    bool SetCommentSymbol(const char *comment_symbol);
	/**
	*\brief ���������ļ�
	*
	* ������ļ���Ϊ��ǰ�ڴ��д洢���ļ���
	*
	* \return 
	* *true ����ɹ�
	* *false ����ʧ��
	* \since 0.0.0.1
	* \see SaveFileAs
	*/
	bool SaveFile();
	/**
	*\brief ���Ϊ����
	*
	* ��һ���µ��ļ������������ļ�����Ϊ���ļ��������Ϊ�ɹ��󣬵�ǰ���޸ĵ�״̬��ת��Ϊδ�޸ĵ�״̬
	*
	* \param[in] file_name �����ļ���
	* \return
	* *true ���Ϊ�ɹ�
	* *false ���Ϊʧ��
	* \since 0.0.0.1
	* \see SaveFile
	*/
	bool SaveFileAs(const char *file_name);
	/**
	*\brief ���һ������ֵΪ�ַ�����������
	*
	* ���һ���������group���£���groupֵ�����ڣ��½�һ����Ϊgroup���飬��������keyֵ�Ѵ��ڣ������ʧ�ܣ�
	* keyֵ��valueֵ��groupֵ��������Ϊnullptr
	*
	* \param[in] key ��ֵ��������Ϊnullptr
	* \param[in] value ����ֵ��������Ϊnullptr
	* \param[in] group ������û��������Ĭ��Ϊ_default
	* \return 
	* *true ���������ɹ�
	* *false ���������ʧ��
	* \since 0.0.0.1
	* \see AddInteger, AddDouble, AddBoolean
	*/
    bool AddString(const char *key, const char *value, const char *group = "_default");
	/**
	*\brief ���һ������ֵΪ���͵�������
	*
	* ���һ���������group���£���groupֵ�����ڣ��½�һ����Ϊgroup���飬��������keyֵ�Ѵ��ڣ������ʧ�ܣ�
	* keyֵ��groupֵ��������Ϊnullptr
	*
	* \param[in] key ��ֵ��������Ϊnullptr
	* \param[in] value ����ֵ
	* \param[in] group ������û��������Ĭ��Ϊ_default
	* \return
	* *true ���������ɹ�
	* *false ���������ʧ��
	* \since 0.0.0.1
	* \see AddString, AddDouble, AddBoolean
	*/
    bool AddInteger(const char *key, int value, const char *group = "_default");
	/**
	*\brief ���һ������ֵΪ�����͵�������
	*
	* ���һ���������group���£���groupֵ�����ڣ��½�һ����Ϊgroup���飬��������keyֵ�Ѵ��ڣ������ʧ�ܣ�
	* keyֵ��groupֵ��������Ϊnullptr
	*
	* \param[in] key ��ֵ��������Ϊnullptr
	* \param[in] value ����ֵ
	* \param[in] group ������û��������Ĭ��Ϊ_default
	* \return
	* *true ���������ɹ�
	* *false ���������ʧ��
	* \since 0.0.0.1
	* \see AddString, AddInteger, AddBoolean
	*/
    bool AddDouble(const char *key, double value, const char *group = "_default");
	/**
	*\brief ���һ������ֵΪ�����͵�������
	*
	* ���һ���������group���£���groupֵ�����ڣ��½�һ����Ϊgroup���飬��������keyֵ�Ѵ��ڣ������ʧ�ܣ�
	* keyֵ��groupֵ��������Ϊnullptr
	*
	* \param[in] key ��ֵ��������Ϊnullptr
	* \param[in] value ����ֵ
	* \param[in] group ������û��������Ĭ��Ϊ_default
	* \return
	* *true ���������ɹ�
	* *false ���������ʧ��
	* \since 0.0.0.1
	* \see AddString, AddInteger, AddBoolean
	*/
    bool AddBoolean(const char *key, bool value, const char *group = "_default");
	/**
	*\brief ���������ͼ����Ƴ�����
	*
	* ���ڴ���Ѱ�ҵ�ǰ�������ͼ���������������������ڣ��򷵻�ʧ�ܣ����ҵ���Ӧ�������ɾ���������
	* ��������������Ĭ��_default.
	*
	* \param[in] key ��ֵ��������Ϊnullptr
	* \param[in] group ������û��������Ĭ��Ϊ_default
	* \return
	* *true �Ƴ�����ɹ�
	* *false �Ƴ�����ʧ��
	* \since 0.0.0.1
	*/
    bool Remove(const char *key, const char *group = "_default");
	/**
	*\brief �޸������ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽��������޸���������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ������Ϊnullptr
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return 
	* *true �޸ĳɹ�
	* *false �޸�ʧ��
	* \since 0.0.0.1
	* \see GetString
	*/
    bool SetString(const char *key, const char *value, const char *group = "_default");
	/**
	*\brief ��ȡ�����ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽���������ȡ��������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ������Ϊnullptr
	* \param[in] size �ַ����ĳ���
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true ��ȡ�ɹ�
	* *false ��ȡʧ��
	* \since 0.0.0.1
	* \see SetString
	*/
    bool GetString(const char *key, char *value, int size, const char *group = "_default");
	/**
	*\brief �޸������ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽��������޸���������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true �޸ĳɹ�
	* *false �޸�ʧ��
	* \since 0.0.0.1
	* \see GetInteger
	*/
    bool SetInteger(const char *key, int value, const char *group = "_default");
	/**
	*\brief ��ȡ�����ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽���������ȡ��������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ������Ϊnullptr
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true ��ȡ�ɹ�
	* *false ��ȡʧ��
	* \since 0.0.0.1
	* \see SetInteger
	*/
    bool GetInteger(const char *key, int *value, const char *group = "_default"); 
	/**
	*\brief �޸������ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽��������޸���������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true �޸ĳɹ�
	* *false �޸�ʧ��
	* \since 0.0.0.1
	* \see GetDouble
	*/
    bool SetDouble(const char *key, double value, const char *group = "_default");
	/**
	*\brief ��ȡ�����ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽���������ȡ��������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ������Ϊnullptr
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true �޸ĳɹ�
	* *false �޸�ʧ��
	* \since 0.0.0.1
	* \see SetDouble
	*/
    bool GetDouble(const char *key, double *value, const char *group = "_default");
	/**
	*\brief �޸������ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽��������޸���������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true �޸ĳɹ�
	* *false �޸�ʧ��
	* \since 0.0.0.1
	* \see GetBoolean
	*/
    bool SetBoolean(const char *key, bool value, const char *group = "_default");
	/**
	*\brief ��ȡ�����ļ��о�����Ŀ������
	*
	* ���������ͼ�ֵƥ�䵽���������ȡ��������ݡ�û��ƥ�䵽���������򷵻�false��
	*
	* \param[in] key ��ֵ������Ϊnullptr
	* \param[in] value ����ֵ������Ϊnullptr
	* \param[in] group ������û��������Ĭ��Ϊ_default������Ϊnullptr
	* \return
	* *true �޸ĳɹ�
	* *false �޸�ʧ��
	* \since 0.0.0.1
	* \see SetBoolean
	*/
    bool GetBoolean(const char *key, bool *value, const char *group = "_default");
	/**
	* \brief ��ȡ��������
	* \return const char *�ַ������ͣ���������
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

#ifndef __REBUILDBUFER_H__
#define __REBUILDBUFER_H__

namespace RoadRebuild
{
	/**
	* @brief ��ȡ774��2.1ʸ��·������ͼЭ��
	* @param type	1 ��ʾ����Э�飬2��ʾ����Э��
	* @param buf	������buffer
	* @param len	buffer����
	* @return void *	MediaObject���
	**/
	void *_MemoryImport21(Gint32 type, void *buf, Guint32 len);

	Gbool _VectorExport(void *handle, Gpstr savefile);
	Gbool _VectorExportBuf(void *handle, void **pBuf, Guint32 &size);

};
#endif // __REBUILDBUFER_H__
#ifndef VECTOR_PAINTER_HEADER_FILE
#define VECTOR_PAINTER_HEADER_FILE

/*!*********************************************************************
 * \class  CVectorPainterFile
 *
 * TODO:   ʸ����ͼ���ݲ����ļ�
 *
 * \author lbhna
 * \date   2016/05/27 
 ***********************************************************************/

//-------------------------------------------------------------------------------------

#include "../RoadGenerateSDK/RoadGenerateSDK_api.h"


#pragma pack(push,1)

#define                VP_FILE_FLAG            (unsigned short)(((unsigned char)('V'))|((unsigned char)('P')<<8))

//------------------���ݿ����Ͷ���--------------------------------------------------------------

#define                VP_BLOCK_POLYGON              0x1001
#define                VP_BLOCK_POLYLINE             0x1002

//------------------�������Ͷ���-------------------------------------------------------------

#define                VP_OBJECT_RoadSurface           0x01       //��·��
#define                VP_OBJECT_Junction              0x02       //·��
#define                VP_OBJECT_DoubleYellowLine      0x03       //˫����
#define                VP_OBJECT_EdgeWhiteLine         0x04       //��Ե����


//--------------------------------------------------------------------------------------


struct  VP_Vector2f   
{
    Gfloat  x,y;
    VP_Vector2f()
    {x=y=0;}
};

struct  VP_FileHeader
{
    unsigned short        flag;
    VP_Vector2f           vMin,vMax;
    VP_FileHeader()
    {
        flag    =   VP_FILE_FLAG;
    }
};

struct VP_BlockHeader
{
    unsigned short        type;
    unsigned short        count;
    VP_BlockHeader()
    {
        type     =0;
        count    =0;
    }
};

struct VP_PolygonBlock
{//����ο���Ϣ

    unsigned char           type;           //��������
    unsigned char           level;          //����˳�򣬴�С����
    unsigned int            color;          //�����ɫ
    unsigned short          pointCount;     //���������
  
    VP_PolygonBlock()
    {
        type            =0;
        pointCount      =0;
        level           =0;
        color           =0xffff0000;
    }

};
struct VP_PolylineBlock
{//���� ����Ϣ

    unsigned char           type;           //��������
    unsigned char           level;          //����˳�򣬴�С����
    unsigned int            color;          //��ɫ
    Gfloat                   width;          //�߿�
    unsigned short          pointCount;     //���������
	bool                    bDashLine;      //�Ƿ��ǵ���
  
    VP_PolylineBlock()
    {
        type            =0;
        width           =2.0f;
        level           =0;
        color           =0xffffff00;
        pointCount      =0;
		bDashLine = false;
    }

};





struct VP_PolygonRecord
{
    VP_PolygonBlock         blockInfo;
    AnGeoVector<VP_Vector2f>     points;
};
struct VP_PolylineRecord
{
    VP_PolylineBlock        blockInfo;
    AnGeoVector<VP_Vector2f>     points;
};


/////////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
/////////////////////////////////////////////////////////////////////////////



class CVectorPainterFile
{
public:
    VP_FileHeader                   m_FileHeader;
    AnGeoVector<VP_PolygonRecord>        m_Polygons;
    AnGeoVector<VP_PolylineRecord>       m_Polylines;

public:
    CVectorPainterFile();
    ~CVectorPainterFile();
public:
    bool            Load(void* pBuf,int size);
    void            Save(void** ppBuf,int& size);

    void            Clear();
protected:
    int             totalSize();

};










//-------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------

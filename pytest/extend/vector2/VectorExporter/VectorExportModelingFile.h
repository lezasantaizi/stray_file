#ifndef __VECTOR_MODELING_FILE_HEADER
#define __VECTOR_MODELING_FILE_HEADER


/*!*********************************************************************
 * \class  CVectorModelingFile
 *
 * TODO:   ʸ��ģ���ļ�������
 *
 * \author lbhna
 * \date   2016/05/27 
 ***********************************************************************/

#include "../RoadGenerateSDK/RoadGenerateSDK_api.h"


//-------------------------------------------------------
#pragma  pack(push , 4)

struct vec4f 
{
    Gfloat x,y,z,w;
    vec4f(){x=y=z=w=0.0f;}
    vec4f(Gfloat X,Gfloat Y,Gfloat Z,Gfloat W){x=X;y=Y;z=Z;w=W;}
};

struct vec4d 
{
    Gdouble x,y,z,w;
    vec4d(){x=y=z=w=0.0f;}
    vec4d(Gdouble left,Gdouble top,Gdouble right,Gdouble down)
    {x=left;y=top;z=right;w=down;}
};

//------------------------------------------------------------

//����ϵ���Ͷ���
#define			VECTOR_DATA_COORD_GLOBAL		0
#define			VECTOR_DATA_COORD_MERCTO		1
#define			VECTOR_MODELING_VERSION			0x01001002
//------------------------------------------------------
struct VMEFileHeader
{
    VMEFileHeader()
    {
        version = 0;
        dataSize = 0;
        crc32 = 0;
        left = top = right = down = 0.0;
        reserved[0] = reserved[1] = reserved[2] = reserved[3] = 0;
    }
    Guint32				version;                        //���ݰ汾��
    Guint32                dataSize;                       //�������ܳ���
    Guint32                crc32;                          //������CRCУ����
    Gdouble						left,top,right,down;			//ī������
    Gint8			            reserved[4];					
};


//�������ݿ����Ͷ���
typedef enum
{
    VMBT_ROADS					= 1,			//��·���ݼ�¼
    VMBT_FORKS					= 2,			//·�����ݼ�¼
    VMBT_SECTIONS				= 3,			//�������ݼ�¼
    VMBT_PIERS					= 4,			//�Ŷ����ݼ�¼
    VMBT_BUILDINGS				= 6,			//�������ݼ�¼
    VMBT_PLANTS					= 7,			//ֲ�����ݼ�¼
    VMBT_BRIDGE_BOTTOMS			= 8,			//�ŵ�����
    VMBT_TUNNELS				= 9,			//�������
    VMBT_LAND					= 10,			//��������
    VMBT_PIPELINE				= 11,			//��������//��˫���ߵ�
    VMBT_NAVILINE               = 12,           //������/������
    VMBT_POLYGON                = 14,           //�Զ�������
    
    VMEBLOCK_TYPE_FORCE_WORD	= 0x7FFF,
}VMEBLOCK_TYPE;

//�������ݿ���Ϣͷ�ṹ����
struct VMEBlockHeader
{
    VMEBlockHeader()
    {
        blockType = 0;
        recordCount = 0;
        blockSize       = 0;
    }
    Guint16					blockType;				//�����¼����VMEBLOCK_TYPE
    Guint16					recordCount;			//���������¼����
    Guint32                 blockSize;              //���������ֽ���
};

//��·��Ϣ���ݽṹ����
struct VMERoadBlock
{
    VMERoadBlock()
    {
        roadId = 0;
        roadClass = 0;
        formWay = 0;
        nameSize = 0;
        channelCount = 0;
        roadBackType = 0;
        leftWidth = 0;
        rightWidth = 0;
        pointCount = 0;
        startIndex = 0;
        endIndex = 0;
        startOffset = 0;
        endOffset = 0;
        extendDataSize = 0;
    }
    Guint64		roadId;					//��·ID
    Guint32			roadClass;				//��·�ȼ�

    Guint8           formWay;                //
    Guint8			nameSize;				//��·���ֳ���0~255
    union
    {
        Guint8			channelCount;
        struct  
        {
            Guint8		leftRoadCount:4;		//��߳�����0~15
            Guint8		rightRoadCount:4;		//�ұ߳�����0~15
        };
    };
    Guint8			roadBackType;			//��·��ͼ��������0~255

    Gint16					leftWidth;				//��·�����(0.01��)
    Gint16					rightWidth;				//��·�Ҳ���(0.01��)

    Guint16			pointCount;				//��·��������
    Guint16			startIndex;				//����·��ʱ��ʼ��������

    Guint16			endIndex;				//����·��ʱ��ֹ��������

    Gfloat					startOffset;			//����·��ʱ��ʼ��ƫ����
    Gfloat					endOffset;				//����·��ʱ��ֹ��ƫ����

    Guint8           extendDataSize;         //�������ݳ���

};



//·�ڷֶ���Ϣ�ṹ����
struct VMEForkPartBlock
{
    VMEForkPartBlock()
    {
        roadIndex = 0;
        partInfo = 0;
        extendDataSize = 0;
        
    }
public:
    Guint16			roadIndex;					//��·������
    union 
    {
        Guint16		partInfo;
        struct
        {
            Guint16			sameRoadDirect:1;			//·���Ƿ�͵�·����һ��
            Guint16			makeBentSector:1;			//·���Ƿ������������
            Guint16			haveRightAdjustPoint:1;		//·���Ҳ��Ƿ��е�����
            Guint16			haveLeftAdjustPoint:1;		//·������Ƿ��е�����
            Guint16			rightPointCount:3;			//·���Ҳ���������0~7
            Guint16			rightLinkBent:1;			//�Ҳ���Ƿ�������һ���غ�
            Guint16			leftPointCount:3;			//·�������������0~7
            Guint16			leftLinkBent:1;				//�����Ƿ�����һ�����غ�
            Guint16			bentPointCount:4;			//·��������������0~15
        };
    };
    Guint8                extendDataSize;         //�������ݳ���
    
};
//·����Ϣ�ṹ����
struct VMEForkBlock
{
    VMEForkBlock ()
    {
        forkPartCount = 0;
    }
    Guint8				forkPartCount;	//��·�ڹ��ּ���Ƭ��0~31
};

//���������¼��Ϣ����
struct VMESectionBlock 
{
    VMESectionBlock ()
    {
        roadIndex = 0;
        typeId = 0;
        locate = 0;
    }
    
    Guint16			roadIndex;			//��·������
    Guint8			typeId;				//��������ID
    union
    {
        Guint8		locate;
        struct  
        {
            Guint8			location:2;			//����λ�ڵ�·�δ� 0:��࣬1:�м䣬2:�Ҳ�
            Guint8			reserved:6;			
        };
    };
};
//�ŵ����ݼ�¼�ṹ����
struct VMEBridgeBottomBlock
{
    VMEBridgeBottomBlock()
    {
        roadIndex = 0;
        typeId = 0;
    }
    
    Guint16			roadIndex;			//����������·������	
    Guint8			typeId;				//��������ID
};
//�Ŷ����ݼ�¼�ṹ����
struct VMEPierBlock
{
    VMEPierBlock ()
    {
        roadIndex = 0;
        padding = 0;
        texTypeId = 0;
        cylinderCount = 0;
        startIndex = 0;
        endIndex = 0;
        startOffset = 0;
        endOffset = 0;
    }
    
    Guint16			roadIndex;			//��·������	
    Guint16			padding;			//���0.01��
    
    Guint8			texTypeId;			//�Ŷ���������ID		0~255
    Guint8			cylinderCount;		//ÿ���Ŷ���������	1~7
    
    Guint16			startIndex;			//�Ŷշֲ�λ��·������λ������
    Guint16			endIndex;			//�Ŷշֲ�λ��·����յ�λ������
    Gfloat					startOffset;		//�Ŷշֲ�λ��·������λ��ƫ����
    Gfloat					endOffset;			//�Ŷշֲ�λ��·����յ�λ��ƫ����
    
};
//������ݼ�¼�ṹ����
struct VMETunnelBlock
{
    VMETunnelBlock()
    {
        roadIndex = 0;
        typeId = 0;
        startIndex = 0;
        endIndex = 0;
        startOffset = 0;
        endOffset = 0;
    }
    
    Guint16			roadIndex;			//��·������	
    Guint8			typeId;				//�������Id
    Guint16			startIndex;			//���λ��·������λ������
    Guint16			endIndex;			//���λ��·����յ�λ������
    Gfloat					startOffset;		//���λ��·������λ��ƫ����
    Gfloat					endOffset;			//���λ��·����յ�λ��ƫ����
};

//�������ݿ�
struct VMEBuildingBlock
{
    VMEBuildingBlock()
    {
        typeAndTexId = 0;
        floors = 0;
        vertexCount = 0;
        indexCount = 0;
        extendDataSize = 0;
    }
    
    union
    {
        Guint8				typeAndTexId;
        struct  
        {
            Guint8			type:4;			// Ҫ�ط������ 0��recce��1��apple,
            Guint8			texId:4;		// ��������ID����JSON������0~15
        };
    };
    Guint8			floors;			// ¥����
    Guint16			vertexCount;	// ���涥������
    Guint16			indexCount;		// ��������
    Guint8           extendDataSize;         //�������ݳ���
    
};
//�������ݿ�
#define LAND_TYPE_land			0			//����
#define LAND_TYPE_inhabit		1			//��ס����
#define LAND_TYPE_grass			2			//�̵�
#define LAND_TYPE_water			3			//ˮ��
#define LAND_TYPE_land_patch	4			//���油��

struct VMELandBlock
{
    VMELandBlock ()
    {
        typeAndTexId = 0;
        vertexCount = 0;
        indexCount = 0;
        segmentCount = 0;
        extendDataSize = 0;
    }
    
    union
    {
        Guint8				typeAndTexId;
        struct  
        {
            Guint8			type:4;			// Ҫ�ط������ 0�����棬1����ס�õأ���2���̵أ�3��ˮϵ
            Guint8			texId:4;		// ��������ID ,��JSON������0~15
        };
    };
    
    Guint16			vertexCount;	// ���涥������
    Guint16			indexCount;		// ��������
    Guint8			segmentCount;	// ����0~255
    Guint8           extendDataSize; //�������ݳ���
};
//ֲ�����ݿ�
struct VMEPlantBlock
{
    VMEPlantBlock ()
    {
        typeId = 0;
        pointCount = 0;
        minHeight = 0;
        maxHeight = 0;
    }
    Guint8           typeId;             //����ID,������json�����ò�ͬ���������ʽ
    Guint16          pointCount;         //�ֲ������
    Guint16          minHeight;          //ֲ����С�߶�0.01��
    Guint16          maxHeight;          //ֲ��������0.01��
    
};

//�������ݿ�
struct VMEPipelineBlock
{
    VMEPipelineBlock ()
    {
        typeId = 0;
        pathSize = 0;
    }
    Guint8			typeId;			//��������ID
    Guint16			pathSize;		//·��������
};

//ת����/���������ݿ�
struct VMENavilineBlock
{
    VMENavilineBlock ()
    {
        typeId              =0;
        pointCount          =0;
	    entranceRoadAngle   =0;		    // �ӽǵĽǶ�	����Ϊ0��˳ʱ��仯����λ����
    }
    Guint8           typeId;                // ����ID
    TVector2d        center;		        // ���ĵ�	��ī������
	vec4d            minbox;			    // ʸ��ͼ��������С��Χ		��ī������
	vec4d            maxbox;			    // ʸ��ͼ���������Χ		��ī������
	Gfloat	         entranceRoadAngle;	    // �ӽǵĽǶ�	����Ϊ0��˳ʱ��仯����λ����
    Guint16          pointCount;            // �����߹ᴩ·��������(����center��������)
};
//�Զ����������ݿ�
struct VMEPolygonBlock
{
    VMEPolygonBlock ()
    {
        typeId = 0;
        pointCount = 0;
        indexCount = 0;
    }
    Guint8           typeId;         //����ID
    Guint16          pointCount;     //����ιؼ�������
    Guint16          indexCount;     //�������������
};

#pragma pack(pop)



//-----------------------------------------------------------------------------
//��·��Ϣ��¼
struct VMERoadRecord
{
    VMERoadRecord ()
    {
        m_name = "\0";
    }
    VMERoadBlock						        m_roadBlockInfo;
    AnGeoString								    m_name;
    AnGeoVector<TVector3f>						m_Points;
    AnGeoVector<Guint8>                          m_extendData;
};


//·��������Ϣ��
struct VMEForkPartRecord
{
    VMEForkPartBlock					    m_Part;
    TVector3f								m_LeftAdjustPoint;
    TVector3f								m_RightAdjustPoint;
    AnGeoVector<vec4f>						m_LeftPoints;
    AnGeoVector<vec4f>						m_RightPoints;
    AnGeoVector<TVector3f>					m_bentPoints;
    AnGeoVector<Guint8>                      m_extendData;
};
//·����Ϣ��
struct VMEForkRecord
{
    VMEForkBlock						    m_ForkBlock;
    AnGeoVector<VMEForkPartRecord>			m_ForkParts;
    
};

// ������¼�ṹ����
struct VMEBuildingRecord
{
    VMEBuildingBlock				        m_BuildBlock;
    AnGeoVector<TVector2us>					m_VertexArray;
    AnGeoVector<Guint16>					m_IndexArray;
    AnGeoVector<Guint8>                      m_extendData;
};
//�����¼�ṹ����
struct VMELandRecord
{
    VMELandBlock					        m_LandBlock;
    AnGeoVector<TVector2us>					m_VertexArray;
    AnGeoVector<Guint16>					m_IndexArray;
    AnGeoVector<Guint16>					m_SegmentIndicates;
    AnGeoVector<Guint8>                      m_extendData;
};
//ֲ���¼�ṹ����
struct VMEPlantRecord
{
    VMEPlantBlock                           m_PlantBlock;
    AnGeoVector<TVector2us>					m_PointArray;
};
//�����¼�ṹ����
struct VMEPipelineRecord 
{
    VMEPipelineBlock				        m_PipelineBlock;
    AnGeoVector<TVector3f>					m_path;
};

//�����߼�¼�ṹ���� 
struct VMENavilineRecord
{
    VMENavilineBlock                        m_NavilineBlock;
    AnGeoVector<TVector3f>					m_naviPath;
};

//����μ�¼�ṹ���� 
struct VMEPolygonRecord
{
    VMEPolygonBlock                         m_PolygonBlock;
    AnGeoVector<TVector3f>                  m_Points;
    AnGeoVector<Guint16>                    m_Indicates;
};
//-----------------------------------------------------------------------


class CVectorExportModelingFile
{
public:
    VMEFileHeader								    m_FileHeader;		//�ļ�ͷ��Ϣ
    AnGeoVector<VMERoadRecord>						m_Roads;			//��·��Ϣ
    AnGeoVector<VMEForkRecord>						m_RoadForks;		//·����Ϣ
    AnGeoVector<VMESectionBlock>					m_Sections;			//������Ϣ
    AnGeoVector<VMEPierBlock>						m_Piers;			//�Ŷ���Ϣ
    AnGeoVector<VMEBridgeBottomBlock>				m_BridgeBottoms;	//�ŵ�����
    AnGeoVector<VMETunnelBlock>						m_Tunnels;			//�������
    AnGeoVector<VMEBuildingRecord>					m_Buildings;		//��������
    AnGeoVector<VMELandRecord>						m_Lands;			//��������
    AnGeoVector<VMEPipelineRecord>					m_Pipelines;		//��������
    AnGeoVector<VMENavilineRecord>                  m_Navilines;        //����������
    AnGeoVector<VMEPolygonRecord>                   m_Polygons;         //���������
    AnGeoVector<VMEPlantRecord>                     m_Plants;           //ֲ������
public:
    Gfloat										    m_fRoadHeightScale;	//��·�߶�����
public:
    CVectorExportModelingFile();
    ~CVectorExportModelingFile();
public:
    bool				LoadFromMemory(void* pBuffer,Guint32 uSize);
    Guint32		        SaveToMemory(void** ppBuffer);
    void				Reset();
protected:
    void				scaleHeight(Gfloat scale);
};

extern Guint32          IndexToRoadClass(Gbyte index);
extern Gbyte            RoadClassToIndex(Guint32 roadClass);


#endif
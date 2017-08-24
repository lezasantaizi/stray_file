#ifndef __GTL_VECTOR_GRAPHICS_LIB_WINV2__
#define __GTL_VECTOR_GRAPHICS_LIB_WINV2__

#include "DEF.hpp"
#include "CLR.hpp"
#include <stdio.h>
#if defined(ANDROID) || defined(__ANDROID__)
#include <android/log.h>
#endif

#if defined WIN32 || defined _WIN32_WCE
#include <windows.h>
#endif

namespace GTL
{

#ifndef BI_RGB
#define BI_RGB       0
#endif

#ifndef BI_RLE8
#define BI_RLE8      1
#endif

#ifndef BI_RLE4
#define BI_RLE4      2
#endif

#ifndef BI_BITFIELDS
#define BI_BITFIELDS 3
#endif

#pragma pack(2)
typedef struct BITMAPFILEHEAD
{ //bmfh
	WORD bfType;			// ָʾ�ļ������ͣ������ǡ�BM��
	SINT bfSize;			// ָʾ�ļ��Ĵ�С������BITMAPFILEHEADER
	WORD bfReserved1;		// ������=0
	WORD bfReserved2;		// ������=0
	SINT bfOffBits;			// ���ļ�ͷ��λͼ���ݵ�ƫ���ֽ���
}BITMAPFILEHEAD;			// sizeof() == 14B

typedef struct BITMAPINFOHEAD
{ //bmih
	SINT biSize;			// BITMAPINFOHEADER�ṹ�Ĵ�С��BMP�ж���汾���Ϳ�biSize������
							//   BMP3.0��BITMAPINFOHEADER = 40
							//   BMP4.0��BITMAPV4HEADER = 108
							//   BMP5.0��BITMAPV5HEADER = 124 
	SINT biWidth;			// λͼ�Ŀ�ȣ���λ������
							//   λͼÿһɨ���е��ֽ���������4����������Ҳ����DWORD����
	SINT biHeight;			// λͼ�ĸ߶ȣ���λ������
							//   �����ֵ��һ��������˵��ͼ���ǵ���ģ�
							//   �����ֵ��һ��������˵��ͼ��������ġ�
							//   �������BMP�ļ����ǵ����λͼ����BMP
							//   ��һ������λͼʱ��ͼ�񽫲��ܱ�ѹ����
	WORD biPlanes;			// �豸��λƽ���������ڶ���1
	WORD biBitCount;		// ͼ�����ɫλ��
							//   0�� ��biCompression = BI_JPEGʱ����Ϊ0(BMP 5.0)
							//   1�� ��ɫλͼ
							//   4�� 16ɫλͼ
							//   8�� 256ɫλͼ
							//   16����ǿɫλͼ��Ĭ��Ϊ555��ʽ
							//       ��biCompression��ֵ��BI_RGBʱ��ʾ555��ʽ
							//       ��biCompression��ֵ��BI_BITFIELDSʱ�ɱ�ʾ���ָ�ʽ��
							//       ��ɫ���λ�ñ�����DWORD����ռ�ݣ���Ϊ�졢�̡������룬
							//       555��ʽ�£��졢�̡���������ֱ��ǣ�0x7C00��0x03E0��0x001F��
							//       565��ʽ�£��졢�̡���������ֱ��ǣ�0xF800��0x07E0��0x001F��
							//   24�����ɫλͼ
							//   32��32λλͼ��Ĭ�������Windows���ᴦ�����8λ�����Խ�����Ϊ�Լ���Alphaͨ��
	SINT biCompression;		// ѹ����ʽ
							//   BI_RGB����ѹ��
							//   BI_RLE8���г̱���ѹ����biBitCount�������8
							//   BI_RLE4���г̱���ѹ����biBitCount�������4
							//   BI_BITFIELDS��ָ��RGB���룬biBitCount�������16��32
							//   BI_JPEG��JPEGѹ��(BMP 5.0)
							//   BI_PNG��PNGѹ��(BMP 5.0)
	SINT biSizeImage;		// ʵ�ʵ�λͼ������ռ�ֽ�(biCompression=BI_RGBʱ����ʡ��)
	SINT biXPelsPerMeter;	// Ŀ���豸��ˮƽ�ֱ��ʣ���λ��ÿ�׵����ظ���
	SINT biYPelsPerMeter;	// Ŀ���豸�Ĵ�ֱ�ֱ��ʣ���λ��ÿ�׵����ظ���
	SINT biClrUsed;			// ʹ�õ���ɫ��(��biBitCount����1��4��8ʱ����Ч)���������Ϊ0����ʾ��ɫ��Ϊ2^biBitCount
	SINT biClrImportant;	// ��Ҫ����ɫ�����������Ϊ0����ʾ������ɫ������Ҫ��
}BITMAPINFOHEAD;			// sizeof() == 40B

typedef struct BITMAPHEAD
{
	BITMAPINFOHEAD Info;
	UINT           Mark[3];
}BITMAPHEAD;
#pragma pack()

template <class TCLR>
class TDIB
{
public:
	TDIB()
	{
		m_wlen = 0;
		m_hlen = 0;
		m_data = NULL;
	}
	void Attach(long W, long H, void *Data)
	{
		m_wlen = W;
		m_hlen = H;
		m_data = Data;
		InitHead(W, H);
	}

	typedef typename TCLR::TYPE TYPE;
#if defined WIN32 || defined _WIN32_WCE
	void Draw(HDC hDC)
	{
		long w = m_wlen;
		long h = m_hlen;
		::SetDIBitsToDevice(hDC, 0, 0, w, h, 0, 0, 0, h, m_data,
			(BITMAPINFO *)&m_head.Info, DIB_RGB_COLORS);
	}
	void Draw(HDC hDC, long X, long Y)
	{
		long w = m_wlen;
		long h = m_hlen;
		::SetDIBitsToDevice(hDC, X, Y, w, h, 0, 0, 0, h, m_data,
			(BITMAPINFO *)&m_head.Info, DIB_RGB_COLORS);
	}
	void Draw(HDC hDC, long X, long Y, long W, long H)
	{
		long n = m_hlen - Y - H;
		::SetDIBitsToDevice(hDC, X, Y, W, H, X, n, n, H, m_data,
			(BITMAPINFO *)&m_head.Info, DIB_RGB_COLORS);
	}
#endif
	void ExportToFile(const char *Path)
	{
		if (Path == NULL || m_data == NULL)
			return;
		FILE *file = fopen(Path, "wb");
		if (file == NULL)
			return;

		SINT h = sizeof(BITMAPFILEHEAD) + sizeof(BITMAPINFOHEAD) +
				 (m_head.Info.biCompression ? 12 : 0);
        
		BITMAPFILEHEAD t =
		{
			0x4D42,
			static_cast<SINT>(h + m_wlen * m_hlen * sizeof(TYPE)),
			0,
			0,
			h
		};
		fwrite(&t, sizeof(t), 1, file);
		fwrite(&m_head, sizeof(BITMAPINFOHEAD), 1, file);
		if(m_head.Info.biCompression)
			fwrite(&m_head.Mark, 12, 1, file);
		fwrite(m_data, m_wlen * m_hlen * sizeof(TYPE), 1, file);
		fclose(file);
	}

	unsigned int ExportToMemory(unsigned char* pBuffer)
	{
		SINT h = sizeof(BITMAPFILEHEAD)+sizeof(BITMAPINFOHEAD)+
			(m_head.Info.biCompression ? 12 : 0);

		BITMAPFILEHEAD t =
		{
			0x4D42,
			static_cast<SINT>(h + m_wlen * m_hlen * sizeof(TYPE)),
			0,
			0,
			h
		};

		unsigned int nBufferLen = 0;
		if (pBuffer)
		{
			memcpy(pBuffer, &t, sizeof(t));
			pBuffer += sizeof(t);
		}
		nBufferLen += sizeof(t);

		if (pBuffer)
		{
			memcpy(pBuffer, &m_head, sizeof(BITMAPINFOHEAD));
			pBuffer += sizeof(BITMAPINFOHEAD);
		}
		nBufferLen += sizeof(BITMAPINFOHEAD);

		if (m_head.Info.biCompression)
		{
			if (pBuffer)
			{
				memcpy(pBuffer, &m_head.Mark, 12);
				pBuffer += 12;
			}
			nBufferLen += 12;
		}
			
		if (pBuffer)
		{
			memcpy(pBuffer, m_data, m_wlen * m_hlen * sizeof(TYPE));
		}
		nBufferLen += m_wlen * m_hlen * sizeof(TYPE);
		
		return nBufferLen;
	}

protected:
	void InitHead(long W, long H);

protected:
	BITMAPHEAD m_head;
	long       m_wlen;
	long       m_hlen;
	void      *m_data;
};

typedef TDIB<CCLR::C555> CDIB555;
typedef TDIB<CCLR::C565> CDIB565;
typedef TDIB<CCLR::C888> CDIB888;
typedef TDIB<CCLR::RGBA> CDIBRGB;


/////////////////////////////////////////////////////////////////////////////
//
// TDIB
//
/////////////////////////////////////////////////////////////////////////////

template <class TCLR>
void TDIB<TCLR>::InitHead(long W, long H)
{
	m_head.Info.biSize          = sizeof(BITMAPINFOHEAD);
	m_head.Info.biWidth         = (SINT) W;
	m_head.Info.biHeight        = (SINT)-H;
	m_head.Info.biPlanes        = 1;
	m_head.Info.biBitCount      = BITSOFTYPE(TYPE);
	m_head.Info.biCompression   = BI_RGB;
	m_head.Info.biSizeImage     = 0;
	m_head.Info.biXPelsPerMeter = 0xB12;
	m_head.Info.biYPelsPerMeter = 0xB12;
	m_head.Info.biClrUsed       = 0;
	m_head.Info.biClrImportant  = 0;
}

/////////////////////////////////////////////////////////////////////////////
//
// TDIB end
//
/////////////////////////////////////////////////////////////////////////////

}

#endif

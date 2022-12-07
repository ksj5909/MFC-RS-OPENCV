
// MFC+RS+OPENCVDlg.h: 헤더 파일
//

#pragma once
#include <librealsense2/rs.hpp>
#include <stdio.h>
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include "mmsystem.h"
#include "windows.h"

using namespace std;
using namespace cv;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     These parameters are reconfigurable(color)                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define STREAM_COLOR          RS2_STREAM_COLOR  // rs2_stream is a types of data provided by RealSense device            //
#define FORMAT_COLOR          RS2_FORMAT_RGB8   // rs2_format identifies how binary data is encoded within a frame       //
#define WIDTH_COLOR           1920              // Defines the number of columns for each frame                         //
#define HEIGHT_COLOR          1080              // Defines the number of lines for each frame                           //
#define FPS_COLOR             30                // Defines the rate of frames per second                                  //
#define STREAM_INDEX_COLOR    0                 // Defines the stream index, used for multiple streams of the same type  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                     These parameters are reconfigurable(depth)                                        //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define STREAM_DEPTH          RS2_STREAM_DEPTH  // rs2_stream is a types of data provided by RealSense device            //
#define FORMAT_DEPTH          RS2_FORMAT_Z16    // rs2_format identifies how binary data is encoded within a frame       //
#define WIDTH_DEPTH           1280              // Defines the number of columns for each frame                          //
#define HEIGHT_DEPTH          720               // Defines the number of lines for each frame                            //
#define FPS_DEPTH             30                // Defines the rate of frames per second                                 //
#define STREAM_INDEX_DEPTH    1                 // Defines the stream index, used for multiple streams of the same type  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool device_with_streams(std::vector <rs2_stream> stream_requests, std::string& out_serial);
void check_error(rs2_error* e);
void print_device_info(rs2_device* dev);
float get_depth_scale(rs2::device dev);


enum color_scheme
{
	RS_COLOR_SCHEME_JET,
	RS_COLOR_SCHEME_CLASSIC,
	RS_COLOR_SCHEME_WHITETOBLACK,
	RS_COLOR_SCHEME_BLACKTOWHITE,
	RS_COLOR_SCHEME_BIO,
	RS_COLOR_SCHEME_COLD,
	RS_COLOR_SCHEME_WARM,
	RS_COLOR_SCHEME_QUANTIZED,
	RS_COLOR_SCHEME_PATTERN,
	RS_COLOR_SCHEME_HUE
};

typedef struct box_information
{
	int left, right, top, bottom;
	Point pt;
} BoxInfo;


// CMFCRSOPENCVDlg 대화 상자
class CMFCRSOPENCVDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCRSOPENCVDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCRSOPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	rs2::pipeline m_pipe;
	rs2::align *m_align_to_color;
	rs2::colorizer* m_colorizer;
	rs2::pipeline_profile m_profile;

	Mat mat_frame_color;
	Mat mat_frame_depth;
	Mat mat_frame_depth2; // not colorized, real depth image frame
	Mat mat_depth_mask;
	vector<Mat> vecmat_bgr_frames;
	Mat mat_avgImg;
	Mat mat_background_frame, mat_background_frame_gray;
	Mat mat_buffer_frame, mat_buffer_frame2;
	Mat mat_stats, mat_centroids;
	BoxInfo m_prev_box;
	vector<Point> mvp_points;
	uchar m_bbox_update_cnt;
	VideoWriter* videoWriter;
	FILE* mfp_depth;


	bool mb_bgrismade;
	bool mb_detect;
	bool mb_record;

	float m_depth_scale;

	int test();
	int rs_init_live();
	void rs_init_load();
	void imgproc();
	void setBgrFrame();
	void setParams();
	void MakeBgr();
	void Detection();
	void Track();
	void depthtest();


	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	CSliderCtrl m_sldTest;
	afx_msg void OnBnClickedButtonRecord();
	CComboBox m_ctrlBox;
	afx_msg void OnBnClickedButtonSet();
};



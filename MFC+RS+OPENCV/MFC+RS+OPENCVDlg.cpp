
// MFC+RS+OPENCVDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC+RS+OPENCV.h"
#include "MFC+RS+OPENCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCRSOPENCVDlg 대화 상자



CMFCRSOPENCVDlg::CMFCRSOPENCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCRSOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCRSOPENCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_TEST, m_sldTest);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlBox);
}

BEGIN_MESSAGE_MAP(CMFCRSOPENCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_RECORD, &CMFCRSOPENCVDlg::OnBnClickedButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CMFCRSOPENCVDlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CMFCRSOPENCVDlg 메시지 처리기

BOOL CMFCRSOPENCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	//test();
	//rs_init_live();

	m_sldTest.SetRange(0, 100);
	m_sldTest.SetPos(50);
	m_sldTest.SetLineSize(1);
	m_sldTest.SetPageSize(10);

	m_ctrlBox.AddString(_T("Live"));
	m_ctrlBox.AddString(_T("Load & Play"));

	if (m_ctrlBox.GetCount() > 0)
	{
		m_ctrlBox.SetCurSel(0);
	}
	
	setParams();
	//SetTimer(1000, 1000 / 30, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCRSOPENCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCRSOPENCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCRSOPENCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool device_with_streams(std::vector <rs2_stream> stream_requests, std::string& out_serial)
{
	rs2::context ctx;
	auto devs = ctx.query_devices();
	std::vector <rs2_stream> unavailable_streams = stream_requests;
	for (auto dev : devs)
	{
		std::map<rs2_stream, bool> found_streams;
		for (auto& type : stream_requests)
		{
			found_streams[type] = false;
			for (auto& sensor : dev.query_sensors())
			{
				for (auto& profile : sensor.get_stream_profiles())
				{
					if (profile.stream_type() == type)
					{
						found_streams[type] = true;
						unavailable_streams.erase(std::remove(unavailable_streams.begin(), unavailable_streams.end(), type), unavailable_streams.end());
						if (dev.supports(RS2_CAMERA_INFO_SERIAL_NUMBER))
							out_serial = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
					}
				}
			}
		}
		// Check if all streams are found in current device
		bool found_all_streams = true;
		for (auto& stream : found_streams)
		{
			if (!stream.second)
			{
				found_all_streams = false;
				break;
			}
		}
		if (found_all_streams)
			return true;
	}
	// After scanning all devices, not all requested streams were found
	for (auto& type : unavailable_streams)
	{
		switch (type)
		{
		case RS2_STREAM_POSE:
		case RS2_STREAM_FISHEYE:
			std::cerr << "Connect T26X and rerun the demo" << std::endl;
			break;
		case RS2_STREAM_DEPTH:
			std::cerr << "The demo requires Realsense camera with DEPTH sensor" << std::endl;
			break;
		case RS2_STREAM_COLOR:
			std::cerr << "The demo requires Realsense camera with RGB sensor" << std::endl;
			break;
		default:
			throw std::runtime_error("The requested stream: " + std::to_string(type) + ", for the demo is not supported by connected devices!"); // stream type
		}
	}
	return false;
}

int CMFCRSOPENCVDlg::test()
{
	std::string serial;
	if (!device_with_streams({ RS2_STREAM_COLOR, RS2_STREAM_DEPTH }, serial))
	{
		return EXIT_SUCCESS;
	}
	rs2::colorizer c(color_scheme::RS_COLOR_SCHEME_JET);
	/*
		*                           0 - Jet
		*                           1 - Classic
		*                           2 - WhiteToBlack
		*                           3 - BlackToWhite
		*                           4 - Bio
		*                           5 - Cold
		*                           6 - Warm
		*                           7 - Quantized
		*                           8 - Pattern
		*                           9 - Hue
		*
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


	*/
	rs2::pipeline pipe;
	rs2::config cfg;
	if (!serial.empty())
	{
		cfg.enable_device(serial);
	}

	cfg.enable_stream(RS2_STREAM_DEPTH, STREAM_INDEX_COLOR, WIDTH_DEPTH, HEIGHT_DEPTH, FORMAT_DEPTH, FPS_DEPTH);

	cfg.enable_stream(RS2_STREAM_COLOR, STREAM_INDEX_COLOR, WIDTH_COLOR, HEIGHT_COLOR, FORMAT_COLOR, FPS_COLOR);
	// 이게 왜 됨? 왜 되는 지 잘 모르겠음 되게 했긴 한데.. 그리고 위에 지워진 걸로 하면 왜 안 되는 지도 모르겠음
	pipe.start(cfg);

	rs2::align align_to_color(RS2_STREAM_COLOR);

	float alpha = 0.5f;
	int cnt = 0;
	while (cnt < 500)
	{
		rs2::frameset frameset = pipe.wait_for_frames();

		frameset = align_to_color.process(frameset);

		auto depth = frameset.get_depth_frame();
		auto color = frameset.get_color_frame();
		auto colorized_depth = c.colorize(depth);
		int width, height;

		width = colorized_depth.as<rs2::video_frame>().get_width();
		height = colorized_depth.as<rs2::video_frame>().get_height();
		Mat depth_frame(Size(width, height), CV_8UC3, (void*)colorized_depth.get_data(), Mat::AUTO_STEP);
		cvtColor(depth_frame, depth_frame, COLOR_BGR2RGB);
		imshow("colorized_depth", depth_frame);

		width = color.as<rs2::video_frame>().get_width();
		height = color.as<rs2::video_frame>().get_height();
		Mat color_frame(Size(width, height), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
		color_frame = color_frame.clone();
		cvtColor(color_frame, color_frame, COLOR_BGR2RGB);
		imshow("color", color_frame);
		waitKey(1);
		cnt++;

	}



	return 0;

}

int CMFCRSOPENCVDlg::rs_init_live()
{
	std::string serial;
	if (!device_with_streams({ RS2_STREAM_COLOR, RS2_STREAM_DEPTH }, serial))
	{
		return EXIT_SUCCESS;
	}

	//rs2::colorizer c(color_scheme::RS_COLOR_SCHEME_WHITETOBLACK);
	/*
		*                           0 - Jet
		*                           1 - Classic
		*                           2 - WhiteToBlack
		*                           3 - BlackToWhite
		*                           4 - Bio
		*                           5 - Cold
		*                           6 - Warm
		*                           7 - Quantized
		*                           8 - Pattern
		*                           9 - Hue
		*
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


	*/
	rs2::config cfg;
	if (!serial.empty())
	{
		cfg.enable_device(serial);
	}

	cfg.enable_stream(RS2_STREAM_DEPTH, STREAM_INDEX_COLOR, WIDTH_DEPTH, HEIGHT_DEPTH, FORMAT_DEPTH, FPS_DEPTH);

	cfg.enable_stream(RS2_STREAM_COLOR, STREAM_INDEX_COLOR, WIDTH_COLOR, HEIGHT_COLOR, FORMAT_COLOR, FPS_COLOR);
	// 이게 왜 됨? 왜 되는 지 잘 모르겠음 되게 했긴 한데.. 그리고 위에 지워진 걸로 하면 왜 안 되는 지도 모르겠음
	m_profile = m_pipe.start(cfg);
	m_depth_scale = get_depth_scale(m_profile.get_device());
	//rs2::align align_to_color(RS2_STREAM_COLOR);
	//m_align_to_color
	m_align_to_color = new rs2::align(RS2_STREAM_COLOR);
	m_colorizer = new rs2::colorizer(RS_COLOR_SCHEME_WHITETOBLACK);

	float alpha = 0.5f;

	SetTimer(0, 1000 / 30, NULL);

	return 0;
}

void CMFCRSOPENCVDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (0 == nIDEvent)
	{
		rs2::frameset frameset = m_pipe.wait_for_frames();
		//cout << m_depth_scale << endl;
		frameset = m_align_to_color->process(frameset);
		auto depth = frameset.get_depth_frame();
		auto color = frameset.get_color_frame();
		auto colorized_depth = m_colorizer->colorize(depth);

		int width, height;

		width = colorized_depth.as<rs2::video_frame>().get_width();
		height = colorized_depth.as<rs2::video_frame>().get_height();
		Mat depth_frame(Size(width, height), CV_8UC3, (void*)colorized_depth.get_data(), Mat::AUTO_STEP);
		cvtColor(depth_frame, depth_frame, COLOR_BGR2RGB);
		mat_frame_depth = depth_frame.clone();

		Mat depth_frame2(Size(width, height), CV_16UC1, (void*)depth.get_data(), Mat::AUTO_STEP);
		mat_frame_depth2 = depth_frame2.clone();


		width = color.as<rs2::video_frame>().get_width();
		height = color.as<rs2::video_frame>().get_height();
		Mat color_frame(Size(width, height), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
		mat_frame_color = color_frame.clone();
		cvtColor(mat_frame_color, mat_frame_color, COLOR_BGR2RGB);

		imgproc();

	}


	CDialogEx::OnTimer(nIDEvent);
}


void CMFCRSOPENCVDlg::OnDestroy()
{

	delete( m_align_to_color );
	delete( m_colorizer );
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMFCRSOPENCVDlg::imgproc()
{
	setBgrFrame();
	depthtest();
	Detection();
	Track();
	
	//imshow("colorized_depth", mat_frame_depth);
	//imshow("color", mat_frame_color);

	Mat frame(1080, 1920, CV_8UC3, Scalar(255));
	if (mb_record)
	{
		( *videoWriter ) << mat_frame_color;

		fwrite(mat_frame_depth2.data, sizeof(unsigned short), WIDTH_COLOR * HEIGHT_COLOR, mfp_depth);
	}
	//if (mb_bgrismade)
	//{
	//	imshow("mat_background_frame", mat_background_frame);
	//}

	return;
}

void CMFCRSOPENCVDlg::setBgrFrame()
{
	if (mat_frame_color.empty())
	{
		return;
	}
	if (!mb_bgrismade)
	{
		if (vecmat_bgr_frames.size() < 32)
		{

			vecmat_bgr_frames.push_back(mat_frame_color);
			if (vecmat_bgr_frames.size() == 1)
			{
				mat_avgImg.create(vecmat_bgr_frames[0].rows, vecmat_bgr_frames[0].cols, CV_8UC3);
				mat_avgImg.setTo(Scalar(0, 0, 0));
			}
			MakeBgr();

			if (vecmat_bgr_frames.size() == 32)
			{
				mat_background_frame = mat_avgImg.clone();
				cvtColor(mat_background_frame, mat_background_frame_gray, COLOR_BGR2GRAY);
				mb_bgrismade = true;
				vecmat_bgr_frames.clear();
			}
		}
	}
	else
	{
		//imshow("mat_background_frame", mat_background_frame);
		if (!mb_detect)
		{
			if (vecmat_bgr_frames.size() < 32)
			{

				vecmat_bgr_frames.push_back(mat_frame_color);
				if (vecmat_bgr_frames.size() == 1)
				{
					mat_avgImg.setTo(Scalar(0, 0, 0));
				}
				MakeBgr();

				if (vecmat_bgr_frames.size() == 32)
				{
					mat_background_frame = mat_avgImg.clone();
					cvtColor(mat_background_frame, mat_background_frame_gray, COLOR_BGR2GRAY);
					vecmat_bgr_frames.clear();
				}
			}

		}
	}
	return;

}

void CMFCRSOPENCVDlg::setParams()
{
	mb_bgrismade = false;
	mb_detect = false;
	mb_record = false;
	m_depth_scale = 0.001;

	m_prev_box.top = 0;
	m_prev_box.left = 0;
	m_prev_box.right = 0;
	m_prev_box.bottom = 0;


	return;
}

void CMFCRSOPENCVDlg::MakeBgr()
{
	int frame_row = vecmat_bgr_frames[0].rows;
	int frame_col = vecmat_bgr_frames[0].cols;
	for (int row = 0; row < frame_row; row++)
	{
		for (int col = 0; col < frame_col; col++)
		{
			//mat_avgImg.at<Vec3b>(row, col)[0] += ( vecmat_bgr_frames[vecmat_bgr_frames.size() - 1].at<Vec3b>(row, col)[0] + 16 ) >> 5;
			//mat_avgImg.at<Vec3b>(row, col)[1] += ( vecmat_bgr_frames[vecmat_bgr_frames.size() - 1].at<Vec3b>(row, col)[1] + 16 ) >> 5;
			//mat_avgImg.at<Vec3b>(row, col)[2] += ( vecmat_bgr_frames[vecmat_bgr_frames.size() - 1].at<Vec3b>(row, col)[2] + 16 ) >> 5;
			mat_avgImg.at<Vec3b>(row, col)[0] += ( vecmat_bgr_frames[vecmat_bgr_frames.size() - 1].at<Vec3b>(row, col)[0] ) >> 5;
			mat_avgImg.at<Vec3b>(row, col)[1] += ( vecmat_bgr_frames[vecmat_bgr_frames.size() - 1].at<Vec3b>(row, col)[1] ) >> 5;
			mat_avgImg.at<Vec3b>(row, col)[2] += ( vecmat_bgr_frames[vecmat_bgr_frames.size() - 1].at<Vec3b>(row, col)[2] ) >> 5;

		}

	}
	return;

}

void CMFCRSOPENCVDlg::Detection()
{
	if (!mb_bgrismade)
	{
		return;
	}
	cvtColor(mat_frame_color, mat_buffer_frame, COLOR_BGR2GRAY);
	mat_buffer_frame2 = mat_buffer_frame.clone();
	Canny(mat_buffer_frame2, mat_buffer_frame2, 1, 200, 3, false);
	dilate(mat_buffer_frame2, mat_buffer_frame2, Mat(), Point(-1, -1), 1);

	Mat canny_frame = mat_buffer_frame2.clone();

	absdiff(mat_buffer_frame, mat_background_frame_gray, mat_buffer_frame);
	//imshow("output of absdiff", mat_buffer_frame);

	threshold(mat_buffer_frame, mat_buffer_frame, 40, 255, THRESH_BINARY);
	//imshow("output of threshold", mat_buffer_frame);

	erode(mat_buffer_frame, mat_buffer_frame, Mat(), Point(-1, -1), 3);
	dilate(mat_buffer_frame, mat_buffer_frame, Mat(), Point(-1, -1), 1);
	mat_buffer_frame = mat_depth_mask.clone();

	//imshow("mat_buffer_frame", mat_buffer_frame);

	//imshow("output of thresholding", mat_buffer_frame);
	int NumofLabels = connectedComponentsWithStats(mat_buffer_frame, mat_buffer_frame2, mat_stats, mat_centroids, 8, CV_32S);

	int area = 0;
	int top = 0;
	int left = 0;
	int width = 0;
	int height = 0;
	int numofBigBlobs = 0;
	//mui_MaxArea = 0, mui_MaxLabelIdx = 0;

	int max_left = mat_buffer_frame.cols;
	int max_right = 0;
	int max_top = mat_buffer_frame.rows;
	int max_bottom = 0;

	for (int labelIdx = 1; labelIdx < NumofLabels; labelIdx++)
	{
		area = mat_stats.at<int>(labelIdx, CC_STAT_AREA);
		if (area < 5000)
		{

		}
		else
		{
			left = mat_stats.at<int>(labelIdx, CC_STAT_LEFT);
			top = mat_stats.at<int>(labelIdx, CC_STAT_TOP);
			width = mat_stats.at<int>(labelIdx, CC_STAT_WIDTH);
			height = mat_stats.at<int>(labelIdx, CC_STAT_HEIGHT);
			numofBigBlobs++;
			max_left = left < max_left ? left : max_left;
			max_right = ( left + width ) > max_right ? ( left + width ) : max_right;
			max_top = top < max_top ? top : max_top;
			max_bottom = ( top + height ) > max_bottom ? ( top + height ) : max_bottom;


			//rectangle(mat_frame, Point(left, top), Point(left + width, top + height), Scalar(0, 255, 255), 3);
			//rectangle(mat_buffer_frame, Point(left, top), Point(left + width, top + height), Scalar(255, 0, 0), 3);
			//rectangle(mat_buffer_frame, Point(left + width / 2, top + height / 2), Point(left + width / 2 + 1, top + height / 2 + 1), Scalar(255, 0, 255), 3);

			//putText(mat_frame, "area :" + to_string(area), Point(left, top -20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 3);
			//putText(mat_buffer_frame, "area :" + to_string(area), Point(left, top -20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
			//putText(mat_frame, "labelIdx :" + to_string(labelIdx), Point(left, top + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
			//putText(mat_buffer_frame, "labelIdx :" + to_string(labelIdx), Point(left, top + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);


		}

	}

	//cout << numofBigBlobs << endl;
	//imshow("mat_buffer_frame", mat_buffer_frame);


	if (numofBigBlobs)
	{
		mb_detect = true;
		//putText(mat_frame, "# of Bigblobs :" + to_string(numofBigBlobs), Point(20, 980), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
		putText(mat_buffer_frame, "# of Bigblobs :" + to_string(numofBigBlobs), Point(20, 980), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
		//rectangle(mat_buffer_frame, Point(max_left, max_top), Point(max_right, max_bottom), Scalar(255, 0, 0), 10);
		Mat temp(canny_frame.size(), CV_8U, Scalar(0));
		Mat temp2;
		Mat roi;
		roi = temp(Rect(max_left, max_top, max_right - max_left, max_bottom - max_top));
		roi = Scalar(255);
		bitwise_or(mat_buffer_frame, canny_frame, temp2, temp);

		//bitwise_and(temp2, mat_depth_mask, mat_buffer_frame, temp);
		// ("mat_buffer_frame2", mat_buffer_frame2);
		//imshow("canny_frame", canny_frame);
		//imshow("temp", temp);
		//imshow("temp2", temp2);
		numofBigBlobs = 0;

		NumofLabels = connectedComponentsWithStats(temp2, mat_buffer_frame2, mat_stats, mat_centroids, 8, CV_32S);
		int maxIdx = 0;
		int maxArea = 0;
		for (int labelIdx = 1; labelIdx < NumofLabels; labelIdx++)
		{
			area = mat_stats.at<int>(labelIdx, CC_STAT_AREA);

			if (area < 4500)
			{

			}
			else
			{
				numofBigBlobs++;
				if (area > maxArea)
				{
					maxArea = area;
					maxIdx = labelIdx;
				}

			}
		}

		cout << numofBigBlobs << endl;
		if (numofBigBlobs)
		{
			left = mat_stats.at<int>(maxIdx, CC_STAT_LEFT);
			top = mat_stats.at<int>(maxIdx, CC_STAT_TOP);
			width = mat_stats.at<int>(maxIdx, CC_STAT_WIDTH);
			height = mat_stats.at<int>(maxIdx, CC_STAT_HEIGHT);
			if (!m_prev_box.left && !m_prev_box.right && !m_prev_box.top && !m_prev_box.bottom)
			{
				m_prev_box.left = left;
				m_prev_box.right = left + width;
				m_prev_box.top = top;
				m_prev_box.bottom = top + height;
				m_prev_box.pt.x = (int)( mat_centroids.at<double>(maxIdx, 0) );
				m_prev_box.pt.y = (int)( mat_centroids.at<double>(maxIdx, 1) );
				//line(mat_frame, prev_box.pt, prev_box.pt, Scalar(0, 255, 255), 10);
				mvp_points.push_back(m_prev_box.pt);
				rectangle(mat_buffer_frame, Point(left, top), Point(left + width, top + height), Scalar(255, 0, 0), 3);
				putText(mat_buffer_frame, "area :" + to_string(maxArea), Point(left, top - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);


			}
			else
			{
				int right = left + width;
				int bottom = top + height;
				int threshold = 60;

				int leftdiff = m_prev_box.left - left;
				int rightdiff = m_prev_box.right - right;
				int topdiff = m_prev_box.top - top;
				int bottomdiff = m_prev_box.bottom - bottom;

				if (leftdiff > -1 * threshold && leftdiff < threshold // 비슷한 bbox 있을 시 갱신
					&& rightdiff > -1 * threshold && rightdiff < threshold
					&& topdiff > -1 * threshold && topdiff < threshold
					&& bottomdiff > -1 * threshold && bottomdiff < threshold)
					//if (false)
				{
					rectangle(mat_buffer_frame, Point(left, top), Point(left + width, top + height), Scalar(255, 0, 0), 3);
					putText(mat_buffer_frame, "area :" + to_string(maxArea), Point(left, top - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
					m_prev_box.left = left;
					m_prev_box.right = left + width;
					m_prev_box.top = top;
					m_prev_box.bottom = top + height;

					m_prev_box.pt.x = (int)( mat_centroids.at<double>(maxIdx, 0) );
					m_prev_box.pt.y = (int)( mat_centroids.at<double>(maxIdx, 1) );
					//line(mat_frame, prev_box.pt, prev_box.pt, Scalar(0, 255, 255), 10);
					mvp_points.push_back(m_prev_box.pt);


				}
				else     // 없으면 이전 것 그대로 쓰기, 너무 오래 계속 이것만 쓰면 새로 갈아야함
				{

					if (m_bbox_update_cnt < 20)
					{
						rectangle(mat_buffer_frame, Point(m_prev_box.left, m_prev_box.top), Point(m_prev_box.right, m_prev_box.bottom), Scalar(255, 0, 0), 3);
						putText(mat_buffer_frame, "area :" + to_string(maxArea), Point(m_prev_box.left, m_prev_box.top - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);

						//line(mat_frame, prev_box.pt, prev_box.pt, Scalar(0, 255, 255), 10);
						mvp_points.push_back(m_prev_box.pt);


						m_bbox_update_cnt++;
					}
					else
					{
						m_bbox_update_cnt = 0;
						rectangle(mat_buffer_frame, Point(left, top), Point(left + width, top + height), Scalar(255, 0, 0), 3);
						putText(mat_buffer_frame, "area :" + to_string(maxArea), Point(left, top - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3);
						m_prev_box.left = left;
						m_prev_box.right = left + width;
						m_prev_box.top = top;
						m_prev_box.bottom = top + height;

						m_prev_box.pt.x = (int)( mat_centroids.at<double>(maxIdx, 0) );
						m_prev_box.pt.y = (int)( mat_centroids.at<double>(maxIdx, 1) );
						//line(mat_frame, prev_box.pt, prev_box.pt, Scalar(0, 255, 255), 10);
						mvp_points.push_back(m_prev_box.pt);



					}


				}
			}
		}

		//imshow("찾았을 때", mat_buffer_frame);
	}
	else
	{
		mb_detect = false;
	}
	String str = mb_detect ? "true" : "false";
	//putText(mat_frame, "mb_detect :" + str, Point(20, mat_frame.rows - 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 3);
	putText(mat_buffer_frame, "mb_detect :" + str, Point(20, mat_buffer_frame.rows - 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 3);
	//putText(mat_frame, "frame_number :" + to_string(frame_number), Point(20, mat_frame.rows - 180), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 3);
	//frame_number++;


	return;
}

void CMFCRSOPENCVDlg::Track()
{
	//detection 진행 중 아닐 때는 점 하나씩 지우는 것도 코드에 넣어야됨
	if (mb_detect)
	{
		if (mvp_points.size() < 30)
		{
			for (int i = 0; i < mvp_points.size(); i++)
			{
				line(mat_frame_color, mvp_points[i], mvp_points[i], Scalar(0, 255, 255), 10);
			}
		}
		else
		{
			mvp_points.erase(mvp_points.begin());
			for (int i = 0; i < mvp_points.size(); i++)
			{
				line(mat_frame_color, mvp_points[i], mvp_points[i], Scalar(0, 255, 255), 10);
			}
		}
	}
	else
	{
		if (mvp_points.size() > 0)
		{
			mvp_points.erase(mvp_points.begin());
		}
		for (int i = 0; i < mvp_points.size(); i++)
		{
			line(mat_frame_color, mvp_points[i], mvp_points[i], Scalar(0, 255, 255), 10);
		}
	}

	if (!mat_frame_color.empty() && !mat_buffer_frame.empty())
	{
		//imshow("mat_frame", mat_frame);
		imshow("mat_buffer_frame", mat_buffer_frame);
	}



	return;
}

float get_depth_scale(rs2::device dev)
{
	// Go over the device's sensors
	for (rs2::sensor& sensor : dev.query_sensors())
	{
		// Check if the sensor if a depth sensor
		if (rs2::depth_sensor dpt = sensor.as<rs2::depth_sensor>())
		{
			return dpt.get_depth_scale();
		}
	}
	throw std::runtime_error("Device does not have a depth sensor");
}

void CMFCRSOPENCVDlg::depthtest()
{
	float iPos = (float)m_sldTest.GetPos() / 20;
	cout << iPos << endl;
	int width = mat_frame_depth2.cols;
	int height = mat_frame_depth2.rows;




	const uint16_t* p_depth_frame = reinterpret_cast<const uint16_t*>(mat_frame_depth2.data);

	mat_depth_mask.create(height, width, CV_8UC1);
	uchar* pt = mat_depth_mask.data;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//pt[y * width + x] = p_depth_frame[y * width + x] % 255;
			auto pixel_distance = m_depth_scale * p_depth_frame[y * width + x];

			if (pixel_distance <= 0.f || pixel_distance > iPos)
			{
				pt[y * width + x] = 0;
			}
			else
			{
				pt[y * width + x] = 255;
			}


		}
	}

	//imshow("mat_depth_mask", mat_depth_mask);


	return;
}

void CMFCRSOPENCVDlg::OnBnClickedButtonRecord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CEdit* pBtnRecord;

	pBtnRecord = (CEdit*)GetDlgItem(IDC_BUTTON_RECORD);

	if (!mb_record)
	{
		videoWriter = new VideoWriter;
		mfp_depth = NULL;


		pBtnRecord->SetWindowText(_T("Stop"));
		mb_record = !mb_record;

		time_t timer = time(NULL);
		tm* t = localtime(&timer);
		String hour, min, sec;
		hour = t->tm_hour < 10 ? "0" + to_string(t->tm_hour) : to_string(t->tm_hour);
		min = t->tm_min < 10 ? "0" + to_string(t->tm_min) : to_string(t->tm_min);
		sec = t->tm_sec < 10 ? "0" + to_string(t->tm_sec) : to_string(t->tm_sec);

		float fps = 30.0;
		int width = 1920;
		int height = 1080;
		String filepath, outputvideoname;
		filepath = "C:/videos/RGBD/";
		outputvideoname = filepath + hour + min + sec + "_" + to_string(width) + "x" + to_string(height) + ".yuv";
		const char* filename = "C:/videos/RGBD/depth/221202depth.d16";

		//videoWriter->open(outputvideoname, videoWriter->fourcc('M', 'J', 'P', 'G'), fps, Size(width, height), true);
		videoWriter->open(outputvideoname, videoWriter->fourcc('N', 'V', '2', '1'), fps, Size(width, height), true);
		//videoWriter->open(outputvideoname, -1, fps, Size(width, height), true);
		mfp_depth = fopen(filename, "w+b");


	}
	else
	{
		pBtnRecord->SetWindowTextW(_T("Record"));
		mb_record = !mb_record;
		delete videoWriter;
		fclose(mfp_depth);
	}



}

void CMFCRSOPENCVDlg::rs_init_load()
{
	FILE* fp = fopen("C:/videos/RGBD/depth/221205depth.d16", "rb");
	FILE* fp2 = fopen("C:/videos/RGBD/154430_1920x1080.yuv", "rb");

	if (fp == NULL || fp2 == NULL)
	{
		cout << "error" << endl;
	}

	unsigned short* buffer;
	unsigned char* buffer2;
	buffer = new unsigned short[1920 * 1080];
	buffer2 = new unsigned char[1920 * 1080 * 3 / 2];

	int width = 1920;
	int height = 1080;

	while (fread(buffer, sizeof(unsigned short), 1080 * 1920, fp) != NULL)
	{

		Mat test(height, width, CV_16UC1, (void*)buffer);
		mat_frame_depth2 = test.clone();
		int max = 0;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				max = test.at<unsigned short>(y, x) > max ? test.at<unsigned short>(y, x) : max;
			}
		}

		int scaling_factor = max / 257;
		Mat test2(height, width, CV_8UC1);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				test2.at<unsigned char>(y, x) = (unsigned char)( test.at<unsigned short>(y, x) / scaling_factor );
			}
		}
		//test = test / 256;
		test2 = test2.clone();
		//imshow("test2", test2);
		fread(buffer2, sizeof(unsigned char), 1080 * 1920 * 3 / 2, fp2);
		Mat test3(height * 1.5, width, CV_8UC1, (void*)buffer2);
		cvtColor(test3, test3, COLOR_YUV2RGB_YV12);
		//imshow("test3", test3);

		mat_frame_color = test3.clone();

		imgproc();


		waitKey(33);
	}

	//while (fread(buffer2, sizeof(unsigned char), 1080 * 1920 * 3 / 2, fp2) != NULL)
	//{

	//	Mat test3(height * 1.5, width, CV_8UC1, (void*)buffer2);
	//	cvtColor(test3, test3, COLOR_YUV2RGB_YV12);
	//	imshow("test3", test3);
	//	waitKey(33);

	//}


	delete[] buffer;
	delete[] buffer2;
	if (!fp)
	{
		fclose(fp);
	}
	if (!fp2)
	{
		fclose(fp2);
	}


	return;
}

void CMFCRSOPENCVDlg::OnBnClickedButtonSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nCurSel = m_ctrlBox.GetCurSel();


	if (nCurSel >-1)
	{
		//CString strText = _T("");
		//strText.Format(_T("현재 선택한 콤보 박스의 인덱스는 %d 입니다."), nCurSel);
		//MessageBox(strText);

		if (0 == nCurSel)
		{
			rs_init_live();
		}
		else if (1 == nCurSel)
		{
			rs_init_load();
		}
	}
}

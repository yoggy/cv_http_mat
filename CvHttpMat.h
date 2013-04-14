#pragma once

// for cURL
#include <curl/curl.h>

// for OpenCV2
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef WIN32
	#pragma comment(lib, "libcurl.lib")
	#ifdef _DEBUG
		#pragma comment(lib, "opencv_core244d.lib")
		#pragma comment(lib, "opencv_imgproc244d.lib")
		#pragma comment(lib, "opencv_highgui244d.lib")
	#else
		#pragma comment(lib, "opencv_core244.lib")
		#pragma comment(lib, "opencv_imgproc244.lib")
		#pragma comment(lib, "opencv_highgui244.lib")
	#endif
#endif

class CvHttpMat
{
	public:
		CvHttpMat();
		virtual ~CvHttpMat();

		std::string url() const;
		void url(const std::string &val);

		cv::Mat image() const;

		void clear();
		bool download();

	protected:
		size_t recv_data_(void *buffer, size_t size, size_t nmemb);
		static size_t recv_data_static_(void *buffer, size_t size, size_t nmemb, void *userdata);

	private:
		CURL     *curl_;

		std::string url_;
		cv::Mat image_;

		std::vector<uchar> recv_buf_;
};

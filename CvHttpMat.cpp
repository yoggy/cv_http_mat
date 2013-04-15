#include "CvHttpMat.h"

CvHttpMat::CvHttpMat() : url_(""), curl_(NULL)
{
}

CvHttpMat::~CvHttpMat()
{
}

std::string CvHttpMat::url() const
{
	return this->url_;
}

void CvHttpMat::url(const std::string &val)
{
	this->url_ = val;
}

cv::Mat CvHttpMat::image() const
{
	return image_;
}

void CvHttpMat::clear()
{
	image_.release();
	recv_buf_.clear();

	if (curl_ != NULL) {
		curl_easy_cleanup(curl_);
		curl_ = NULL;
	}
}

bool CvHttpMat::download()
{
	CURLcode res;

	recv_buf_.clear();

	curl_ = curl_easy_init();
	curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void *)this);
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, CvHttpMat::recv_data_static_);

	res = curl_easy_perform(curl_);

	if(res != CURLE_OK) {
		printf("curl_easy_perform() failed...%s\n", curl_easy_strerror(res));
		clear();
		return false;
	}

	image_ = cv::imdecode(recv_buf_, -1);
	if (image_.empty()) {
		clear();
		return false;
	}

	curl_easy_cleanup(curl_);
	curl_ = NULL;

	return true;
}

size_t CvHttpMat::recv_data_(void *buffer, size_t size, size_t nmemb)
{
	size_t segsize = size * nmemb;

	size_t old_size = recv_buf_.size();
	recv_buf_.resize(old_size + segsize);
	memcpy((&(recv_buf_[old_size])), buffer, segsize);

	return segsize;
}

size_t CvHttpMat::recv_data_static_(void *buffer, size_t size, size_t nmemb, void *userdata)
{
	CvHttpMat *http = (CvHttpMat*)userdata;
	return http->recv_data_(buffer, size, nmemb);
}


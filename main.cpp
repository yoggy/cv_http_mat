#ifdef WIN32
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif 

#include "CvHttpMat.h"

void usage(int argc, char* argv[])
{
	printf("usage : %s [image source url]\n");
	printf("\n");
	printf("    example\n");
	printf("        %s http://farm8.staticflickr.com/7118/7446163748_fd8ace754f.jpg\n");
	printf("\n");
	exit(1);
}

int main(int argc, char* argv[])
{
	if (argc != 2) usage(argc, argv);

	CvHttpMat http_mat;
	http_mat.url(argv[1]);

	while(true) {
		http_mat.download();
		if(!http_mat.image().empty()) {
			cv::imshow("image", http_mat.image());
		}

		int c = cv::waitKey(1);
		if (c == 27) break;
	}

	return 0;
}



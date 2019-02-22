#include "fix_rotate.h"
Mat fix_rotate::fix_rotate(char *inputfile)
{
	try
	{
		tesseract::Orientation orientation;
		tesseract::WritingDirection direction;
		tesseract::TextlineOrder order;
		float deskew_angle;
		
		PIX *image = pixRead(inputfile);
		
		tesseract::TessBaseAPI *api_osd = new tesseract::TessBaseAPI();
		if (api_osd->Init(NULL, "eng"))
		{
			printf("Could not initialize tesseract.\n");
		}
		
		api_osd->SetPageSegMode(tesseract::PSM_AUTO_OSD);
		api_osd->SetImage(image);
		api_osd->Recognize(0);
	
		tesseract::PageIterator *it = api_osd->AnalyseLayout();
		cv::Mat src = cv::imread(inputfile, cv::IMREAD_UNCHANGED);
		if (it == NULL)
		{
			return src;
		}
		it->Orientation(&orientation, &direction, &order, &deskew_angle);
		cout<<26<<endl;
		printf("Orientation: %d;\nWritingDirection: %d\nTextlineOrder: %d\n"
			   "Deskew angle: %.4f\n",
			   orientation, direction, order, deskew_angle);
		//printf("%d", cv::ROTATE_90_COUNTERCLOCKWISE);

		
		double angle = 90 * orientation;

		// get rotation matrix for rotating the image around its center in pixel coordinates
		cv::Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
		cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
		// determine bounding rectangle, center not relevant
		cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
		// adjust transformation matrix
		rot.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
		rot.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;

		cv::Mat dst;
		cv::warpAffine(src, dst, rot, bbox.size());
		return dst;
	}
	catch (cv::Exception &e)
	{
		const char *err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
	}
}

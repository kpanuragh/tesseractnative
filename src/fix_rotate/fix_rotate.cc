#include "fix_rotate.h"
// Return the rotation matrices for each rotation
void fix_rotate::rotate(Mat& src, double angle, Mat& dst)
{
	Point2f pt(src.cols / 2., src.rows / 2.);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
}
Mat fix_rotate::fix_rotate(char* inputfile)
{
    cv::Mat im = cv::imread(inputfile);
	tesseract::Orientation orientation;
	tesseract::WritingDirection direction;
	tesseract::TextlineOrder order;
	float deskew_angle;
	PIX *image = pixRead(inputfile);
	tesseract::TessBaseAPI  *api_osd = new tesseract::TessBaseAPI();
	if (api_osd->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		getchar();
		exit(1);
	}
	api_osd->SetPageSegMode(tesseract::PSM_AUTO_OSD);
	api_osd->SetImage(image);
	api_osd->Recognize(0);

	tesseract::PageIterator* it = api_osd->AnalyseLayout();
	it->Orientation(&orientation, &direction, &order, &deskew_angle);
	printf("Orientation: %d;\nWritingDirection: %d\nTextlineOrder: %d\n" \
		"Deskew angle: %.4f\n",
		orientation, direction, order, deskew_angle);
	//printf("%d", cv::ROTATE_90_COUNTERCLOCKWISE);

	 // Make larger image
	int rows = im.rows;
	int cols = im.cols;
	int largest = 0;
	if (rows > cols) {
		largest = rows;
	}
	else {
		largest = cols;
	}
	Mat temp = Mat::zeros(largest, largest, CV_8UC3);

	// Copy your original image
	// First define the roi in the large image --> draw this on a paper to make it clear
	// There are two possible cases
	Rect roi;
	if (im.rows > im.cols) {
		roi = Rect((temp.cols - im.cols) / 2, 0, im.cols, im.rows);
	}
	if (im.cols > im.rows) {
		roi = Rect(0, (temp.rows - im.rows) / 2, im.cols, im.rows);
	}

	// Copy the original to the black large temp image
	im.copyTo(temp(roi));

	// Rotate the image
	Mat rotated = temp.clone();
	fix_rotate::rotate(temp, orientation*90, rotated);
	Mat result = rotated(Rect(roi.y, roi.x, roi.height, roi.width)).clone();
    return result;
}
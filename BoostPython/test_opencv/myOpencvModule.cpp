#include <boost/python.hpp>
#include <opencv2/opencv.hpp>

void showImage()
{
    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
    cv::imshow("", image);
    cv::waitKey(0);
}

BOOST_PYTHON_MODULE( myOpencvModule ) {
    boost::python::def("showImage", &showImage);
}
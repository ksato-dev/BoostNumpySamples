// boost libs
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

// #include <boost/python/module.hpp>
// #include <boost/python/def.hpp>
// #include <boost/python/class.hpp>
// #include <boost/python/tuple.hpp>
// #include <boost/python/extract.hpp>

// #include <boost/python/object/pickle_support.hpp>

// cv libs
#include <opencv2/opencv.hpp>

// std libs
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

// original
// #include "boost_python_pickle.hpp"
// class_name_suite hoge;

class Utils
{
public:
    int imgWidth, imgHeight;
    // std::istream ifs;
    // const char *cal_dir;

    // calibration matrices
    // cv::Mat mtx;
    // cv::Mat dist;
    // boost::python::numpy::ndarray mtx;
    // boost::python::numpy::ndarray dist;

//    void setCalibratedMatrices(const boost::python::dict &pickle) {
//        int len = boost::python::len(pickle);
//        boost::python::list keys = pickle.keys();
//
//        for (int sId = 0; sId < len; sId++)
//        {
//            std::string str = boost::python::extract<std::string>(keys[sId]);
//            // if (str == "mtx") this->mtx = boost::python::extract<cv::Mat>(pickle[str]);
//            // else if (str == "dist") this->dist = boost::python::extract<cv::Mat>(pickle[str]);
//            if (str == "mtx") {
//                auto mtx = boost::python::extract<boost::python::numpy::ndarray>(pickle[str]);
//                // std::cout << mtx << std::endl;
//            }
//            else if (str == "dist") {
//                auto dist = boost::python::extract<boost::python::numpy::ndarray>(pickle[str]);
//                // std::cout << dist << std::endl;
//            }
//
//        }
//    }

    void setMTX(boost::python::numpy::ndarray np_mtx) {
        const double* data = reinterpret_cast<double *>(np_mtx.get_data()) ;
        std::cout << data[0] << std::endl;
    }

    void setImgSize(const int width, const int height)
    {
        this->imgWidth = width;
        this->imgHeight = height;

        // cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
        // cv::imshow("", image);
        // cv::waitKey(0);
    }

    // cv::Mat undistort(const cv::Mat &img, cv::Mat &dst, const cv::Mat &mtx, cv::Mat &dst) {
    // cv::Mat undistort(const cv::Mat &img, cv::Mat &dst, const boost::python::dict &pickle) {
    //     cv::Mat mtx = boost::python::extract<std::string>()
    //     cv::undistort(img, img, pickle, img)
    // }

};

BOOST_PYTHON_MODULE(curvedLaneDetectionUtils)
{
    Py_Initialize();
    boost::python::numpy::initialize();
    using namespace boost::python;
    class_<Utils>("Utils")
    .def("setMTX", &Utils::setMTX)
    .def("setImgSize", &Utils::setImgSize);
}
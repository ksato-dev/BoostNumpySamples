#include "CubicSpline/CppCubicSpline/CppCubicSpline.h"
//
// #include <boost/python.hpp>
#include <boost/python/numpy.hpp>

// #include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace p = boost::python;
namespace np = boost::python::numpy;

const double get_value_from_2darray(const np::ndarray &array_2dim,
                              const int x, const int y,
                              const int stride_x, const int stride_y)
{
    return *reinterpret_cast<uint8_t *>(
        array_2dim.get_data() + y * stride_y + x * stride_x);
}

const std::vector<double> extract_curved_points(const np::ndarray &curved_bin_image)
{
    int nd = curved_bin_image.get_nd();

    if (nd != 2)
    {
        std::cout << "Must 2 Dimension" << std::endl;
        throw std::runtime_error("a must be two-dimensional");
        return std::vector<double>();
    }

    // params of ndarray
    const int size_y = curved_bin_image.shape(0);
    const int size_x = curved_bin_image.shape(1);
    const int stride_y = curved_bin_image.get_strides()[0];
    const int stride_x = curved_bin_image.get_strides()[1];

    // extract points per each y-pixels.
    std::vector<double> curved_points(size_y, -1.0);
    // std::vector<double> curved_points;
    for (int y = 0; y < size_y; y++)
    {
        int min_x = 1e9;
        int max_x = -1e9;
        bool min_flag = false;
        bool max_flag = false;
        for (int x = 0; x < size_x; x++)
        {
            const double curr_value = get_value_from_2darray(curved_bin_image, x, y, stride_x, stride_y);

            if (curr_value < 255)
                continue;

            // std::cout << "(y, x) = (" << y << ", " << x << "), value:" << curr_value << std::endl;
            if (x < min_x)
            {
                min_x = x;
                min_flag = true;
            }
            if (x > max_x)
            {
                max_x = x;
                max_flag = true;
            }
        }
        if (min_flag == false && max_flag == false)
            continue;

        // std::cout << "y = " << y << "; (min_x, max_x) = (" << min_x << ", " << max_x << ")" << std::endl;
        const double mean_x = (min_x + max_x) * 0.5;
        // std::cout << "mean_x = " << mean_x << std::endl;
        // curved_points[y] = std::round(mean_x);
        curved_points[y] = std::round(mean_x);
    }

    return curved_points;
}

// const np::ndarray spline_fitting2(const std::vector<double> &curved_points)
void spline_fitting3(const std::vector<double> &curved_points)
{
    CppCubicSpline cppCubicSpline(curved_points);
    vector<double> rx;
    vector<double> ry;
    for (double i = 0.0; i <= curved_points.size(); i += 1.0)
    {
        rx.push_back(i);
        ry.push_back(cppCubicSpline.Calc(i));
    }

    for (int id = 0; id < curved_points.size(); id++)
        std::cout << ry[id] << " " << rx[id] << std::endl;
}

np::ndarray polyfit(const np::ndarray &curved_bin_image)
// np::ndarray polyfit(np::ndarray curved_bin_image)
{
    int nd = curved_bin_image.get_nd();
    // std::cout << "dim: " << nd << std::endl;

    // spline fitting (2 dim)

    spline_fitting3(extract_curved_points(curved_bin_image));
    
    p::tuple shape = p::make_tuple(2);
    np::dtype dtype = np::dtype::get_builtin<double>();
    return np::zeros(shape, dtype);
}

BOOST_PYTHON_MODULE( polyfit_curved_lane ) {
    Py_Initialize();
    np::initialize();

    p::def("polyfit", &polyfit);
}

// #include "CubicSpline/CppCubicSpline/CppCubicSpline.h"
#include "spline/src/spline.h"
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

np::ndarray convert_vec2ndarray(const std::vector<double> &curved_fitting_x)
{
    Py_intptr_t shape[1] = {curved_fitting_x.size()};
    np::ndarray result = np::zeros(1, shape, np::dtype::get_builtin<double>());
    std::copy(curved_fitting_x.begin(), curved_fitting_x.end(), reinterpret_cast<double*>(result.get_data()));
    return result;
}

const np::ndarray extract_curved_points(const np::ndarray &curved_bin_image, const int step = 10)
{
    int nd = curved_bin_image.get_nd();

    if (nd != 2)
    {
        std::cout << "Must 2 Dimension" << std::endl;
        throw std::runtime_error("a must be two-dimensional");
        // return std::vector<double>();
    }

    // params of ndarray
    const int size_y = curved_bin_image.shape(0);
    const int size_x = curved_bin_image.shape(1);
    const int stride_y = curved_bin_image.get_strides()[0];
    const int stride_x = curved_bin_image.get_strides()[1];

    std::cout << "size_y:" << size_y << std::endl;

    // extract points per each y-pixels.
    std::vector<double> curved_points_x;
    std::vector<double> curved_points_y;
    // std::vector<double> curved_points;
    for (int y = 0; y < size_y; y += step)
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
        // std::cout << "mean_x = " << std::round(mean_x) << std::endl;
        // std::cout << std::endl;
        // curved_points[y] = std::round(mean_x);
        // curved_points[y] = std::round(mean_x);
        curved_points_x.push_back(std::round(mean_x));
        curved_points_y.push_back(y);

    }
    std::cout << "size:" << curved_points_y.size() << std::endl;

    // spline fitting (3dim)
    std::vector<double> ret_curved_x_from(size_y, -1);

#if 1
    tk::spline spline_util;
    spline_util.set_points(curved_points_y, curved_points_x);

    for (int y = 0; y < size_y; y++)
    {
        const int x = spline_util(y);
        std::cout << "x:" << x << ", y:" << y << std::endl;
        ret_curved_x_from[y] = x;
    }

#else
    int y_count = 0;
    CppCubicSpline cppCubicSplineX(curved_points_x);
#if 0
    for (int y = 0; y < size_y; y++)
    {
        const double calc_x = cppCubicSplineX.Calc((double)y);
        ret_curved_y[y] = calc_x;
        std::cout << calc_x << ", " << y << std::endl;
    }
#else
    const int num_curved_range = curved_points_x.size();
    for (int _y = 0; _y < num_curved_range + 1; _y++)
    {

        double curved_y = 0.0;
        if (_y > 0)
            curved_y = curved_points_y[_y - 1];

        double next_curved_y = size_y - 1;
        if (_y <= num_curved_range - 1)
            next_curved_y = curved_points_y[_y];

        const double real_range_y = next_curved_y - curved_y;
        const double delta_ry = 1.0 / real_range_y;
        std::cout << "real range y:" << real_range_y << std::endl;
        std::cout << "delta_ry:" << delta_ry << std::endl;
        for (double y = 0.0; y < 1.0; y += delta_ry)
        {
            const double in_y = _y + y;
            const double calc_x = cppCubicSplineX.Calc(in_y);
            ret_curved_y[y_count++] = calc_x;
            std::cout << "calc_x" << calc_x << std::endl;
            std::cout << "real y: " << curved_y + in_y * real_range_y << ", y:" << in_y << std::endl;
            std::cout << std::endl;
        }

        std::cout << "y count:" << y_count << std::endl;
        // ret_curved_y.push_back(calc_x);
    }
#endif
#endif

    return convert_vec2ndarray(ret_curved_x_from);
}

#if 0
// const np::ndarray spline_fitting2(const std::vector<double> &curved_points)
void spline_fitting3(const std::vector<double> &curved_points, const int size_p)
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
#endif

const np::ndarray polyfit(const np::ndarray &curved_bin_image, const int step_y)
// np::ndarray polyfit(np::ndarray curved_bin_image)
{
    int nd = curved_bin_image.get_nd();
    // std::cout << "dim: " << nd << std::endl;

    // spline fitting (2 dim)

    return extract_curved_points(curved_bin_image, step_y);
    // spline_fitting3(extract_curved_points(curved_bin_image));
    
    // p::tuple shape = p::make_tuple(2);
    // np::dtype dtype = np::dtype::get_builtin<double>();
    // return np::zeros(shape, dtype);
}

BOOST_PYTHON_MODULE( polyfit_curved_lane ) {
    Py_Initialize();
    np::initialize();

    p::def("polyfit", &polyfit);
}

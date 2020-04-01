// #include <boost/python.hpp>
#include <boost/python/numpy.hpp>

// #include <stdexcept>
// #include <algorithm>
#include <iostream>

namespace p = boost::python;
namespace np = boost::python::numpy;

const double get_value_from_2darray(const np::ndarray &array_2dim,
                              const int x, const int y,
                              const int stride_x, const int stride_y)
{
    return *reinterpret_cast<double *>(
        array_2dim.get_data() + y * stride_y + x * stride_x);
}

void extract_curved_points(const np::ndarray &curved_bin_image)
{
    int nd = curved_bin_image.get_nd();
    std::cout << "__dim: " << nd << std::endl;

    if (nd != 2)
    {
        std::cout << "Must 2 Dimension" << std::endl;
        throw std::runtime_error("a must be two-dimensional");
        return;
    }

    double *dbl_data = reinterpret_cast<double *>(curved_bin_image.get_data());

    // params of ndarray
    int count = 0;
    const int size_y = curved_bin_image.shape(0);
    const int size_x = curved_bin_image.shape(1);
    const int stride_y = curved_bin_image.get_strides()[0];
    const int stride_x = curved_bin_image.get_strides()[1];

    // extract points per each y-pixels.
    for (int y = 0; y < size_y; y++)
	    for (int x = 0; x < size_x; x++)
        {
#if 0
            std::cout << "y:" << y << ", x:" << x 
		<< ", val:"
                << *reinterpret_cast<double *>
                (curved_bin_image.get_data()
                + y * stride_y + x * stride_x)
                << std::endl;
#else
            const double curr_value = get_value_from_2darray(curved_bin_image, x, y, stride_x, stride_y);
            std::cout << "(y, x) = (" << y << ", " << x << "), value:" << curr_value << std::endl;
#endif
            count++;
        }

    std::cout << "count: " << count << std::endl;
    // return np::ndarray();
}

np::ndarray spline_fitting2(np::ndarray curved_points)
{

}

np::ndarray polyfit(const np::ndarray &curved_bin_image)
// np::ndarray polyfit(np::ndarray curved_bin_image)
{
    int nd = curved_bin_image.get_nd();
    std::cout << "dim: " << nd << std::endl;

    // spline fitting (2 dim)

    extract_curved_points(curved_bin_image);
    
    p::tuple shape = p::make_tuple(2);
    np::dtype dtype = np::dtype::get_builtin<double>();
    return np::zeros(shape, dtype);
}

BOOST_PYTHON_MODULE( polyfit_curved_lane ) {
    Py_Initialize();
    np::initialize();

    p::def("polyfit", &polyfit);
}

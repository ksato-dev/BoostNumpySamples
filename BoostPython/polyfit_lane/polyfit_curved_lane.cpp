// #include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>

namespace p = boost::python;
namespace np = boost::python::numpy;

void extract_curved_points(const np::ndarray &curved_bin_image)
{
    int nd = curved_bin_image.get_nd();
    std::cout << "__dim: " << nd << std::endl;

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

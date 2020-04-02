// #include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <iostream>

namespace p = boost::python;
namespace np = boost::python::numpy;

void polyfit(np::ndarray np_array)
{
    int nd = np_array.get_nd();
    std::cout << "dim: " << nd << std::endl;
}

BOOST_PYTHON_MODULE( polyfit_curved_lane ) {
    Py_Initialize();
    np::initialize();

    p::def("polyfit", &polyfit);
}

#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/extract.hpp>
#include "class_name.hpp"

struct class_name_suite : boost::python::pickle_suite
{
    //static
    //boost::python::tuple
    //getinitargs(const ipr::pcap_input& w)
    //{ 
    //    return boost::python::make_tuple(w.id);
    //} 
        
                                
    static
    boost::python::tuple getstate(boost::python::object w_obj)
    {   
        class_name const& w = boost::python::extract<class_name const&>(w_obj)();
        return boost::python::make_tuple(
                  w_obj.attr("__dict__") //If the python object has other attributes, they will be stored in the dict
                , w.id
                , w.status);
    }   
    static
    void
    setstate(boost::python::object w_obj, boost::python::tuple state)
    {   
        using namespace boost::python;
        class_name& w = extract<class_name&>(w_obj)();
        // restore the object's __dict__
        dict d = extract<dict>(w_obj.attr("__dict__"))();
        d.update(state[0]);
        w.id = extract<std::string>(state[1]);
        w.status = extract<std::string>(state[2]);
    }   
    static bool getstate_manages_dict() { return true; }
};

//exporting the c++ class
#include <boost/python.hpp>

 class_<class_name,  boost::noncopyable>("class_name")
    .enable_pickling()         
    .def_pickle(class_name_suite()) 
    .def("get_tag", &class_name::get_tag)
    
//sample test 
   @nose.tools.with_setup(setUp)
    def test_persist_class_name(self):
        from my_classes import class_name
        input = class_name.create()
        input.id = "Test_Source"
        input.status = 'Completed'
        
        import pickle
        pickled1 = pickle.dumps(input, 0)
        pickled2 = pickle.dumps(input, 1)
        pickled3 = pickle.dumps(input, 2)
        unpickled = pickle.loads(pickled)
        self.assertEqual(unpickled.id, input.id)
        self.assertEqual(unpickled.status, input.status)


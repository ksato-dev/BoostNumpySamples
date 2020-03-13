#include "Python.h"
extern int add(int, int);
extern void out(const char*, const char*);

PyObject* hello_add(PyObject* self, PyObject* args)
{
    int x, y, g;

    if (!PyArg_ParseTuple(args, "ii", &x, &y))
        return NULL;
    g = add(x, y);
    return Py_BuildValue("i", g);
}

PyObject* hello_out(PyObject* self, PyObject* args, PyObject* kw)
{
    const char* adrs = NULL;
    const char* name = NULL;
    static char* argnames[] = {"adrs", "name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kw, "|ss",
            argnames, &adrs, &name))
        return NULL;
    out(adrs, name);
    return Py_BuildValue("");
}

static PyMethodDef hellomethods[] = {
    {"add", hello_add, METH_VARARGS},
    {"out", hello_out, METH_VARARGS | METH_KEYWORDS},
    {NULL}
};

static struct PyModuleDef hellomodule =
{
    PyModuleDef_HEAD_INIT,
    "hellomodule", /* name of module */
    "",            /* module documentation, may be NULL */
    -1,            /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    hellomethods
};

PyMODINIT_FUNC PyInit_hellomodule(void)
{
    return PyModule_Create(&hellomodule);
}

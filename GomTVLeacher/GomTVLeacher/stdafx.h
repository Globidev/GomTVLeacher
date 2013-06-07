#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
namespace bp = boost::python;

#include <functional>
#include <algorithm>
#include <thread>

#define Constant static const auto
#define Global static auto
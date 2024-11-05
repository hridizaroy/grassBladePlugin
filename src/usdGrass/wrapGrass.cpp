//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "./grass.h"
#include "pxr/usd/usd/schemaBase.h"

#include "pxr/usd/sdf/primSpec.h"

#include "pxr/usd/usd/pyConversions.h"
#include "pxr/base/tf/pyContainerConversions.h"
#include "pxr/base/tf/pyResultConversions.h"
#include "pxr/base/tf/pyUtils.h"
#include "pxr/base/tf/wrapTypeHelpers.h"

#include <boost/python.hpp>

#include <string>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

#define WRAP_CUSTOM                                                     \
    template <class Cls> static void _CustomWrapCode(Cls &_class)

// fwd decl.
WRAP_CUSTOM;

        
static UsdAttribute
_CreateRadiusAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateRadiusAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double), writeSparsely);
}
        
static UsdAttribute
_CreateHeightAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateHeightAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double), writeSparsely);
}
        
static UsdAttribute
_CreateHeightPosAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateHeightPosAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double), writeSparsely);
}
        
static UsdAttribute
_CreateHorizontalStretchAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateHorizontalStretchAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double), writeSparsely);
}
        
static UsdAttribute
_CreateThinningAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateThinningAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double), writeSparsely);
}
        
static UsdAttribute
_CreateColorAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateColorAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Color3f), writeSparsely);
}
        
static UsdAttribute
_CreateExtentAttr(UsdGrassGrass &self,
                                      object defaultVal, bool writeSparsely) {
    return self.CreateExtentAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float3Array), writeSparsely);
}

static std::string
_Repr(const UsdGrassGrass &self)
{
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf(
        "UsdGrass.Grass(%s)",
        primRepr.c_str());
}

} // anonymous namespace

void wrapUsdGrassGrass()
{
    typedef UsdGrassGrass This;

    class_<This, bases<UsdGeomGprim> >
        cls("Grass");

    cls
        .def(init<UsdPrim>(arg("prim")))
        .def(init<UsdSchemaBase const&>(arg("schemaObj")))
        .def(TfTypePythonClass())

        .def("Get", &This::Get, (arg("stage"), arg("path")))
        .staticmethod("Get")

        .def("Define", &This::Define, (arg("stage"), arg("path")))
        .staticmethod("Define")

        .def("GetSchemaAttributeNames",
             &This::GetSchemaAttributeNames,
             arg("includeInherited")=true,
             return_value_policy<TfPySequenceToList>())
        .staticmethod("GetSchemaAttributeNames")

        .def("_GetStaticTfType", (TfType const &(*)()) TfType::Find<This>,
             return_value_policy<return_by_value>())
        .staticmethod("_GetStaticTfType")

        .def(!self)

        
        .def("GetRadiusAttr",
             &This::GetRadiusAttr)
        .def("CreateRadiusAttr",
             &_CreateRadiusAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))
        
        .def("GetHeightAttr",
             &This::GetHeightAttr)
        .def("CreateHeightAttr",
             &_CreateHeightAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))
        
        .def("GetHeightPosAttr",
             &This::GetHeightPosAttr)
        .def("CreateHeightPosAttr",
             &_CreateHeightPosAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))
        
        .def("GetHorizontalStretchAttr",
             &This::GetHorizontalStretchAttr)
        .def("CreateHorizontalStretchAttr",
             &_CreateHorizontalStretchAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))
        
        .def("GetThinningAttr",
             &This::GetThinningAttr)
        .def("CreateThinningAttr",
             &_CreateThinningAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))
        
        .def("GetColorAttr",
             &This::GetColorAttr)
        .def("CreateColorAttr",
             &_CreateColorAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))
        
        .def("GetExtentAttr",
             &This::GetExtentAttr)
        .def("CreateExtentAttr",
             &_CreateExtentAttr,
             (arg("defaultValue")=object(),
              arg("writeSparsely")=false))

        .def("__repr__", ::_Repr)
    ;

    _CustomWrapCode(cls);
}

// ===================================================================== //
// Feel free to add custom code below this line, it will be preserved by 
// the code generator.  The entry point for your custom code should look
// minimally like the following:
//
// WRAP_CUSTOM {
//     _class
//         .def("MyCustomMethod", ...)
//     ;
// }
//
// Of course any other ancillary or support code may be provided.
// 
// Just remember to wrap code in the appropriate delimiters:
// 'namespace {', '}'.
//
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

namespace {

WRAP_CUSTOM {
}

}

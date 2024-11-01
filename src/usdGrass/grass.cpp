//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "./grass.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdGrassGrass,
        TfType::Bases< UsdGeomGprim > >();
    
    // Register the usd prim typename as an alias under UsdSchemaBase. This
    // enables one to call
    // TfType::Find<UsdSchemaBase>().FindDerivedByName("Grass")
    // to find TfType<UsdGrassGrass>, which is how IsA queries are
    // answered.
    TfType::AddAlias<UsdSchemaBase, UsdGrassGrass>("Grass");
}

/* virtual */
UsdGrassGrass::~UsdGrassGrass()
{
}

/* static */
UsdGrassGrass
UsdGrassGrass::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdGrassGrass();
    }
    return UsdGrassGrass(stage->GetPrimAtPath(path));
}

/* static */
UsdGrassGrass
UsdGrassGrass::Define(
    const UsdStagePtr &stage, const SdfPath &path)
{
    static TfToken usdPrimTypeName("Grass");
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdGrassGrass();
    }
    return UsdGrassGrass(
        stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdGrassGrass::_GetSchemaKind() const
{
    return UsdGrassGrass::schemaKind;
}

/* static */
const TfType &
UsdGrassGrass::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdGrassGrass>();
    return tfType;
}

/* static */
bool 
UsdGrassGrass::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdGrassGrass::_GetTfType() const
{
    return _GetStaticTfType();
}

UsdAttribute
UsdGrassGrass::GetRadiusAttr() const
{
    return GetPrim().GetAttribute(UsdGrassTokens->radius);
}

UsdAttribute
UsdGrassGrass::CreateRadiusAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdGrassTokens->radius,
                       SdfValueTypeNames->Double,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdGrassGrass::GetHeightAttr() const
{
    return GetPrim().GetAttribute(UsdGrassTokens->height);
}

UsdAttribute
UsdGrassGrass::CreateHeightAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdGrassTokens->height,
                       SdfValueTypeNames->Double,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdGrassGrass::GetWidthAttr() const
{
    return GetPrim().GetAttribute(UsdGrassTokens->width);
}

UsdAttribute
UsdGrassGrass::CreateWidthAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdGrassTokens->width,
                       SdfValueTypeNames->Double,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdGrassGrass::GetHeightPosAttr() const
{
    return GetPrim().GetAttribute(UsdGrassTokens->heightPos);
}

UsdAttribute
UsdGrassGrass::CreateHeightPosAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdGrassTokens->heightPos,
                       SdfValueTypeNames->Double,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdGrassGrass::GetColorAttr() const
{
    return GetPrim().GetAttribute(UsdGrassTokens->color);
}

UsdAttribute
UsdGrassGrass::CreateColorAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdGrassTokens->color,
                       SdfValueTypeNames->Color3f,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdGrassGrass::GetExtentAttr() const
{
    return GetPrim().GetAttribute(UsdGrassTokens->extent);
}

UsdAttribute
UsdGrassGrass::CreateExtentAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdGrassTokens->extent,
                       SdfValueTypeNames->Float3Array,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

namespace {
static inline TfTokenVector
_ConcatenateAttributeNames(const TfTokenVector& left,const TfTokenVector& right)
{
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
}

/*static*/
const TfTokenVector&
UsdGrassGrass::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        UsdGrassTokens->radius,
        UsdGrassTokens->height,
        UsdGrassTokens->width,
        UsdGrassTokens->heightPos,
        UsdGrassTokens->color,
        UsdGrassTokens->extent,
    };
    static TfTokenVector allNames =
        _ConcatenateAttributeNames(
            UsdGeomGprim::GetSchemaAttributeNames(true),
            localNames);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

#include "pxr/usd/usdGeom/boundableComputeExtent.h"
#include "pxr/base/tf/registryManager.h"
#include <cmath>

PXR_NAMESPACE_OPEN_SCOPE

bool
UsdGrassGrass::ComputeExtent(double radius, double height, double width,
                                VtVec3fArray* extent)
{
    extent->resize(2);

    (*extent)[0] = GfVec3f(-radius, 0.0, -radius);

    // Placeholder
    (*extent)[1] = GfVec3f(radius + width, height, radius);

    return true;
}

bool
UsdGrassGrass::ComputeExtent(double radius, double height, double width,
                              const GfMatrix4d& transform,
                              VtVec3fArray* extent)
{
    extent->resize(2);

    GfBBox3d bbox = GfBBox3d(
        GfRange3d(GfVec3f(-radius, 0.0, -radius),
                  GfVec3d(radius + width, height, radius)),
        transform);
    
    GfRange3d range = bbox.ComputeAlignedRange();
    (*extent)[0] = GfVec3f(range.GetMin());
    (*extent)[1] = GfVec3f(range.GetMax());

    return true;
}

static bool
_ComputeExtentForGrassBlade(const UsdGeomBoundable& boundable,
                          const UsdTimeCode& time,
                          const GfMatrix4d* transform,
                          VtVec3fArray* extent)
{
    const UsdGrassGrass grassBlade(boundable);
    if (!TF_VERIFY(grassBlade))
    {
        return false;
    }

    double height;
    double width;
    double radius;
    if (!grassBlade.GetRadiusAttr().Get(&radius, time) ||
        !grassBlade.GetHeightAttr().Get(&height, time) || 
        !grassBlade.GetWidthAttr().Get(&width, time))
    {
        return false;
    }

    if (transform)
    {
        return UsdGrassGrass::ComputeExtent(radius, height, width, *transform, extent);
    } else {
        return UsdGrassGrass::ComputeExtent(radius, height, width, extent);
    }
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
    UsdGeomRegisterComputeExtentFunction<UsdGrassGrass>(
        _ComputeExtentForGrassBlade);
}

PXR_NAMESPACE_CLOSE_SCOPE

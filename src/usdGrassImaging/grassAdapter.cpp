//
// Copyright © 2024 Weta Digital Limited
//
// SPDX-License-Identifier: Apache-2.0
//
#include "grassAdapter.h"
#include "debugCodes.h"

#include <grassbladeplugin/usdGrass/grass.h>

#include <pxr/imaging/hd/tokens.h>
#include <pxr/usd/usdGeom/tokens.h>
#include <pxr/usdImaging/usdImaging/indexProxy.h>
#include <pxr/usdImaging/usdImaging/tokens.h>

#include <cmath>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    typedef UsdGrassImagingGrassAdapter Adapter;
    TfType adapterType =
        TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
    adapterType.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

bool
UsdGrassImagingGrassAdapter::IsSupported(
    const UsdImagingIndexProxy* index) const
{
    return index->IsRprimTypeSupported(HdPrimTypeTokens->mesh);
}

void
UsdGrassImagingGrassAdapter::TrackVariability(
    const UsdPrim& usdPrim,
    const SdfPath& cachePath,
    HdDirtyBits* o_timeVaryingBits,
    const UsdImagingInstancerContext* i_instancerContext) const
{
    BaseAdapter::TrackVariability(
        usdPrim, cachePath, o_timeVaryingBits, i_instancerContext);

    // TO REVIEW: Should I be adding an IsVarying for every attribute?
    // If sideLength varies over time then points need to be pulled on time
    // change.
    _IsVarying(usdPrim,
               UsdGrassTokens->height,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               o_timeVaryingBits,
               /*inherited*/ false);

    _IsVarying(usdPrim,
               UsdGrassTokens->width,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               o_timeVaryingBits,
               /*inherited*/ false);

    _IsVarying(usdPrim,
               UsdGrassTokens->radius,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               o_timeVaryingBits,
               /*inherited*/ false);

    _IsVarying(usdPrim,
               UsdGrassTokens->heightPos,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               o_timeVaryingBits,
               /*inherited*/ false);

    TF_DEBUG(USDGRASSIMAGING)
        .Msg("[%s] <%s>, <%s>, dirtyBits: %s\n",
             TF_FUNC_NAME().c_str(),
             usdPrim.GetPath().GetText(),
             cachePath.GetText(),
             HdChangeTracker::StringifyDirtyBits(*o_timeVaryingBits).c_str());
}

SdfPath
UsdGrassImagingGrassAdapter::Populate(
    const UsdPrim& usdPrim,
    UsdImagingIndexProxy* index,
    const UsdImagingInstancerContext* instancerContext)
{
    TF_DEBUG(USDGRASSIMAGING)
        .Msg(
            "[%s] <%s>\n", TF_FUNC_NAME().c_str(), usdPrim.GetPath().GetText());

    return _AddRprim(HdPrimTypeTokens->mesh,
                     usdPrim,
                     index,
                     GetMaterialUsdPath(usdPrim),
                     instancerContext);
}

HdDirtyBits
UsdGrassImagingGrassAdapter::ProcessPropertyChange(const UsdPrim& usdPrim,
                                                    const SdfPath& cachePath,
                                                    const TfToken& propertyName)
{

    TF_DEBUG(USDGRASSIMAGING)
        .Msg("[%s] <%s>, <%s>, propertyName: %s\n",
             TF_FUNC_NAME().c_str(),
             usdPrim.GetPath().GetText(),
             cachePath.GetText(),
             propertyName.GetText());

    // If the sideLength attribute changes, then the points are dirty.
    if (propertyName == UsdGrassTokens->height ||
        propertyName == UsdGrassTokens->width ||
        propertyName == UsdGrassTokens->radius ||
        propertyName == UsdGrassTokens->heightPos) {
        return HdChangeTracker::DirtyPoints;
    }

    // Allow base class to handle change processing.
    return BaseAdapter::ProcessPropertyChange(usdPrim, cachePath, propertyName);
}

VtValue
UsdGrassImagingGrassAdapter::GetPoints(const UsdPrim& usdPrim,
                                        UsdTimeCode timeCode) const
{
    UsdGrassGrass grass(usdPrim);
    TF_VERIFY(grass);

    double height;
    double width;
    double radius;
    double heightPos;
    TF_VERIFY(grass.GetHeightAttr().Get(&height, timeCode));
    TF_VERIFY(grass.GetWidthAttr().Get(&width, timeCode));
    TF_VERIFY(grass.GetRadiusAttr().Get(&radius, timeCode));
    TF_VERIFY(grass.GetHeightPosAttr().Get(&heightPos, timeCode));
    
    int numDivisions = this->BASE_NUM_DIV * radius;

    VtVec3fArray points;

    // center
    points.push_back(GfVec3f(0.0f, 0.0f, 0.0f));

    // base
    double angle = 2 * M_PI/numDivisions;
    for (int idx = 0; idx < numDivisions; idx++)
    {
        double currAngle = angle * idx;
        double xPos = radius * std::cos(currAngle);
        double zPos = radius * std::sin(currAngle);

        points.push_back(GfVec3f(xPos, 0.0f, zPos));
    }

    return VtValue(points);
}

VtValue
UsdGrassImagingGrassAdapter::GetTopology(const UsdPrim& usdPrim,
                                          const SdfPath& cachePath,
                                          UsdTimeCode time) const
{
    UsdGrassGrass grass(usdPrim);
    TF_VERIFY(grass);

    double height;
    double width;
    double radius;
    double heightPos;
    TF_VERIFY(grass.GetHeightAttr().Get(&height, time));
    TF_VERIFY(grass.GetWidthAttr().Get(&width, time));
    TF_VERIFY(grass.GetRadiusAttr().Get(&radius, time));
    TF_VERIFY(grass.GetHeightPosAttr().Get(&heightPos, time));

    int numDivisions = this->BASE_NUM_DIV * radius;

    // A single triangle.
    VtIntArray faceVertexCounts(numDivisions, 3);
    VtIntArray faceVertexIndices;

    for (int idx = 1; idx <= numDivisions; idx++)
    {
        faceVertexIndices.push_back(0);
        faceVertexIndices.push_back(idx);
        
        // last face
        if (idx == numDivisions)
        {
            faceVertexIndices.push_back(1);
        }
        else
        {
            faceVertexIndices.push_back(idx + 1);
        }
    }

    static HdMeshTopology planeTopology(UsdGeomTokens->catmullClark,
                                        HdTokens->rightHanded,
                                        faceVertexCounts,
                                        faceVertexIndices);
    return VtValue(planeTopology);
}

PXR_NAMESPACE_CLOSE_SCOPE

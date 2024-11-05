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

    _IsVarying(usdPrim,
            UsdGrassTokens->radius,
            HdChangeTracker::DirtyPoints,
            UsdImagingTokens->usdVaryingPrimvar,
            o_timeVaryingBits,
            /*inherited*/ false);

    _IsVarying(usdPrim,
               UsdGrassTokens->height,
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

    _IsVarying(usdPrim,
               UsdGrassTokens->horizontalStretch,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               o_timeVaryingBits,
               /*inherited*/ false);

    _IsVarying(usdPrim,
               UsdGrassTokens->thinning,
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
    if (propertyName == UsdGrassTokens->radius ||
        propertyName == UsdGrassTokens->height ||
        propertyName == UsdGrassTokens->heightPos ||
        propertyName == UsdGrassTokens->horizontalStretch ||
        propertyName == UsdGrassTokens->thinning
        ) {
        return HdChangeTracker::DirtyPoints;
    }

    // Allow base class to handle change processing.
    return BaseAdapter::ProcessPropertyChange(usdPrim, cachePath, propertyName);
}

GfVec3f UsdGrassImagingGrassAdapter::GetRotatedPointsAboutZ(
                                            GfVec3f& point, double angle) const
{
    double sinT = std::sin(angle);
    double cosT = std::cos(angle);

    return GfVec3f(point[0] * cosT - point[1] * sinT,
                    point[0] * sinT + point[1] * cosT,
                    point[2]);
}

VtVec3fArray UsdGrassImagingGrassAdapter::GetPointsFromCoeffs(
                                            const std::vector<double>& coeffs,
                                            const double radius,
                                            const double thinning,
                                            const double x_max,
                                            const double x_min) const
{
    // TODO: Value validation - coeffs must not be empty
    // TODO: Clamp minRadius value
    float minRadius = (1 - thinning) * radius;

    int numDivs = BASE_NUM_DIV * radius;
    int numCoeffs = coeffs.size();

    double correctionAngle = 0;

    VtVec3fArray points;

    for (int ii = 0; ii <= NUM_CIRC_PLANES; ii++)
    {
        double ratio = ii / (double)NUM_CIRC_PLANES;

        double x = ratio * x_max;
        double y = coeffs[0];
        double derivative = 0;

        for (int idx = 1; idx < numCoeffs; idx++)
        {
            y += coeffs[idx] * std::pow(x, idx);
            derivative += idx * coeffs[idx] * std::pow(x, idx - 1);
        }

        double currRadius = minRadius + (1 - ratio) * (radius - minRadius);
        double planeAngle = -(M_PI/2 - std::atan(derivative));

        if (ii == 0)
        {
            correctionAngle = -planeAngle;
        }
        
        // Circle
        // center
        GfVec3f center = GfVec3f(x, y, 0.0f);
        points.push_back(center);

        // base
        double sectorAngle = 2 * M_PI/numDivs;
        for (int idx = 0; idx < numDivs; idx++)
        {
            double circAngle = sectorAngle * idx;

            double xPos = currRadius * std::cos(circAngle);
            double zPos = currRadius * std::sin(circAngle);

            GfVec3f point = GfVec3f(xPos, 0.0f, zPos);

            GfVec3f rotationVector = GetRotatedPointsAboutZ(point, planeAngle + correctionAngle);

            GfVec3f finalPoint = center + rotationVector;

            points.push_back(finalPoint);
        }
    }

    return points;
}

VtValue
UsdGrassImagingGrassAdapter::GetPoints(const UsdPrim& usdPrim,
                                        UsdTimeCode timeCode) const
{
    UsdGrassGrass grass(usdPrim);
    TF_VERIFY(grass);

    double radius;
    double height;
    double heightPos;
    double horizontalStretch;    
    double thinning;

    TF_VERIFY(grass.GetRadiusAttr().Get(&radius, timeCode));
    TF_VERIFY(grass.GetHeightAttr().Get(&height, timeCode));
    TF_VERIFY(grass.GetHeightPosAttr().Get(&heightPos, timeCode));
    TF_VERIFY(grass.GetHorizontalStretchAttr().Get(&horizontalStretch, timeCode));    
    TF_VERIFY(grass.GetThinningAttr().Get(&thinning, timeCode));
    
    int numDivisions = this->BASE_NUM_DIV * radius;

    double x = horizontalStretch/2 * (1 + heightPos);

    // c, b, a
    std::vector<double> coeffs{0, 2 * height/x , -height/(x * x)};

    VtVec3fArray points = GetPointsFromCoeffs(coeffs, radius, thinning,
                                              horizontalStretch);

    return VtValue(points);
}

VtValue
UsdGrassImagingGrassAdapter::GetTopology(const UsdPrim& usdPrim,
                                          const SdfPath& cachePath,
                                          UsdTimeCode time) const
{
    UsdGrassGrass grass(usdPrim);
    TF_VERIFY(grass);

    double radius;
    double height;
    double heightPos;
    double horizontalStretch;    
    double thinning;

    TF_VERIFY(grass.GetRadiusAttr().Get(&radius, time));
    TF_VERIFY(grass.GetHeightAttr().Get(&height, time));
    TF_VERIFY(grass.GetHeightPosAttr().Get(&heightPos, time));
    TF_VERIFY(grass.GetHorizontalStretchAttr().Get(&horizontalStretch, time));    
    TF_VERIFY(grass.GetThinningAttr().Get(&thinning, time));

    int numDivisions = this->BASE_NUM_DIV * radius;

    // Circular base
    VtIntArray faceVertexCounts;
    VtIntArray faceVertexIndices;

    // base
    for (int ii = 0; ii < numDivisions; ii++)
    {
        faceVertexCounts.push_back(3);
    }

    // circular planes
    for (int ii = 0; ii < numDivisions * NUM_CIRC_PLANES; ii++)
    {
        faceVertexCounts.push_back(4);
    }

    // top circular plane
    for (int ii = 0; ii < numDivisions; ii++)
    {
        faceVertexCounts.push_back(3);
    }

    // Base
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

    // Connecting the Circular planes
    for (int ii = 0; ii < NUM_CIRC_PLANES; ii++)
    {
        for (int jj = 1; jj <= numDivisions; jj++)
        {
            int base_idx_0 = (numDivisions + 1) * ii;
            int base_idx_1 = (numDivisions + 1) * (ii + 1);

            faceVertexIndices.push_back(base_idx_0 + jj);
            faceVertexIndices.push_back(base_idx_1 + jj);

            // last face
            if (jj == numDivisions)
            {
                faceVertexIndices.push_back(base_idx_1 + 1);
                faceVertexIndices.push_back(base_idx_0 + 1);
            }
            else
            {
                faceVertexIndices.push_back(base_idx_1 + jj + 1);
                faceVertexIndices.push_back(base_idx_0 + jj + 1);
            }
        }
    }

    // top plane
    int top_base_idx = (numDivisions + 1) * NUM_CIRC_PLANES;
    for (int idx = 1; idx <= numDivisions; idx++)
    {
        faceVertexIndices.push_back(top_base_idx);
        faceVertexIndices.push_back(top_base_idx + idx);
        
        // last face
        if (idx == numDivisions)
        {
            faceVertexIndices.push_back(top_base_idx + 1);
        }
        else
        {
            faceVertexIndices.push_back(top_base_idx + idx + 1);
        }
    }

    static HdMeshTopology planeTopology(UsdGeomTokens->catmullClark,
                                        HdTokens->rightHanded,
                                        faceVertexCounts,
                                        faceVertexIndices);
    return VtValue(planeTopology);
}

PXR_NAMESPACE_CLOSE_SCOPE

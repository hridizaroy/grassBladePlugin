#pragma once

#include <pxr/usdImaging/usdImaging/gprimAdapter.h>
#include <pxr/base/gf/vec3f.h>

PXR_NAMESPACE_OPEN_SCOPE

/// \class UsdGrassImagingGrassAdapter
///
/// PrimAdapter plugin for the "Grass" prim type.
class UsdGrassImagingGrassAdapter : public UsdImagingGprimAdapter
{
public:
    using BaseAdapter = UsdImagingGprimAdapter;

    // ---------------------------------------------------------------------- //
    /// \name Initialization
    // ---------------------------------------------------------------------- //

    virtual SdfPath Populate(
        const UsdPrim& usdPrim,
        UsdImagingIndexProxy* index,
        const UsdImagingInstancerContext* instancerContext = nullptr) override;

    virtual bool IsSupported(const UsdImagingIndexProxy* index) const override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //

    virtual void TrackVariability(
        const UsdPrim& usdPrim,
        const SdfPath& cachePath,
        HdDirtyBits* timeVaryingBits,
        const UsdImagingInstancerContext* i_instancerContext =
            nullptr) const override;

    // ---------------------------------------------------------------------- //
    /// \name Change processing
    // ---------------------------------------------------------------------- //

    virtual HdDirtyBits ProcessPropertyChange(
        const UsdPrim& usdPrim,
        const SdfPath& cachePath,
        const TfToken& propertyName) override;

    // ---------------------------------------------------------------------- //
    /// \name GprimAdapter overrides
    // ---------------------------------------------------------------------- //

    /// Override the implementation in GprimAdapter and provide \em custom
    /// points for a grass blade.
    virtual VtValue GetPoints(const UsdPrim& usdPrim,
                              UsdTimeCode timeCode) const override;

    /// Override the implementation in GprimAdapter and provide \em custom
    /// topology for a grass blade.
    virtual VtValue GetTopology(const UsdPrim& usdPrim,
                                const SdfPath& cachePath,
                                UsdTimeCode time) const override;

private:
    // Number of sections to divide a circular base of radius 1.0 into
    const int BASE_NUM_DIV = 100;

    // Number of circular planes to use for a curve of length 1.0
    const int NUM_CIRC_PLANES = 300;

    /// Helper function for rotating the given point counterclockwise about
    /// the Z axis, by the given angle
    GfVec3f GetRotatedPointsAboutZ(GfVec3f& point, double angle) const;

    /// \p coeffs - vector of coefficients for the curve, in order, starting
    /// with the coefficient for x^0
    /// \return Array of all vertices for the given curve from x_min to x_max
    VtVec3fArray GetPointsFromCoeffs(const std::vector<double>& coeffs,
                                     const double radius,
                                     const double thinning,
                                     const double x_max,
                                     const double x_min = 0.0f) const;
};

PXR_NAMESPACE_CLOSE_SCOPE

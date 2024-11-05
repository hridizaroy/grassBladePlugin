//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGRASS_TOKENS_H
#define USDGRASS_TOKENS_H

/// \file usdGrass/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
// 
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "pxr/pxr.h"
#include "./api.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/token.h"
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE


/// \class UsdGrassTokensType
///
/// \link UsdGrassTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdGrassTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdGrassTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdGrassTokens->color);
/// \endcode
struct UsdGrassTokensType {
    USDGRASS_API UsdGrassTokensType();
    /// \brief "color"
    /// 
    /// UsdGrassGrass
    const TfToken color;
    /// \brief "extent"
    /// 
    /// UsdGrassGrass
    const TfToken extent;
    /// \brief "height"
    /// 
    /// UsdGrassGrass
    const TfToken height;
    /// \brief "heightPos"
    /// 
    /// UsdGrassGrass
    const TfToken heightPos;
    /// \brief "horizontalStretch"
    /// 
    /// UsdGrassGrass
    const TfToken horizontalStretch;
    /// \brief "radius"
    /// 
    /// UsdGrassGrass
    const TfToken radius;
    /// \brief "thinning"
    /// 
    /// UsdGrassGrass
    const TfToken thinning;
    /// \brief "Grass"
    /// 
    /// Schema identifer and family for UsdGrassGrass
    const TfToken Grass;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdGrassTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdGrassTokensType
extern USDGRASS_API TfStaticData<UsdGrassTokensType> UsdGrassTokens;

PXR_NAMESPACE_CLOSE_SCOPE

#endif

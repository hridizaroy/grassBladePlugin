//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "./tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdGrassTokensType::UsdGrassTokensType() :
    color("color", TfToken::Immortal),
    extent("extent", TfToken::Immortal),
    height("height", TfToken::Immortal),
    heightPos("heightPos", TfToken::Immortal),
    radius("radius", TfToken::Immortal),
    width("width", TfToken::Immortal),
    Grass("Grass", TfToken::Immortal),
    allTokens({
        color,
        extent,
        height,
        heightPos,
        radius,
        width,
        Grass
    })
{
}

TfStaticData<UsdGrassTokensType> UsdGrassTokens;

PXR_NAMESPACE_CLOSE_SCOPE

//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGRASS_API_H
#define USDGRASS_API_H

#include "pxr/base/arch/export.h"

#if defined(PXR_STATIC)
#   define USDGRASS_API
#   define USDGRASS_API_TEMPLATE_CLASS(...)
#   define USDGRASS_API_TEMPLATE_STRUCT(...)
#   define USDGRASS_LOCAL
#else
#   if defined(USDGRASS_EXPORTS)
#       define USDGRASS_API ARCH_EXPORT
#       define USDGRASS_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#       define USDGRASS_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#   else
#       define USDGRASS_API ARCH_IMPORT
#       define USDGRASS_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#       define USDGRASS_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#   endif
#   define USDGRASS_LOCAL ARCH_HIDDEN
#endif

#endif

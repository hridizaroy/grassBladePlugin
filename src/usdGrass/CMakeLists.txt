usd_library(usdGrass

    PUBLIC_HEADERS_INSTALL_PREFIX
        ${ORGANIZATION}

    PYTHON_INSTALL_PREFIX
        ${ORGANIZATION}

    LIBRARIES
        js
        plug
        tf
        sdf
        vt
        gf
        usd
        usdGeom
        arch

    PUBLIC_CLASSES
        grass

    PUBLIC_HEADERS
        api.h
        tokens.h

    CPPFILES
        tokens.cpp

    PYTHON_CPPFILES
        moduleDeps.cpp

    PYMODULE_CPPFILES
        module.cpp
        wrapTokens.cpp
        wrapGrass.cpp

    PYTHON_FILES
        __init__.py

    RESOURCE_FILES
        generatedSchema.usda
        plugInfo.json
)

usd_executable(grassBladeCounter

    CPPFILES
        grassBladeCounter.cpp

    LIBRARIES
        tf
        sdf
        usd
        usdGrass
)

# add_subdirectory(tests)

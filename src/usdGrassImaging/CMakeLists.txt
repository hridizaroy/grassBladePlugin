usd_plugin(usdGrassImaging

    CPPFILES
        grassAdapter.cpp
        debugCodes.cpp

    LIBRARIES
        arch
        js
        plug
        usd
        tf
        sdf
        vt
        gf
        hd
        usdGeom
        usdImaging
        usdGrass

    RESOURCE_FILES
        plugInfo.json
)


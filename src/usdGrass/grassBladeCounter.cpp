/* A simple program which opens an input USD file, and prints
 * the number of prims of type "Grass" in the composed stage */

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/primRange.h>
#include <grassbladeplugin/usdGrass/grass.h>

PXR_NAMESPACE_USING_DIRECTIVE

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: grassBladeCounter <USD_FILE>\n");
        return EXIT_FAILURE;
    }

    int grassBladeCount = 0;
    UsdStageRefPtr stage = UsdStage::Open(argv[1]);
    for (UsdPrim prim : stage->TraverseAll()) {
        if (prim.IsA<UsdGrassGrass>()) {
            grassBladeCount++;
        }
    }

    printf("Number of grass blades: %i\n", grassBladeCount);
    return EXIT_SUCCESS;
}

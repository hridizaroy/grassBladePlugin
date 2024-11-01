from pxr import Tf
from pxr.Usdviewq.plugin import PluginContainer


def DefineChildGrassBlade(usdviewApi):
    for selectedPath in usdviewApi.selectedPaths:
        usdviewApi.stage.DefinePrim(selectedPath.AppendChild("grass"), "Grass")


class UsdviewGrassPluginContainer(PluginContainer):

    def registerPlugins(self, plugRegistry, usdviewApi):
        self._defineChildGrassBlade = plugRegistry.registerCommandPlugin(
            "UsdviewGrassPluginContainer.DefineChildGrassBlade",
            "Define Child Grass Blade",
            DefineChildGrassBlade)

    def configureView(self, plugRegistry, plugUIBuilder):
        grassMenu = plugUIBuilder.findOrCreateMenu("Grass")
        grassMenu.addItem(self._defineChildGrassBlade)


Tf.Type.Define(UsdviewGrassPluginContainer)

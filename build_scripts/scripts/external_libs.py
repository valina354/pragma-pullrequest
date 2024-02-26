import scripts.shared
from sys import platform

scripts.shared.init_global_vars()
from scripts.shared import *

curDir = os.getcwd()

external_libs_dir = curDir +"/external_libs"
os.chdir(external_libs_dir)
get_submodule("alsoundsystem","https://github.com/Silverlan/alsoundsystem.git","4dc79d3180bdf62ab63043efac797409309d63a8")
get_submodule("datasystem","https://github.com/Silverlan/datasystem.git","a6dfff6")
get_submodule("iglfw","https://github.com/Silverlan/iglfw.git","e0531a55f5bdd9c9a1dadfbb7a8a610474d69d19")
get_submodule("luasystem","https://github.com/Silverlan/luasystem.git","fd9fc0ea830b53f2be4337215d36632b082cdb62")
get_submodule("materialsystem","https://github.com/Silverlan/materialsystem.git","d900667907c42e64d70a9e49eab16fcb39073089")
get_submodule("mathutil","https://github.com/Silverlan/mathutil.git","9ed30f22da26cfc0b9debdd4e0ac43ffa9e869b8")
get_submodule("networkmanager","https://github.com/Silverlan/networkmanager.git","68d2f5c")
get_submodule("panima","https://github.com/Silverlan/panima.git","9a32d345bdee87f5872e9d1b65de5772db996df3")
get_submodule("prosper","https://github.com/Slaweknowy/prosper.git","afae094b76aa91fcc41c9a6a7fcc7c2fba168d6b")
get_submodule("sharedutils","https://github.com/Slaweknowy/sharedutils.git","5f15a3e71204688f865b39247b7b3140678779dd")
get_submodule("util_bsp","https://github.com/Silverlan/util_bsp.git","3c11053")
get_submodule("util_formatted_text","https://github.com/Silverlan/util_formatted_text.git","3bd9e2de37d0cb14bf8228fde5e25c97698e927b")
get_submodule("util_image","https://github.com/Slaweknowy/util_image.git","d3aaf0f7905164633f83e234a6d7ba425d7a623e")
get_submodule("util_pad","https://github.com/Silverlan/util_pad.git","7a827f8")
get_submodule("util_pragma_doc","https://github.com/Silverlan/util_pragma_doc.git","6a4a089")
get_submodule("util_smdmodel","https://github.com/Silverlan/util_smdmodel.git","5e581ab")
get_submodule("util_sound","https://github.com/Slaweknowy/util_sound.git","db844a7b053b3f0de86ba9cc6a0668c771d8059f")
get_submodule("util_source2","https://github.com/Silverlan/util_source2.git","cf553d6")
get_submodule("util_source_script","https://github.com/Silverlan/util_source_script.git","ea0d03a")
get_submodule("util_timeline_scene","https://github.com/Silverlan/util_timeline_scene.git","76d02ff")
get_submodule("util_udm","https://github.com/Silverlan/util_udm.git","ef75043cc082740c7940d6111712fb9635e3432a")
get_submodule("util_versioned_archive","https://github.com/Silverlan/util_versioned_archive.git","be6d3fe")
get_submodule("util_vmf","https://github.com/Silverlan/util_vmf.git","cdba99d")
get_submodule("util_zip","https://github.com/Silverlan/util_zip.git","c484726740580b6a6583a13e23e4a3136a8fd815")
get_submodule("vfilesystem","https://github.com/Silverlan/vfilesystem.git","374693fb55ab3a18a268f5dca6d7fe0ba97243ca")
get_submodule("wgui","https://github.com/Silverlan/wgui.git","6a9cedd95e34b9ebf7f9ddf3f4344e4d5d22d3d4")

os.chdir(curDir)

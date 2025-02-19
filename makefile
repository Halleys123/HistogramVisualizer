# My Folders
include_folder = ./include
lib_folder = ./lib

# Libraries to include
my_libraries = User32.lib Gdi32.lib ucrt.lib kernel32.lib vcruntime.lib msvcrt.lib opengl32.lib glu32.lib

# INFO(Include Folders)
# Windows Kit Include Folders
kit_include_1 = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/winrt"
kit_include_2 = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/ucrt"
kit_include_3 = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um"
kit_include_4 = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared"
kit_include_5 = "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/cppwinrt"

# Windows Kit Lib Folders
kit_lib_1 = "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64"
kit_lib_2 = "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/ucrt/x64"

# MSVC Include Folders
msvc_include = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.41.34120/include"
msvc_atlmfc_include = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.41.34120/atlmfc/include"

# MSVC Lib Folders
msvc_lib = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.41.34120/lib/x64"
msvc_atlmfc_lib = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.41.34120/atlmfc/lib/x64"

# INFO(Combined Include Folders)
include_folders = /I$(msvc_include) /I$(msvc_atlmfc_include) /I$(kit_include_1) /I$(kit_include_2) /I$(kit_include_3) /I$(kit_include_4) /I$(kit_include_5) /I$(include_folder) /I"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared"

#INFO(Combined Lib Folders)
lib_folders = /LIBPATH:$(msvc_lib) /LIBPATH:$(msvc_atlmfc_lib) /LIBPATH:$(kit_lib_1) /LIBPATH:$(kit_lib_2) /LIBPATH:$(lib_folder) $(my_libraries)

# When using windows kit 10.0.19041.0 i.e. Win32
build:
	cl main.cpp ./src/WndProc.cpp ${include_folders} /link ${lib_folders} /OUT:./bin/program.exe /SUBSYSTEM:WINDOWS /NODEFAULTLIB
	del *.obj
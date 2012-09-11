# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=
Release_Include_Path=

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=
Release_Libraries=

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _CONSOLE 
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _CONSOLE 

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-Wall -O0 -g 
Release_Compiler_Flags=-Wall -O2 

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Release 

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/Code/NetDebugLog/NetDebugLog.o gccDebug/Code/main.o 
	g++ gccDebug/Code/NetDebugLog/NetDebugLog.o gccDebug/Code/main.o  $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o gccDebug/NetDebugLog.exe

# Compiles file Code/NetDebugLog/NetDebugLog.cpp for the Debug configuration...
-include gccDebug/Code/NetDebugLog/NetDebugLog.d
gccDebug/Code/NetDebugLog/NetDebugLog.o: Code/NetDebugLog/NetDebugLog.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Code/NetDebugLog/NetDebugLog.cpp $(Debug_Include_Path) -o gccDebug/Code/NetDebugLog/NetDebugLog.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Code/NetDebugLog/NetDebugLog.cpp $(Debug_Include_Path) > gccDebug/Code/NetDebugLog/NetDebugLog.d

# Compiles file Code/main.cpp for the Debug configuration...
-include gccDebug/Code/main.d
gccDebug/Code/main.o: Code/main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Code/main.cpp $(Debug_Include_Path) -o gccDebug/Code/main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Code/main.cpp $(Debug_Include_Path) > gccDebug/Code/main.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/Code/NetDebugLog/NetDebugLog.o gccRelease/Code/main.o 
	g++ gccRelease/Code/NetDebugLog/NetDebugLog.o gccRelease/Code/main.o  $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o gccRelease/NetDebugLog.exe

# Compiles file Code/NetDebugLog/NetDebugLog.cpp for the Release configuration...
-include gccRelease/Code/NetDebugLog/NetDebugLog.d
gccRelease/Code/NetDebugLog/NetDebugLog.o: Code/NetDebugLog/NetDebugLog.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Code/NetDebugLog/NetDebugLog.cpp $(Release_Include_Path) -o gccRelease/Code/NetDebugLog/NetDebugLog.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Code/NetDebugLog/NetDebugLog.cpp $(Release_Include_Path) > gccRelease/Code/NetDebugLog/NetDebugLog.d

# Compiles file Code/main.cpp for the Release configuration...
-include gccRelease/Code/main.d
gccRelease/Code/main.o: Code/main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Code/main.cpp $(Release_Include_Path) -o gccRelease/Code/main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Code/main.cpp $(Release_Include_Path) > gccRelease/Code/main.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug
	mkdir -p gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f gccDebug/*.a
	rm -f gccDebug/*.so
	rm -f gccDebug/*.dll
	rm -f gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f gccRelease/*.a
	rm -f gccRelease/*.so
	rm -f gccRelease/*.dll
	rm -f gccRelease/*.exe


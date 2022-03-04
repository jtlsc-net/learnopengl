Compiling

Ensure that the cube.obj file is with the others.
Ensure that the glm include library (no lib / .a files) is in the same directory as GL and GLFW include directories.
Compile with normal commands.  Presumably, 
g++ -lglfw -lglew Source.cpp Shader.cpp ObjectLoader.cpp
will work, but I was unable to test it.
To call an object file other than Ågcube.objÅh, please edit the value in line 83 of Source.cpp.

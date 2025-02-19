Shader is a c program, that runs on gpu and is highly isolated
the only communication it have is the input, output variables and uniforms

Entry point of the shader is main function

general structure of shader
#version version_number profile mode(core | compatibility)
in type in_variable_name;
in type in_variable_name;
out type out_variable_name;
uniform type uniform_name;
void main()
{
---- process input(s) and do some weird graphics stuff
...
---- output processed stuff to output variable
---- out_variable_name = weird_stuff_we_processed;
}

When talking about vertex shader
each input variable is called vertex attribute
There is a limit on how many vertex attributes a shader can have, it depends on the hardware
although opengl made sure that there are atleast 16 (4 component vector) vertex attributes available
To get information about how many vertex attributes are available, we can use
CODE: int nrAttributes;
CODE: glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
CODE: std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes
CODE: << std::endl;

GLSL Data Types
int, float, uint, bool, double are the basic data types
vector and matrices are also available

A vector can have 1 to 4 components
vecn(n should 1 or 2 or 3 or 4 i.e. vec4, vec3, vec2, vec1) where n is the number of components - this saves float
ivecn - int vector
bvecn - bool vector
uvecn - unsigned int vector
dvecn - double vector

Accessing values in vectors
In Case of positions, we can access the values using x, y, z, w
for texture coordinates, we can access the values using s, t, p, q
There is swizzling available, which means we can access the values in any order
for example, vec4 someVec = vec4(1.0f, 0.4f, 0.8f, 1.0f);
to access xyzx we can use someVec.xyzx
eg2 someVec.zx = someVec.xz; this will swap the values of z and x

in and out
Shaders use in and out keywords to communicate with each other
in is used to give input to the shader
out is used to output data from the shader to the next stage
when a variable is declared out then you can access it in the next stage
when a variable is declared in then you can access it from the previous stage

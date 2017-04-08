
all: 
	
	g++ -lglfw -lOpenGL Main.cpp -o Main SpringSystem.cpp Spring.cpp Mass.cpp Geometry.cpp Shader.cpp 



clean:
	
	rm -f Main

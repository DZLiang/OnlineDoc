CC=$(CXX)
CCFLAGS=$(CXXFLAGS)
OBJ=simpleOpenGLWindow.o
DEST=APP
FRAMEWORK=-f -framework glut -framework opengl
$(DEST):$(OBJ)
	$(CC) -o $(DEST) $(OBJ) $(FRAMEWORK)
$(OBJ):simpleOpenGLWindow.cpp
	$(CC) -c simpleOpenGLWindow.cpp $(FRAMEWORK)
.PHONY:clean
clean:
	rm $(OBJ)

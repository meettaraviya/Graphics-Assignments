#include <gl_framework.hpp>

class Model{

	struct Part{
		vector<glm::vec4> vertices;
		vector<glm::vec4> colors;
		GLuint vbo;
	};

	GLuint vao, attrib_col, attrib_pos;
	int draw_mode;
	vector<struct Part*> parts;

public:
	Model(){}
	Model(GLuint vPosition, GLuint vColor, GLuint vArray, int shape);
	void fromFile(string inFileName);
	void render();

};
void renderModel();
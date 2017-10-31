#include "Scene.hpp"

using namespace std;

Scene::Scene(int shape){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	
	draw_mode = shape;
}

void Scene::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	Scene_Element* scene_element = new Scene_Element;
	
	while(fscanf(inpFile,"%f %f %f %f %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2])>0){
		scene_element->vertices.push_back(pos);
		scene_element->colors.push_back(col);
	}

	// cout << scene_elements.size() << endl;
	scene_elements.push_back(scene_element);
	fclose(inpFile);
}

void Scene::loadBuffers(int index){
	Scene_Element* scene_element = scene_elements[index];
	glBindVertexArray (vao);
	glGenBuffers (1, &scene_element->vbo);
	glBindBuffer (GL_ARRAY_BUFFER, scene_element->vbo);

	glBufferData (GL_ARRAY_BUFFER, (scene_element->vertices.size() + scene_element->colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, scene_element->vertices.size() * sizeof(glm::vec4), scene_element->vertices.data() );
	glBufferSubData( GL_ARRAY_BUFFER, scene_element->vertices.size() * sizeof(glm::vec4), scene_element->colors.size() * sizeof(glm::vec4), scene_element->colors.data() );

	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(scene_element->vertices.size()*sizeof(glm::vec4)) );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// glBindVertexArray(0);

}

void Scene::render(){

	glBindVertexArray (vao);

  	// cout << "vao = " << vao << endl;


	for(int i=0; i<scene_elements.size(); i++){

		glBindBuffer (GL_ARRAY_BUFFER, scene_elements[i]->vbo);
		// cout << scene_elements[i]->vbo << endl;

		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(scene_elements[i]->vertices.size()*sizeof(glm::vec4)) );
		
		glDrawArrays(draw_mode, 0, scene_elements[i]->vertices.size());
	}
	
}

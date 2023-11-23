#include "Scene.h"



int main()
{
	Scene* sc1 = new Scene();
	const GLfloat* usedModel2 = plain;
	const GLsizeiptr modelSize2 = sizeof(plain);

	Model plain = Model(usedModel2, modelSize2);
	DrawableObject* dm2 = new DrawableObject(&plain);
	dm2->Initialize();
	dm2->Scale(glm::vec3(10));
	vector<DrawableObject*> drawableObjects;

	drawableObjects.push_back(dm2);
	sc1->AddModels(drawableObjects);
	sc1->Initialize();
	delete(sc1);

	exit(EXIT_SUCCESS);
}
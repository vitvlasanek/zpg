#include "Application.h"



int main()
{
	Application* app = new Application();
	app->Initialize();
	delete(app);

	exit(EXIT_SUCCESS);
}
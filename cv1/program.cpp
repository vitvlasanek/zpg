#include "Application.h"



int main()
{
	Application* app = new Application();
	app->Initialize(2);

	app->Run();
	exit(EXIT_SUCCESS);
}
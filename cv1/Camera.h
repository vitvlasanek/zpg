// ---- Camera .h ---
// dopredna deklarace
class Shader;
class Camera {
private:
	Shader* sh;
public:
	Camera(Shader* s);
	void metoda();
	Camera();
};

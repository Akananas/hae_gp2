// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> //Inclut un header appelle iostream
#include <SFML/Graphics.hpp> //Inclut le header Graphics.hpp du dossier SFML
#include "Game.hpp"
#include "Lib.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

static sf::Shader* bloomShader = nullptr;
static sf::Shader* blurShader = nullptr;


static std::vector<float>kernel;
static std::vector<sf::Glsl::Vec2>offsets;

static std::vector<float>kernelX;
static std::vector<sf::Glsl::Vec2>offsetsX;

static std::vector<float>kernelY;
static std::vector<sf::Glsl::Vec2>offsetsY;
//offset must be normalized by texture size
static void getKernelOffsets(float dx, std::vector<float>& _kernel, std::vector<sf::Glsl::Vec2>& _offsets, float offsetScale = 1.0f, bool isHoriz = true) {
	int kernel_size = (int)(dx / 0.65f + 0.5f) * 2 + 1;

	_kernel.clear();
	_offsets.clear();

	for (int i = 0; i < kernel_size; i++) {
		_kernel.push_back(0.0f);
		_offsets.push_back(sf::Glsl::Vec2());
	}

	Lib::m_gaussian_kernel(_kernel.data(), kernel_size, dx);

	for (int i = 0; i < kernel_size; i++) {
		float ofs = (offsetScale * (i - kernel_size * 0.5f));
		_offsets[i].x = isHoriz ? ofs : 0.0f;
		_offsets[i].y = isHoriz ? 0.0f : ofs;
	}
}

static void blur(float dx, sf::Texture* source, sf::Shader* _blurShader, sf::RenderTexture* destX, sf::RenderTexture* destFinal) {

	source->setSmooth(true);
	destX->setSmooth(true);
	destFinal->setSmooth(true);
	{
		_blurShader->setUniform("texture", *source);

		sf::Sprite sprX(*source);

		getKernelOffsets(dx, kernelX, offsets);

		int nbSamples = kernelX.size();
		_blurShader->setUniform("samples", nbSamples);
		for (int i = 0; i < nbSamples; i++)
			offsets[i].x *= 1.0f / source->getSize().x;
		_blurShader->setUniformArray("kernel", kernelX.data(), nbSamples);
		_blurShader->setUniformArray("offsets", offsets.data(), nbSamples);

		auto k = 1.0f;
		_blurShader->setUniform("srcMul", sf::Glsl::Vec4(k, k, k, 1.0f));

		destX->draw(sprX, _blurShader);
		destX->display();
	}

	{
		getKernelOffsets(dx, kernelY, offsets, 1.0, false);
		int nbSamples = kernelY.size();
		_blurShader->setUniform("samples", nbSamples);
		for (int i = 0; i < nbSamples; i++)
			offsets[i].y *= 1.0f / source->getSize().y;
		_blurShader->setUniformArray("kernel", kernelY.data(), nbSamples);
		_blurShader->setUniformArray("offsets", offsets.data(), nbSamples);

		sf::Sprite sprXY(destX->getTexture());
		_blurShader->setUniform("texture", destX->getTexture());
		_blurShader->setUniform("srcMul", sf::Glsl::Vec4(1, 1, 1, 1));

		destFinal->draw(sprXY, _blurShader);
		destFinal->display();
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280 , 720), "Tortue");//Creer une fenetre de taille 200x200 et la nomme "SFML works!"
    //window.setMouseCursorVisible(false);
	Game newGame(&window);

	ImGui::SFML::Init(window);

	double frameStart = 0.0;
	double frameEnd = 0.0;
	window.setFramerateLimit(60);

	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("../res/arial.ttf")) {
		std::cout << "ERROR NO FONT" << std::endl;
		return 1;
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(10, 20);
	text.setFillColor(sf::Color::White);
	sf::Color bgColor;
	float color[3] = { 0.f, 0.f, 0.f };

	sf::Clock deltaClock;

	bloomShader = new sf::Shader();
	if (!bloomShader->loadFromFile("../res/simple.vert", "../res/bloom.frag"))
		printf("unable to load shaders\n");

	blurShader = new sf::Shader();
	if (!blurShader->loadFromFile("../res/simple.vert", "../res/blur.frag"))
		printf("unable to load shaders\n");
	float blurWidth = 50.0f;
	sf::RenderTexture* destX = new sf::RenderTexture();
	destX->create(window.getSize().x, window.getSize().y);
	destX->clear(sf::Color(0, 0, 0, 0));

	sf::RenderTexture* destFinal = new sf::RenderTexture();
	destFinal->create(window.getSize().x, window.getSize().y);
	destFinal->clear(sf::Color(0, 0, 0, 0));

	sf::Texture winTex;
	winTex.create(window.getSize().x, window.getSize().y);

    while (window.isOpen())//Tant que la fenetre est ouverte
    {

		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimeStamp();

		if (dt < 0.001) {
			dt = 0.001;
		}
        sf::Event event;//Creer une variable qui va contenir les inputs de l'utilisateur
		while (window.pollEvent(event))//Execute les events
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Si on essaye de fermer la fenetre
				window.close();//Ferme la fenetre
			newGame.processInput(event);
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Background color"); // begin window
		ImGui::SetWindowSize(ImVec2(200, 100));
											   // Background color edit
		if (ImGui::ColorEdit3("Color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		ImGui::End(); // end window

		newGame.Update(dt);
		window.clear(bgColor); // fill background with color
		newGame.draw();
		window.draw(text);
		///Draw all bloomed before this
		{
			winTex.update(window);
			destX->clear(sf::Color(0, 0, 0, 255));
			destFinal->clear(sf::Color(0, 0, 0, 255));
			blur(blurWidth, &winTex, blurShader, destX, destFinal);
			sf::Sprite sp(destFinal->getTexture());
			sf::RenderStates rs;

			rs.blendMode = sf::BlendAdd;

			bloomShader->setUniform("texture", destFinal->getTexture());
			bloomShader->setUniform("bloomPass", 0.6f);
			bloomShader->setUniform("bloomMul", sf::Glsl::Vec4(1.3f, 1.3f, 1.0f, 1.0f));

			rs.shader = bloomShader;
			sf::Color c = sp.getColor();
			c.a = (int)(c.a * 0.8);
			sp.setColor(c);

			window.draw(sp, rs);
			blurWidth += (1.0f / 60.0f) * 2;

			if (blurWidth >= 64)
				blurWidth = 54;
		}
		ImGui::SFML::Render(window);
		window.display();
		frameEnd = Lib::getTimeStamp();
		text.setString("FPS: " + std::to_string((1.0/dt)));
    }

	ImGui::SFML::Shutdown();
    return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> //Inclut un header appelle iostream
#include <SFML/Graphics.hpp> //Inclut le header Graphics.hpp du dossier SFML
#include "Game.hpp"
#include "Lib.hpp"
#include <imgui.h>
#include <imgui-SFML.h>

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

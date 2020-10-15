// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> //Inclut un header appelle iostream
#include <SFML/Graphics.hpp> //Inclut le header Graphics.hpp du dossier SFML
#include "Tank.hpp";
#include "Bullet.hpp";
#include "Game.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280 , 720), "SFML works!", sf::Style::None);//Creer une fenetre de taille 200x200 et la nomme "SFML works!"
    //window.setMouseCursorVisible(false);
	Game newGame(&window);
    while (window.isOpen())//Tant que la fenetre est ouverte
    {
        sf::Event event;//Creer une variable qui va contenir les inputs de l'utilisateur
		while (window.pollEvent(event))//Execute les events
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Si on essaye de fermer la fenetre
				window.close();//Ferme la fenetre
			newGame.processInput(event);
		}
		newGame.Update();
		window.clear();
		newGame.draw();
		window.display();
    }
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

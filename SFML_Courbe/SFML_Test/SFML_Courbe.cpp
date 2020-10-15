// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> //Inclut un header appelle iostream
#include <SFML/Graphics.hpp> //Inclut le header Graphics.hpp du dossier SFML
#include "catmull2.hpp"
#include "interp.hpp"
sf::Vertex getVert(int idx, std::vector<sf::Vertex> points) {
	return points[std::max(0, std::min((int)idx, (int)points.size() - 1))];
}
sf::Color randomColor() {
	return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}
sf::Color interCol(sf::Color col, float t) {
	return sf::Color(col.r / t, col.g / t, col.b / t);
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280 , 720), "SFML works!", sf::Style::None);//Creer une fenetre de taille 200x200 et la nomme "SFML works!"
    sf::Color vertColors[]{
        sf::Color::Cyan,    
        sf::Color::Green,
        sf::Color::Magenta
    };
    int currentColor = 0;
    //window.setMouseCursorVisible(false);
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("../res/arial.ttf")) {
        std::cout << "ERROR NO FONT" << std::endl;
        return 1;
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setPosition(900, 20);
    text.setFillColor(sf::Color::White);
    text.setString("Backspace pour clear les points");
	std::vector<sf::Vertex> myPoints;
    sf::VertexArray vert(sf::LinesStrip);
    while (window.isOpen())//Tant que la fenetre est ouverte
    {
        sf::Event event;//Creer une variable qui va contenir les inputs de l'utilisateur
        while (window.pollEvent(event))//Execute les events
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Si on essaye de fermer la fenetre
                window.close();//Ferme la fenetre
            if (event.type == sf::Event::MouseButtonPressed) {
                /*vert.resize(vert.getVertexCount() + 1);
                vert[vert.getVertexCount()-1].position = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                vert[vert.getVertexCount() - 1].color = vertColors[currentColor];
				currentColor = (currentColor + 1) % 3;*/		
				sf::Vertex tmpVert(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), vertColors[currentColor]);
				currentColor = (currentColor + 1) % 3;
				myPoints.push_back(tmpVert);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    myPoints.clear();
                }
            }
        }	
		vert.clear();
		if (myPoints.size() > 1) {
			for (int i = 0; i < myPoints.size() - 1; i++) {
				sf::Vertex v0 = getVert(i-1,myPoints);
				sf::Vertex v1 = getVert(i,myPoints);
				sf::Vertex v2 = getVert(i+1,myPoints);
				sf::Vertex v3 = getVert(i+2,myPoints);
				for (int j = 0; j <= 20; j++) {
					sf::Color col;
					col.a = 255;
					col.r = catmull2::catmull(v0.color.r, v1.color.r, v2.color.r, v3.color.r, j / 20.0);
					col.g = catmull2::catmull(v0.color.g, v1.color.g, v2.color.g, v3.color.g, j / 20.0);
					col.b = catmull2::catmull(v0.color.b, v1.color.b, v2.color.b, v3.color.b, j / 20.0);
					vert.append(sf::Vertex(catmull2::c2(v0.position, v1.position, v2.position, v3.position, j / 20.0),col));
				}
			}
		}
        window.clear();//Supprime tout ce qui ete affiche
        window.draw(vert);
        window.draw(text);
        window.display();//Remplace le frontbuffer par le backbuffer
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

// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> //Inclut un header appelle iostream
#include <SFML/Graphics.hpp> //Inclut le header Graphics.hpp du dossier SFML
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280 , 720), "SFML works!", sf::Style::None);//Creer une fenetre de taille 200x200 et la nomme "SFML works!"
    sf::CircleShape shape(100.f);//Creer un cercle de rayon 100  
    shape.setOrigin(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Green);//Changer la couleur du cercle
    window.setMouseCursorVisible(false);
    while (window.isOpen())//Tant que la fenetre est ouverte
    {
        sf::Event event;//Creer une variable qui va contenir les inputs de l'utilisateur
        while (window.pollEvent(event))//Execute les events
        {
            sf::Vector2f pos = shape.getPosition();
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Si on essaye de fermer la fenetre
                window.close();//Ferme la fenetre
            if (event.type == sf::Event::MouseButtonPressed) {
                shape.setFillColor(sf::Color::Red);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                shape.setFillColor(sf::Color::Blue);
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::T) {
                    sf::Vector2f tmpVec(1280 - shape.getRadius() * 2, 720 - shape.getRadius() * 2);
                    shape.setPosition(tmpVec);
                }
                sf::Vector2f dir;
                if (event.key.code == sf::Keyboard::Left) {
                    pos.x -= 5;
                    shape.setPosition(pos);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    pos.x += 5;
                    shape.setPosition(pos);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    pos.y += 5;
                    shape.setPosition(pos);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    pos.y -= 5;
                    shape.setPosition(pos);
                }
                if (event.key.code == sf::Keyboard::R) {
                    sf::Color tmpColor(50, 50, 50);
                    shape.setFillColor(tmpColor);
                }
                if (event.key.code == sf::Keyboard::A) {
                    shape.setFillColor(sf::Color::Yellow);
                }
                if (event.key.code == sf::Keyboard::Z) {
                    shape.setFillColor(sf::Color::Magenta);
                }
                if (event.key.code == sf::Keyboard::E) {
                    shape.setFillColor(sf::Color::Cyan);
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f tmpPos(event.mouseMove.x, event.mouseMove.y);
                shape.setPosition(tmpPos);
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                shape.setRadius(shape.getRadius() + event.mouseWheelScroll.delta);
            }
        }
        //sf::Vector2f tmpPos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        //shape.setPosition(tmpPos);
        sf::Vertex vert[500] = {};
        for (int i = 0; i < 500; i++) {
            vert[i].position = sf::Vector2f(125 * (i * i) + 50 * i , 500 * i);
            vert[i].color = sf::Color::Cyan;
        }
        sf::Texture texture;
        texture.loadFromFile("texture.png");

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setColor(sf::Color(255, 255, 255, 255));
        sprite.setPosition(100, 25);

        window.clear();//Supprime tout ce qui ete affiche
        window.draw(vert, 5,sf::LinesStrip);
        window.draw(shape);//Render le cercle dans le backbuffer
        window.draw(sprite);
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

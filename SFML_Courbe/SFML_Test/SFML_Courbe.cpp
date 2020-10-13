// SFML_Test.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream> //Inclut un header appelle iostream
#include <SFML/Graphics.hpp> //Inclut le header Graphics.hpp du dossier SFML
#include <algorithm>
float catmull(float p0, float p1, float p2, float p3, float t) {
    float q = 2.0 * p1;
    float t2 = t * t;

    q += (-p0 + p2) * t;
    q += (2.0 * p0 - 5.0 * p1 + 4 * p2 - p3) * t2;
    q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

    return 0.5 * q;
}
sf::Vertex getVert(sf::VertexArray point, int idx) {
    return point[std::clamp(idx, 0, (int)point.getVertexCount() - 1)];
}
sf::VertexArray c2(float i, sf::VertexArray point) {

    return point;
}
sf::VertexArray plotWhole(float t, sf::VertexArray point) {
    return c2(t * (point.getVertexCount() - 1), point);
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
    sf::VertexArray vert(sf::LinesStrip);
    while (window.isOpen())//Tant que la fenetre est ouverte
    {
        sf::Event event;//Creer une variable qui va contenir les inputs de l'utilisateur
        while (window.pollEvent(event))//Execute les events
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//Si on essaye de fermer la fenetre
                window.close();//Ferme la fenetre
            if (event.type == sf::Event::MouseButtonPressed) {
                vert.resize(vert.getVertexCount() + 1);
                vert[vert.getVertexCount()-1].position = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                vert[vert.getVertexCount() - 1].color = vertColors[currentColor];
                currentColor = (currentColor + 1) % 3;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    vert.clear();
                }
            }
        }
        sf::Texture texture;
        texture.loadFromFile("texture.png");

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setColor(sf::Color(255, 255, 255, 255));
        sprite.setPosition(100, 25);
        window.clear();//Supprime tout ce qui ete affiche
        window.draw(vert);
        window.draw(sprite);
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


#include "pch.h"
#include <iostream>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include <string>
using namespace std;

int main() {
	Vector3 v1(3, 2, 5);
	Vector3 v2(4, 6, 1);
	Vector3 cross = v1.Cross(v2);
	cout << to_string(cross.x) << " " << to_string(cross.y) << " " << to_string(cross.z) << " " << to_string(cross.Mag());
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

# render3D

<h4>A 3D render method created from scratch.</h4>

<h5>Goals :</h5>
<ul>
<li>For the moment, I'm just trying to create a Wolfenstein style game.</li>
<ul>
<li>I'm building the walls from a text file, no texture just colors</li>
</ul>
</ul>

<h5>Tools :</h5>
<ul>
<li>C++ (g++ on Ubuntu)</li>
<li>SDL</li>
<li>QuickCG</li>
<li>Atom from Github</li>
</ul>

<h5>Progression :</h5>
alpha 0.0.1 : 9/10/2016 => 00h51
	+ gros bug dans la facon de faire le rendu
	+ bug dans le DDA
	+ pas de possibilités d'arret (problematique nan?)
	+ framerate inf (normal quoi)

alpha 0.0.2 : 9/10/2016 => 01h10
	+ ajout d'une touche pour echap
	+ ces bandes de couleurs a la place d'un rendu normal
		ca donne un style, malgre que ca donne mal a
		la tete. En vrai ca ferait un jeu mega dur!
	+ ajout des texts trop cools

alpha 0.0.3 : 10/10/2016 => 14h35
	+ essais de corriger le moteur de rendu (ne marche pas)
		- image pas normal (courbe)
		- rafraichissement bizarre

alpha 0.0.4 : 10/10/2016 => 15h
	+ mise a jour du moteur de rendu (moins bugge)
		- triangles noirs en bas (raycaster bug)
		- trous noirs parfois

alpha 0.0.5 : 10/10/2016 => 15h42
	+ changement des keys
  + essais changement moteur de rendu

alpha 0.1.0 : 10/10/2016 => 17h00
  + Moteur de rendu sans textures fini.

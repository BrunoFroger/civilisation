# civilisation

Ce programme permet de simuler l'évolution d'une civilisation, il peut être adapté par l'intermédiaire de scripts propre à chaque type d'élément de cette civilisation
les types d'éléments actuellement proposé sont :

- humain
- entreprise


## Description du fichier de script
Ce fichier doit contenir le comportement qui régit chaque évolution de l'objet concerné, le nom du fichier de script est compose du mon du type + '.scr'. les scripts sont stockés dans un répertoire nommé 'scripts'

- '#' désigne un commentaire => ligne ignorée
- Les lignes vides sont ignorées
- Il est possible d'indenter les lignes
- Les doublons d'espaces sont supprimés avant analyse

## Grammaire d'analyse de scripts
	<script> = <listeInstructions>
	<listeInstructions> = <instruction> <listeInstructions> | <instruction>
	<instruction> = <test> | <affectation>
	<test> = si <expression> alors <ListeCommandes> sinon <ListeCommandes> finsi
	<expression> = (<expression>) <operateur> (<expression>) | <item> <opTest> <item>
	<operateur> = "&&" | "||"
	<item> = <variable> | <valeur> | "("<expression>")"
	<opTest> = "=" | "!=" | "<" | ">" | "<=" | ">="
	<Variable> = 'voir ci dessous la liste des variables disponibles'
	<valeur> = nombre
	<affectation> = <variable> "=" <valeur>
	
	<listeCommandes> = <commande> | <listeCommandes>
	<commande> = 'voir ci dessous la liste des commandes disponibles'


### Liste des commandes de script disponibles par type d'objet : 

- civilisation :
	- humain, [homme|femme], < nom >, < capital initial > => creation d'un humain (exemple humain, homme, gilbert, 4000)
	- entreprise, < type >, < nom >, < capital initial > => creation d'une entreprise (entreprise, 1, aubonpain, 10000)

- Humain : 
	- mort => si age > 15 et age > 75 + rnd(30)
	- evolutionSituationMaritale => a verifier
	- ecole => a verifier
	- naissancePossible => genere une naissance si age entre 20 et 50 + une condition aleatoire.
	- achat-< nom entreprise > => achete nourriture a l'entreprise citee apres le '-' (exemple achat-aubonpain)
- Entreprise : 
	- produire	=> lance la produition du nombre de produit prevu pour chaque salarie
	- embaucher => cherche dans les humain si une personne est embeauchable
	- debaucher => supprime un des salarié

### Liste des variables de script disponibles par type d'objet : 

- Variables obligatoires : 
	- civilisation: 
		- tauxEpargne
	- Humain : 
	- Entreprise : 
		- nom
		- cout Salarie
		- prix produit
		- cout produit
		- maxEmploye
		- productiviteSalarie

- Variables facultatives : 
	- civilisation : 
	- Humain : 
		- age
	- Entreprise : 
		- nbSalarie
		- stock
		- nbCommande
	
	
## Differents niveau de log
	LOG_ERROR   0 : signale les erreurs d'exécution	
	LOG_WARNING 1 : signale avertissement lors de l'exécution
	LOG_INFO'   2 : message informatif sans 
	LOG_DEBUG   3 : utilise pour la mise au point du programme
	
## Algorithme analyse de script
	A rediger .....
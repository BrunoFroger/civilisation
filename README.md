# civilisation

Ce programme permet de simuler l'évolution d'une civilisation, il peut être adapté par l'intermédiaire de scripts propre à chaque type d'élément de cette civilisation
les types d'éléments actuellement proposé sont :

- humain
- entreprise


## Description du fichier de script
ce fichier doit contenir le comportement qui régit chaque évolution de l'objet concerné, le nom du fichier de script est compose du mon du type + '.scr'. les scripts sont stockés dans un répertoire nommé 'scripts'

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
	<Variable> = texte du nom de la variable dépend de l'objet
	<valeur> = nombre
	<affectation> = <variable> "=" <valeur>
	
	<listeCommandes> = <commande> | <listeCommandes>
	<commande> = texte du nom de la fonction a réaliser dépend de l'objet


### Liste des commandes disponibles pour l'objet Humain :
	<commande> =["mort"|"evolutionSituationMaritale"|"ecole"|
		"naissancePossible"|"achatNouriture"]
	
	
## Differents niveau de log
	LOG_INFO'   0 : message informatif sans 
	LOG_WARNING 1 : signale avertissement lors de l'exécution
	LOG_ERROR   2 : signale les erreurs d'exécution
	LOG_DEBUG   3 : utilise pour la mise au point du programme
	
## Algorithme analyse de script
	
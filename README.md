# civilisation


# differents niveau de log
LOG_DEBUG : utilise pour la mise au point du programme

## description du fichier de script
ce fichier doit contenir le comportement qui regit chaque evolution de l'objet concerné
'#' designe un commentaire => ligne ignoree
les lignes vides sont ignorees
il est possible d'indenter les lignes

### pour l'ojet Humain :
liste des commandes disponibles 
<test> = si <expression> alors <ListeCommandes> sinon <ListeCommandes> finsi

<expression> = (<expression>) <operateur> (<expression<>) | <item> <opTest> <item>
<operateur> = "&&" | "||"
<item> = <variable> | <valeur> | "("<expression>")"
<opTest> = "=" | "!=" | "<" | ">" | "<=" | ">="
<Variable> = texte du nom de la variable depend de l'objet
<valeur> = nombre

<listeCommandes> = <commande> | <listeCommandes>
<commande> = texte du nom de la fonction a realiser depend de l'objet
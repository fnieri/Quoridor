# Formatage du SRD

## Documents

- documents dans le dossier `tex/`
- images dans le dossier `img/`
- code dans le dossier `code/`

## Nommage

- documents : `<section>_<sujet>_<initiales_participants>.tex`
- images : `<section>_<sujet_image>.eps`
- code : `<section>_<sujet_code>.<ext>`

## Contenu

Ne mettez pas ce qui est avant `\begin{document}` et ce qui est après `\end{document}`,
juste le texte entre les deux.
Si vous voulez ajouter des packages,
ajoutez les au `main.tex` et faites un
PR.

Utilisez les commandes `\addimg{}` et `\addcode{}` pour que
tous nos composants soient les mêmes.

```latex
\addimg{img/image.eps}{width=\linewidth}{Caption}{label}
\addcode{code/code.cpp}{Caption}{C++}{label}
```

Pour le rendu PDF, compilez `main.tex` avec `xelatex main.tex` en faisant bien
attention à ajouter au `main.tex` un `\input{tex/fichier.tex}` si vous avez
ajouté de nouveaux fichiers.


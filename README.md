
# minishell

Le but du projet est de recréer un shell minimaliste fonctionnel en C. Il permet d’exécuter des commandes Unix, de gérer les redirections, les pipes, les variables d’environnement et plusieurs commandes internes, le tout en respectant des règles strictes de gestion de la mémoire et des signaux.

## Dépendances

- [`readline`](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [`make`](https://www.gnu.org/software/make/) pour compiler
- OS : Linux ou macOS

## Lancer le projet

```bash
git clone <repository>
cd ft_minishell
make
./minishell
```

## Fonctions obligatoires implémentées

- Affichage d’un prompt interactif
- Historique des commandes
- Exécution de commandes à partir de :
  - `$PATH`
  - chemin absolu
  - chemin relatif

- Gestion des quotes :
  - `'` (single quotes)
  - `"` (double quotes)

- Redirections :
  - `<` : redirection d'entrée
  - `>` : redirection de sortie
  - `>>` : redirection de sortie en append
  - `<<` : here-document

- Pipes `|`
- Variables d’environnement (`$VAR`) et `$?`
- Gestion des signaux :
  - `ctrl-C` : nouvelle ligne + prompt
  - `ctrl-D` : quitte le shell
  - `ctrl-\` : ignoré

- Built-ins :
  - `echo` (+ option `-n`)
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

# Uam-Bibliography-Processor
Task for passing classes

# Description
Założenia są następujące:
Aplikacja jednostanowiskowa, nie wymagana jest obsługa wielu użytkowników.
Program ma pracować na plikach z bibliografią w formacie amsrefs (wpis typu key-value, np. `author={Mleczko, P.}`, w dokumentach ma dokonywać zmian w dwóch rzeczach:

1. pozyskiwał z sieci numer doi pozycji (być mże uda się z http://search.crossref.org/ bądź innego serwsu)

2. sprawdzałby, czy nazwa czasopisma wpisana jest w poprawnej formie skróconej (np. Stud. Math. a nie Studia Mathematica lub Studia Math.). Bazę skrótów jest wstępnie przygotowana – mogłaby być rozszerzana. Poprawiony skrót powinien być akceptowany przez użytkownika – albo przez niego wprowadzany. Dane można zapisywać w tworzonej własnej bazie (trzymanej w pliku xml, czy SQL Lite)

Być może można by rozwinąć na inne formaty przechowywania informacji bibliografii naukowej.

Przykład:

Np. dane to plik tekstowy z bibliografią w formacie amsrefs (w załaczeniu
przykład)
Zapis ma być w tym samym formacie z dopisanymi polami  `doi={}`, np. wpis

```
\bib{FHKT}{article}{
   author={Flores, J.},
   author={Hern{\'a}ndez, {F.\,L.}},
   author={Kalton, {N.\,J.}},
   author={Tradacete, P.},
   title={Characterizations of strictly singular operators on Banach lattices},
   journal={J. London Math. Soc.},
   volume={79},
   date={2009},
   pages={612--630},
}
```

powinien wyglądać tak:

```
\bib{FHKT}{article}{
   author={Flores, J.},
   author={Hern{\'a}ndez, {F.\,L.}},
   author={Kalton, {N.\,J.}},
   author={Tradacete, P.},
   title={Characterizations of strictly singular operators on Banach lattices},
   journal={J. London Math. Soc.},
   volume={79},
   date={2009},
   pages={612--630},
   doi={10.1112/jlms/jdp007},
}
```


http://search.crossref.org/help/api

----
# Flags

 --config FILE_PATH
 	eg. --config /home/user/config.json

 --input FILE_PATH
 	eg. --input /home/user/1132.tex


----
# config.json
Opcje:
 - replaceExistingDoi Jesli true to zastąpi aktualne DOI jeśli zostanie znalezione nowe


Moduł crossref
 - enable (true/false) Włącza/Wyłącza użycie crossref do szukania DOI
 - types Jest to mapa typów z amsref do tego co używa crossref. Lista dostępnych typów jest pod adresem: http://api.crossref.org/types

Moduł nameValidator
 - enable (true/false) Włącza/Wyłącza sprawdzanie pola "journal" w każdym BIB
 - askBeforeReplace Przed każdą "poprawą" journal w BIB pytasię.
 - replaceMap Mapa z wszystkim zmień z czego ("from") na co ("to")

----
# Useful

http://bib-it.sourceforge.net/help/fieldsAndEntryTypes.php#article

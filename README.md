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

Pytanie:
Dear Editors of crossref.org,

I'm secretary of the Commentationes Mathematicae journal published by
the Polish Mathematical Society. During the process of preparing
manuscripts for publication we wish to supplement the bibliographic
data with the propriate DOI. The Polish Mathematical Society owns an
account on crossref.org.

How can we do it in an automated way? Do you provide any API? Are
there any fees for that?

Odpowiedź:
There are a few options for querying for DOI matches - we do have a REST API (details: http://api.crossref.org) that can be used to both retrieve DOIs in bulk and match DOIs to citations. The results returned do need to be evaluated for accuracy as the API will return all matches found.

If you are able to mark up your citations, we also support XML querying as described here:

http://help.crossref.org/query_basics

XML querying is very accurate and the results do not require evaluation.

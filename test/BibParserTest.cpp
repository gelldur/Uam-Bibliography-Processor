#pragma once

#include <gtest/gtest.h>
#include <parser/BibParser.h>

TEST(BibParserTest, simple)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{LibroA}{book}{\n"
										  "  author={Albiac, F.},\n"
										  "  author={Kalton, N.J.},\n"
										  "  title={Topics in Banach spaces theory},\n"
										  "  series={Grad. Text in Math.},\n"
										  "  volume={233},\n"
										  "  publisher={Springer},\n"
										  "  date={2006},\n"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("LibroA", bib.getCite());
	EXPECT_EQ("book", bib.getEntryType());
	EXPECT_EQ("Albiac, F.", bib.getValue("author"));
	EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
	EXPECT_EQ("Grad. Text in Math.", bib.getValue("series"));
	EXPECT_EQ("233", bib.getValue("volume"));
	EXPECT_EQ("Springer", bib.getValue("publisher"));
	EXPECT_EQ("2006", bib.getValue("date"));
	EXPECT_EQ("Topics in Banach spaces theory", bib.getValue("title"));
}

TEST(BibParserTest, notFormated)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{LibroA}{book}{"
										  "author={Albiac, F.},"
										  "author={Kalton, N.J.},"
										  "title={Topics in Banach spaces theory},"
										  "series={Grad. Text in Math.},"
										  "volume={233},"
										  "publisher={Springer},"
										  "date={2006},"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("LibroA", bib.getCite());
	EXPECT_EQ("book", bib.getEntryType());
	EXPECT_EQ("Albiac, F.", bib.getValue("author"));
	EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
	EXPECT_EQ("Grad. Text in Math.", bib.getValue("series"));
	EXPECT_EQ("233", bib.getValue("volume"));
	EXPECT_EQ("Springer", bib.getValue("publisher"));
	EXPECT_EQ("2006", bib.getValue("date"));
}

TEST(BibParserTest, extraSpaces)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib  {LibroA}   {book}    {"
										  "    author={Albiac, F.}   ,   "
										  "   author={Kalton, N.J.} ,   "
										  "  title={Topics in Banach spaces theory}         ,            "
										  " series={Grad. Text in Math.} , "
										  "             volume={233},       "
										  "       publisher={Springer}           ,"
										  "      date={2006}    ,     "
										  "           }");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("LibroA", bib.getCite());
	EXPECT_EQ("book", bib.getEntryType());
	EXPECT_EQ("Albiac, F.", bib.getValue("author"));
	EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
	EXPECT_EQ("Grad. Text in Math.", bib.getValue("series"));
	EXPECT_EQ("233", bib.getValue("volume"));
	EXPECT_EQ("Springer", bib.getValue("publisher"));
	EXPECT_EQ("2006", bib.getValue("date"));
}

TEST(BibParserTest, minimalKeys)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{A}{B}{"
										  "a={Albiac, F.},"
										  "a={Kalton, N.J.},"
										  "t={Topics in Banach spaces theory},"
										  "s={Grad. Text in Math.},"
										  "v={233},"
										  "p={Springer},"
										  "d={2006},"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("A", bib.getCite());
	EXPECT_EQ("B", bib.getEntryType());
	EXPECT_EQ("Topics in Banach spaces theory", bib.getValue("t"));
	EXPECT_EQ("Albiac, F.", bib.getValue("a"));
	EXPECT_EQ("Kalton, N.J.", bib.getValue("a", 1));
	EXPECT_EQ("Grad. Text in Math.", bib.getValue("s"));
	EXPECT_EQ("233", bib.getValue("v"));
	EXPECT_EQ("Springer", bib.getValue("p"));
	EXPECT_EQ("2006", bib.getValue("d"));
}

TEST(BibParserTest, minimalKeysAndValues)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{A}{B}{"
										  "a={a},"
										  "a={b},"
										  "t={c},"
										  "s={d},"
										  "v={e},"
										  "p={f},"
										  "d={{}},"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("A", bib.getCite());
	EXPECT_EQ("B", bib.getEntryType());
	EXPECT_EQ("c", bib.getValue("t"));
	EXPECT_EQ("a", bib.getValue("a"));
	EXPECT_EQ("b", bib.getValue("a", 1));
	EXPECT_EQ("d", bib.getValue("s"));
	EXPECT_EQ("e", bib.getValue("v"));
	EXPECT_EQ("f", bib.getValue("p"));
	EXPECT_EQ("{}", bib.getValue("d"));
}

TEST(BibParserTest, minimalKeysAndValuesRandomSpaces)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib  {A} {B}  {"
										  "a={a}  ,"
										  "             a={b}  ,"
										  "   t={c} , "
										  "  s={d},   "
										  "       v={e},"
										  "p={f}  ,"
										  "d={{  }  },"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("A", bib.getCite());
	EXPECT_EQ("B", bib.getEntryType());
	EXPECT_EQ("c", bib.getValue("t"));
	EXPECT_EQ("a", bib.getValue("a"));
	EXPECT_EQ("b", bib.getValue("a", 1));
	EXPECT_EQ("d", bib.getValue("s"));
	EXPECT_EQ("e", bib.getValue("v"));
	EXPECT_EQ("f", bib.getValue("p"));
	EXPECT_EQ("{  }  ", bib.getValue("d"));
}

TEST(BibParserTest, nested)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{KostrikinS1965}{article}{ author={Kostrikin, A. I.}, "
										  "author={\\v{S}afarevi\\v{c}, I. R.}, title={Cartan pseudogroups and Lie "
										  "$p$-algebras}, journal={Dokl. Akad. Nauk SSSR}, volume={168}, date={1965},"
										  " pages={740--742}, translation={ journal={Soviet Math. Dokl.}, volume={6}, date={1965}, pages={715--718} }, review={\\MR{0199235}} }");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("KostrikinS1965", bib.getCite());
	EXPECT_EQ("article", bib.getEntryType());
	EXPECT_EQ("Kostrikin, A. I.", bib.getValue("author"));
	EXPECT_EQ("\\v{S}afarevi\\v{c}, I. R.", bib.getValue("author", 1));
	EXPECT_EQ("168", bib.getValue("volume"));
	EXPECT_EQ("1965", bib.getValue("date"));
	EXPECT_EQ("740--742", bib.getValue("pages"));
	EXPECT_EQ("\\MR{0199235}", bib.getValue("review"));
	EXPECT_EQ(" journal={Soviet Math. Dokl.}, volume={6}, date={1965}, pages={715--718} ", bib.getValue("translation"));
	//TODO check parsing nested
	EXPECT_EQ("Dokl. Akad. Nauk SSSR", bib.getValue("journal"));
	EXPECT_EQ("Cartan pseudogroups and Lie $p$-algebras", bib.getValue("title"));
}

TEST(BibParserTest, two)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{LibroA}{book}{\n"
										  "  author={Albiac, F.},\n"
										  "  author={Kalton, N.J.},\n"
										  "  title={Topics in Banach spaces theory},\n"
										  "  series={Grad. Text in Math.},\n"
										  "  volume={233},\n"
										  "  publisher={Springer},\n"
										  "  date={2006},\n"
										  "}\n"
										  "\\bib{LibroCa}{book}{\n"
										  "  author={Carothers, N.},\n"
										  "  title={A~short course on Banach spaces theory},\n"
										  "  series={London Math. Soc student text},\n"
										  "  volume={64},\n"
										  "  publisher={Cambridge Univ. Press},\n"
										  "  date={2004},\n"
										  "}");

	EXPECT_EQ(2, singleBib.size());
	{
		auto& bib = singleBib[0];
		EXPECT_EQ("LibroA", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Albiac, F.", bib.getValue("author"));
		EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
		EXPECT_EQ("233", bib.getValue("volume"));
		EXPECT_EQ("2006", bib.getValue("date"));
		EXPECT_EQ("Grad. Text in Math.", bib.getValue("series"));
		EXPECT_EQ("Springer", bib.getValue("publisher"));
		EXPECT_EQ("Topics in Banach spaces theory", bib.getValue("title"));
	}
	{
		auto& bib = singleBib[1];
		EXPECT_EQ("LibroCa", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Carothers, N.", bib.getValue("author"));
		EXPECT_EQ("A~short course on Banach spaces theory", bib.getValue("title"));
		EXPECT_EQ("London Math. Soc student text", bib.getValue("series"));
		EXPECT_EQ("64", bib.getValue("volume"));
		EXPECT_EQ("Cambridge Univ. Press", bib.getValue("publisher"));
		EXPECT_EQ("2004", bib.getValue("date"));
	}
}

TEST(BibParserTest, three)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{LibroA}{book}{\n"
										  "  author={Albiac, F.},\n"
										  "  author={Kalton, N.J.},\n"
										  "  title={Topics in Banach spaces theory},\n"
										  "  series={Grad. Text in Math.},\n"
										  "  volume={233},\n"
										  "  publisher={Springer},\n"
										  "  date={2006},\n"
										  "}\n"
										  "\\bib{LibroCa}{book}{\n"
										  "  author={Carothers, N.},\n"
										  "  title={A~short course on Banach spaces theory},\n"
										  "  series={London Math. Soc student text},\n"
										  "  volume={64},\n"
										  "  publisher={Cambridge Univ. Press},\n"
										  "  date={2004},\n"
										  "}\n"
										  "\\bib{LibroC}{book}{\n"
										  "  author={Cruz-Uribe, D.},\n"
										  "  author={Fiorenza, A.},\n"
										  "  title={Variable Lebesgue spaces. Foundations and harmonic analysis},\n"
										  "  series={Applied and Numerical Harmonic Analysis},\n"
										  "  publisher={Birkhauser/Springer},\n"
										  "  place={Heidelberg.},\n"
										  "  date={2013},\n"
										  "}");

	EXPECT_EQ(3, singleBib.size());
	{
		auto& bib = singleBib[0];
		EXPECT_EQ("LibroA", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Albiac, F.", bib.getValue("author"));
		EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
		EXPECT_EQ("233", bib.getValue("volume"));
		EXPECT_EQ("2006", bib.getValue("date"));
		EXPECT_EQ("Grad. Text in Math.", bib.getValue("series"));
		EXPECT_EQ("Springer", bib.getValue("publisher"));
		EXPECT_EQ("Topics in Banach spaces theory", bib.getValue("title"));
	}
	{
		auto& bib = singleBib[1];
		EXPECT_EQ("LibroCa", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Carothers, N.", bib.getValue("author"));
		EXPECT_EQ("A~short course on Banach spaces theory", bib.getValue("title"));
		EXPECT_EQ("London Math. Soc student text", bib.getValue("series"));
		EXPECT_EQ("64", bib.getValue("volume"));
		EXPECT_EQ("Cambridge Univ. Press", bib.getValue("publisher"));
		EXPECT_EQ("2004", bib.getValue("date"));
	}
	{
		auto& bib = singleBib[2];
		EXPECT_EQ("LibroC", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Cruz-Uribe, D.", bib.getValue("author"));
		EXPECT_EQ("Fiorenza, A.", bib.getValue("author", 1));
		EXPECT_EQ("Variable Lebesgue spaces. Foundations and harmonic analysis", bib.getValue("title"));
		EXPECT_EQ("Applied and Numerical Harmonic Analysis", bib.getValue("series"));
		EXPECT_EQ("Heidelberg.", bib.getValue("place"));
		EXPECT_EQ("Birkhauser/Springer", bib.getValue("publisher"));
		EXPECT_EQ("2013", bib.getValue("date"));
	}
}

TEST(BibParserTest, threeMinimalFormat)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib{LibroA}{book}{"
										  "author={Albiac, F.},"
										  "author={Kalton, N.J.},"
										  "title={Topics in Banach spaces theory},"
										  "series={Grad. Text in Math.},"
										  "volume={233},"
										  "publisher={Springer},"
										  "date={2006},"
										  "}"
										  "\\bib{LibroCa}{book}{"
										  "author={Carothers, N.},"
										  "title={A~short course on Banach spaces theory},"
										  "series={London Math. Soc student text},"
										  "volume={64},"
										  "publisher={Cambridge Univ. Press},"
										  "date={2004},"
										  "}"
										  "\\bib{LibroC}{book}{"
										  "author={Cruz-Uribe, D.},"
										  "author={Fiorenza, A.},"
										  "title={Variable Lebesgue spaces. Foundations and harmonic analysis},"
										  "series={Applied and Numerical Harmonic Analysis},"
										  "publisher={Birkhauser/Springer},"
										  "place={Heidelberg.},"
										  "date={2013},"
										  "}");

	EXPECT_EQ(3, singleBib.size());
	{
		auto& bib = singleBib[0];
		EXPECT_EQ("LibroA", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Albiac, F.", bib.getValue("author"));
		EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
		EXPECT_EQ("233", bib.getValue("volume"));
		EXPECT_EQ("2006", bib.getValue("date"));
		EXPECT_EQ("Grad. Text in Math.", bib.getValue("series"));
		EXPECT_EQ("Springer", bib.getValue("publisher"));
		EXPECT_EQ("Topics in Banach spaces theory", bib.getValue("title"));
	}
	{
		auto& bib = singleBib[1];
		EXPECT_EQ("LibroCa", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Carothers, N.", bib.getValue("author"));
		EXPECT_EQ("A~short course on Banach spaces theory", bib.getValue("title"));
		EXPECT_EQ("London Math. Soc student text", bib.getValue("series"));
		EXPECT_EQ("64", bib.getValue("volume"));
		EXPECT_EQ("Cambridge Univ. Press", bib.getValue("publisher"));
		EXPECT_EQ("2004", bib.getValue("date"));
	}
	{
		auto& bib = singleBib[2];
		EXPECT_EQ("LibroC", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Cruz-Uribe, D.", bib.getValue("author"));
		EXPECT_EQ("Fiorenza, A.", bib.getValue("author", 1));
		EXPECT_EQ("Variable Lebesgue spaces. Foundations and harmonic analysis", bib.getValue("title"));
		EXPECT_EQ("Applied and Numerical Harmonic Analysis", bib.getValue("series"));
		EXPECT_EQ("Heidelberg.", bib.getValue("place"));
		EXPECT_EQ("Birkhauser/Springer", bib.getValue("publisher"));
		EXPECT_EQ("2013", bib.getValue("date"));
	}
}

TEST(BibParserTest, threeWithNewLinesAndTabs)
{
	BibParser parser;

	auto singleBib = parser.parse("\t\n\t\n\t\n\\bib\t\n{LibroA}\t\n{book}\t\n{\n"
										  "  author={Albiac, F.},\n"
										  "  \t\n\t\nauthor={Kalton, N.J.},\n"
										  "  title={Topics in Banach spaces theory},\n"
										  "  series={Grad.\t\n Text in Math.},\n"
										  "  \t\n\t\nvolume={233},\t\n\n"
										  "  \t\t\t\t\t\tpublisher={Springer}\t\t\t\t,\n"
										  "  \tdate={2006},\n"
										  "}\n"
										  "\n\n\n\\bib{LibroCa}{book}{\n"
										  "  \t\nauthor={Carothers, N.},\n"
										  "  \n\n\ntitle={A~short course on Banach spaces theory},\n"
										  "  \n\n\nseries={London Math. Soc student text},\n"
										  "  volume={64},\n"
										  "  \npublisher={Cambridge Univ. Press},\n"
										  "  date={2004},\n"
										  "\n\n\n}\n"
										  "\n\n\n\\bib{LibroC}{book}{\n"
										  "  author={Cruz-Uribe, D.},\n"
										  "  author={Fiorenza, A.},\n"
										  "  title={Variable Lebesgue spaces. Foundations and harmonic analysis},\n"
										  "  \t\n\t\n\t\nseries={Applied and Numerical Harmonic Analysis},\n"
										  "  publisher={Birkhauser/Springer},\n"
										  "  place={Heidelberg.},\n"
										  "  date={2013}\t\n\t\n\t\n\t\n,\n"
										  "}");

	EXPECT_EQ(3, singleBib.size());
	{
		auto& bib = singleBib[0];
		EXPECT_EQ("LibroA", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Albiac, F.", bib.getValue("author"));
		EXPECT_EQ("Kalton, N.J.", bib.getValue("author", 1));
		EXPECT_EQ("233", bib.getValue("volume"));
		EXPECT_EQ("2006", bib.getValue("date"));
		EXPECT_EQ("Grad.\t\n Text in Math.", bib.getValue("series"));
		EXPECT_EQ("Springer", bib.getValue("publisher"));
		EXPECT_EQ("Topics in Banach spaces theory", bib.getValue("title"));
	}
	{
		auto& bib = singleBib[1];
		EXPECT_EQ("LibroCa", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Carothers, N.", bib.getValue("author"));
		EXPECT_EQ("A~short course on Banach spaces theory", bib.getValue("title"));
		EXPECT_EQ("London Math. Soc student text", bib.getValue("series"));
		EXPECT_EQ("64", bib.getValue("volume"));
		EXPECT_EQ("Cambridge Univ. Press", bib.getValue("publisher"));
		EXPECT_EQ("2004", bib.getValue("date"));
	}
	{
		auto& bib = singleBib[2];
		EXPECT_EQ("LibroC", bib.getCite());
		EXPECT_EQ("book", bib.getEntryType());
		EXPECT_EQ("Cruz-Uribe, D.", bib.getValue("author"));
		EXPECT_EQ("Fiorenza, A.", bib.getValue("author", 1));
		EXPECT_EQ("Variable Lebesgue spaces. Foundations and harmonic analysis", bib.getValue("title"));
		EXPECT_EQ("Applied and Numerical Harmonic Analysis", bib.getValue("series"));
		EXPECT_EQ("Heidelberg.", bib.getValue("place"));
		EXPECT_EQ("Birkhauser/Springer", bib.getValue("publisher"));
		EXPECT_EQ("2013", bib.getValue("date"));
	}
}

TEST(BibParserTest, testCase1)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib   {FHKT}     {article}{\n"
										  "\n"
										  "   author={Flores, J.}   ,\n"
										  "\n"
										  "   author={Hern{\\'a}ndez, {F.\\,L.}}  ,\n"
										  "\n"
										  "   author={Kalton, {N.\\,J.}    },\n"
										  "\n"
										  "   author={Tradacete, P.}    ,\n"
										  "\n"
										  "   title={Characterizations of strictly singular operators on Banach\n"
										  "lattices},\n"
										  "\n"
										  "   journal={J. London Math. Soc.}         ,\n"
										  "\n"
										  "               volume={79},\n"
										  "\n"
										  "      date={2009}         ,\n"
										  "\n"
										  "   pages={612--630}          ,\n"
										  "\n"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("FHKT", bib.getCite());
	EXPECT_EQ("article", bib.getEntryType());
	EXPECT_EQ("Flores, J.", bib.getValue("author"));
	EXPECT_EQ("Hern{\\'a}ndez, {F.\\,L.}", bib.getValue("author", 1));
	EXPECT_EQ("Kalton, {N.\\,J.}    ", bib.getValue("author", 2));
	EXPECT_EQ("Tradacete, P.", bib.getValue("author", 3));
	EXPECT_EQ("Characterizations of strictly singular operators on Banach\nlattices", bib.getValue("title"));
	EXPECT_EQ("J. London Math. Soc.", bib.getValue("journal"));
	EXPECT_EQ("79", bib.getValue("volume"));
	EXPECT_EQ("2009", bib.getValue("date"));
	EXPECT_EQ("612--630", bib.getValue("pages"));
}

TEST(BibParserTest, spacesInKeyValue)
{
	BibParser parser;

	auto singleBib = parser.parse("\\bib   {FHKT}     {article}{\n"
										  "\n"
										  "   author=          {Flores, J.}   ,"
										  ""
										  "   author     ={Hern{\\'a}ndez, {F.\\,L.}}  ,\n"
										  "\n"
										  "   author =    {Kalton, {N.\\,J.}    },\n"
										  "\n"
										  "   author     =     {Tradacete, P.}    ,\n"
										  "\n"
										  "   title           ={Characterizations of strictly singular operators on "
										  "Banach\n"
										  "lattices},\n"
										  "\n"
										  "   journal= {J. London Math. Soc.}         ,\n"
										  "\n"
										  "               volume={79},\n"
										  "\n"
										  "      date = {2009}         ,\n"
										  "\n"
										  "   pages         ={612--630}          ,\n"
										  "\n"
										  "}");

	EXPECT_EQ(1, singleBib.size());

	auto& bib = singleBib.front();
	EXPECT_EQ("FHKT", bib.getCite());
	EXPECT_EQ("article", bib.getEntryType());
	EXPECT_EQ("Flores, J.", bib.getValue("author"));
	EXPECT_EQ("Hern{\\'a}ndez, {F.\\,L.}", bib.getValue("author", 1));
	EXPECT_EQ("Kalton, {N.\\,J.}    ", bib.getValue("author", 2));
	EXPECT_EQ("Tradacete, P.", bib.getValue("author", 3));
	EXPECT_EQ("Characterizations of strictly singular operators on Banach\nlattices", bib.getValue("title"));
	EXPECT_EQ("J. London Math. Soc.", bib.getValue("journal"));
	EXPECT_EQ("79", bib.getValue("volume"));
	EXPECT_EQ("2009", bib.getValue("date"));
	EXPECT_EQ("612--630", bib.getValue("pages"));
}

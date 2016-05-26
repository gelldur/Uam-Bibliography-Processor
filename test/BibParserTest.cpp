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


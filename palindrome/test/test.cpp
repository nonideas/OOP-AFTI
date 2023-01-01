#include "test.h"
#include <iostream>
#include <fstream>

TEST(SingleWord, Empty) {
	EXPECT_TRUE(CheckPalindrome::check_word_for_palindrome(""));
}

TEST(SingleWord, Word0) {
	EXPECT_TRUE(CheckPalindrome::check_word_for_palindrome("A"));
}

TEST(SingleWord, Word1) {
	EXPECT_TRUE(CheckPalindrome::check_word_for_palindrome("ABOBA"));
}

TEST(SingleWord, Word2) {
	EXPECT_TRUE(CheckPalindrome::check_word_for_palindrome("CivIc"));
}

TEST(SingleWord, Word3) {
	EXPECT_TRUE(CheckPalindrome::check_word_for_palindrome("dewed"));
}

TEST(SingleWord, Word4) {
	EXPECT_TRUE(CheckPalindrome::check_word_for_palindrome("BOOB"));
}

TEST(SingleWord, Word5) {
	EXPECT_FALSE(CheckPalindrome::check_word_for_palindrome("Word"));
}

TEST(SingleWord, Word6) {
	EXPECT_FALSE(CheckPalindrome::check_word_for_palindrome("google"));
}

TEST(SentenceWord, Empty) {
	EXPECT_TRUE(CheckPalindrome::check_sentence_for_palindrome(""));
}

TEST(SentenceWord, Space) {
	EXPECT_TRUE(CheckPalindrome::check_sentence_for_palindrome(" ."));
}

TEST(SentenceWord, Sentence1) {
	EXPECT_TRUE(CheckPalindrome::check_sentence_for_palindrome("A new order began, a more Roman age bred Rowena"));
}

TEST(SentenceWord, Sentence2) {
	EXPECT_TRUE(CheckPalindrome::check_sentence_for_palindrome("Anne, I vote more cars race Rome to Vienna."));
}

TEST(SentenceWord, Sentence3) {
	EXPECT_FALSE(CheckPalindrome::check_sentence_for_palindrome("Eva, eva"));
}

TEST(SentenceWordSet, Empty) {
	EXPECT_TRUE(CheckPalindrome::check_word_set_for_palindrome(""));
}

TEST(SentenceWordSet, Space) {
	EXPECT_TRUE(CheckPalindrome::check_word_set_for_palindrome(" ."));
}

TEST(SentenceWordSet, Sentence1) {
	EXPECT_TRUE(CheckPalindrome::check_word_set_for_palindrome("Luna tuna, tuna luna"));
}

TEST(SentenceWordSet, Sentence2) {
	EXPECT_FALSE(CheckPalindrome::check_word_set_for_palindrome("Luna tuna, tuna tina"));
}

TEST(ParseFile, TextFele) {
	std::stringstream stream("A nut for a jar of tuna");
	Palindrome palindrome(stream);
	EXPECT_TRUE(palindrome.GetIsSentensePalindrome());
	EXPECT_FALSE(palindrome.GetIsWordSetPalindrome());
	EXPECT_TRUE(palindrome.GetIsWordPalindrome()[0].get_is_palindrome());
	EXPECT_FALSE(palindrome.GetIsWordPalindrome()[1].get_is_palindrome());
	EXPECT_FALSE(palindrome.GetIsWordPalindrome()[2].get_is_palindrome());
	EXPECT_TRUE(palindrome.GetIsWordPalindrome()[3].get_is_palindrome());
	EXPECT_FALSE(palindrome.GetIsWordPalindrome()[4].get_is_palindrome());
	EXPECT_FALSE(palindrome.GetIsWordPalindrome()[5].get_is_palindrome());
	EXPECT_FALSE(palindrome.GetIsWordPalindrome()[6].get_is_palindrome());
}

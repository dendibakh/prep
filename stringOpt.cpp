#include <string>
#include <array>
#include <map>
#include <unordered_map>
#include <gtest/gtest.h>
#include <random>
#include <algorithm>
#include <cstring>

static const int NTimes = 100000;

std::array<std::string, 26> storage =
{
    "alpha" ,    "bravo",  
    "charlie" ,    "delta" ,
    "echo" ,    "foxtrot" ,  
    "golf" ,    "hotel" ,
    "india" ,    "juliet" ,  
    "kilo" ,    "lima" ,
    "mike" ,    "november" , 
    "oscar" ,    "papa" ,
    "quebec" ,    "romeo" ,
    "sierra" ,    "tango" ,
    "uniform" ,    "victor" ,
    "whiskey" ,    "x-ray" ,
    "yankee" ,    "zulu" 
};

std::array<std::string, 26> storageLost 
{
     "lpha" ,    "ravo",  
     "harlie" ,    "elta" ,
     "cho" ,    "oxtrot" ,  
     "olf" ,    "otel" ,
     "ndia" ,    "uliet" ,  
     "ilo" ,    "ma" ,
     "ike" ,    "ovember" , 
     "scar" ,    "apa" ,
     "uebec" ,   "omeo" ,
     "ierra" ,    "ango" ,
     "niform" ,    "ictor" ,
     "hiskey" ,    "-ray" ,
     "ankee" ,    "ulu" 
};

TEST(OptSearch, baseline)
{
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 25); // distribution in range [0, 25]
  std::mt19937 rng;
  rng.seed(std::random_device()());

  std::map<std::string, unsigned> const table {
    { "alpha",   1 },   { "bravo",   2 },  
    { "charlie", 3 },   { "delta",   4 },
    { "echo",    5 },   { "foxtrot", 6 },  
    { "golf",    7 },   { "hotel",   8 },
    { "india",   9 },   { "juliet", 10 },  
    { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 }, 
    { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },
    { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },
    { "whiskey",23 },   { "x-ray",  24 },
    { "yankee", 25 },   { "zulu",   26 }
  };

  auto hotFunc = [&table](std::string const& key) 
  {
    auto it = table.find(key);
    return it != table.end();
  };

  for (unsigned j = 0; j < NTimes; ++j)
  {
    unsigned countFound = 0;
    for (unsigned i = 0; i < 26; ++i)
      countFound += hotFunc(storage[dist(rng)]);

    unsigned countLost = 0;
    for (unsigned i = 0; i < 26; ++i)
      countLost += hotFunc(storageLost[dist(rng)]);

    EXPECT_EQ(26, countFound);
    EXPECT_EQ(0, countLost);
  }
}

TEST(OptSearch, hash_table)
{
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 25); // distribution in range [0, 25]
  std::mt19937 rng;
  rng.seed(std::random_device()());

  std::unordered_map<std::string, unsigned> const table {
    { "alpha",   1 },   { "bravo",   2 },  
    { "charlie", 3 },   { "delta",   4 },
    { "echo",    5 },   { "foxtrot", 6 },  
    { "golf",    7 },   { "hotel",   8 },
    { "india",   9 },   { "juliet", 10 },  
    { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 }, 
    { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },
    { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },
    { "whiskey",23 },   { "x-ray",  24 },
    { "yankee", 25 },   { "zulu",   26 }
  };

  auto hotFunc = [&table](std::string const& key) 
  {
    auto it = table.find(key);
    return it != table.end();
  };

  for (unsigned j = 0; j < NTimes; ++j)
  {
    unsigned countFound = 0;
    for (unsigned i = 0; i < 26; ++i)
      countFound += hotFunc(storage[dist(rng)]);

    unsigned countLost = 0;
    for (unsigned i = 0; i < 26; ++i)
      countLost += hotFunc(storageLost[dist(rng)]);

    EXPECT_EQ(26, countFound);
    EXPECT_EQ(0, countLost);
  }
}

TEST(OptSearch, std_array_sorted)
{
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 25); // distribution in range [0, 25]
  std::mt19937 rng;
  rng.seed(std::random_device()());

  struct Elem
  {
    std::string fir;
    unsigned sec;
  };

  std::array<Elem, 26> table {
    Elem{ "alpha",   1 },   Elem{ "bravo",   2 },  
    Elem{ "charlie", 3 },   Elem{ "delta",   4 },
    Elem{ "echo",    5 },   Elem{ "foxtrot", 6 },  
    Elem{ "golf",    7 },   Elem{ "hotel",   8 },
    Elem{ "india",   9 },   Elem{ "juliet", 10 },  
    Elem{ "kilo",   11 },   Elem{ "lima",   12 },
    Elem{ "mike",   13 },   Elem{ "november",14 }, 
    Elem{ "oscar",  15 },   Elem{ "papa",   16 },
    Elem{ "quebec", 17 },   Elem{ "romeo",  18 },
    Elem{ "sierra", 19 },   Elem{ "tango",  20 },
    Elem{ "uniform",21 },   Elem{ "victor", 22 },
    Elem{ "whiskey",23 },   Elem{ "x-ray",  24 },
    Elem{ "yankee", 25 },   Elem{ "zulu",   26 }
  };

  auto strLess = [](const Elem& lhs, const Elem& rhs)
      {
        return lhs.fir < rhs.fir;
      }; 

  std::sort(table.begin(), table.end(), strLess);

  for (unsigned j = 0; j < NTimes; ++j)
  {
    unsigned countFound = 0;
    for (unsigned i = 0; i < 26; ++i)
      countFound += std::binary_search(table.begin(), table.end(), Elem{storage[dist(rng)], 0}, strLess);

    unsigned countLost = 0;
    for (unsigned i = 0; i < 26; ++i)
      countLost += std::binary_search(table.begin(), table.end(), Elem{storageLost[dist(rng)], 0}, strLess);

    EXPECT_EQ(26, countFound);
    EXPECT_EQ(0, countLost);
  }
}

// Array didn't give to much benefit, so trying to implement 
// new comparison algorithm instead of lexicographical_compare 

TEST(OptSearch, hash_table_strcmp)
{
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 25); // distribution in range [0, 25]
  std::mt19937 rng;
  rng.seed(std::random_device()());

  struct KeyEq
  {
  bool operator()(const std::string& lhs, const std::string& rhs) const
  {
    if (lhs.size() != rhs.size())
      return false;
    
    return !strcmp(lhs.c_str(), rhs.c_str());
  }
  };

  std::unordered_map<std::string, unsigned, std::hash<std::string>, KeyEq> const table {
    { "alpha",   1 },   { "bravo",   2 },  
    { "charlie", 3 },   { "delta",   4 },
    { "echo",    5 },   { "foxtrot", 6 },  
    { "golf",    7 },   { "hotel",   8 },
    { "india",   9 },   { "juliet", 10 },  
    { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 }, 
    { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },
    { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },
    { "whiskey",23 },   { "x-ray",  24 },
    { "yankee", 25 },   { "zulu",   26 }
  };

  auto hotFunc = [&table](std::string const& key) 
  {
    auto it = table.find(key);
    return it != table.end();
  };

  for (unsigned j = 0; j < NTimes; ++j)
  {
    unsigned countFound = 0;
    for (unsigned i = 0; i < 26; ++i)
      countFound += hotFunc(storage[dist(rng)]);

    unsigned countLost = 0;
    for (unsigned i = 0; i < 26; ++i)
      countLost += hotFunc(storageLost[dist(rng)]);

    EXPECT_EQ(26, countFound);
    EXPECT_EQ(0, countLost);
  }
}

// Checking size first and using strcmp helped a bit.
// Now will try keeping char* instead of std::string

std::array<const char*, 26> storageCharStar =
{
    "alpha" ,    "bravo",  
    "charlie" ,    "delta" ,
    "echo" ,    "foxtrot" ,  
    "golf" ,    "hotel" ,
    "india" ,    "juliet" ,  
    "kilo" ,    "lima" ,
    "mike" ,    "november" , 
    "oscar" ,    "papa" ,
    "quebec" ,    "romeo" ,
    "sierra" ,    "tango" ,
    "uniform" ,    "victor" ,
    "whiskey" ,    "x-ray" ,
    "yankee" ,    "zulu" 
};

std::array<const char*, 26> storageLostCharStar
{
     "lpha" ,    "ravo",  
     "harlie" ,    "elta" ,
     "cho" ,    "oxtrot" ,  
     "olf" ,    "otel" ,
     "ndia" ,    "uliet" ,  
     "ilo" ,    "ma" ,
     "ike" ,    "ovember" , 
     "scar" ,    "apa" ,
     "uebec" ,   "omeo" ,
     "ierra" ,    "ango" ,
     "niform" ,    "ictor" ,
     "hiskey" ,    "-ray" ,
     "ankee" ,    "ulu" 
};

TEST(OptSearch, hash_table_strcmp_char_star)
{
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 25); // distribution in range [0, 25]
  std::mt19937 rng;
  rng.seed(std::random_device()());

  struct KeyHash 
  {
    std::size_t operator()(const char* s) const noexcept
    {
    size_t result = 0;
    const size_t prime = 31;
    size_t i = 0;
    while (s[i])
    {
      result = s[i] + (result * prime);
      ++i;
    }
    return result;
    }
  };

  struct KeyEq
  {
  bool operator()(const char* lhs, const char* rhs) const
  {
    return !strcmp(lhs, rhs);
  }
  };

  std::unordered_map<const char*, unsigned, KeyHash, KeyEq> const table {
    { "alpha",   1 },   { "bravo",   2 },  
    { "charlie", 3 },   { "delta",   4 },
    { "echo",    5 },   { "foxtrot", 6 },  
    { "golf",    7 },   { "hotel",   8 },
    { "india",   9 },   { "juliet", 10 },  
    { "kilo",   11 },   { "lima",   12 },
    { "mike",   13 },   { "november",14 }, 
    { "oscar",  15 },   { "papa",   16 },
    { "quebec", 17 },   { "romeo",  18 },
    { "sierra", 19 },   { "tango",  20 },
    { "uniform",21 },   { "victor", 22 },
    { "whiskey",23 },   { "x-ray",  24 },
    { "yankee", 25 },   { "zulu",   26 }
  };

  /*auto hotFunc = [&table](const char* key) 
  {
    auto it = table.find(key);
    return it != table.end();
  };*/

  for (unsigned j = 0; j < NTimes; ++j)
  {
    unsigned countFound = 0;
    for (unsigned i = 0; i < 26; ++i)
    {
      auto it = table.find(storageCharStar[dist(rng)]);
      countFound += it != table.end();
    }

    unsigned countLost = 0;
    for (unsigned i = 0; i < 26; ++i)
    {
      auto it = table.find(storageLostCharStar[dist(rng)]);
      countLost += it != table.end();
    }

    EXPECT_EQ(26, countFound);
    EXPECT_EQ(0, countLost);
  }
}


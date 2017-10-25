#include "TestBigInteger.h"
#include "Libs/BigInteger.h"

namespace EulerTest {

    using namespace EulerLib;

    /**
     * Run test.
     */
    bool TestBigInteger::Run()
    {
        TestConstructors();
        TestOperatorAssign();
        TestToString();

        TestOperatorSmallerThan();
        TestOperatorGreaterThan();
        TestOperatorSmallerThanOrEquals();
        TestOperatorGreaterThanOrEquals();
        TestOperatorEquals();
        TestOperatorNotEquals();

        TestAddBins();
        TestOperatorAddAssign();
        TestOperatorMulAssign();

        return true;
    }

    /**
     * Test all the class constructors.
     */
    void TestBigInteger::TestConstructors()
    {
        std::cout << __FUNCTION__;

        // Test default constructor
        BigInteger bigDefault;

        assert(bigDefault.m_vBins.size() == 0 &&
               "Default constructor should produce zero size.");

        // Test copy constructor
        bigDefault.m_vBins.push_back(3);
        bigDefault.m_vBins.push_back(1);
        BigInteger bigCopy(bigDefault);

        assert(bigCopy.m_vBins.size() == bigDefault.m_vBins.size() &&
               "Copy constructor should produce BigInteger that have same size.");
        assert(bigCopy.m_vBins[0] == bigCopy.m_vBins[0] &&
               "Copy constructor should copy the same values.");
        assert(bigCopy.m_vBins[1] == bigCopy.m_vBins[1] &&
               "Copy constructor should copy the same values.");

        // Test specialized constructor for unsigned integers.
        BigInteger bigUnsignedLongLong(0xFFFFFFFFFFFFFFFFull);
        BigInteger bigUnsignedLong(0xFFFFFFFFul);

        assert(bigUnsignedLongLong.m_vBins.size() == 1 &&
               "A 64-bit unsigned integer should only use one location.");
        assert(bigUnsignedLongLong.m_vBins[0] == 0xFFFFFFFFFFFFFFFFull &&
               "Value differs");

        assert(bigUnsignedLong.m_vBins.size() == 1 &&
               "A 32-bit unsigned integer should only use one location.");
        assert(bigUnsignedLong.m_vBins[0] == 0xFFFFFFFFull &&
               "Value differs");

        // Test unsigned integer constructor with signed integer
        BigInteger bigSignedLongLong(-1ll);

        assert(bigSignedLongLong.m_vBins.size() == 1 &&
               "A 64-bit signed integer should be convert to an unsigned integer with one location.");
        assert(bigSignedLongLong.m_vBins[0] == 0xFFFFFFFFFFFFFFFFull &&
               "Value differs");

        // Test specialized construtor using a small string number (315).
        std::string strNumber = "315";
        BigInteger bigSmallString(strNumber);

        assert(bigSmallString.m_vBins.size() == 1 &&
               "A 3-digit number should use exactly one location.");
        assert(bigSmallString.m_vBins[0] == 315ull &&
               "Value differs.");

        // Test specialized construtor using a large string number (2**65-2).
        std::string strLargeNumber = "36893488147419103230";
        BigInteger bigLargeString(strLargeNumber);

        assert(bigLargeString.m_vBins.size() == 2 &&
               "This 20-digit number should use exactly two locations.");
        assert(bigLargeString.m_vBins[0] == 0xFFFFFFFFFFFFFFFEull &&
               "Value differs.");
        assert(bigLargeString.m_vBins[1] == 0x1ull &&
               "Value differs.");

        // Test specialized construtor using a small string number with
        // invalid character (31Z15). Such characters are converted to zero.
        std::string strBadNumber = "31%15";
        BigInteger bigBadString(strBadNumber);

        assert(bigBadString.m_vBins.size() == 1 &&
               "A 3-digit number should use exactly one location.");
        assert(bigBadString.m_vBins[0] == 31015ull &&
               "Value differs.");

        // Test specifalized constructor with hex string number
        std::string strDwordHexNumber = "0xABBA3FF3";
        BigInteger bigDwordHexString(strDwordHexNumber);

        assert(bigDwordHexString.m_vBins.size() == 1 &&
               "This 8-digit hex number should use exactly one location.");
        assert(bigDwordHexString.m_vBins[0] == 0xABBA3FF3ull &&
               "Value differs.");

        std::string strQwordHexNumberOdd = "0xDEADBEEFABBA3FF3";
        BigInteger bigQwordHexStringOdd(strQwordHexNumberOdd);

        assert(bigQwordHexStringOdd.m_vBins.size() == 1 &&
               "This 16-digit hex number should use exactly one location.");
        assert(bigQwordHexStringOdd.m_vBins[0] == 0xDEADBEEFABBA3FF3ull &&
               "Value differs.");

        // Test specifalized constructor with hex string number
        std::string strLargeHexNumber = "0x1FFFFFFFFFFFFFFFE";
        BigInteger bigLargeHexString(strLargeHexNumber);

        assert(bigLargeHexString.m_vBins.size() == 2 &&
               "This 17-digit hex number should use exactly two locations.");
        assert(bigLargeHexString.m_vBins[0] == 0xFFFFFFFFFFFFFFFEull &&
               "Value differs.");
        assert(bigLargeHexString.m_vBins[1] == 0x1ull &&
               "Value differs.");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test ToString function calls.
     */
    void TestBigInteger::TestToString()
    {
        std::cout << __FUNCTION__;

        // Small integer to string
        BigInteger bigSmallInt(123);

        std::string strSmallInt = bigSmallInt.ToString();

        assert(strSmallInt == "123" &&
               "String number does not match (1 nom_");

        // Large integer to string
        BigInteger bigLargeInt("36893488147419103230");

        std::string strLargeInt = bigLargeInt.ToString();

        assert(strLargeInt == "36893488147419103230" &&
               "String number does not match (2 bins)");

        // Large integer to string
        BigInteger bigEmpty;

        std::string strEmpty = bigEmpty.ToString();

        assert(strEmpty == "" &&
               "Not empty string.");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test assignment operator = cases.
     */
    void TestBigInteger::TestOperatorAssign()
    {
        std::cout << __FUNCTION__;

        // Test assignment: we only need to test assignment from
        // a BigInteger, since assignment from other types will try
        // to call a matching copy constructor.
        BigInteger bigTest;
        BigInteger bigNumber;

        bigTest.m_vBins.push_back(1);
        bigTest.m_vBins.push_back(1);

        bigNumber.m_vBins.push_back(2);
        bigNumber.m_vBins.push_back(5);
        bigNumber.m_vBins.push_back(3);

        bigTest = bigNumber;

        assert(bigTest.m_vBins.size() == 3 &&
               "Equals should copy the three elements present.");
        assert(bigTest.m_vBins[0] == 2 &&
               "Copy constructor should copy the same values.");
        assert(bigTest.m_vBins[1] == 5 &&
               "Copy constructor should copy the same values.");
        assert(bigTest.m_vBins[2] == 3 &&
               "Copy constructor should copy the same values.");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test boolean operator < cases.
     */
    void TestBigInteger::TestOperatorSmallerThan()
    {
        std::cout << __FUNCTION__;

        // Test a < b, where a is smaller than b (uint64),
        // such that only one bin is used.
        BigInteger a(0x1);
        BigInteger b(0xFFFFFFFFFFFFFFFFull);

        // Test basic cases without all coverage
        assert(a < b &&
               "a is not greater than b");
        assert(!(b < a) &&
               "b is not smaller than a");
        assert(!(a < a) &&
               "a is not smaller than a");

        // Test x < y where x is maller than b (string),
        // such that more than one bin is used. Full coverage.
        BigInteger x("18446744073709551615");
        BigInteger y("36893488147419103230");
        BigInteger z("36893488147419103235");
        BigInteger w("36893488147419103229");

        // Size of bins will differ, returning true
        assert(x < y &&
               "x is not greater than y");
        // Size of bins will differ, returning false
        assert(!(y < x) &&
               "y is not smaller than x");
        // Size of bins is the same, returning false
        assert(!(x < x) &&
               "x is not smaller than x");
        // Size of bins is the same, second bin differs, returning true
        assert(y < z &&
               "y is not greater than z");
        // Size of bins is the same, first bin differs, returning true
        assert(w < y &&
               "w is not greater than y");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test boolean operator > cases.
     */
    void TestBigInteger::TestOperatorGreaterThan()
    {
        std::cout << __FUNCTION__;

        // Test b > a b, where a is greater than b (uint64),
        // such that only one bin is used.
        BigInteger a(0x1);
        BigInteger b(0xFFFFFFFFFFFFFFFFull);

        // Test basic cases without all coverage
        assert(b > a &&
               "b is not smaller than a");
        assert(!(a > b) &&
               "a is not smaller than b");
        assert(!(a > a) &&
               "a is not greater than a");

        // Test y > x where y is greater than b (string),
        // such that more than one bin is used. Full coverage.
        BigInteger x("18446744073709551615");
        BigInteger y("36893488147419103230");
        BigInteger z("36893488147419103235");
        BigInteger w("36893488147419103229");

        // Size of bins will differ, returning true
        assert(y > x &&
               "y is not smaller than x");
        // Size of bins will differ, returning false
        assert(!(x > y) &&
               "x is not smaller than y");
        // Size of bins is the same, returning false
        assert(!(x > x) &&
               "x is not greater than x");
        // Size of bins is the same, second bin differs, returning true
        assert(z > y &&
               "y is smaller than z");
        // Size of bins is the same, first bin differs, returning true
        assert(y > w &&
               "w is smaller than y");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test boolean operator <= cases.
     */
    void TestBigInteger::TestOperatorSmallerThanOrEquals()
    {
        std::cout << __FUNCTION__;

        // Test a < b, where a is smaller than b (uint64),
        // such that only one bin is used.
        BigInteger a(0x1);
        BigInteger b(0xFFFFFFFFFFFFFFFFull);

        // Test basic cases without all coverage
        assert(a <= b &&
               "a is not greater than b");
        assert(!(b <= a) &&
               "b is not smaller than a");
        assert(a <= a &&
               "a is not greater than a");

        // Test x < y where x is maller than b (string),
        // such that more than one bin is used. Full coverage.
        BigInteger x("18446744073709551615");
        BigInteger y("36893488147419103230");
        BigInteger z("36893488147419103235");
        BigInteger w("36893488147419103229");

        // Size of bins will differ, returning true
        assert(x <= y &&
               "x is not greater than y");
        // Size of bins will differ, returning false
        assert(!(y <= x) &&
               "y is not smaller than x");
        // Size of bins is the same, returning false
        assert(x <= x &&
               "x is not greater than x");
        // Size of bins is the same, second bin differs, returning true
        assert(y <= z &&
               "y is not greater than z");
        // Size of bins is the same, first bin differs, returning true
        assert(w <= y &&
               "w is not greater than y");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test boolean operator >= cases.
     */
    void TestBigInteger::TestOperatorGreaterThanOrEquals()
    {
        std::cout << __FUNCTION__;

        // Test b > a b, where a is greater than b (uint64),
        // such that only one bin is used.
        BigInteger a(0x1);
        BigInteger b(0xFFFFFFFFFFFFFFFFull);

        // Test basic cases without all coverage
        assert(b >= a &&
               "b is not smaller than a");
        assert(!(a >= b) &&
               "a is not smaller than b");
        assert(a >= a &&
               "a is not smaller than a");

        // Test y > x where y is greater than b (string),
        // such that more than one bin is used. Full coverage.
        BigInteger x("18446744073709551615");
        BigInteger y("36893488147419103230");
        BigInteger z("36893488147419103235");
        BigInteger w("36893488147419103229");

        // Size of bins will differ, returning true
        assert(y >= x &&
               "y is not smaller than x");
        // Size of bins will differ, returning false
        assert(!(x >= y) &&
               "x is not smaller than y");
        // Size of bins is the same, returning false
        assert(x >= x &&
               "x is not smaller than x");
        // Size of bins is the same, second bin differs, returning true
        assert(z >= y &&
               "y is smaller than z");
        // Size of bins is the same, first bin differs, returning true
        assert(y >= w &&
               "w is smaller than y");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test equals operator == test cases.
     */
    void TestBigInteger::TestOperatorEquals()
    {
       std::cout << __FUNCTION__;

       // Test a = b,
       BigInteger a(0x1);
       BigInteger b(0xA0);
       BigInteger c("0x1FFFFFFFFFFFFFFFE");
       BigInteger d("0x1FFFFFFFFFFFFFFF1");

       assert(a == a &&
              "a does not equal a (1 bin)");
       assert(c == c &&
              "c does not equal c (2 bins)");
       assert(!(a == c) &&
              "a equals c (1 bin/2 bins)");
       assert(!(a == b) &&
              "a equals b (1 bin/1 bin)");
       assert(!(c == d) &&
              "c equals d (2 bins/2 bins)");

       std::cout << "... PASS" << std::endl;
    }

    /**
     * Test not equals operator != test cases.
     */
    void TestBigInteger::TestOperatorNotEquals()
    {
       std::cout << __FUNCTION__;

       // Test a = b,
       BigInteger a(0x1);
       BigInteger b(0xA0);
       BigInteger c("0x1FFFFFFFFFFFFFFFE");
       BigInteger d("0x1FFFFFFFFFFFFFFF1");

       assert(!(a != a) &&
              "a does not equal a (1 bin)");
       assert(!(c != c) &&
              "c does not equal c (2 bins)");
       assert(a != c &&
              "a equals c (1 bin/2 bins)");
       assert(a != b &&
              "a equals b (1 bin/1 bin)");
       assert(c != d &&
              "c equals d (2 bins/2 bins)");

       std::cout << "... PASS" << std::endl;
    }

    /**
     * Test AddBins function.
     */
    void TestBigInteger::TestAddBins()
    {
        std::cout << __FUNCTION__;

        BigInteger bigNumber;
        uint64_t number = 0;
        uint64_t carry = 0;

        // Test no carry in, no carry out
        carry = 0;
        number = bigNumber.AddBins(0xFFFFFFFF, 1, carry);

        assert(number == 0x100000000 && "Wrong number.");
        assert(carry == 0 && "No carry.");

        // Test no carry in, with carry out
        carry = 1;
        number = bigNumber.AddBins(0xFFFFFFFF, 1, carry);

        assert(number == 0x100000001 && "Wrong number.");
        assert(carry == 0 && "No carry.");

        // Test with carry in, no carry out
        carry = 0;
        number = bigNumber.AddBins(0xFFFFFFFFFFFFFFFF, 1, carry);

        assert(number == 0x0 && "Wrong number.");
        assert(carry == 1 && "Should have a carry.");

        // Test with carry in, with carry out
        carry = 1;
        number = bigNumber.AddBins(0xFFFFFFFFFFFFFFFF, 1, carry);

        assert(number == 0x1 && "Wrong number.");
        assert(carry == 1 && "Should have a carry.");

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test add assign operator += test cases.
     */
    void TestBigInteger::TestOperatorAddAssign()
    {
        std::cout << __FUNCTION__;

        // Two objects for testing
        BigInteger bigNumber1;
        BigInteger bigNumber2;
        std::string strNumber;

        // Start by adding two single bin numbers (no carry over)
        bigNumber1 = 12;
        bigNumber2 = 63;

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "75" &&
               "Number is wrong.");

        // Add two single bin numbers (with carry over)
        bigNumber1 = 0xFFFFFFFFFFFFFFFFull;
        bigNumber2 = 1;

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "18446744073709551616" &&
               "Number is wrong.");

        // Add a two bins number with a single bin number (no carry over)
        bigNumber1 = std::string("0x1FFFFFFFFFFFFFFFF");
        bigNumber2 = 1;

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "36893488147419103232" &&
               "Number is wrong.");

        // Add two two bins numbers (no carry over)
        bigNumber1 = std::string("0x10000000000000001");
        bigNumber2 = std::string("0x10000000000000001");

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "36893488147419103234" &&
               "Number is wrong.");

        // Add one two bins number with one bin number (with carry over)
        bigNumber1 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        bigNumber2 = 1;

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "340282366920938463463374607431768211456" &&
               "Number is wrong.");

        // Add two two bins numbers (with carry over)
        bigNumber1 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        bigNumber2 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "680564733841876926926749214863536422910" &&
               "Number is wrong.");

        // Add four bins with two bins numbers (no carry over)
        bigNumber1 = std::string("0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        bigNumber2 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "12554203470773361528011861213336271295668085496359837237246" &&
               "Number is wrong.");

        // Add two bins with four bins numbers (no carry over)
        bigNumber1 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        bigNumber2 = std::string("0x1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

        bigNumber1 += bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber== "12554203470773361528011861213336271295668085496359837237246" &&
               "Number is wrong." && bigNumber1.ToString().c_str());

        std::cout << "... PASS" << std::endl;
    }

    /**
     * Test multiply assign operator *= test cases.
     */
    void TestBigInteger::TestOperatorMulAssign()
    {
        std::cout << __FUNCTION__;

        // Two objects for testing
        BigInteger bigNumber1;
        BigInteger bigNumber2;
        std::string strNumber;

        // Multiply single bin number with single bin number (no carry over)
        bigNumber1 = 505;
        bigNumber2 = 11;

        bigNumber1 *= bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "5555" &&
               "Number is wrong.");
        assert(bigNumber1.m_vBins.size() == 1 &&
               "Wrong number of bins.");

        // Multiply single bin number with single bin number (with carry over)
        bigNumber1 = 0xFFFFFFFFFFFFFFFFull;
        bigNumber2 = 2;

        bigNumber1 *= bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "36893488147419103230" &&
               "Number is wrong.");
        assert(bigNumber1.m_vBins.size() == 2 &&
               "Wrong number of bins.");

        // Multiply two bins number with single bin number (no carry over)
        bigNumber1 = std::string("0x1FFFFFFFFFFFFFFFF");
        bigNumber2 = 2;

        bigNumber1 *= bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "73786976294838206462" &&
               "Number is wrong.");
        assert(bigNumber1.m_vBins.size() == 2 &&
               "Wrong number of bins.");

        // Multiply two bins number with single bin number (with carry over)
        bigNumber1 = std::string("0x1FFFFFFFFFFFFFFFF");
        bigNumber2 = std::string("0xFFFFFFFFFFFFFFFF");

        bigNumber1 *= bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "680564733841876926871408982642407768065" &&
               "Number is wrong.");
        assert(bigNumber1.m_vBins.size() == 3 &&
               "Wrong number of bins.");

        // Multiply two bins number with two bins number (no carry over)
        bigNumber1 = std::string("0x1FFFFFFFFFFFFFFFF");
        bigNumber2 = std::string("0x1FFFFFFFFFFFFFFFF");

        bigNumber1 *= bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "1361129467683753853779711453432234639361" &&
               "Number is wrong.");
        assert(bigNumber1.m_vBins.size() == 3 &&
               "Wrong number of bins.");

        // Multiply two bins number with two bins number (with carry over)
        bigNumber1 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
        bigNumber2 = std::string("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

        bigNumber1 *= bigNumber2;
        strNumber = bigNumber1.ToString();

        assert(strNumber == "115792089237316195423570985008687907852589419931798687112530834793049593217025" &&
               "Number is wrong.");
        assert(bigNumber1.m_vBins.size() == 4 &&
               "Wrong number of bins.");

        std::cout << "... PASS" << std::endl;
    }
}

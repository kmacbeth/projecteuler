#include "Problem0054_Hand.h"

namespace _Problem54 {

    bool CardValueCompare::operator() (const std::string& a_rLhs, const std::string& a_rRhs)
    {
        uint32_t lindex = 0;
        uint32_t rindex = 0;

        for (uint32_t i = 0; i < 13; ++i)
        {
            if (a_rLhs == Hand::kCardValues[i])
            {
                lindex = i;
            }
            if (a_rRhs == Hand::kCardValues[i])
            {
                rindex = i;
            }
        }

        return lindex < rindex;
    }

    bool CardColorCompare::operator() (const std::string& a_rLhs, const std::string& a_rRhs)
    {
        uint32_t lindex = 0;
        uint32_t rindex = 0;

        for (uint32_t i = 0; i < 4; ++i)
        {
            if (a_rLhs == Hand::kCardColors[i])
            {
                lindex = i;
            }
            if (a_rRhs == Hand::kCardColors[i])
            {
                rindex = i;
            }
        }

        return lindex < rindex;
    }

    const std::string Hand::kCardColors[4] = { "C", "D", "S", "H" };
    const std::string Hand::kCardValues[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };
    const std::string Hand::kRank[10] = { "H", "P", "2P", "3K", "S", "F", "FH", "4K", "SF", "RT" };

    /**
     * Player default constructor
     */
    Hand::Hand() :
        m_HandRanks(),
        m_vHand(),
        m_vValues(13),
        m_vColors(13),
        m_mValuesIndexCache(),
        m_mColorsIndexCache()

    {
        BuildValuesCache();
        BuildColorsCache();
    }

    /**
    * Prebuild values [std::string] index
    */
    void Hand::BuildValuesCache()
    {
        for (uint32_t i = 0; i < 13; ++i)
        {
            m_mValuesIndexCache[kCardValues[i]] = i;
        }
    }

    /**
    * Prebuild colors [std::string] index
    */
    void Hand::BuildColorsCache()
    {
        for (uint32_t i = 0; i < 4; ++i)
        {
            m_mColorsIndexCache[kCardColors[i]] = i;
        }
    }

    /**
    * Add a card to player's hand
    *
    * @param card Card to add ([Value][Color])
    */
    void Hand::AddCard(std::string& a_rCard)
    {
        // Add card to hand
        m_vHand.push_back(a_rCard);

        // Add card value and color
        m_vValues[m_mValuesIndexCache[a_rCard.substr(0, 1)]]++;
        m_vColors[m_mColorsIndexCache[a_rCard.substr(1, 1)]]++;
    }

    /**
    * Initialize hand statistic and rank back to initial state.
    */
    void Hand::Initialize()
    {
        // Clear previous card values and types
        // This safe as we use a POD type: uint32_t.
        ::memset(&m_vValues[0], 0, sizeof(m_vValues[0]) * m_vValues.size());
        ::memset(&m_vColors[0], 0, sizeof(m_vColors[0]) * m_vColors.size());

        m_HandRanks.clear();
    }

    /**
    * Compute and return the player current hand.
    *
    * @return An object returning the current rank and accompanying
    *        information to determine a winning hand.
    */
    const Hand::THandRank& Hand::GetRank()
    {
        // Check if we've got five of the same color
        bool fiveColors = false;

        for (const auto& color : m_vColors)
        {
            if (color == 5)
            {
                fiveColors = true;
            }
        }

        // Check 4-3-2 same values and sequence of five consecutive values
        std::vector<int32_t> num2;
        std::vector<int32_t> singleCards;
        uint32_t highestCard = 0;
        uint32_t countOfFive = 0;
        int32_t num4 = -1;
        int32_t num3 = -1;

        for (uint32_t i = 0; i < 13; ++i)
        {
            if (m_vValues[i] > 0)
            {
                highestCard = i;
            }

            if (m_vValues[i] > 3)
            {
                num4 = i;
            }
            else if (m_vValues[i] > 2)
            {
                num3 = i;
            }
            else if (m_vValues[i] > 1)
            {
                num2.push_back(i);
            }
            else if (m_vValues[i] > 0)
            {
                countOfFive++;
                singleCards.push_back(i);
            }
            else
            {
                if (countOfFive < 5)
                {
                    countOfFive = 0;
                }
            }
        }

        // Royal and straight flush
        if (fiveColors && countOfFive == 5)
        {
            if (m_vValues[12] == 1) // Ace
            {
                m_HandRanks.push_back(std::make_pair("RF", ""));
            }
            else
            {
                m_HandRanks.push_back(std::make_pair("SF", kCardValues[highestCard]));
            }
            return m_HandRanks;
        }

        // Four-of-a-kind
        if (num4 > -1)
        {
            m_HandRanks.clear();
            m_HandRanks.push_back(std::make_pair("4K", ""));
            return m_HandRanks;
        }

        // Full house
        if (num3 > -1 && num2.size() == 1)
        {
            m_HandRanks.clear();
            m_HandRanks.push_back(std::make_pair("FH", kCardValues[num3]));
            return m_HandRanks;
        }

        // Flush
        if (fiveColors)
        {
            m_HandRanks.push_back(std::make_pair("F", kCardValues[highestCard]));
            return m_HandRanks;
        }

        // Straight
        if (countOfFive == 5 || // A-2-3-4-5
            (singleCards.size() == 5 &&
                m_vValues[12] && m_vValues[0] && m_vValues[1] && m_vValues[2] && m_vValues[3]))
        {
            m_HandRanks.push_back(std::make_pair("S", kCardValues[highestCard]));
            return m_HandRanks;
        }

        // Three-of-a-kind
        if (num3 > -1)
        {
            m_HandRanks.push_back(std::make_pair("3K", ""));
            return m_HandRanks;
        }

        // Two pairs
        if (num2.size() == 2)
        {
            m_HandRanks.push_back(std::make_pair("2P", kCardValues[num2[0] > num2[1] ? num2[0] : num2[1]]));
            m_HandRanks.push_back(std::make_pair("2P", kCardValues[num2[1] > num2[0] ? num2[1] : num2[0]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[0]]));
            return m_HandRanks;
        }

        // Single pair
        if (num2.size() == 1)
        {
            m_HandRanks.push_back(std::make_pair("P", kCardValues[num2[0]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[2]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[1]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[0]]));
            return m_HandRanks;
        }

        // Highests
        m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[4]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[3]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[2]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[1]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[singleCards[0]]));

        return m_HandRanks;
    }

}
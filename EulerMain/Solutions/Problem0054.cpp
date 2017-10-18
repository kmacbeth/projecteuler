#include "Problem0054.h"
#include "Libs/EulerMath.h"
#include "Libs/EulerUtils.h"

namespace Euler {
    
    /**
     * Player default constructor
     */
    Problem54::Player::Player() :
        m_HandRanks(),
        m_Hand(),
        m_Values(13),
        m_ValuesIndexCache(),
        m_Colors(13),
        m_ColorsIndexCache()

    {
        BuildValuesCache();
        BuildColorsCache();
    }

    /**
     * Prebuild values [std::string] index
     */
    void Problem54::Player::BuildValuesCache()
    {
        for (uint32_t i = 0; i < 13; ++i)
        {
            m_ValuesIndexCache[kCardValues[i]] = i;
        }
    }

    /**
     * Prebuild colors [std::string] index
     */
    void Problem54::Player::BuildColorsCache()
    {
        for (uint32_t i = 0; i < 4; ++i)
        {
            m_ColorsIndexCache[kCardColors[i]] = i;
        }
    }

    /**
     * Add a card to player's hand
     *
     * @param card Card to add ([Value][Color])
     */
    void Problem54::Player::AddCard(std::string& card)
    {
        // Add card to hand
        m_Hand.push_back(card);

        // Add card value and color
        m_Values[m_ValuesIndexCache[card.substr(0, 1)]]++;
        m_Colors[m_ColorsIndexCache[card.substr(1, 1)]]++;
    }

    /**
     * Initialize hand statistic and rank back to initial state.
     */
    void Problem54::Player::Initialize()
    {
        // Clear previous card values and types
        // This safe as we use a POD type: uint32_t.
        ::memset(&m_Values[0], 0, sizeof(m_Values[0]) * m_Values.size());
        ::memset(&m_Colors[0], 0, sizeof(m_Colors[0]) * m_Colors.size());

        m_HandRanks.clear();
    }

    /**
     * Compute and return the player current hand.
     *
     * @return An object returning the current rank and accompanying
     *        information to determine a winning hand.
     */
    const Problem54::Player::THandRank& Problem54::Player::GetHand()
    {
        // Check if we've got five of the same color
        bool five_colors = false;

        for (const auto& color : m_Colors)
        {
            if (color == 5)
            {
                five_colors = true;
            }
        }

        // Check 4-3-2 same values and sequence of five consecutive values
        std::vector<int32_t> num2;
        std::vector<int32_t> single_cards;
        uint32_t highest_card = 0;
        uint32_t count_of_five = 0;
        int32_t num4 = -1;
        int32_t num3 = -1;

        for (uint32_t i = 0; i < 13; ++i)
        {
            if (m_Values[i] > 0)
            {
                highest_card = i;
            }

            if (m_Values[i] > 3)
            {
                num4 = i;
            }
            else if (m_Values[i] > 2)
            {
                num3 = i;
            }
            else if (m_Values[i] > 1)
            {
                num2.push_back(i);
            }
            else if (m_Values[i] > 0)
            {
                count_of_five++;
                single_cards.push_back(i);
            }
            else
            {
                if (count_of_five < 5)
                {
                    count_of_five = 0;
                }
            }
        }

        // Royal and straight flush
        if (five_colors && count_of_five == 5)
        {
            if (m_Values[12] == 1) // Ace
            {
                m_HandRanks.push_back(std::make_pair("RF", ""));
            }
            else
            {
                m_HandRanks.push_back(std::make_pair("SF", kCardValues[highest_card]));
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
        if (five_colors)
        {
            m_HandRanks.push_back(std::make_pair("F", kCardValues[highest_card]));
            return m_HandRanks;
        }

        // Straight
        if (count_of_five == 5 || // A-2-3-4-5
                (single_cards.size() == 5 && 
                 m_Values[12] && m_Values[0] && m_Values[1] && m_Values[2] && m_Values[3]))
        {
            m_HandRanks.push_back(std::make_pair("S", kCardValues[highest_card]));
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
            m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[0]]));
            return m_HandRanks;
        }

        // Single pair
        if (num2.size() == 1)
        {
            m_HandRanks.push_back(std::make_pair("P", kCardValues[num2[0]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[2]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[1]]));
            m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[0]]));
            return m_HandRanks;
        }

        // Highests
        m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[4]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[3]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[2]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[1]]));
        m_HandRanks.push_back(std::make_pair("H", kCardValues[single_cards[0]]));

        return m_HandRanks;
    }


    const std::string Problem54::kCardColors[4] = { "C", "D", "S", "H" };
    const std::string Problem54::kCardValues[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A" };
    const std::string Problem54::kRank[10] = {"H", "P", "2P", "3K", "S", "F", "FH", "4K", "SF", "RT"};
    
    
    /**
     * Problem: Poker hands
     *
     * In the card game poker, a hand consists of five cards and are ranked, 
     * from lowest to highest, in the following way:
     *
     * High Card: Highest value card.
     * One Pair: Two cards of the same value.
     * Two Pairs: Two different pairs.
     * Three of a Kind: Three cards of the same value.
     * Straight: All cards are consecutive values.
     * Flush: All cards of the same suit.
     * Full House: Three of a kind and a pair.
     * Four of a Kind: Four cards of the same value.
     * Straight Flush: All cards are consecutive values of same suit.
     * Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
     * The cards are valued in the order:
     *  2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
     *
     * If two players have the same ranked hands then the rank made up of the 
     * highest value wins; for example, a pair of eights beats a pair of fives
     * (see example 1 below). But if two ranks tie, for example, both players 
     * have a pair of queens, then highest cards in each hand are compared (see
     * example 4 below); if the highest cards tie then the next highest cards 
     * are compared, and so on.
     *
     * Consider the following five hands dealt to two players:
     *
     *  Hand      Player 1            Player 2	       Winner
     *    1	 	5H 5C 6S 7S KD      2C 3S 8S 8D TD     Player2
     *          Pair of Fives       Pair of Eights
     *    2     5D 8C 9S JS AC      2C 5C 7D 8S QH     Player1
     *          Highest card Ace    Highest card Queen
     *    3	    2D 9C AS AH AC      3D 6D 7D TD QD     Player2
     *          Three Aces          Flush with Diamonds
 	 *    4	    4D 6S 9H QH QC      3D 6D 7H QD QS     Player1
     *          Pair of Queens      Pair of Queens
     *          Highest card Nine   Highest card Seven
     *    5	    2H 2D 4C 4D 4S      3C 3D 3S 9S 9D     Player1
     *          Full House          Full House
     *          With Three Fours    with Three Threes
     *
     * The file, poker.txt, contains one-thousand random hands dealt to two 
     * players. Each line of the file contains ten cards (separated by a single
     * space): the first five are Player 1's cards and the last five are Player
     * 2's cards. You can assume that all hands are valid (no invalid characters 
     * or repeated cards), each player's hand is in no specific order, and in 
     * each hand there is a clear winner.
     *
     * How many hands does Player 1 win?
     */
    void Problem54::Solve()
    {
        std::string strFilename = "../Data/Euler/p054_poker.txt";
        std::vector<std::string> vLines;

        EulerLib::ReadFile(strFilename, vLines);
        size_t numLines = vLines.size();

        uint32_t result = 0;
        std::vector<Player> players(2);

        // For each line in file (both players' hand) determine a winner.
        //while (std::getline(input_file, line))
        for (size_t i = 0; i < numLines; ++i)
        {
            players[0].Initialize();
            players[1].Initialize();

            GetPlayersHand(vLines[i], players);
            
            // Determine the player hand rank
            const auto& hand0 = players[0].GetHand();
            const auto& hand1 = players[1].GetHand();

            // Then we compare rank and resolve when rank are equals
            uint32_t size = std::min(hand0.size(), hand1.size());

            for (uint32_t i = 0; i < size; ++i)
            {
                uint32_t ranking0 = FindRankIndex(hand0[i].first);
                uint32_t ranking1 = FindRankIndex(hand1[i].first);

                if (ranking0 > ranking1)
                {
                    result++;
                    break;
                }
                else if (ranking1 > ranking0)
                {
                    break;
                }
                else
                {
                    // With same rank index, we must use accompanying information
                    // to determine a winner, otherwise we will continue iterating
                    // with next rank of the hand.
                    if (IsValueGreaterThan(hand0[i].second, hand1[i].second))
                    {
                        result++;
                        break;
                    }
                    else if (IsValueGreaterThan(hand1[i].second, hand0[i].second))
                    {
                        break;
                    }
                }
            }
        }

        //input_file.close();

        SetAnswer(result);
    }


    void Problem54::GetPlayersHand(std::string& line,
                                   std::vector<Problem54::Player>& players)
    {
        std::istringstream hands(line);
        std::string card;

        for (uint32_t i = 0; i < 10; ++i)
        {
            std::getline(hands, card, ' ');
            
            players[i / 5].AddCard(card);
        }
    }

    uint32_t Problem54::FindRankIndex(const std::string& rank)
    {
        for (uint32_t i = 10; i > 0; --i)
        {
            if (kRank[i - 1] == rank)
            {
                return i;
            }
        }

        return 0;
    }

    bool Problem54::IsValueGreaterThan(const std::string& lhs, const std::string& rhs)
    {
        uint32_t lhs_value = 0;
        uint32_t rhs_value = 0;

        for (uint32_t i = 13; i > 0; --i)
        {
            if (kCardValues[i - 1] == lhs)
            {
                lhs_value = i;
            }
            if (kCardValues[i - 1] == rhs)
            {
                rhs_value = i;
            }
        }

        return (lhs_value > rhs_value);
    }
}
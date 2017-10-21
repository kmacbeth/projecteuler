#include "Problem0054.h"
#include "Libs/EulerMath.h"
#include "Libs/EulerUtils.h"

namespace Euler {  
    
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
        std::vector<_Problem54::Hand> vHands(2);

        // For each line in file (both players' hand) determine a winner.
        //while (std::getline(input_file, line))
        for (size_t i = 0; i < numLines; ++i)
        {
			vHands[0].Initialize();
			vHands[1].Initialize();

            GetPlayersHand(vLines[i], vHands);
            
            // Determine the player hand rank
            const auto& hand0 = vHands[0].GetRank();
            const auto& hand1 = vHands[1].GetRank();

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

        SetAnswer(result);
    }

	/**
	 * Get players hands from string.
	 *
	 * @param a_rstrLine Line containing the string with the hand.
	 * @param a_rHand    Hands container.
	 */
    void Problem54::GetPlayersHand(std::string& a_rstrLine,
                                   std::vector<_Problem54::Hand>& a_rHands)
    {
        std::istringstream ssHands(a_rstrLine);
        std::string strCard;

        for (uint32_t i = 0; i < 10; ++i)
        {
            std::getline(ssHands, strCard, ' ');
            
			a_rHands[i / 5].AddCard(strCard);
        }
    }

	/**
	 * Find rank index.
	 *
	 * @param a_rstrRank Current hand rank.
	 *
	 * @return Index of the rank from the table.
	 */
    uint32_t Problem54::FindRankIndex(const std::string& a_rstrRank)
    {
        for (uint32_t i = 10; i > 0; --i)
        {
            if (_Problem54::Hand::kRank[i - 1] == a_rstrRank)
            {
                return i;
            }
        }

        return 0;
    }

	/**
	 * Check left value is greater than right value.
	 *
	 * @param a_rLhs Left-hand value.
	 * @param a_rRhs Right-hand value.
	 *
	 * @return Whether left value is greater.
	 */
    bool Problem54::IsValueGreaterThan(const std::string& a_rLhs, const std::string& a_rRhs)
    {
        uint32_t lhsValue = 0;
        uint32_t rhsValue = 0;

        for (uint32_t i = 13; i > 0; --i)
        {
            if (_Problem54::Hand::kCardValues[i - 1] == a_rLhs)
            {
                lhsValue = i;
            }
            if (_Problem54::Hand::kCardValues[i - 1] == a_rRhs)
            {
                rhsValue = i;
            }
        }

        return (lhsValue > rhsValue);
    }
}
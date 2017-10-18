#ifndef __EULER_PROBLEM54_H__
#define __EULER_PROBLEM54_H__

#include "Problem.h"
#include "Libs/Euler.h"

namespace Euler {

    class Problem54 : public Problem {
        
    public:
        Problem54() : Problem("Problem 54") {}

        static const std::string kRank[10];
        static const std::string kCardColors[4];
        static const std::string kCardValues[13];

        void Solve();
        
    private:

        class Player {

        private:
            struct CardValueCompare {
                bool operator() (const std::string& lhs, const std::string& rhs)
                {
                    uint32_t lindex = 0;
                    uint32_t rindex = 0;
            
                    for (uint32_t i = 0; i < 13; ++i)
                    {
                        if (lhs == Problem54::kCardValues[i])
                        {
                            lindex = i;
                        }
                        if (rhs == Problem54::kCardValues[i])
                        {
                            rindex = i;
                        }
                    }

                    return lindex < rindex;
                }
            };

            struct CardColorCompare {
                bool operator() (const std::string& lhs, const std::string& rhs)
                {
                    uint32_t lindex = 0;
                    uint32_t rindex = 0;
            
                    for (uint32_t i = 0; i < 4; ++i)
                    {
                        if (lhs == Problem54::kCardColors[i])
                        {
                            lindex = i;
                        }
                        if (rhs == Problem54::kCardColors[i])
                        {
                            rindex = i;
                        }
                    }

                    return lindex < rindex;
                }
            };

            public:
                
                typedef std::vector<std::pair<std::string, std::string> > THandRank;
                
                Player();

                void Initialize();

                void AddCard(std::string& card);
                const THandRank& GetHand();

            private:
                void BuildValuesCache();
                void BuildColorsCache();

                THandRank m_HandRanks;
                std::vector<std::string> m_Hand;
                std::vector<uint32_t> m_Values;
                std::map<std::string, uint32_t> m_ValuesIndexCache;
                std::vector<uint32_t> m_Colors;
                std::map<std::string, uint32_t> m_ColorsIndexCache;
                
        };

        void GetPlayersHand(std::string& line,
                                   std::vector<Player>& players);
        uint32_t FindRankIndex(const std::string& rank);
        bool IsValueGreaterThan(const std::string& lhs, const std::string& rhs);

    };

}

#endif // __EULER_PROBLEM54_H__
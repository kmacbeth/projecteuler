#ifndef __EULER_PROBLEM54_PLAYER_H__
#define __EULER_PROBLEM54_PLAYER_H__

#include "Libs/Euler.h"

namespace _Problem54 {

	struct CardValueCompare {

		bool operator() (const std::string& a_rLhs, const std::string& a_rRhs);
	};

	struct CardColorCompare {

		bool operator() (const std::string& a_rLhs, const std::string& a_rRhs);
	};

	class Hand {

	public:
		typedef std::vector<std::pair<std::string, std::string> > THandRank;

		static const std::string kRank[10];
		static const std::string kCardColors[4];
		static const std::string kCardValues[13];

		Hand();

		void Initialize();

		void AddCard(std::string& a_rCard);
		const THandRank& GetRank();

	private:
		void BuildValuesCache();
		void BuildColorsCache();

		THandRank m_HandRanks;
		std::vector<std::string> m_vHand;
		std::vector<uint32_t> m_vValues;
		std::vector<uint32_t> m_vColors;
		std::map<std::string, uint32_t> m_mValuesIndexCache;
		std::map<std::string, uint32_t> m_mColorsIndexCache;
	};
}

#endif // __EULER_PROBLEM54_PLAYER_H__

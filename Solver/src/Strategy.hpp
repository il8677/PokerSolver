#include <unordered_map>
#include <array>
#include <string>
#include <vector>

using InformationSet=std::string;
using InfromationPartition=std::vector<std::string>;

template<int ACTION_COUNT>
class Strategy {
	using Actions=std::array<float, ACTION_COUNT>;
public:
	Strategy(const InfromationPartition& p) {
		Actions defaultArr{};
		defaultArr.fill(1.f/ACTION_COUNT);

		for(const InformationSet& set : p) {
			actionsPerISet[set] = defaultArr;
		}
	}

	float getAction(const InformationSet& iSet, size_t index) {
		return actionsPerISet.at(iSet)[index];
	}

	void updateAction(const InformationSet& iSet, Actions a) {
		actionsPerISet[iSet] = a;
	}
private:
	std::unordered_map<InformationSet, Actions> actionsPerISet;
};
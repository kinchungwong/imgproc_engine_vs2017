#pragma once

// This design is based on the old "splittable, straddle"
// which are not suitable for handling rectangles with extreme aspect ratios.
//
// To avoid unbounded recursive call, all operations code are 
// implemented in a different class, therefore the node class
// is merely a data class without methods.
//
class RectTreeNode
{
public:
	// Rectangle must be square-shaped (equal width and height), 
	// and their value must be an integer power of two.
	cv::Rect m_rect;

	// Four children
	std::unique_ptr<RectTreeNode> m_children[2][2];

	// Splittables: these have rectangles that can be sent to 
	// one of the children, but currently they are not split up
	// because this list is currently too small to worth splitting.
	//
	std::vector<size_t> m_splittables; 

	// Straddles: these rectangles straddle between two or more 
	// children rectangles. Therefore, they can never be split up.
	// Even after a node split operation, these rectangles will 
	// continue to stay with the parent (current) node.
	// Also, because they can't be split up, their count do not 
	// influence the decision of when to split, because splitting
	// doesn't help reduce the amount of time scanning this 
	// list (of rectangles that straddle).
	//
	std::vector<size_t> m_straddles;
};

template <typename KT, typename MT, class KH = std::hash<KT>>
class RectTreeT
{
public:
	using KeyType = KT;
	using MappedType = MT;
	using KeyHash = KH;
	using TupleType = std::tuple<KeyType, cv::Rect, MappedType>;
	using KeyLookup = std::unordered_map<KeyType, TupleType, KeyHash>;

public:
	bool Add(const KeyType& key, const cv::Rect& rect, const MappedType& data);

private:
	KeyLookup m_lookupByKey;
	std::unique_ptr<RectTreeNode> m_rootNode;
};

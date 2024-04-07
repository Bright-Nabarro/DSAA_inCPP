#include <random>
#include "avl_tree.h"

template<typename Ty, typename Compare, bool multi>
class B_RemoveTree : public AvlTree<Ty, Compare, multi>
{
	using base = AvlTree<Ty, Compare, multi>;
public:
	bool erase(const Ty& value)
	{
		return erase(value, base::root);
	}
private:
	bool erase(const Ty& value, base::uptr& ptr, bool needUpdate = true)
	{
		static enum { LEFT, RIGHT } LOR { LEFT };
		static typename base::uptrV trash;
		bool ret;
		
		if(ptr == nullptr)
			ret = false;
		else if(base::cmp(value, ptr->element))
			ret = erase(value, ptr->left, needUpdate);
		else if(base::cmp(ptr->element, value))
			ret = erase(value, ptr->right, needUpdate);
		else
		{
		CON_IF(multi)
			// implament later
		CON_ELSE
			if(ptr->left != nullptr && ptr->right != nullptr)
			{
				typename base::uptrV rpv;
				if(LOR == LEFT)
				{
					rpv = base::find_min(ptr->right);
					ptr->element = rpv->element;
					erase(ptr->element, rpv.release(), false);
					if(needUpdate)
						--base::currentSize;
					ret = true;

					LOR = RIGHT;
				}
				else
				{
					rpv = base::find_max(ptr->left);
					ptr->element = rpv->element;
					erase(ptr->element, rpv.release(), false);
					if(needUpdate)
						--base::currentSize;
					ret = true;

					LOR = LEFT;
				}
			}
			else
			{
				ptr = (ptr->left != nullptr) ? std::move(ptr->left) : std::move(ptr->right);
				if (ptr != nullptr)
				{
					if(ptr->left != nullptr)
						ptr->left->parent = ptr;
					else if(ptr->right != nullptr)
						ptr->right->parent = ptr;
				}
				base::balance(ptr, trash);
				if(needUpdate)
					--base::currentSize;
				ret = true;
 			}
		CON_END
		}
		base::balance(ptr, trash);
		return ret;
		}
};


template<typename Ty, typename Compare, bool multi>
class C_RemoveTree : public AvlTree<Ty, Compare, multi>
{
	using base = AvlTree<Ty, Compare, multi>;
	std::mt19937 gen;
	std::bernoulli_distribution dist;
public:
	C_RemoveTree(): base{}
	{
		std::random_device rd;
		gen.seed(rd());
	}
	bool erase(const Ty& value)
	{
		return erase(value, base::root);
	}
private:
	bool erase(const Ty& value, base::uptr& ptr, bool needUpdate = true)
	{
		static bool isLeft {true};
		static typename base::uptrV trash;
		bool ret;
		
		if(ptr == nullptr)
			ret = false;
		else if(base::cmp(value, ptr->element))
			ret = erase(value, ptr->left, needUpdate);
		else if(base::cmp(ptr->element, value))
			ret = erase(value, ptr->right, needUpdate);
		else
		{
		CON_IF(multi)
			// implament later
		CON_ELSE
			if(ptr->left != nullptr && ptr->right != nullptr)
			{
				typename base::uptrV rpv;
				if(isLeft)
				{
					rpv = base::find_min(ptr->right);
					ptr->element = rpv->element;
					erase(ptr->element, rpv.release(), false);
					if(needUpdate)
						--base::currentSize;
					ret = true;

					isLeft = dist(gen);
				}
				else
				{
					rpv = base::find_max(ptr->left);
					ptr->element = rpv->element;
					erase(ptr->element, rpv.release(), false);
					if(needUpdate)
						--base::currentSize;
					ret = true;

					isLeft = dist(gen);
				}
			}
			else
			{
				ptr = (ptr->left != nullptr) ? std::move(ptr->left) : std::move(ptr->right);
				if (ptr != nullptr)
				{
					if(ptr->left != nullptr)
						ptr->left->parent = ptr;
					else if(ptr->right != nullptr)
						ptr->right->parent = ptr;
				}
				base::balance(ptr, trash);
				if(needUpdate)
					--base::currentSize;
				ret = true;
 			}
		CON_END
		}
		base::balance(ptr, trash);
		return ret;
	}
};

class list
{
	class iterator;
	/*
	* normal implament
	*/
private:
	struct node{
		/*
		* normal implament
		*/
		node* next;
		node* pre;
		bool m_deleted;
	};
	int m_size;
	int m_deletedItems;
public:
	iterator erase(iterator itr)
	{
		if (!itr->m_deleted)
			itr++;
		itr->m_deleted = false;
		itr++;
		m_size--;
		m_deletedItems++;
		if(m_deletedItems > m_size/2)
			recycle();
		return itr;
	}
private:	
	void real_erase(iterator itr);
	void recycle()
	{
		auto itr = begin();
		while(itr != end())
		{
			real_erase(itr);
			itr++;
		}
	}
};
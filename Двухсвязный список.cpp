#include <iostream>

template<typename T>
class List
{
public:

	List();
	~List();

	void push_from(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();

	void insert(const T& data, const int& index);
	void remove(const T& data);

	void clear();
	int get_size() const { return m_size; }
	T& operator[](const int& index);

private:

	struct Node
	{
		T m_data;
		Node* m_next{ nullptr };
		Node* m_prev{ nullptr };
		Node(const T& data, Node* prev = nullptr, Node* next = nullptr);
	};

	Node* m_head;
	Node* m_tail;
	int m_size;
};

template<typename T>
void print_list(List<T>& ls);

int main()
{
	List<int> a;
	a.push_back(34);
	a.push_from(9);
	a.push_back(4);
	a.push_back(8);
	a.push_back(12);
	a.insert(68,3);
	std::cout << "Begin :\n";
	print_list(a);
	std::cout << "End :\n";
	a.remove(4);
	print_list(a);
	
	return 0;
}

template<typename T>
List<T>::Node::Node(const T& data, Node* prev, Node* next) :m_data{ data }, m_prev{prev}, m_next{ next }{}

template<typename T>
List<T>::List() : m_size{ 0 }, m_head{ nullptr }, m_tail{nullptr}{}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::push_from(const T& data)
{
	Node* p = new Node(data);
	p->m_next = m_head;
	m_head->m_prev = p;
	m_head = p;
	m_size++;
}

template<typename T>
void List<T>::push_back(const T& data)
{
	if (!m_head)
	{
		Node* p = new Node(data);
		m_head = p;
		m_tail = p;

	}
	else
	{
		Node* p = new Node(data,m_tail);
		m_tail->m_next = p;
		m_tail = p;
	}
	m_size++;
}

template<typename T>
void List<T>::pop_front()
{
	if (!m_head) return;
	if (m_head->m_next) {
		Node* p = m_head->m_next;
		p->m_prev = nullptr;
		delete m_head;
		m_head = p;
	}
	else {
		delete m_head;
		m_head = m_tail = nullptr;
	}
	
	m_size--;
}

template<typename T>
void List<T>::pop_back()
{
	if (!m_tail) return;
	if (m_tail->m_prev)
	{
		Node* p = m_tail->m_prev;
		p->m_next = nullptr;
		delete m_tail;
		m_tail = p;
	}
	else 
	{
		delete m_tail;
		m_tail = m_head =  nullptr;
	}

	m_size--;

}

template<typename T>
void List<T>::insert(const T& data, const int& index)
{
	if (index == 0)
	{
		push_from(data);
		return;
	}
	else if (index == m_size)
	{
		push_back(data); 
		return;
	}
	if (index<=m_size/2)
	{
		Node* p = m_head;
		for (int i{ 0 }; i < index - 1; ++i)
		{
			p = p->m_next;
		}
		Node* new_node = new Node(data,p,p->m_next);
		p->m_next = new_node;
		p = new_node->m_next;
		p->m_prev = new_node;
		m_size++;
		return;
	}
	Node* p = m_tail;
	for (int i{ m_size -1 }; i > index ; --i)
	{
		p = p->m_prev;
	}
	Node* new_node = new Node(data, p->m_prev, p);
	p->m_prev = new_node;
	p = new_node->m_prev;
	p->m_next = new_node;
	m_size++;
}

template<typename T>
void List<T>::remove(const T& data)
{
	Node* p = m_head;
	Node* p_next = p->m_next;
	while (p_next && p_next->m_data != data)
	{
		p_next = p_next->m_next;
		p = p->m_next;
	}
	if (!p_next)
	{
		std::cout << "This element cloes not exist" << std::endl;
		return;
	}
	p->m_next = p_next->m_next;
	p = p_next->m_next;
	p->m_prev = p_next->m_prev;
	delete p_next;
	m_size--;
}

template<typename T>
void List<T>::clear()
{
	while (m_size)
	{
		pop_front();
	}
}

template<typename T>
T& List<T>::operator[](const int& index)
{
	Node* p = m_head;
	int i{ 0 };

	while (p)
	{
		if (i == index)
		{
			return p->m_data;
		}
		p = p->m_next;
		i++;
	}
}

template<typename T>
void print_list(List<T>& ls)
{
	for (int i{ 0 }; i < ls.get_size(); ++i)
	{

		std::cout << "Data " << i + 1 << " :" << ls[i] << std::endl;
	}
}

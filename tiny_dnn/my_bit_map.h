#pragma once
template<std::size_t BITSIZE>
struct bitset
{
public:
	const static std::size_t int_size = BITSIZE / 32 + (BITSIZE & 0x07 ? 1 : 0);
public:
	bitset()
	{
		this->reset();
	}
	bitset(const bitset& old)
	{
		memcpy(this->data, old.data, int_size * sizeof(int32_t));
	}
	size_t size()const
	{
		return BITSIZE;
	}

	bool bit(size_t id)const
	{
		return (data[id / 32] >> (id & 0x07)) & 0x01;
	};
	bool operator[](size_t id)const
	{
		return this->bit(id);
	}

	void set()
	{
		memset(data, 0xFF, int_size*sizeof(int32_t));
	}
	bool set(size_t id)
	{
		int32_t& b = data[id / 32];
		b |= 1 << (id & 0x07);
		return true;
	}
	void reset()
	{
		memset(data, 0, int_size * sizeof(int32_t));
	}
	bool reset(size_t id)
	{
		int32_t& b = data[id / 32];
		b &= ~(1 << (id & 0x07));
		return false;
	}
	
	 bitset operator &(const bitset& a) {
		return a;
	}
	friend std::ostream & operator<<(std::ostream &os, const bitset &c);
public:
	int32_t data[int_size];
};

template<std::size_t BITSIZE>
std::ostream & operator << (std::ostream &os,bitset<BITSIZE> &c){
	os <<"bit size:"<< BITSIZE << std::endl;
	for (int bit = 0; bit < BITSIZE; bit++) {
		os << (int)c.bit(bit) << ' ';
	}
	return os;
}
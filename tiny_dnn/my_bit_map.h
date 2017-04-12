#pragma once
template<std::size_t BITSIZE>
struct bitset
{
public:
	const static std::size_t int_size = (BITSIZE+31) / 32;
public:
	bitset()
	{
		this->reset();
	}

	bitset(const std::vector<uint32_t>& temp)
	{
		for (int i = 0; i < int_size; i++) {
			this->data[i] = temp[i];
		}
	}
	bitset(const bitset& old)
	{
		memcpy(this->data, old.data, int_size * sizeof(uint32_t));
	}
	size_t size()const
	{
		return BITSIZE;
	}

	bool bit(size_t id)const
	{
		return (data[id / 32] >> (id & 0x1f)) & 0x01;
	};
	bool operator[](size_t id)const
	{
		return this->bit(id);
	}

	void set()
	{
		memset(data, 0xFFFFFFFF, int_size*sizeof(uint32_t));
	}
	bool set(size_t id)
	{
		uint32_t& b = data[id / 32];
		b |= 1 << (id & 0x1f);
		return true;
	}
	void reset()
	{
		memset(data, 0, int_size * sizeof(uint32_t));
	}
	bool reset(size_t id)
	{
		uint32_t& b = data[id / 32];
		b &= ~(1 << (id & 0x1f));
		return false;
	}
	
	 bitset operator &(const bitset& a) {
		bitset<BITSIZE> result;
		for (int i = 0; i < int_size; i++) {
			result.data[i] = this->data[i] & a.data[i];
		}
		return result;
	}
	bitset operator ^(const bitset& a) {
		 bitset result;
		 for (int i = 0; i < int_size; i++) {
			 result.data[i] = this->data[i] ^ a.data[i];
		 }
		 return result;
	}
	friend std::ostream & operator<<(std::ostream &os, const bitset &c) {
		os << "bit size:" << BITSIZE << std::endl;
		for (int bit = 0; bit < BITSIZE; bit++) {
			os << (int)c.bit(bit) << ' ';
		}
		return os;
	}
public:
	uint32_t data[int_size];
};
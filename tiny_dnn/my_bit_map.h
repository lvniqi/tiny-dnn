#pragma once
template<std::size_t BITSIZE>
struct bitset
{
public:
	const static std::size_t byte_size = BITSIZE / 32 + (BITSIZE & 0x07 ? 1 : 0);
public:
	bitset()
	{
		this->reset();
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
		memset(data, 0xFF, byte_size);
	}
	bool set(size_t id)
	{
		byte_t& b = data[id / 32];
		b |= 1 << (id & 0x07);
		return true;
	}
	void reset()
	{
		memset(data, 0, byte_size);
	}
	bool reset(size_t id)
	{
		byte_t& b = data[id / 32];
		b &= ~(1 << (id & 0x07));
		return false;
	}
public:
	int data[byte_size];
};

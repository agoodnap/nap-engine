#pragma once

#include <memory>
#include <unordered_map>

template<class T> 
class ResourceDataCache {
private:
	std::unordered_map<std::string, std::shared_ptr<T>> m_cache;

public:
	ResourceDataCache() : m_cache() {}
	~ResourceDataCache() { m_cache.clear(); }
	void add(const std::string& id, const std::shared_ptr<T> data)
	{
		if (m_cache.find(id) != m_cache.end())
			return;

		m_cache.insert({ id, data });
	}

	std::shared_ptr<T> get(const std::string& id)
	{
		return m_cache[id];
	}

	void erase(const std::string& id)
	{
		if (m_cache.find(id) != m_cache.end())
			m_cache.erase(id);
	}

	void clear() 
	{
		m_cache.clear();
	}
};
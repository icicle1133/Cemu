#include "Whitelist.h"

namespace nsyshid
{
	Whitelist& Whitelist::GetInstance()
	{
		static Whitelist whitelist;
		return whitelist;
	}

	Whitelist::Whitelist()
	{
		// add known built-in devices
		m_builtinDevices.emplace_back(0x0e6f, 0x0241); // lego dimensions portal
		m_builtinDevices.emplace_back(0x1430, 0x0150); // skylanders portal
		m_builtinDevices.emplace_back(0x1430, 0x1F17); // skylanders 360 portal
		m_builtinDevices.emplace_back(0x0e6f, 0x0129); // disney infinity base
		m_builtinDevices.emplace_back(0x0e6f, 0x200A); // kamen rider ride gate
	}

	bool Whitelist::IsDeviceWhitelisted(uint16 vendorId, uint16 productId)
	{
		auto key = std::tuple<uint16, uint16>(vendorId, productId);
		if (std::find(m_builtinDevices.begin(), m_builtinDevices.end(), key) != m_builtinDevices.end())
			return true;
		if (std::find(m_userDevices.begin(), m_userDevices.end(), key) != m_userDevices.end())
			return true;
		return false;
	}

	void Whitelist::AddDevice(uint16 vendorId, uint16 productId)
	{
		if (!IsDeviceWhitelisted(vendorId, productId))
			m_userDevices.emplace_back(vendorId, productId);
	}

	void Whitelist::RemoveDevice(uint16 vendorId, uint16 productId)
	{
		m_userDevices.remove(std::tuple<uint16, uint16>(vendorId, productId));
	}

	std::vector<std::pair<uint16, uint16>> Whitelist::GetUserDevices() const
	{
		std::vector<std::pair<uint16, uint16>> result;
		for (const auto& [vid, pid] : m_userDevices)
			result.emplace_back(vid, pid);
		return result;
	}

	void Whitelist::SetUserDevices(const std::vector<std::pair<uint16, uint16>>& devices)
	{
		m_userDevices.clear();
		for (const auto& [vid, pid] : devices)
		{
			auto key = std::tuple<uint16, uint16>(vid, pid);
			if (std::find(m_builtinDevices.begin(), m_builtinDevices.end(), key) == m_builtinDevices.end())
				m_userDevices.emplace_back(vid, pid);
		}
	}

	std::list<std::tuple<uint16, uint16>> Whitelist::GetDevices()
	{
		auto combined = m_builtinDevices;
		combined.insert(combined.end(), m_userDevices.begin(), m_userDevices.end());
		return combined;
	}

	void Whitelist::RemoveAllDevices()
	{
		m_userDevices.clear();
	}
} // namespace nsyshid

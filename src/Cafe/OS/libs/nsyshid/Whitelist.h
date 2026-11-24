#ifndef CEMU_NSYSHID_WHITELIST_H
#define CEMU_NSYSHID_WHITELIST_H

#include <utility>
#include <vector>

namespace nsyshid
{
	class Whitelist {
	  public:
		static Whitelist& GetInstance();

		Whitelist(const Whitelist&) = delete;

		Whitelist& operator=(const Whitelist&) = delete;

		bool IsDeviceWhitelisted(uint16 vendorId, uint16 productId);

		// User-configured devices (not built-ins)
		void AddDevice(uint16 vendorId, uint16 productId);
		void RemoveDevice(uint16 vendorId, uint16 productId);
		std::vector<std::pair<uint16, uint16>> GetUserDevices() const;
		void SetUserDevices(const std::vector<std::pair<uint16, uint16>>& devices);

		// Legacy API operating on user devices
		std::list<std::tuple<uint16, uint16>> GetDevices();
		void RemoveAllDevices();

	  private:
		Whitelist();

		// vendorId, productId
		std::list<std::tuple<uint16, uint16>> m_builtinDevices;
		std::list<std::tuple<uint16, uint16>> m_userDevices;
	};
} // namespace nsyshid

#endif // CEMU_NSYSHID_WHITELIST_H

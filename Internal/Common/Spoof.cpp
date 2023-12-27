#include "Spoof.h"

uint64_t GetAddressFromSignature(const std::vector<int> signature, uint64_t startaddress = 0, uint64_t endaddress = 0)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	if (startaddress == 0) {
		startaddress = reinterpret_cast<uint64_t>(si.lpMinimumApplicationAddress);
	}

	if (endaddress == 0) {
		endaddress = reinterpret_cast<uint64_t>(si.lpMaximumApplicationAddress);
	}

	MEMORY_BASIC_INFORMATION mbi { 0 };
	uint64_t protectflags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

	for (uint64_t i = startaddress; i < endaddress - signature.size(); i++) {
		if (VirtualQuery(reinterpret_cast<LPCVOID>(i), &mbi, sizeof(mbi))) {
			if (mbi.Protect & protectflags || !(mbi.State & MEM_COMMIT)) {
				i += mbi.RegionSize;
				continue; // if bad adress then dont read from it
			}
			for (uint64_t k = reinterpret_cast<uint64_t>(mbi.BaseAddress); k < reinterpret_cast<uint64_t>(mbi.BaseAddress) + mbi.RegionSize - signature.size(); k++) {
				for (uint64_t j = 0; j < signature.size(); j++) {
					if (signature.at(j) != -1 && signature.at(j) != *reinterpret_cast<BYTE*>(k + j))
						break;
					if (j + 1 == signature.size())
						return k;
				}
			}
			i = reinterpret_cast<uint64_t>(mbi.BaseAddress) + mbi.RegionSize;
		}
	}
	return NULL;
}
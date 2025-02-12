#pragma once

namespace RE
{
	struct TESFormRefCount
	{
	public:
		SF_RTTI(TESFormRefCount);

		// members
		volatile mutable std::uint64_t refCount;  // 0x0
	};
	static_assert(sizeof(TESFormRefCount) == 0x08);
}

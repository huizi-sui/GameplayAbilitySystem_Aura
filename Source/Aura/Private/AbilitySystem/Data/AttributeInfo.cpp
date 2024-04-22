// Liuxijun


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoFormTag(const FGameplayTag& AttributeTag, bool blogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		// if (Info.AttributeTag == AttributeTag)
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (blogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
